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
*	n1		nk		25/nov/2013		Fun��o iniciar novo jogo
*	n2		nk		28/nov/2013		Corre��es e desenvolvimento
*	n3		nk		29/nov/2013		Desenvolvimento
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

/* Vari�veis globais */
char baralho[TOTAL_CARTAS][TAM_CARTA];
Mesa mesa;

/* Prot�tipos de fun��es */
int SelecionarMenu(int status);
int IniciarNovoJogo();
int DistribuirCartas();
int ContarFreecells();
int MoverCarta(Carta carta, char tipoOrigem, int numOrigem, char tipoDestino, int numDestino);
void VerificarMoverCarta(Carta carta, char tipoOrigem, int numOrigem, char tipoDestino, int numDestino, int *validaRemocao, int *validaInsercao)
void ExibirMesa();

int main(){
	//---------- Declara��o de vari�veis ----------
	int opcaoDeJogo, // op��o para iniciar ou sair
		opcaoDeMovimento, // op��o para mover ou desistir
		status = OFF, // determina se h� um jogo em andamento ou n�o
		numOrigem,
		numDestino,
		numCelulasLivres,
		condRet; // recebe as condi��es de retorno das fun��es
	
	char carta[TAM_CARTA], // recebe a carta que o jogador deseja mover
		 tipoOrigem,
		 tipoDestino;
	//--------------------------------------------------

	//---------- In�cio ----------
	mesa = LIS_CriarLista(NULL);
	opcaoDeJogo = SelecionarMenu(status);

	// Se jogador decidiu iniciar novo jogo...
	if(opcaoDeJogo == INICIAR){
		// Setar status para ON
		status = ON;

		// Cria uma nova mesa
		printf("Nova mesa sendo criada...\n");
		condRet = IniciarNovoJogo();
		if(condRet == 0){
			printf("SUCESSO!\n");
		}
		else{
			printf("Ops... Algo deu errado ao criar a mesa!\n");
			return -1;
		}

		// Distribui as cartas pelas sequ�ncias vis�veis
		printf("Distribuindo as cartas...\n");
		condRet = DistribuirCartas(baralho);
		if(condRet == 0){
			printf("SUCESSO!\n");
		}
		else{
			printf("Ops... Algo deu errado ao distribuir as cartas!\n");
			return -1;
		}

		// Enquanto o jogador n�o desistir ou vencer o jogo
		//ExibirMesa();
		opcaoDeMovimento = SelecionarMenu(status);
		
		while(opcaoDeMovimento == MOVER){
			printf("\nIndique a carta que deseja transferir, a coluna fonte e a coluna destino.\n");
			printf("HINT: E - Extra; N  - Naipe; S - sequ�ncia\n");
			scanf("%s %c%d %c%d", carta, &tipoOrigem, &numOrigem, &tipoDestino, &numDestino);

			numCelulasLivres = ContarFreecells;
			printf("Pode mover %d\n", numCelulasLivres);

			condRet = MoverCarta(carta, tipoOrigem, numOrigem, tipoDestino, numDestino);
			/* TESTE */
			printf("%s - ", carta);
			printf("%c", tipoOrigem);
			printf("%d - ", numOrigem);
			printf("%c", tipoDestino);
			printf("%d\n\n", numDestino);

			if(condRet != 0){
				//ExibirMesa();
				opcaoDeMovimento = SelecionarMenu(status);
			}


		
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
		printf("");
		printf("O que deseja fazer?\n\t[1] Iniciar novo jogo\n\t[2] Sair\n\n");
		scanf("%d", &opcao);
	}
	
	else{
		printf("O que deseja fazer?\n\t[1] Mover uma carta\n\t[2] Desistir\n\n");
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
	LIS_tpCondRet condRet;
	EXT_Coluna extra;
	NPE_Coluna naipe1, naipe2, naipe3, naipe4;
	SV_Coluna seq1, seq2, seq3, seq4, seq5, seq6, seq7, seq8;	 

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
	int i, j, k = 0, condRet;
	char copiaSet[TAM_SET];
	Carta carta;
	FILE *set = fopen("baralho.txt", "r");

	// Recebimento do baralho
	if(set == NULL){ 
		//Procura em outra pasta
		printf("N%co estou achando o set...\n", 227);
	    set = fopen ("..\\Fontes\\baralho.txt" , "r");
        if (set == NULL)
			printf("N%c achei o set!\n", 227);
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

	for(i = 0; i < 52; i++){
		printf("%s\t", baralho[i]);
	}

	// Embaralhamento das cartas
	condRet = EMB_Embaralha(baralho);
	if(condRet != EMB_CondRetOK){
		printf("N%c consegui embaralhar!\n", 227);
		return -1;
	}

	// Distribui as cartas embaralhadas pelas colunas de sequ�ncias vis�veis
	IrInicioLista(mesa);
	LIS_AvancarElementoCorrente(mesa, 5);

	for(i = 0; i < 8; i++){
		// Colunas 1 a 4 s�o populadas com 7 cartas
		if(i < 4){
			for(j = 0; j < 7; j++){				
				condRet = SV_PopularSeqVis(mesa, baralho[k]);
				k++;
			}
		}
		// Colunas 5 a 8 s�o populadas com 6 cartas
		else{
			for(j = 0; j < 6; j++){				
				condRet = SV_PopularSeqVis(mesa, baralho[k]);
				k++;
			}
		}
		
		// Segue para pr�xima coluna 
		LIS_AvancarElementoCorrente(mesa, 1);
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
	int validaRemocao, validaInsercao;

	// Checagem das entradas
	if(tipoOrigem != 'E' || tipoOrigem != 'N' || tipoOrigem != 'S'){
		printf("\nOps...Parece que voc%c digitou errado.\n\n", 136);
		return -1;
	}

	if(tipoDestino != 'E' || tipoDestino != 'N' || tipoDestino != 'S'){
		printf("\nOps...Parece que voc%c digitou errado.\n\n", 136);
		return -1;
	}

	VerificarMoverCarta(carta, tipoOrigem, numOrigem, tipoDestino, numDestino, &validaRemocao, &validaInsercao);
	// Se o movimento n�o for v�lido, n�o efetua nada
	if(validaRemocao == FAIL || validaInsercao == FAIL){
		return -1;

	
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
						int *validaRemocao, int validaInsercao){
	
	IrInicioLista(mesa);

	// Verificar possibilidade de remo��o
	
	if(tipoOrigem == 'E'){
		condRet = EXT_VerificarRemoverCarta(mesa, carta);
		if(condRet == EXT_CondRetCartaNaoExiste){
			printf("\nOps... A carta que voc%c escolheu n%co existe aqui!\n\n", 136, 298);
			*validaRemocao = FAIL;
		}
		else if(condRet == EXT_CondRetNaoPodeRemover){
			printf("\nN%co % poss%cvel remover esta carta desta coluna.\n\n", 298, 130, 161);
			*validaRemocao = FAIL;
		}
		else{
			*validaRemocao = OK;
		}
	}

	else if(tipoOrigem == 'N'){
		printf("\nN%co % poss%cvel remover cartas de naipe.\n\n", 298, 130, 161);
		*validaRemocao = FAIL;
	}
	
	else{
		if(numOrigem < 1 || numOrigem > 8){
			printf("\nOps... O n%cmero desta coluna n%co existe!\n\n", 163, 298);
			*validaRemocao = FAIL;
		}
		else{
			LIS_AvancarElementoCorrente(mesa, numOrigem + 4);	
			condRet = SV_VerificarRemoverCarta(mesa, carta);
			if(condRet == SV_CondRetCartaNaoExiste){
				printf("\nOps... A carta que voc%c escolheu n%co existe aqui!\n\n", 136, 298);
				*validaRemocao = FAIL;
			}
			else if(condRet == SV_CondRetNaoPodeRemover){
				printf("\nN%co % poss%cvel remover esta carta desta coluna.\n\n", 298, 130, 161);
				*validaRemocao = FAIL;
			}
			else{
				*validaRemocao = OK;
			}
		}
	}

	// Verificar possibilidade de inser��o
	
	if(tipoDestino == 'E'){
		condRet = EXT_VerificarInserirCarta(mesa, carta);
		if(condRet == EXT_CondRetCartaNaoExiste){
			printf("\nOps... A carta que voc%c escolheu n%co existe aqui!\n\n", 136, 298);
			*validaInsercao = FAIL;
		}
		else if(condRet == EXT_CondRetNaoPodeInserir){
			printf("\nN%co % poss%cvel inserir esta carta desta coluna.\n\n", 298, 130, 161);
			*validaInsercao = FAIL;
		}
		else{
			*validaInsercao = OK;
		}	
	}

	else if(tipoDestino == 'N'){
		if(numOrigem < 1 || numOrigem > 4){
			printf("\nOps... O n%cmero desta coluna n%co existe!\n\n", 163, 298);
			*validaInsercao = FAIL;
		}
		else{
			LIS_AvancarElementoCorrente(mesa, numOrigem + 1);	
			condRet = NPE_VerificarInserirCarta(mesa, carta);
			if(condRet == NPE_CondRetCartaNaoExiste){
				printf("\nOps... A carta que voc%c escolheu n%co existe aqui!\n\n", 136, 298);
				*validaInsercao = FAIL;
			}
			else if(condRet == NPE_CondRetNaoPodeInserir){
				printf("\nN%co % poss%cvel inserir esta carta desta coluna.\n\n", 298, 130, 161);
				*validaInsercao = FAIL;
			}
			else{
				*validaInsercao = OK;
			}	
		}
	}

	else{
		if(numOrigem < 1 || numOrigem > 8){
			printf("\nOps... O n%cmero desta coluna n%co existe!\n\n", 163, 298);
			*validaInsercao = FAIL;
		}
		else{
			LIS_AvancarElementoCorrente(mesa, numOrigem + 4);	
			condRet = SV_VerificarInserirCarta(mesa, carta);
			if(condRet == SV_CondRetCartaNaoExiste){
				printf("\nOps... A carta que voc%c escolheu n%co existe aqui!\n\n", 136, 298);
				*validaInsercao = FAIL;
			}
			else if(condRet == SV_CondRetNaoPodeRemover){
				printf("\nN%co % poss%cvel inserir esta carta desta coluna.\n\n", 298, 130, 161);
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
	int numFreecell = 0, condRet;

	IrInicioLista(mesa);
	// Verificar n�mero de espa�os vazios em extra

	// Verificar n�mero de espa�os vazios em naipe

	// Verificar n�mero de espa�os vazios em sequ�ncia vis�vel
	return numFreecell;
}

/***************************************************************************
*	$FC Fun��o: &Exibir Mesa
*	
*	$ED Descri��o da fun��o
*   Exibe todas as cartas da mesa em suas colunas.
***************************************************************************/
void ExibirMesa(){
	int n;

	system("cls");
	IrInicioLista(mesa);
	
	// Exibir as cartas da coluna extra
	printf("EXTRA:\t");
	EXT_ExibirCartas(mesa);
	LIS_AvancarElementoCorrente(mesa, 1);
	printf("\n");

	// Exibir as cartas (do topo) das 4 colunas de naipe
	for(n = 0; n < 4; n++){
		LIS_AvancarElementoCorrente(mesa, 1);
		printf("NAIPE #%d: ", n + 1);
		NPE_ExibirCarta(mesa);
		printf("\n");
	}

	printf("\n");

	// Exibir (todas) as cartas das 8 colunas de naipe
	for(n = 0; n < 8; n++){
		LIS_AvancarElementoCorrente(mesa, 1);
		printf("SEQ #%d: ", n + 1);
		SV_ExibirCartas(mesa);
		printf("\n");
	}

	printf("\n");
}

