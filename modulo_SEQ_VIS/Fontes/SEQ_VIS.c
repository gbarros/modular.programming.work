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
*	1 		lg		13/out/2013		Criação e início do desenvolvimento do módulo
*    
***************************************************************************/

#include <LISTA.H>

typedef LIS_tppLista SEQ_VIS_Coluna;
typedef char* Carta;

public SEQ_VIS_Coluna SEQ_VIS_CriaColuna(void)
{
	return LIS_CriarLista(NULL);
}

public int SEQ_VIS_ExcluirColuna(SEQ_VIS_Coluna coluna)
{
	LIS_DestruirLista(coluna);
	return 0;
}

public int SEQ_VIS_InserirCarta (SEQ_VIS_Coluna destino, Carta carta)
{
	// checar se a carta na última posição da lista é 1 valor a menos e pertence a um naipe de cor oposta
}

public int SEQ_VIS_ExcluirCarta (SEQ_VIS_Coluna alvo, Carta carta)
{
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

