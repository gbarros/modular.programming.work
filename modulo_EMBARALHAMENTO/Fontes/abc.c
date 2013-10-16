#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 


#define QTD 52
#define TAMANHO 4
#define TAMANHOSTRING 180
typedef enum {
	EMB_CondRetOK,
	// Concluiu corretamente
	EMB_CondRetBaralhoInvalido,
	// Recebeu um baralho inválido
	EMB_CondRetErroNoEmbaralhamento,
	// Erro na função de embaralhamento 
	EMB_CondRetErroNaReferencia
	//O Baralho Referencia
} EMB_tpCondRet ;


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
	pFile = fopen ("BaralhoReferencia.txt" , "r");

	if (pFile == NULL) 
			return EMB_CondRetErroNaReferencia;
	else {
	 if ( fgets (barRef , TAMANHOSTRING , pFile) != NULL ){
	 	fclose (pFile);
	 }
	 else
	 	return EMB_CondRetErroNaReferencia;
	}
	EMB_ConverteBaralhoStringChar(barRef, baralho);

	return EMB_CondRetOK;
}


EMB_tpCondRet EMB_Embaralha(char bar[QTD][TAMANHO]){
 
	char barAux[QTD][TAMANHO],
		 barRef [QTD][TAMANHO],
		 A[]="AC";
	int i,n,embEmbaralhou=0;

   //Altera a seed da função random (rand)
	srand(time(NULL));

	//Carrega o Baralho Referencia e testa para erros
	EMB_BarReferencia(barRef);

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
 		n= rand()%51;

		while( !strcmp(bar[n],"0"))
		{
			n++;
			if( n>51)
				n=0;
		}
		
		EMB_CopiaMarca(bar[n],barAux[i]);
	}


	// Copia o baralho embaralhado para a variavel de saida e verifica
	//se houve pelo menos uma mudança
	for (i=0;i<51;i++)
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

int main (void){
    //char baralho[QTD][TAMANHO];
    char baralho2 [QTD][TAMANHO];
    int i=0;

	EMB_BarReferencia(baralho2);

	printf("\n");

    for (i=0;i<QTD;i++){
  	 	printf("%s ",baralho2[i]);
   }

	printf ("\nErro ? no emb: %d \n", EMB_Embaralha(baralho2));

	printf("\n");

	for (i=0;i<QTD;i++){
	 	printf("%s ",baralho2[i]);
	}


	printf("\n oi ie!");
	return 0;


}