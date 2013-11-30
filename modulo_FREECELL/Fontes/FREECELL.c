/***************************************************************************
*	$MCD M�dulo de implementa��o: Freecell
*
*	Arquivo gerado:              FREECELL.c
*
*	Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*	Projeto: [INF 1301] Implementa��o do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Hist�rico de evolu��o:
*	Vers�o  Autor	Data			Observa��es
*	1       nk		15/nov/2013		In�cio desenvolvimento
*	2		nk		25/nov/2013		Fun��o iniciar novo jogo
*	3		nk		28/nov/2013		Corre��es e desenvolvimento
*	4		nk		29/nov/2013		Desenvolvimento
*	5		nk		30/nov/2013		Desenvolvimento
*    
***************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "embaralha.h"
#include "extra.h"
#include "lista.h"
#include "naipe.h"
#include "seq_vis.h"

#define ON				1
#define OFF				0

#define OK				0
#define FAIL			-1

#define INICIAR			1	 
#define MOVER			1
#define DESISTIR		2
#define SAIR			2

#define TOTAL_CARTAS	52
#define TAM_CARTA		4
#define TAM_SET			180

typedef char *Carta;
typedef LIS_tppLista Mesa;

/*---------- Vari�veis globais ----------*/
char baralho[TOTAL_CARTAS][TAM_CARTA];
Mesa mesa[13];

/*---------- Prot�tipos de fun��es ----------*/
int SelecionarMenu(int status);
int MoverCarta(Carta carta, char tipoOrigem, int numOrigem, char tipoDestino, int numDestino);
int ContarFreecells();
int ContarCartas(void * coluna);
int VerificarNaipes();
void ExibirMesa();
void IniciarNovoJogo();
void DistribuirCartas(char baralho[][TAM_CARTA]);
void VerificarMoverCarta(Carta carta, 
						 char tipoOrigem, int numOrigem, char tipoDestino, int numDestino, 
						 int *validaRemocao, int *validaInsercao);

int main(){
	/*---------- Declara��o de vari�veis ----------*/
	int opcaoDeJogo,		// op��o para iniciar ou sair
		opcaoDeMovimento,	// op��o para mover ou desistir
		status = OFF,		// determina se h� um jogo em andamento ou n�o
		condRet,			// recebe condi��es de retorno das fun��es
		numOrigem,			// recebe o n�mero da coluna para movimento
		numDestino,			// recebe o n�mero da coluna para movimento
		numCelulasLivres,
		i;
	
	char carta[TAM_CARTA],	// recebe a carta que o jogador deseja mover
		 tipoOrigem,		// recebe o tipo da coluna para movimento
		 tipoDestino;		// recebe o tipo da coluna para movimento
	/*--------------------------------------------------*/

	opcaoDeJogo = SelecionarMenu(status);

	// Se jogador decidiu iniciar novo jogo...
	if(opcaoDeJogo == INICIAR){
		// Setar status para ON
		status = ON;

		// Cria uma nova mesa
		IniciarNovoJogo();
		
		// Distribui as cartas pelas sequ�ncias vis�veis
		DistribuirCartas(baralho);

		// Enquanto o jogador n�o desistir ou vencer o jogo
		ExibirMesa();
		opcaoDeMovimento = SelecionarMenu(status);
		
		while(opcaoDeMovimento == MOVER || VerificarNaipes() != 0){
			printf("\nIndique a carta que deseja transferir, a coluna fonte e a coluna destino.\n");
			printf("HINT: E - EXTRA; N  - NAIPE; S - SEQ\n\n");
			scanf("%s %c%d %c%d", carta, &tipoOrigem, &numOrigem, &tipoDestino, &numDestino);

			condRet = MoverCarta(carta, tipoOrigem, numOrigem, tipoDestino, numDestino);
			
			/*--/--/--/ �REA DE TESTE /--/--/--*/
			/*printf("%s - ", carta);
			printf("%c", tipoOrigem);
			printf("%d - ", numOrigem);
			printf("%c", tipoDestino);
			printf("%d\n\n", numDestino);*/
			/*--/--/--/--/--/--/--/--/--/--/--*/
			
			if(condRet != 0){
				// Ap�s mensagem de erro, requer novo movimento
				printf("Nao pude fazer nada...\n");
			}

			ExibirMesa();
			printf("Faltam %d cartas.\n", VerificarNaipes());
			opcaoDeMovimento = SelecionarMenu(status);
		}
		for(i = 0; i <= 12; i++){
			LIS_DestruirLista(mesa[i]);
		}
		printf("\nQue pena...\nVolte em breve para um novo jogo!\n\n");
		exit(EXIT_SUCCESS);
	}	

	// Se jogador decidiu sair...
	else{
		printf("\nJa indo?\nVolte em breve para um novo jogo!\n\n");
		exit(EXIT_SUCCESS);
	}

	printf("VOCE VENCEU!\n\n");
	for(i = 0; i <= 12; i++){
		LIS_DestruirLista(mesa[i]);
	}
	return 0;
}

/***************************************************************************
*	$FC Fun��o: &Selecionar Menu
*
*	$ED Descri��o da fun��o
*	Exibe menu ao jogador e coleta sua op��o.
***************************************************************************/
int SelecionarMenu(int status){
	int opcao;

	//Primeiro, o menu verifica se h� ou n�o um jogo em andamento
	if(status == OFF){
		printf("");
		printf("O que deseja fazer?\n\t[1] Iniciar novo jogo\n\t[2] Sair\n\n");
		scanf("%d", &opcao);
	}
	
	else{
		printf("O que deseja fazer?\n\t[1] Mover uma carta\n\t[2] Desistir\n\n");
		scanf("%d", &opcao);
	}

	while(opcao != 1 && opcao != 2){
		printf("\nOps...Parece que voce digitou errado.\n\n");
		opcao = SelecionarMenu(status);
	}

	return opcao;
}

/***************************************************************************
*	$FC Fun��o: &Iniciar Novo Jogo
*
*	$ED Descri��o da fun��o
*	Cria as colunas do jogo e as insere na mesa.
***************************************************************************/
void IniciarNovoJogo(){
	int i;
	printf("Nova mesa sendo criada...\n");

	// Criar uma coluna tipo extra
	mesa[0] = EXT_CriarColunaExtra();
	
	// Criar quatro colunas tipo naipe
	for(i = 1; i <= 4; i++){
		mesa[i] = NPE_CriarColunaNaipe();
	}
	
	// Criar oito colunas tipo sequ�ncia vis�vel
	for(i = 5; i <= 12; i++){
		mesa[i] = SV_CriarColunaSeqVis();
	}
}

/***************************************************************************
*	$FC Fun��o: &Distribuir Cartas
*
*	$ED Descri��o da fun��o
*	Embaralha as cartas e distribui pelas sequ�ncias vis�veis.
***************************************************************************/
void DistribuirCartas(char baralho[][TAM_CARTA]){
	int i, j, k = 0, condRet;
	char copiaSet[TAM_SET];
	Carta carta;
	FILE *set = fopen("BarRef.txt", "r");

	printf("Distribuindo as cartas...\n");
	
	// Recebimento do baralho
	if(set == NULL){ 
		//Procura em outra pasta
		printf("Nao estou achando o set...\n");
	    set = fopen ("..\\Fontes\\BarRef.txt" , "r");
        if (set == NULL)
			printf("Nao achei o set!\n");
    }

	// Copia o set do arquivo TXT para vetor local como string
	if(fgets(copiaSet, TAM_SET, set) != NULL){
		i = 0;
		carta = strtok(copiaSet, ",");
		while(carta != NULL){
 			strcpy(baralho[i], carta);
			carta = strtok (NULL, ",");
			i++;
		}
		fclose(set);
    }

	/*--/--/--/ �REA DE TESTE /--/--/--*/
	printf("ORIGINAL\n");
	for(i = 0; i < 52; i++){
		printf("%s\t", baralho[i]);
	}
	printf("\n\n");
	/*--/--/--/--/--/--/--/--/--/--/--*/

	// Embaralhamento das cartas
	condRet = EMB_Embaralha(baralho);
	if(condRet != EMB_CondRetOK){
		printf("Nao consegui embaralhar!\n");

		/*--/--/--/ �REA DE TESTE /--/--/--*/
		/*if(condRet == EMB_CondRetBaralhoInvalido)
			printf("ERRO: Baralho invalido.\n");
		if(condRet == EMB_CondRetErroNoEmbaralhamento)
			printf("ERRO: Erro no embaralhamento.\n");
		if(condRet == EMB_CondRetErroNaReferencia)
			printf("ERRO: Erro na referencia.\n");*/
		/*--/--/--/--/--/--/--/--/--/--/--*/
	}

	/*--/--/--/ �REA DE TESTE /--/--/--*/
	printf("EMBARALHADO\n");
	for(i = 0; i < 52; i++){
		printf("%s\t", baralho[i]);
	}
	printf("\n\n");
	/*--/--/--/--/--/--/--/--/--/--/--*/

	// Distribui as cartas embaralhadas pelas colunas de sequ�ncias vis�veis
	for(i = 5; i <= 12; i++){
		// Colunas 1 a 4 s�o populadas com 7 cartas
		if(i <= 8){
			for(j = 0; j < 7; j++){				
				condRet = SV_PopularSeqVis(mesa[i], baralho[k]);
				k++;
			}
		}
		// Colunas 5 a 8 s�o populadas com 6 cartas
		else{
			for(j = 0; j < 6; j++){				
				condRet = SV_PopularSeqVis(mesa[i], baralho[k]);
				k++;
			}
		}	
	}
}

/***************************************************************************
*	$FC Fun��o: &Mover Carta
*	
*	$ED Descri��o da fun��o
*   Movimento de uma carta (ou um bloco de cartas) de uma coluna para outra.
***************************************************************************/
int MoverCarta(Carta carta, char tipoOrigem, int numOrigem, char tipoDestino, int numDestino){
	int validaRemocao, 
		validaInsercao, 
		numCelulasLivres = 0,
		numCartasMovidas = 0,
		condRet = 0;
	Carta cartaAux;
	LIS_tppLista listaAux = LIS_CriarLista(NULL);

	// Checagem das entradas
	if(tipoOrigem != 'E' && tipoOrigem != 'N' && tipoOrigem != 'S'){
		printf("\nOps...Parece que voce digitou origem errado.\n\n");
		return FAIL;
	}

	if(tipoDestino != 'E' && tipoDestino != 'N' && tipoDestino != 'S'){
		printf("\nOps...Parece que voce digitou destino errado.\n\n");
		return FAIL;
	}

	VerificarMoverCarta(carta, tipoOrigem, numOrigem, tipoDestino, numDestino, &validaRemocao, &validaInsercao);
	// Se o movimento n�o for v�lido, n�o efetua nada
	if(validaRemocao == FAIL || validaInsercao == FAIL){
		return FAIL;
	}

	// Caso contr�rio...
	// Captar n�mero de freecells
	numCelulasLivres = ContarFreecells();

	// Efetuar remo��o
	if(tipoOrigem == 'E'){
		condRet = EXT_RemoverCartaDeExtra(mesa[0], carta);
		// Se der erro, abortar miss�o...
		if(condRet != EXT_CondRetOK)
			return FAIL;			
	}
	else if(tipoOrigem == 'S'){
		// Fazer movimento em loop (at� que n�o tenha mais cartas debaixo daquela)
		while(condRet != LIS_CondRetFimLista){
			condRet = SV_RemoverCartaDeSeqVis(mesa[numOrigem + 4], carta);
			// Se der erro, abortar miss�o...
			if(condRet != EXT_CondRetOK)
				return FAIL;

			LIS_InserirElementoApos(listaAux, carta);
			LIS_AvancarElementoCorrente(mesa[numOrigem + 4], 1);
		}
	}

	// Controle do n�mero de cartas que podem ser movidas
	numCartasMovidas = ContarCartas(listaAux);
	if(numCartasMovidas > numCelulasLivres){
		printf("\nOps...Voce so pode mover %d cartas!\n\n", numCelulasLivres);
		return FAIL;
	}

	// Efetuar inser��o
	else{
		if(tipoDestino == 'E'){
			condRet = EXT_InserirCartaEmExtra(mesa[0], carta);
			//Se der erro, abortar miss�o...
			if(condRet != EXT_CondRetOK)
				return FAIL;
		}
		else if(tipoDestino == 'N'){
			condRet = NPE_InserirCartaEmNaipe(mesa[numDestino], carta);
			//Se der erro, abortar miss�o...
			if(condRet != NPE_CondRetOK)
				return FAIL;
		}
		else{
			// Fazer movimento em loop (at� que n�o tenha mais cartas debaixo daquela)
			IrInicioLista(listaAux);
			while(condRet != LIS_CondRetFimLista){
				cartaAux = LIS_ObterValor(listaAux);
				condRet = SV_InserirCartaEmSeqVis(mesa[numDestino + 4], cartaAux);
				// Se der erro, abortar miss�o...
				if(condRet != EXT_CondRetOK)
					return FAIL;
			
			LIS_AvancarElementoCorrente(mesa[numOrigem + 4], 1);
			}
		}
	}
		
	LIS_DestruirLista(listaAux);	
	return OK;
}

/***************************************************************************
*	$FC Fun��o: &Verifica Mover Carta
*	
*	$ED Descri��o da fun��o
*   Valida ou n�o um movimento de carta dado pelo jogador.
***************************************************************************/
void VerificarMoverCarta(Carta carta, char tipoOrigem, int numOrigem, 
						char tipoDestino, int numDestino,
						int *validaRemocao, int *validaInsercao){
	int condRet;
	
	// Verificar possibilidade de remo��o
	
	if(tipoOrigem == 'E'){
		condRet = EXT_VerificarRemoverCarta(mesa[0], carta);
		if(condRet == EXT_CondRetCartaNaoExiste){
			printf("\nOps... A carta que voce escolheu nao existe aqui!\n\n");
			*validaRemocao = FAIL;
		}
		else if(condRet == EXT_CondRetNaoPodeRemover){
			printf("\nNao e possivel remover esta carta desta coluna.\n\n");
			*validaRemocao = FAIL;
		}
		else{
			*validaRemocao = OK;
		}
	}

	else if(tipoOrigem == 'N'){
		printf("\nNao e possivel remover cartas de naipe.\n\n");
		*validaRemocao = FAIL;
	}
	
	else{
		if(numOrigem < 1 || numOrigem > 8){
			printf("\nOps... O numero desta coluna nao existe!\n\n");
			*validaRemocao = FAIL;
		}
		else{
			condRet = SV_VerificarRemoverCarta(mesa[numOrigem + 4], carta);
			if(condRet == SV_CondRetCartaNaoExiste){
				printf("\nOps... A carta que voce escolheu nao existe aqui!\n\n");
				*validaRemocao = FAIL;
			}
			else if(condRet == SV_CondRetNaoPodeRemover){
				printf("\nNao e possivel remover esta carta desta coluna.\n\n");
				*validaRemocao = FAIL;
			}
			else{
				*validaRemocao = OK;
			}
		}
	}

	// Verificar possibilidade de inser��o
	
	if(tipoDestino == 'E'){
		condRet = EXT_VerificarInserirCarta(mesa[0], carta);
		if(condRet == EXT_CondRetCartaNaoExiste){
			printf("\nOps... A carta que voce escolheu nao existe aqui!\n\n");
			*validaInsercao = FAIL;
		}
		else if(condRet == EXT_CondRetNaoPodeInserir){
			printf("\nNao e possivel inserir esta carta nesta coluna.\n\n");
			*validaInsercao = FAIL;
		}
		else{
			*validaInsercao = OK;
		}	
	}

	else if(tipoDestino == 'N'){
		if(numDestino < 1 || numDestino > 4){
			printf("\nOps... O numero desta coluna nao existe!\n\n");
			*validaInsercao = FAIL;
		}
		else{
			condRet = NPE_VerificarInserirCarta(mesa[numDestino], carta);
			if(condRet == NPE_CondRetCartaNaoExiste){
				printf("\nOps... A carta que voce escolheu nao existe aqui!\n\n");
				*validaInsercao = FAIL;
			}
			else if(condRet == NPE_CondRetNaoPodeInserir){
				printf("\nNao e possivel inserir esta carta nesta coluna.\n\n");
				*validaInsercao = FAIL;
			}
			else{
				*validaInsercao = OK;
			}	
		}
	}

	else{
		if(numDestino < 1 || numDestino > 8){
			printf("\nOps... O numero desta coluna nao existe!\n\n");
			*validaInsercao = FAIL;
		}
		else{
			condRet = SV_VerificarInserirCarta(mesa[numDestino + 4], carta);
			if(condRet == SV_CondRetCartaNaoExiste){
				printf("\nOps... A carta que voce escolheu nao existe aqui!\n\n");
				*validaInsercao = FAIL;
			}
			else if(condRet == SV_CondRetNaoPodeRemover){
				printf("\nNao e possivel inserir esta carta desta coluna.\n\n");
				*validaInsercao = FAIL;
			}
			else{
				*validaInsercao = OK;
			}
		}
	}
}

/***************************************************************************
*	$FC Fun��o: &Contar Freecells
*	
*	$ED Descri��o da fun��o
*   Conta o n�mero de c�lulas livres para controle do movimento.
***************************************************************************/
int ContarFreecells(){
	int numFreecell = 0, i, condRet = 0;

	// Verificar n�mero de espa�os vazios em extra
	IrInicioLista(mesa[0]);
	while(condRet != LIS_CondRetFimLista){
		condRet = LIS_AvancarElementoCorrente(mesa[0], 1);
		numFreecell++;
	}

	// Verificar n�mero de espa�os vazios em sequ�ncia vis�vel
	for(i = 5; i <= 12; i++){
		IrInicioLista(mesa[i]);
		while(condRet != LIS_CondRetFimLista){
			condRet = LIS_AvancarElementoCorrente(mesa[i], 1);
			numFreecell++;
		}
	}
	return numFreecell;
}

/***************************************************************************
*	$FC Fun��o: &Contar Cartas
*	
*	$ED Descri��o da fun��o
*   Conta o n�mero de cartas em uma coluna.
***************************************************************************/
int ContarCartas(void * coluna){
	int numCartas = 0, condRet = 0;

	IrInicioLista(coluna);
	while(condRet != LIS_CondRetFimLista){
		condRet = LIS_AvancarElementoCorrente(coluna, 1);
		numCartas++;
	}

	return numCartas;
}

/***************************************************************************
*	$FC Fun��o: &Exibir Mesa
*	
*	$ED Descri��o da fun��o
*   Exibe todas as cartas da mesa em suas colunas.
***************************************************************************/
void ExibirMesa(){
	int n, condRet;

	//system("cls");

	// Exibir as cartas da coluna extra
	printf("EXTRA:\t");
	condRet = EXT_ExibirCartas(mesa[0]);
	printf("\n\n");

	// Exibir as cartas (do topo) das 4 colunas de naipe
	for(n = 1; n <= 4; n++){
		printf("NAIPE #%d: ", n);
		condRet = NPE_ExibirCarta(mesa[n]);
		printf("\n");
	}

	printf("\n");

	// Exibir (todas) as cartas das 8 colunas de naipe
	for(n = 5; n <= 12; n++){
		printf("SEQ #%d: ", n - 4);
		condRet = SV_ExibirCartas(mesa[n]);
		printf("\n");
	}

	printf("\n");
}

/***************************************************************************
*	$FC Fun��o: &Verificar Naipes
*	
*	$ED Descri��o da fun��o
*   Verifica se o jogador j� preencheu todas as colunas de naipes.
***************************************************************************/
int VerificarNaipes(){
	int naipe1, naipe2, naipe3, naipe4, faltam;

	naipe1 = ContarCartas(mesa[1]);
	naipe2 = ContarCartas(mesa[2]);
	naipe3 = ContarCartas(mesa[3]);
	naipe4 = ContarCartas(mesa[4]);

	faltam = 52 - (naipe1 + naipe2 + naipe3 + naipe4);

	return faltam;
}
