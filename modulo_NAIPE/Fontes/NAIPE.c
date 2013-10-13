/***************************************************************************
*  $MCI Módulo de implementação: NPE Naipe
*
*  Arquivo gerado:              NAIPE.c
*  Letras identificadoras:      NPE
*
*  Nome da base de software:    Jogo FreeCell
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
*  1       nk		11/out/2013		Início desenvolvimento, Criação NAIPE
*  2 	   lg		13/out/2013		Desenvolvimento
*    
***************************************************************************/

#include <LISTA.H>

typedef LIS_tppLista NPE_Coluna;
typedef char* Carta;

public NPE_Coluna NPE_CriaColuna (void)
{
	return LIS_CriarLista(NULL);
}

public int NPE_ExcluirColuna(NPE_Coluna coluna)
{
	LIS_DestruirLista(coluna);
	return 0;
}

static int ContarCartas (NPE_Coluna coluna)
{
	// conta o numero de cartas para saber qual o valor que deve vir a proxima
}

public int NPE_InserirCartaEmNaipe(NPE_Coluna destino, Carta carta)
{
	// ver se o naipe é o equivalente ao da coluna destino
	// ver o numero retornado pelo contar cartas e se é ele+1

}



