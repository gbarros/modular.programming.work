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
*   1       gb		12/out/2013		Início desenvolvimento
*	2		nk		14/out/2013		Mudança de nomenclatura, correções
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EMB_tpCondRet EMB_embaralha(char ** bar){
 	char barAux[52][3];
 	int i, n;
 	
	if (bar == NULL){
 		return -1; 
 	}

 	for (i = 0; i < 52; i++){
 		n = rand()%52;
 	 	
		while(!strc('0', bar[n])){ //Se não encontrou carta		
 	 		n++;
 	 	}
 	 	
		EMB_CopiaMarca(bar[n],barAux[i]);//copia e marca com 0 o elemento já copiado
 	}
 	
	for (i = 0; i < 52; i++){
 		strcpy(bar[i],barAux[i]);
 	}


	if ( bar == NULL){
 		return 1;
 	}
 	return 0;

 }

 static void EMB_CopiaMarca (char a[], char b[]){
 		char aux[3];
 		strcpy(b,a);
 		strcpy(a,'0');
 }