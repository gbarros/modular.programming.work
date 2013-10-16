/***************************************************************************
*	$MCD Módulo de definição: EXT Extra
*
*	Arquivo gerado:              EXTRA.c
*	Letras identificadoras:      EXT
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
*	1       gb, nk	25/set/2013		Início desenvolvimento, definição de funções
*	2 		lg		13/out/2013		Continuação do desenvolvimento
*	3		nk		14/out/2013		Correção de nomenclatura, novas funções
*	4		lg		14/out/2013		Desenvolvimento
*	5		lg		15/out/2013		Desenvolvimento
*    
***************************************************************************/
#define EXTRA_OWN
#include "EXTRA.h"
#include <stdio.h>
#include <string.h>
#undef EXTRA_OWN

/***************************************************************************
*  Função: EXT  &Criar Coluna
***************************************************************************/

EXT_Coluna EXT_CriarColunaExtra(void)
{
	LIS_tppLista extraHead;
	LIS_tpCondRet retornoCriaLista;
	int i;

	extraHead = LIS_CriarLista(NULL);

	if(extraHead == NULL)
	{
		return NULL;
	}

	for(i=0;i<4;i++)
	{
		retornoCriaLista = LIS_InserirElementoApos(extraHead,NULL);
		if(retornoCriaLista != LIS_CondRetOK)
			return NULL;
	}

	return extraHead;

}

/***************************************************************************
*  Função: EXT  &Excluir Coluna
***************************************************************************/

EXT_tpCondRet EXT_ExcluirColunaExtra(EXT_Coluna coluna)
{
	if(LIS_ObterValor(coluna)==NULL)
		return EXT_CondRetColunaInexistente;

	LIS_DestruirLista(coluna);

	if(coluna != NULL)
		return EXT_CondRetColunaNaoFoiDestruida;

	return EXT_CondRetOK;
}

/***************************************************************************
*  Função: EXT  &Verificar Inserir Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarInserirCarta(EXT_Coluna destino, Carta carta)
{
	LIS_tpCondRet retornoVerificaInserir;
	int i;

	if(LIS_ObterValor(destino) == NULL)
		return EXT_CondRetColunaInexistente;

	if(carta == NULL)
		return EXT_CondRetCartaInvalida;

	IrInicioLista(destino);

	for(i=0;i<4;i++)
	{
		if(LIS_ObterValor(destino)==0) //vê se há elemento na posição
			return EXT_CondRetOK;
		else
			LIS_AvancarElementoCorrente(destino,1); //vê próximo elemento da lista
	}

	return EXT_CondRetNaoPodeInserir;
}

/***************************************************************************
*  Função: EXT  &Verificar Remover Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarRemoverCarta(EXT_Coluna origem, Carta carta)
{
	LIS_tpCondRet retornoVerificaRemover;
	int i;

	if(LIS_ObterValor(origem) == NULL)
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe

	if(carta == NULL)
		return EXT_CondRetCartaInvalida; // verifica se a carta é válida

	retornoVerificaRemover = LIS_ProcurarValor(origem,carta); // procura a carta na coluna

	if(retornoVerificaRemover == LIS_CondRetNaoAchou)
		return EXT_CondRetCartaInvalida; // se a carta não estiver na coluna
	else if(retornoVerificaRemover == LIS_CondRetListaVazia)
		return EXT_CondRetColunaVazia; // se a coluna estiver vazia
	else
		return EXT_CondRetOK;

}

/***************************************************************************
*  Função: EXT  &Inserir Carta Em Extra
***************************************************************************/

EXT_tpCondRet EXT_InserirCartaEmExtra(EXT_Coluna destino, Carta carta)
{
	LIS_tpCondRet retornoInserir;
	EXT_tpCondRet possivelInserir;

	if(LIS_ObterValor(destino) == NULL)
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe

	if(carta == NULL)
		return EXT_CondRetCartaInvalida; // verifica se a carta é válida

	possivelInserir = EXT_VerificarInserirCarta(destino,carta); // chama função para verificar se a inserção é possível

	if(possivelInserir == EXT_CondRetOK) // se a inserção for possível
	{
		IrFinalLista(destino); //torna elemento corrente o ultimo elemento
		retornoInserir = LIS_InserirElementoApos(destino,carta); // insere após o elemento corrente
	}

	if(retornoInserir == LIS_CondRetOK)
		return EXT_CondRetOK;

	return EXT_CondRetErroInserção;
}

/***************************************************************************
*  Função: EXT  &Remover Carta De Extra
***************************************************************************/

EXT_tpCondRet EXT_RemoverCartaDeExtra(EXT_Coluna origem, Carta carta)
{
	LIS_tpCondRet retornoRemover;
	EXT_tpCondRet possivelRemover;

	if(LIS_ObterValor(origem) == NULL)
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe

	if(carta == NULL)
		return EXT_CondRetCartaInvalida; // verifica se a carta é válida

	possivelRemover = EXT_VerificarRemoverCarta(origem,carta); // chama função que vê se é possível remover

	if(possivelRemover == EXT_CondRetOK) // se a Remocao for possível
		retornoRemover = LIS_ExcluirElemento(origem); // se estiver, exclui a carta da coluna

	if(retornoRemover == LIS_CondRetOK)
	{
		retornoRemover = LIS_InserirElementoApos(origem,NULL);
		if(retornoRemover == LIS_CondRetOK)
			return EXT_CondRetOK;
	}

	return EXT_CondRetErroRemocao;

}

/***************************************************************************
*  Função: EXT  &Exibir Carta
***************************************************************************/

EXT_tpCondRet EXT_ExibirCartas(EXT_Coluna coluna)
{
	int i;
	LIS_tpCondRet andar;
	char *valor;

	if(LIS_ObterValor(coluna) == NULL)
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe

	IrInicioLista(coluna); // garantir que pegaremos os valores desde o início

	for(i=0;i<4;i++)
	{
		valor = LIS_ObterValor(coluna);

		if(valor == NULL)
			break;
		
		printf("%s ",valor);

		andar = LIS_AvancarElementoCorrente(coluna,1);
	}

	printf("\n");

	return EXT_CondRetOK;
}

int main()
{
	return 0;
}

