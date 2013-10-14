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
*	2 		lg		13/out/2013		Desenvolvimento
*	3		nk		14/out/2013		Correção de nomenclatura, novas funções
*    
***************************************************************************/
#define EXTRA_OWN
#include "EXTRA.h"
#undef EXTRA_OWN

typedef char* Carta;

/***************************************************************************
*  Função: EXT  &Criar Coluna
***************************************************************************/

EXT_Coluna EXT_CriarColunaExtra(Carta carta)
{
	LIS_tppLista extra_head = LIS_CriarLista(NULL);
	var = LIS_InserirElementoApos(extra_head, carta);
	// Verificar se deu certo...
	var = LIS_InserirElementoApos(extra_head, carta);
	// Verificar se deu certo...
	var = LIS_InserirElementoApos(extra_head, carta);
	// Verificar se deu certo...
	var = LIS_InserirElementoApos(extra_head, carta);
	// Verificar se deu certo...

	return extra_head;
}

/***************************************************************************
*  Função: EXT  &Excluir Coluna
***************************************************************************/

EXT_tpCondRet EXT_ExcluirColunaExtra(EXT_Coluna coluna)
{
	LIS_DestruirLista(coluna);
	return 0;
}

/***************************************************************************
*  Função: EXT  &Verificar Inserir Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarInserirCarta(EXT_Coluna destino, Carta carta){

//here goes the code

}

/***************************************************************************
*  Função: EXT  &Verificar Remover Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarRemoverCarta(EXT_Coluna origem, Carta carta){
//here goes the code

}

/***************************************************************************
*  Função: EXT  &Inserir Carta Em Extra
***************************************************************************/

EXT_tpCondRet EXT_InserirCartaEmExtra(EXT_Coluna destino, Carta carta)
{
	int i;

	for(i=0; i<4; i++)
	{
		if(LIS_ObterValor(destino)==NULL) //vê se há elemento na posição
		{
			IrFinalLista(destino); //torna elemento corrente o ultimo elemento
			int deuCerto = LIS_InserirElementoApos(destino,carta); // insere após o elemento corrente
			return deuCerto;
		}

		LIS_AvancarElementoCorrente(destino,1); //vê próximo elemento da lista
	}

	return -1;
}

/***************************************************************************
*  Função: EXT  &Remover Carta De Extra
***************************************************************************/

EXT_tpCondRet EXT_RemoverCartaDeExtra(EXT_Coluna origem, Carta carta){
/*Deve-se analizar os retornos de procurar valor e talvez de ExcluirElemento*/

	if(LIS_ProcurEXTalor(alvo, carta) == LIS_CondRetNaoEncontrou || LIS_ProcurEXTalor(alvo, carta) == LIS_CondRetListaVazia))
	{
		return -1;
	}
	else
	{
		int deuCerto = LIS_ExcluirElemento(alvo);
	}

	return deuCerto;
}

/***************************************************************************
*  Função: EXT  &Exibir Carta
***************************************************************************/

void EXT_ExibirCartas(EXT_Coluna coluna){}

