/***************************************************************************
*  $MCD Módulo de definição: EXT Extra
*
*  Arquivo gerado:              EXTRA.c
*  Letras identificadoras:      EXT
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
*  Versão  Autor	Data			Observações
*  1       gb, nk	25/set/2013		Início desenvolvimento, definição de funções
*  2 	   lg		13/out/2013		Desenvolvimento
*    
***************************************************************************/
#include <LISTA.H>

typedef LIS_tppLista EXT_Coluna;
typedef char* Carta;


public CLI_Coluna CLI_CriaColuna (void)
{
	return LIS_CriarLista(NULL);
}

public int CLI_ExcluirColuna( CLI_Coluna coluna )
{
	LIS_DestruirLista(coluna);
	return 0;
}

public int CLI_InserirCarta ( CLI_Coluna destino, Carta carta)
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

public int CLI_ExcluirCarta (CLI_Coluna alvo, Carta carta)
{
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

static int ContarCartas (CLI_Coluna coluna)
{
	char a, b;

	IrInicioLista(coluna);

	a = LIS_ObterValor(coluna);

	IrFinalLista(coluna);

	b = LIS_ObterValor(coluna);

	if(a == b)
	{
		return 1;
	}

	else
	{
		IrInicioLista(coluna);
		LIS_AvancarElementoCorrente(coluna,1);
		return ContarCartas(&coluna)+1;
	}

	/* implementar contador de cartas, dica: se for um inicio=fim, senão tem que ir do 
	inicio ao fim iterando*/
}
