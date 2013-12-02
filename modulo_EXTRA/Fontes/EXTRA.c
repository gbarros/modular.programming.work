/***************************************************************************
*	$MCD Módulo de definição: EXT Extra
*
*	Arquivo gerado:              EXTRA.c
*	Letras identificadoras:      EXT
*
*	Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão  Autor	Data			Observações
*	1       gb, nk	25/set/2013		Início desenvolvimento, definição de funções
*	2 		lg		13/out/2013		Continuação do desenvolvimento
*	3		nk		14/out/2013		Correção de nomenclatura, novas funções
*	4		lg		14/out/2013		Desenvolvimento
*	5		lg		15/out/2013		Desenvolvimento
*   6       gb      16/out/2013     Desenvolvimento
*    
***************************************************************************/
#define EXTRA_OWN
#include "EXTRA.h"
#include <stdio.h>
#include <string.h>
#undef EXTRA_OWN

static int ObterValor(Carta carta);
static char ObterNaipe(Carta carta);
static char REF [] = " "; //Referencia para espaço vazio


/***************************************************************************
*  Função: EXT  &Criar Coluna
***************************************************************************/

EXT_Coluna EXT_CriarColunaExtra(void){
	int i;
	EXT_Coluna extraHead;
	LIS_tpCondRet condRet;

	extraHead = LIS_CriarLista(NULL);

	if(extraHead == NULL){
		return NULL;
	}

	for(i = 0; i < 4; i++){
		condRet = LIS_InserirElementoApos(extraHead, REF);
		if(condRet != LIS_CondRetOK){
			LIS_DestruirLista(extraHead);
			return NULL;
		}
	}

	return extraHead;

}

/***************************************************************************
*  Função: EXT  &Excluir Coluna
***************************************************************************/

EXT_tpCondRet EXT_ExcluirColunaExtra(EXT_Coluna coluna){
	if(coluna==NULL)
		return EXT_CondRetColunaNaoExiste;

	LIS_DestruirLista(coluna);

	return EXT_CondRetOK;
}

/***************************************************************************
*  Função: EXT  &Verificar Inserir Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarInserirCarta(EXT_Coluna destino, Carta carta){
	int i = 4;

	if(destino == NULL)
		return EXT_CondRetColunaNaoExiste;
	
	// Verifica se a carta é válida
	if(carta == NULL || (ObterValor(carta)== -1)|| (ObterNaipe(carta)=='X'))
		return EXT_CondRetCartaNaoExiste;

	IrFinalLista(destino);

	while(i){
		// Se a posição está vazia, pode inserir
		if(LIS_ObterValor(destino) == REF)
			return EXT_CondRetOK;
		// Caso contrário, verifica o próximo elemento
		else
			LIS_AvancarElementoCorrente(destino,-1); 
		
		i--;
	}

	return EXT_CondRetNaoPodeInserir;
}

/***************************************************************************
*  Função: EXT  &Verificar Remover Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarRemoverCarta(EXT_Coluna origem, Carta carta){
	LIS_tpCondRet retornoVerificaRemover;

	// Verifica se a coluna recebida existe
	if(origem == NULL)
		return EXT_CondRetColunaNaoExiste; 

	// Verifica se a carta recebida é válida
	if(carta == NULL || (ObterValor(carta)== -1)|| (ObterNaipe(carta)=='X'))
		return EXT_CondRetCartaNaoExiste; 

	IrInicioLista(origem);

	// Procura se a carta na existe na coluna
	retornoVerificaRemover = LIS_ProcurarValor(origem, carta); 

	// Se a carta não estiver na coluna, não é possível removê-la
	if(retornoVerificaRemover == LIS_CondRetNaoAchou)
		return EXT_CondRetNaoPodeRemover; 

	// Se a coluna estiver vazia, não é possível removê-la
	else if(retornoVerificaRemover == LIS_CondRetListaVazia)
		return EXT_CondRetNaoPodeRemover; 
	
	else
		return EXT_CondRetOK;
}

/***************************************************************************
*  Função: EXT  &Inserir Carta Em Extra
***************************************************************************/

EXT_tpCondRet EXT_InserirCartaEmExtra(EXT_Coluna destino, Carta carta){
	LIS_tpCondRet condRet;

	if(EXT_VerificarInserirCarta(destino, carta) != EXT_CondRetOK){
		return EXT_CondRetErroAoInserir;
	}

	//Torna elemento corrente o último elemento
	IrFinalLista(destino); 

	// Insere carta após o elemento corrente
	condRet = LIS_InserirElementoApos(destino, carta); 

	if(condRet == LIS_CondRetOK)
		return EXT_CondRetOK;
	else
		return EXT_CondRetErroAoInserir;	
}

/***************************************************************************
*  Função: EXT  &Remover Carta De Extra
***************************************************************************/

EXT_tpCondRet EXT_RemoverCartaDeExtra(EXT_Coluna origem, Carta carta){
	LIS_tpCondRet condRet;

	if(EXT_VerificarRemoverCarta(origem, carta) != EXT_CondRetOK)
		return EXT_CondRetErroAoRemover;

	condRet = LIS_ExcluirElemento(origem);

	// Após remoção, precisamos inserir vazio de novo
	if(condRet == LIS_CondRetOK){
		condRet = LIS_InserirElementoApos(origem, REF);
		
		if(condRet == LIS_CondRetOK)
			return EXT_CondRetOK;
		else
			return EXT_CondRetErroAoRemover;
	}
	else
		return EXT_CondRetErroAoRemover;
}

/***************************************************************************
*  Função: EXT  &Exibir Carta
***************************************************************************/

EXT_tpCondRet EXT_ExibirCartas(EXT_Coluna coluna){
	int i;
	LIS_tpCondRet avancarCondRet;
	char *valor;

	// Verifica se a coluna recebida existe
	if(coluna == NULL)
		return EXT_CondRetColunaNaoExiste;
	
	IrFinalLista(coluna); // garantir que pegaremos os valores desde o início

	for(i = 0; i < 4; i++){
		valor = (Carta) LIS_ObterValor(coluna);
		
		if(valor == NULL)
			break;
		
		printf("[ %s ]\t", valor);

		avancarCondRet = LIS_AvancarElementoCorrente(coluna,-1);
		
		if (avancarCondRet == LIS_CondRetFimLista)
			break;
	}

	return EXT_CondRetOK;
}


static int ObterValor(Carta carta){
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
static char ObterNaipe(Carta carta){
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
