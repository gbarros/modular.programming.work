/***************************************************************************
*	$MCD Módulo de definição: EMB Embaralhamento
*
*	Arquivo gerado:              EMBARALHA.h
*	Letras identificadoras:      EMB
*
*	Nome da base de software:    Jogo FreeCell
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
*	5 		lg		14/out/2013		Ajuste condições de retorno
*   4		nk		14/out/2013		Mudança de nomenclatura, correções 
*	3		gb 		13/out/2013		Teste do módulo
* 	2 		lg, gb  13/out/2013		Desenvolvimento
*   1       gb		12/out/2013		Início desenvolvimento
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  
#define EMBARALHA_OWN
#include "EMBARALHA.h"

static void EMB_CopiaMarca (char* a, char* b)
{
		strcpy(b,a);
        strcpy(a,"0");
} 

EMB_tpCondRet EMB_embaralha(char bar[53][4]){
 
	char barAux[53][4];
	int i,n;

	srand(time(NULL));

	for(i=0; i<53;i++)
	{
		strcpy(barAux[i],"0");
	}

	if (bar==NULL)
	{
 		return EMB_CondRetBaralhoInvalido;
	}

	for (i=0; i<52; i++)
	{
 		n= rand()%51;

		while( !strcmp(bar[n],"0"))
		{
			n++;
			if( n>51)
				n=0;
		}
		
		EMB_CopiaMarca(bar[n],barAux[i]);
	}

	for (i=0;i<51;i++)
	{
		strcpy(bar[i],barAux[i]);
	}

	if (bar==NULL)
	{
		return EMB_CondRetErroNoEmbaralhamento;
	}

	return EMB_CondRetOK;
 }

