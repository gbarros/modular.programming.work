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
*	6		gb 		15/out/2013		Introdução de assertivas 
*	5 		lg		14/out/2013		Ajuste condições de retorno
*   4		nk		14/out/2013		Mudança de nomenclatura, correções 
*	3		gb 		13/out/2013		Teste do módulo
* 	2 		lg, gb  13/out/2013		Desenvolvimento
*   1       gb		12/out/2013		Início desenvolvimento
***************************************************************************/


#define EMBARALHA_OWN
#include "EMBARALHA.h"
#undef EMBARALHA_OWN

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

#define QTD 52
#define TAMANHO 4
#define TAMANHOSTRING 180


static void EMB_ConverteBaralhoStringChar (char String[], char baralho[QTD][TAMANHO]){
   int i=0;
   char *pnome;
   pnome= strtok (String, ",");
   while(pnome!=NULL){
 		strcpy (baralho[i],pnome);
 		pnome= strtok (NULL, ",");
 		i++;
	}

}

static void EMB_CopiaMarca (char* a, char* b)
{
		strcpy(b,a);
        strcpy(a,"0");
} 

static EMB_tpCondRet EMB_BarReferencia (char baralho [QTD][TAMANHO]){

        FILE * pFile;
        char barRef [TAMANHOSTRING];
        pFile = fopen ("BarRef.txt" , "r");

        if (pFile == NULL){ //Procura em outra pasta
        	pFile = fopen ("..\\Fontes\\BarRef.txt" , "r");
        	if (pFile==NULL)
            return EMB_CondRetErroNaReferencia;
        }

         if ( fgets (barRef , TAMANHOSTRING , pFile) != NULL ){
	        EMB_ConverteBaralhoStringChar(barRef, baralho);
	        fclose (pFile);
	        return EMB_CondRetOK;

         }
         else{
     		fclose (pFile);
             return EMB_CondRetErroNaReferencia;
        }
	}

EMB_tpCondRet EMB_Embaralha(char bar[QTD][TAMANHO]){
 
	char barAux[QTD][TAMANHO],
		 barRef [QTD][TAMANHO];
	int i,n,ref,embEmbaralhou=0;
	static int m=0;

   //Altera a seed da função random (rand)
	srand((int)time(NULL));

	//Carrega o Baralho Referencia e testa para erros
      ref=EMB_BarReferencia(barRef);
        if (ref==EMB_CondRetErroNaReferencia){
       
        	return EMB_CondRetErroNoEmbaralhamento;
		}

	//Seta o baralho auxiliar 
	for(i=0; i<QTD;i++){
		strcpy(barAux[i],"0");
	}

    //Testa o parametro de entrada para invalidade
	if (bar==NULL){	

 		return EMB_CondRetBaralhoInvalido;
	}
	//Se não condiz com o Baralho Referencia
	for (i=0;i<QTD;i++){

		if(strcmp(bar[i],barRef[i])){

			return EMB_CondRetBaralhoInvalido;
		}
	}


	//Inicia a operação de embaralhamento
	for (i=0; i<QTD; i++){
 		n= rand()%(QTD-1);

		while( !strcmp(bar[n],"0"))
		{
			n++;
			if( n>(QTD-1))
				n=0;
		}
		
		EMB_CopiaMarca(bar[n],barAux[i]);
	}

	// Copia o baralho embaralhado para a variavel de saida e verifica
	//se houve pelo menos uma mudança
	for (i=0;i<(QTD);i++)
	{
		if (strcmp(barAux[i], barRef[i])){
				embEmbaralhou++;
				strcpy(bar[i],barAux[i]);
		}
    // Protege contra erros de operação
		if ((bar==NULL)||(embEmbaralhou==0)){

			return EMB_CondRetErroNoEmbaralhamento;
		}

	}

		return EMB_CondRetOK;
 	
}