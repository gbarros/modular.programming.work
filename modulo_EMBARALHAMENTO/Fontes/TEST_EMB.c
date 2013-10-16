/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TEST_EMB.C
*  Letras identificadoras:      TEMB
*
*  Nome da base de software:    Teste automatizado do módulo Embaralhamento
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: FreeCell (INF1301)
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Barros, Noemie Nakamura e Leonardo Giroto
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   GB   15/10/2013 Coficação e Ajustes finais
*       2.00   GB   14/10/2013 Implementação Dumb para entender o funcionamento
*       1.00   GB   13/10/2013 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Embaralhamento.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Embaralhamento:
*
*     =criar        - chama a função EMB_Embaralha()
*    
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"
#include    "embaralha.h"



/* Tabela dos nomes dos comandos de teste específicos */
static const char EMBARALHAR_BAR_CMD     [ ] = "=embaralhar";

/* Constantes usadas na definição do projeto*/
#define  QTD 52
#define  TAMANHO 4
#define  TAMANHOSTRING 180

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TEMB Efetuar operações de teste específicas para o Embaralhamento
*
*  $ED Descrição da função
*     Efetua o comandos de teste específico para o módulo
*     embaralhamento sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/


 static void TE_ConverteBaralhoStringChar(char String[], char baralho[QTD][TAMANHO]){

   int i=0;
   char *pnome;
   pnome= strtok (String, ",");
   while(pnome!=NULL){
      strcpy (baralho[i],pnome);
      pnome= strtok (NULL, ",");
      i++;
   }

}
/* Inclue através de arquivo um modelo de baralho para possível embaralhamento
 Retorna 0 se executou perfeitamente ou -2 em caso de arquivo inexistente e -1 para arquivo vazio*/
 static int TE_BarRefEscolhida (char baralho [QTD][TAMANHO], char caminhoArquivo[]){

   FILE * pFile;
   char barRef [TAMANHOSTRING];
   pFile = fopen (caminhoArquivo , "r");

   if (TST_CompararPonteiroNulo(1,pFile, "Arquivo Nao Encontrado")== TST_CondRetErro) 
         return -2;

   else {

       if ( fgets (barRef , TAMANHOSTRING , pFile) != NULL ){
       }
       else{
         fclose (pFile);
         return -1;
      }
   }
   TE_ConverteBaralhoStringChar(barRef, baralho);
   fclose (pFile);

   return 0;
}






   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ){

         char baralhoDado[QTD][TAMANHO];
         char StringDada[30];
         int  numLidos=0;
         TST_tpCondRet CondRet;
        int CondRetEsperada = 0 ;



         if (strcmp(ComandoTeste, EMBARALHAR_BAR_CMD)==0){
            
            numLidos = LER_LerParametros("is",&CondRetEsperada, StringDada);
            if (numLidos!=2){
               return TST_CondRetParm;
            }
            //Se for 0 o baralho a ser usado é o referencia
           if (!strcmp (StringDada, "0")){
              strcpy(StringDada, "..\\Fontes\\BarRef.txt");
            }
            //Carrega o baralho escolhido
            CondRet=TE_BarRefEscolhida(baralhoDado,StringDada);

            if ( TST_CompararInt(0, CondRet, "Encontrei um arquivo vazio") ==TST_CondRetErro){
               return TST_CondRetParm;
            }
      
            //invoca da função a ser testada
            CondRet= EMB_Embaralha(baralhoDado);

           /// CondRet=0;
            if (TST_CompararInt(CondRetEsperada, CondRet, "Erro de execução!")==TST_CondRetErro){
               return TST_CondRetErro;
            }
            else
               return TST_CondRetOK;    

         }

         else
            return TST_CondRetNaoConhec;


   }
