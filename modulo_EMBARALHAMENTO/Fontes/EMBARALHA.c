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
*   1       gb		12/out/2013		Início desenvolvimento
*    
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  

static void EBL_CopiaMarca (char* a, char* b);

int EBL_embaralha(char bar[53][4]){
 
	char barAux[53][4];
	int i,n;

	for(i=0; i<53;i++)
	{
		strcpy(barAux[i],"0");
	}

	if (bar==NULL)
	{
 		return -1;
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
		
		EBL_CopiaMarca(bar[n],barAux[i]);
	}

	for (i=0;i<51;i++)
	{
		strcpy(bar[i],barAux[i]);
	}

	if (bar==NULL)
	{
		return 1;
	}

	return 0;
 }

 static void EBL_CopiaMarca (char* a, char* b)
 {
		strcpy(b,a);
        strcpy(a,"0");
 } 