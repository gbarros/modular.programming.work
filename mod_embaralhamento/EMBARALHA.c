

#include <stdio.h>
#include <string.h>

 int EBL_embaralha(char ** bar){

 	char barAux[52][3];
 	int i,n;
 	if (bar==NULL){

 		return -1; 
 	}

 	for (i=0; i<52; i++){

 		n= rand()%52;
 	 	while(!strcmp('0', bar[n])){ //Se não encontrou carta		
 	 		n++;
 	 	}
 	 	EBL_CopiaMarca(bar[n],barAux[i]);//copia e marca com 0 o elemento já copiado
 	}
 	for (i=0;i<52;i++){

 		strcpy(bar[i],barAux[i]);
 	}


	if ( bar == NULL){

 		return 1;
 	}
 	return 0;

 }
 static void EBL_CopiaMarca (char a[], char b[]){

 		char aux[3];
 		strcpy(b,a);
 		strcpy(a,'0');
 }