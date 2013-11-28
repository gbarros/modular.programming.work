/***************************************************************************
*	$MCD Módulo de definição: FC Freecell
*
*	Arquivo gerado:              FREECELL.c
*	Letras identificadoras:      FC
*
*	Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão  Autor	Data			Observações
*	1       nk		15/nov/2013		Início desenvolvimento
*	n1		nk		25/nov/2013		Função iniciar novo jogo
*	n2		nk		28/nov/2013		Correções e outras funções
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

#define INICIAR			1	 
#define MOVER			1
#define DESISTIR		2
#define SAIR			2

#define TOTAL_CARTAS	52

/* Tipo referência para a carta */
typedef char *Carta;

/* Tipo referência para uma coluna extra */
typedef LIS_tppLista FC_Mesa;

Carta baralho[TOTAL_CARTAS] = {
	"A\x03","2\x03","3\x03","4\x03","5\x03","6\x03","7\x03","8\x03","9\x03","10\x03","J\x03","Q\x03","K\x03",	
	"A\x05","2\x05","3\x05","4\x05","5\x05","6\x05","7\x05","8\x05","9\x05","10\x05","J\x05","Q\x05","K\x05",
	"A\x04","2\x04","3\x04","4\x04","5\x04","6\x04","7\x04","8\x04","9\x04","10\x04","J\x04","Q\x04","K\x04",
	"A\x06","2\x06","3\x06","4\x06","5\x06","6\x06","7\x06","8\x06","9\x06","10\x06","J\x06","Q\x06","K\x06",
};

/***************************************************************************
*  Função: FC  &Selecionar Menu
***************************************************************************/

int FC_SelecionarMenu(int status){
	int opcao;

	//Primeiro, o menu verifica se há ou não um jogo em andamento
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
		printf("\nOps...Parece que voc%c digitou errado.\n", 136);
		opcao = FC_SelecionarMenu(status);
	}

	return opcao;
}

/***************************************************************************
*  Função: FC  &Iniciar Novo Jogo
***************************************************************************/
int FC_IniciarNovoJogo(FC_Mesa mesa){
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
	
	// Criar oito colunas tipo sequência visível
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
*  Função: FC  &Distribuir Cartas
***************************************************************************/
int FC_DistribuirCartas(FC_Mesa mesa, Carta baralho[]){
	//int i, j, 
	//	randomico,
	//	condRet;

	//// Mesa recebe baralho o embaralha
	//condRet = EMB_Embaralha(baralho);
	//if(condRet != EMB_CondRetOK){
	//	return -1;
	//}

	//// Distribui as cartas embaralhadas pelas colunas de sequências visíveis
	//IrInicioLista(mesa);
	//LIS_AvancarElementoCorrente(mesa, 5);

	//for(i = 0; i < 8; i++){
	//	for(j = 0; j < 7; j++){
	//		randomico = srand() % 52;
	//		SV_PopularSeqVis(mesa, baralho[randomico]);
	//	}

	//	LIS_AvancarElementoCorrente(mesa,1);
	//}
	return 0;
}

/***************************************************************************
*  Função: FC  &Exibir Mesa
***************************************************************************/
void FC_ExibirMesa(FC_Mesa mesa){
	int n;

	system("cls");
	IrInicioLista(mesa);
	
	// Exibir as cartas da coluna extra
	printf("EXTRA:\t");
	EXT_ExibirCartas(mesa);
	printf("\n");

	// Exibir as cartas (do topo) das 4 colunas de naipe
	for(n = 0; n < 4; n++){
		LIS_AvancarElementoCorrente(mesa, 1);
		printf("NAIPE #%d: \t", n + 1);
		NPE_ExibirCarta(mesa);
		printf("\n");
	}

	printf("\n");

	// Exibir (todas) as cartas das 8 colunas de naipe
	for(n = 0; n < 8; n++){
		LIS_AvancarElementoCorrente(mesa, 1);
		printf("SEQ #%d: \t", n + 1);
		SV_ExibirCartas(mesa);
		printf("\n");
	}

	printf("\n");
}

/***************************************************************************
*  Função: FC  &Desistir
***************************************************************************/
void FC_Desistir(){
	
}

/***************************************************************************
*  Função: FC  &Mover Carta
***************************************************************************/
int FC_MoverCarta(Carta carta, void* origem, void* destino, char tipoOrigem, char tipoDestino);

int main(){
	//----- Declaração de variáveis
	int opcaoDeJogo, // opção para iniciar ou sair
		opcaoDeMovimento, // opção para mover ou desistir
		status = OFF, // determina se há um jogo em andamento ou não
		condRet; // recebe as condições de retorno das funções
	char carta, // recebe
		 colunaOrigem,
		 colunaDestino;

	FC_Mesa mesa = LIS_CriarLista(NULL);

	//----- Início 
	opcaoDeJogo = FC_SelecionarMenu(status);
	
	// Enquanto jogador não digitar algo válido, rodar menu
	while(opcaoDeJogo != 1 && opcaoDeJogo != 2){
		printf("\nOps...Parece que voc%c digitou errado.\n", 136);
		opcaoDeJogo = FC_SelecionarMenu(status);
	}

	// Se jogador decidiu iniciar novo jogo...
	if(opcaoDeJogo == INICIAR){
		// Setar status para ON
		status = ON;

		// Cria uma nova mesa
		printf("Nova mesa sendo criada...\n");
		condRet = FC_IniciarNovoJogo(mesa);
		if(condRet == 0){
			printf("SUCESSO!\n");
		}
		else{
			printf("Ops... Algo deu errado ao criar a mesa!\n");
			return -1;
		}

		// Distribui as cartas pelas sequências visíveis
		printf("Distribuindo as cartas...\n");
		condRet = FC_DistribuirCartas(mesa, baralho);
		if(condRet == 0){
			printf("SUCESSO!\n");
		}
		else{
			printf("Ops... Algo deu errado ao distribuir as cartas!\n");
			return -1;
		}

		// Enquanto o jogador não desistir ou vencer o jogo
		FC_ExibirMesa(mesa);
		opcaoDeMovimento = FC_SelecionarMenu(status);
		while(opcaoDeMovimento == MOVER){
			printf("Indique a carta que deseja transferir, a coluna fonte e a coluna destino:\n");
			printf("\tHINT:\tPara carta digite o número ou letra seguido de primeira letra maiúscula do naipe.\n");
			printf("\t\tPara coluna digite extra, naipe seguido do número ou seq seguido do número.\n");
			scanf("%s %s %s", carta, colunaOrigem, colunaDestino);
			

		 
		
		}

		// Libera a mesa e termina o jogo
	}	

	// Se jogador decidiu sair...
	else{
		printf("\nJ%c indo?\nVolte em breve para um novo jogo!\n\n", 160);
		exit(EXIT_SUCCESS);
	}

	return 0;
}