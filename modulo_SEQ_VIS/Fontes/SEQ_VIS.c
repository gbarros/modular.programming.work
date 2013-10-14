/***************************************************************************
*  $MCD Módulo de implementação: SV Sequência Visível
*
*  Arquivo gerado:              SEQ_VIS.c
*  Letras identificadoras:      SV
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: [INF 1301] Implementação do Jogo FreCell para fins educacionais
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    gb -	Gabriel Barros
*			   lg - Leonardo Giroto 
*			   nk - Noemie Nakamura
*
*  $HA Histórico de evolução:
*   Versão  Autor	Data			Observações
*	2		nk		14/out/2013		Correção de nomenclatura, novas funções
*	1 		lg		13/out/2013		Criação e início do desenvolvimento do módulo
*    
***************************************************************************/
#define SEQ_VIS_OWN
#include "SEQ_VIS.h"
#undef SEQ_VIS_OWN

typedef char* Carta;

/***************************************************************************
*  Função: SV  &Criar Coluna
***************************************************************************/

SV_Coluna SV_CriarColunaSeqVis(void)
{
	return LIS_CriarLista(NULL);
}

/***************************************************************************
*  Função: SV  &Excluir Coluna
***************************************************************************/

SV_tpCondRet SV_ExcluirColunaSeqVis(SV_Coluna coluna)
{
	LIS_DestruirLista(coluna);
	return 0;
}

/***************************************************************************
*  Função: SV  &Verificar Inserir Carta
***************************************************************************/

SV_tpCondRet SV_VerificarInserirCarta(SVColuna destino, Carta carta){

//here goes the code

}

/***************************************************************************
*  Função: SV  &Verificar Remover Carta
***************************************************************************/

SV_tpCondRet SV_VerificarRemoverCarta(SVColuna origem, Carta carta){
//here goes the code

}

/***************************************************************************
*  Função: SV  &Inserir Carta Em SVra
***************************************************************************/

SV_tpCondRet SV_InserirCarta(SV_Coluna destino, Carta carta)
{
	// checar se a carta na última posição da lista é 1 valor a menos e pertence a um naipe de cor oposta
}

/***************************************************************************
*  Função: SV  &Remover Carta De SVra
***************************************************************************/

SV_tpCondRet SV_RemoverCartaDeSeqVis(SV_Coluna origem, Carta carta){
/*Deve-se analizar os retornos de procurar valor e talvez de ExcluirElemento*/

	if(LIS_ProcurarValor(alvo, carta) == LIS_CondRetNaoEncontrou || LIS_ProcurarValor(alvo, carta) == LIS_CondRetListaVazia))
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
*  Função: SV  &Exibir Carta
***************************************************************************/

void SVExibirCartas(SVColuna coluna){}