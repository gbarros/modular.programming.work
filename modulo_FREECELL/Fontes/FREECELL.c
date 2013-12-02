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
*	6		nk		01/nov/2013		Desenvolvimento
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

/*----------- Vari�veis globais ----------*/
char baralho[TOTAL_CARTAS][TAM_CARTA];
Mesa mesa;

/*---------- Prot�tipos de fun��es ----------*/
int SelecionarMenu(int status);
int IniciarNovoJogo();
int DistribuirCartas();
int VerificarNaipes();
int MoverCarta(Carta carta, char tipoOrigem, int numOrigem, char tipoDestino, int numDestino);
void VerificarMoverCarta(Carta carta, char tipoOrigem, int numOrigem, char tipoDestino, int numDestino, int *validaRemocao, int *validaInsercao);
void ExibirMesa();

int ObterValor(Carta carta);
char ObterNaipe(Carta carta);

int main(){
	//---------- Declara��o de vari�veis ----------
	int opcaoDeJogo, // op��o para iniciar ou sair
		opcaoDeMovimento, // op��o para mover ou desistir
		status = OFF, // determina se h� um jogo em andamento ou n�o
		numOrigem,
		numDestino,
		numFaltam,
		condRet = 0; // recebe as condi��es de retorno das fun��es
	
	char carta[TAM_CARTA], // recebe a carta que o jogador deseja mover
		 tipoOrigem,
		 tipoDestino;
	//--------------------------------------------------

	mesa = LIS_CriarLista(NULL);
	opcaoDeJogo = SelecionarMenu(status);

	// Se jogador decidiu iniciar novo jogo...
	if(opcaoDeJogo == INICIAR){
		// Setar status para ON
		status = ON;

		// Cria uma nova mesa
		condRet = IniciarNovoJogo();
		if(condRet != OK){
			printf("Ops... Algo deu errado ao criar a mesa!\n");
			return -1;
		}
		/*--/--/--/ �REA DE TESTE /--/--/--*/
		/*if(condRet == 0){
			printf("SUCESSO!\n");
		}
		else{
			printf("Ops... Algo deu errado ao criar a mesa!\n");
			return -1;
		}

		
		ExibirMesa();*/
		/*--/--/--/--/--/--/--/--/--/--/--*/

		// Distribui as cartas pelas sequ�ncias vis�veis
		condRet = DistribuirCartas(baralho);
		if(condRet != OK){
			printf("Ops... Algo deu errado ao distribuir as cartas!\n");
			return -1;
		}
		/*--/--/--/ �REA DE TESTE /--/--/--*/
		/*if(condRet == 0){
			printf("SUCESSO!\n");
		}
		else{
			printf("Ops... Algo deu errado ao distribuir as cartas!\n");
			return -1;
		}*/
		/*--/--/--/--/--/--/--/--/--/--/--*/

		// Enquanto o jogador n�o desistir ou vencer o jogo
		ExibirMesa();
		opcaoDeMovimento = SelecionarMenu(status);

		while(opcaoDeMovimento != MOVER && opcaoDeMovimento != DESISTIR)
			opcaoDeMovimento = SelecionarMenu(status);
		
		while(opcaoDeMovimento == MOVER || VerificarNaipes() == 0){
			printf("\nIndique a carta que deseja transferir, a coluna fonte e a coluna destino.\n");
			printf("HINT: E - EXTRA ou N - NAIPE ou S - SEQ + numero\n");
			scanf("%s %c%d %c%d", carta, &tipoOrigem, &numOrigem, &tipoDestino, &numDestino);

			/*--/--/--/ �REA DE TESTE /--/--/--*/
			/*printf("%s - ", carta);
			printf("%c", tipoOrigem);
			printf("%d - ", numOrigem);
			printf("%c", tipoDestino);
			printf("%d\n\n", numDestino);*/
			/*--/--/--/--/--/--/--/--/--/--/--*/
			
			condRet = MoverCarta(carta, tipoOrigem, numOrigem, tipoDestino, numDestino);
			
			if(condRet != OK){
				printf("Movimento invalido.\n");
			}

			printf("Faltam %d cartas.\n\n", VerificarNaipes());

			ExibirMesa();
			opcaoDeMovimento = SelecionarMenu(status);
		}

		// Libera a mesa e termina o jogo
		LIS_DestruirLista(mesa);
	}	

	// Se jogador decidiu sair...
	else{
		printf("\nJ%c indo?\nVolte em breve para um novo jogo!\n\n", 160);
		exit(EXIT_SUCCESS);
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
		printf("O que deseja fazer?\n\t[1] Iniciar novo jogo\n\t[2] Sair\n\n");
		scanf("%d", &opcao);
	}
	
	else{
		printf("\nO que deseja fazer?\n\t[1] Mover uma carta\n\t[2] Desistir\n\n");
		scanf("%d", &opcao);
	}

	while(opcao != 1 && opcao != 2){
		printf("\nOps...Parece que voc%c digitou errado.\n\n", 136);
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
int IniciarNovoJogo(){
	int condRet = 0;
	EXT_Coluna extra;
	NPE_Coluna naipe1, naipe2, naipe3, naipe4;
	SV_Coluna seq1, seq2, seq3, seq4, seq5, seq6, seq7, seq8;	 

	// printf("Nova mesa sendo criada...\n");

	// Criar uma coluna tipo extra
	extra = EXT_CriarColunaExtra();
	
	// Criar quatro colunas tipo naipe
	naipe1 = NPE_CriarColunaNaipe();
	naipe2 = NPE_CriarColunaNaipe();
	naipe3 = NPE_CriarColunaNaipe();
	naipe4 = NPE_CriarColunaNaipe();
	
	// Criar oito colunas tipo sequ�ncia vis�vel
	seq1 = SV_CriarColunaSeqVis();
	seq2 = SV_CriarColunaSeqVis();
	seq3 = SV_CriarColunaSeqVis();
	seq4 = SV_CriarColunaSeqVis();
	seq5 = SV_CriarColunaSeqVis();
	seq6 = SV_CriarColunaSeqVis();
	seq7 = SV_CriarColunaSeqVis();
	seq8 = SV_CriarColunaSeqVis();
	
	// Inserir estas colunas na mesa
	condRet = LIS_InserirElementoApos(mesa, extra);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, naipe1);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, naipe2);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, naipe3);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, naipe4);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq1);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq2);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq3);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq4);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq5);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq6);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq7);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	condRet = LIS_InserirElementoApos(mesa, seq8);
	if(condRet == LIS_CondRetFaltouMemoria){
		return -1;
	}
	return 0;
}

/***************************************************************************
*	$FC Fun��o: &Distribuir Cartas
*
*	$ED Descri��o da fun��o
*	Embaralha as cartas e distribui pelas sequ�ncias vis�veis.
***************************************************************************/
int DistribuirCartas(char baralho[][TAM_CARTA]){
	int n, i, j, condRet;
	char copiaSet[TAM_SET];
	Carta carta;
	SV_Coluna coluna;
	FILE *set = fopen("BarRef.txt", "r");

	// printf("Distribuindo as cartas...\n");
	
	// Recebimento do baralho
	if(set == NULL){ 
		//Procura em outra pasta
		printf("Nao estou achando o set...\n");
	    set = fopen ("..\\Fontes\\BarRef.txt" , "r");
        if (set == NULL)
			printf("Nao achei o set!\n");
			return -1;
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
	else
		return -1;

	/*--/--/--/ �REA DE TESTE /--/--/--*/
	/*printf("ORIGINAL:\n");
	for(i = 0; i < 52; i++){
		printf("%s\t", baralho[i]);
	}
	printf("\n\n");*/
	/*--/--/--/--/--/--/--/--/--/--/--*/

	// Embaralhamento das cartas
	condRet = EMB_Embaralha(baralho);
	if(condRet != EMB_CondRetOK){
		printf("Nao consegui embaralhar!\n");

		/*--/--/--/ �REA DE TESTE /--/--/--*/
		if(condRet == EMB_CondRetBaralhoInvalido)
			printf("ERRO: Baralho invalido.\n");
		if(condRet == EMB_CondRetErroNoEmbaralhamento)
			printf("ERRO: Erro no embaralhamento.\n");
		if(condRet == EMB_CondRetErroNaReferencia)
			printf("ERRO: Erro na referencia.\n");
		/*--/--/--/--/--/--/--/--/--/--/--*/
		return -1;
	}

	/*--/--/--/ �REA DE TESTE /--/--/--*/
	/*printf("EMBARALHADO:\n");
	for(i = 0; i < 52; i++){
		printf("%s\t", baralho[i]);
	}
	printf("\n\n");*/
	/*--/--/--/--/--/--/--/--/--/--/--*/

	// Distribui as cartas embaralhadas pelas colunas de sequ�ncias vis�veis
	
	n = 5;
	i = 0;
	
	while(i < 52){
		IrInicioLista(mesa);

		condRet = LIS_AvancarElementoCorrente(mesa, n);
		//printf("Verificar avanco...\n");
		if(condRet != LIS_CondRetOK){
			return -1;
		}
		
		coluna = (SV_Coluna)LIS_ObterValor(mesa);
		j = i;
		
		// Elementos 5 a 8 tem 7 cartas
		if(n >= 5 && n <= 8){
			for(i = j; i < j + 7; i++){
				condRet = SV_PopularSeqVis(coluna, baralho[i]);
				//printf("Verificar %d...\n", n);
				if(condRet != SV_CondRetOK){
					return -1;
				}
			}
		}

		else{
			for(i = j; i < j + 6; i++){
				condRet = SV_PopularSeqVis(coluna, baralho[i]);
				//printf("Verificar %d...\n", n);
				if(condRet != SV_CondRetOK){
					return -1;
				}
			}
		}
		n++;
	}

	return 0;
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
		condRet = 0;
	EXT_Coluna extra = EXT_CriarColunaExtra();
	NPE_Coluna naipe = NPE_CriarColunaNaipe();
	SV_Coluna seq = SV_CriarColunaSeqVis(); 

	// Checagem das entradas
	if(carta == NULL || ObterValor(carta) == -1 || ObterNaipe(carta) == 'X')
		printf("\nOps...Esta carta nao existe!\n\n", 136);
		return FAIL;

	if(tipoOrigem != 'E' && tipoOrigem != 'N' && tipoOrigem != 'S'){
		printf("\nOps...Parece que voc%c digitou errado.\n\n", 136);
		return FAIL;
	}

	if(tipoDestino != 'E' && tipoDestino != 'N' && tipoDestino != 'S'){
		printf("\nOps...Parece que voc%c digitou errado.\n\n", 136);
		return FAIL;
	}

	VerificarMoverCarta(carta, tipoOrigem, numOrigem, tipoDestino, numDestino, &validaRemocao, &validaInsercao);
	// Se o movimento n�o for v�lido, n�o efetua nada
	if(validaRemocao == FAIL || validaInsercao == FAIL){
		return FAIL;
	}

	// Efetuar remo��o
	if(tipoOrigem == 'E'){
		IrInicioLista(mesa);
		extra = (EXT_Coluna) LIS_ObterValor(mesa);

		condRet = EXT_RemoverCartaDeExtra(extra, carta);
		// Se der erro, abortar miss�o...
		if(condRet != EXT_CondRetOK)
			return FAIL;			
	}
	else if(tipoOrigem == 'S'){
		IrInicioLista(mesa);

		condRet = LIS_AvancarElementoCorrente(mesa, numOrigem + 4);
		if(condRet != LIS_CondRetOK)
			return FAIL;	

		seq = (SV_Coluna) LIS_ObterValor(mesa);
		condRet = SV_RemoverCartaDeSeqVis(seq, carta);
			// Se der erro, abortar miss�o...
			if(condRet != EXT_CondRetOK)
				return FAIL;
	}

	// Efetuar inser��o
	else{
		if(tipoDestino == 'E'){
			extra = (EXT_Coluna) LIS_ObterValor(mesa);
			condRet = EXT_InserirCartaEmExtra(extra, carta);
			//Se der erro, abortar miss�o...
			if(condRet != EXT_CondRetOK)
				return FAIL;
		}
		else if(tipoDestino == 'N'){
			IrInicioLista(mesa);

			condRet = LIS_AvancarElementoCorrente(mesa, numOrigem + 1);
			if(condRet != LIS_CondRetOK)
				return FAIL;

			naipe = (NPE_Coluna) LIS_ObterValor(mesa);
			condRet = NPE_InserirCartaEmNaipe(naipe, carta);
			//Se der erro, abortar miss�o...
			if(condRet != NPE_CondRetOK)
				return FAIL;
		}
		else{
			IrInicioLista(mesa);

			condRet = LIS_AvancarElementoCorrente(mesa, numOrigem + 4);
			if(condRet != LIS_CondRetOK)
				return FAIL;

			seq = (SV_Coluna) LIS_ObterValor(mesa);
			condRet = SV_InserirCartaEmSeqVis(seq, carta);
				// Se der erro, abortar miss�o...
				if(condRet != EXT_CondRetOK)
					return FAIL;
		}
	}
		
	return 0;
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
	int condRet = 0;
	EXT_Coluna extra = EXT_CriarColunaExtra();
	NPE_Coluna naipe = NPE_CriarColunaNaipe();
	SV_Coluna seq = SV_CriarColunaSeqVis(); 
	
	IrInicioLista(mesa);

	// Verificar possibilidade de remo��o
	if(tipoOrigem == 'E'){
		extra = (EXT_Coluna) LIS_ObterValor(mesa);
		condRet = EXT_VerificarRemoverCarta(extra, carta);
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
			LIS_AvancarElementoCorrente(seq, numOrigem + 4);	
			seq = (SV_Coluna) LIS_ObterValor(mesa);
			condRet = SV_VerificarRemoverCarta(seq, carta);
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
		extra = (EXT_Coluna) LIS_ObterValor(mesa);
		condRet = EXT_VerificarInserirCarta(extra, carta);
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
		if(numOrigem < 1 || numOrigem > 4){
			printf("\nOps... O numero desta coluna nao existe!\n\n");
			*validaInsercao = FAIL;
		}
		else{
			LIS_AvancarElementoCorrente(mesa, numOrigem + 1);	
			naipe = (NPE_Coluna) LIS_ObterValor(mesa);
			condRet = NPE_VerificarInserirCarta(naipe, carta);
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
		if(numOrigem < 1 || numOrigem > 8){
			printf("\nOps... O numero desta coluna nao existe!\n\n");
			*validaInsercao = FAIL;
		}
		else{
			LIS_AvancarElementoCorrente(mesa, numOrigem + 4);
			seq = (SV_Coluna) LIS_ObterValor(mesa);
			condRet = SV_VerificarInserirCarta(seq, carta);
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
*	$FC Fun��o: &Exibir Mesa
*	
*	$ED Descri��o da fun��o
*   Exibe todas as cartas da mesa em suas colunas.
***************************************************************************/
void ExibirMesa(){
	int n;
	EXT_Coluna extra;
	NPE_Coluna naipe;
	SV_Coluna seq;

	IrInicioLista(mesa);
	
	// Exibir as cartas da coluna extra
	printf("\nEXTRA:\t");
	extra = (EXT_Coluna) LIS_ObterValor(mesa);
	EXT_ExibirCartas(extra);
	printf("\n\n");
	
	// Exibir as cartas (do topo) das 4 colunas de naipe
	for(n = 1; n <= 4; n++){
		IrInicioLista(mesa);
		LIS_AvancarElementoCorrente(mesa, n);
		naipe = (NPE_Coluna) LIS_ObterValor(mesa);
		
		printf("NAIPE #%d: ", n);
		NPE_ExibirCarta(naipe);
		printf("\n");
	}

	printf("\n");

	// Exibir (todas) as cartas das 8 colunas de naipe
	for(n = 5; n <= 12; n++){
		IrInicioLista(mesa);
		LIS_AvancarElementoCorrente(mesa, n);
		seq = (SV_Coluna) LIS_ObterValor(mesa);
		
		printf("SEQ #%d: ", n - 4);
		SV_ExibirCartas(seq);
		printf("\n");
	}

	printf("\n");

}

/***************************************************************************
*	$FC Fun��o: &Verificar Naipes
*	
*	$ED Descri��o da fun��o
*   Verifica quantas cartas j� est�o nas colunas de naipes, portanto
*	quantas cartas ainda faltam no jogo.
***************************************************************************/
int VerificarNaipes(){
	int n, condRet = 0, 
		numCartas = 0,
		total = 0;
	NPE_Coluna naipe;

	for(n = 1; n <= 4; n++){
		IrInicioLista(mesa);
		condRet = LIS_AvancarElementoCorrente(mesa, n);
		if(condRet != LIS_CondRetOK)
			return -1;

		naipe = LIS_ObterValor(mesa);
		NPE_ContarCartas(naipe, &numCartas);
		total += numCartas;
	}

	return (52 - total);
}

/***************************************************************************
*	$FC Fun��o: &Obter Valor
*	
*	$ED Descri��o da fun��o
*	Indica o valor de uma carta, retornando seu inteiro.
*	Se for inv�lido, retorna -1;
***************************************************************************/
int ObterValor(Carta carta){
	if(carta == NULL)
		return -1;
	
	if(carta[0] == 'A')
		return 1;
	else if(carta[0] == '2')
		return 2;
	else if(carta[0] == '3')
		return 3;
	else if(carta[0] == '4')
		return 4;
	else if(carta[0] == '5')
		return 5;
	else if(carta[0] == '6')
		return 6;
	else if(carta[0] == '7')
		return 7;
	else if(carta[0] == '8')
		return 8;
	else if(carta[0] == '9')
		return 9;
	else if(carta[0] == '1')
		return 10;
	else if(carta[0] == 'J')
		return 11;
	else if(carta[0] == 'Q')
		return 12;
	else if(carta[0] == 'K')
		return 13;
	else
		return -1;
}

/***************************************************************************
*	$FC Fun��o: &Obter Naipe
*	
*	$ED Descri��o da fun��o
*   Indica o naipe de uma carta, retornando seu carater.
*	Se for inv�lido, retona 'X'.
***************************************************************************/
char ObterNaipe(Carta carta){
	int val = ObterValor(carta);
	
	if(val == -1)
		return 'X';

	if(val == 10){
		if(carta[2] == 'P')
			return 'P';
		else if(carta[2] == 'C')
			return 'C';
		else if(carta[2] == 'E')
			return 'E';
		else if(carta[2] == 'O')
			return 'O';
	}
	else{
		if(carta[1] == 'P')
			return 'P';
		else if(carta[1] == 'C')
			return 'C';
		else if(carta[1] == 'E')
			return 'E';
		else if(carta[1] == 'O')
			return 'O';
	}
	return 'X';
}