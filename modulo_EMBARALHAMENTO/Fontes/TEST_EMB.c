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
*       1.00   GB   13/10/2013 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Embaralhamento.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Embaralhamento:
*
*     =criar        - chama a função EBL_embaralha()
*    
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "EMBARALHA.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     EMBARALHAR_BAR_CMD       "=criar"
#define     VALIDAR_BAR_CMD         "=validar"


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/
 




   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ){

         char baralho [53][4]={"AC","2C", "3C","4C","5C","6C","7C","8C","9C","10C","JC","QC","KC",
         "AP","2P", "3P","4P","5P","6P","7P","8P","9P","10P","JP","QP","KP",
         "AO","2O", "3O","4O","5O","6O","7O","8O","9O","10O","JO","QO","KO",
         "AE","2E", "3E","4E","5E","6E","7E","8E","9E","10E","JE","QE","KE","0"};

       /*  char baralho2 [53][4]={"AC","2C", "3C","4C","5C","6C","7C","8C","9C","10C","JC","QC","KC",
         "AP","2P", "3P","4P","5P","6P","7P","8P","9P","10P","JP","QP","KP",
         "AO","2O", "3O","4O","5O","6O","7O","8O","9O","10O","JO","QO","KO",
         "AE","2E", "3E","4E","5E","6E","7E","8E","9E","10E","JE","QE","KE","0"};*/

         char baralhoDado[53][4];
         char StringDada[200];
         char ValorEsperado = '?'  ;
         char ValorObtido   = '!'  ;
         char ValorDado     = '\0' ;
         int  numLidos=0;
         TST_tpCondRet CondRet;
         int CondRetObtido   = 0 ;
        int CondRetEsperada = 0 ;



         if (strcmp(ComandoTeste, EMBARALHAR_BAR_CMD)==0){
            
            numLidos = LER_LerParametros("ii",&CondRetEsperada, &ValorDado);
            if (numLidos!=2){
               return TST_CondRetParm;
            }

            CondRet= EMB_embaralha(baralho);

            if (CondRet!=CondRetEsperada){
               return TST_CondRetErro;
            }
            return TST_CondRetOK;


         }
         else if ( strcmp(ComandoTeste,VALIDAR_BAR_CMD)==0){

            numLidos=LER_LerParametros("is",&CondRetEsperada,&StringDada);

            if (numLidos!=2){

               return TST_CondRetParm;
            }

            converteBaralhoStringChar(StringDada,baralhoDado);

            //Se é válida a entrada
            //Se embaralhou  
            //Se é valido na saida

            CondRet =EMB_embaralha(baralhoDado);

            if (CondRetEsperada==CondRet)
               return TST_CondRetOK;
            else {

               return TST_CondRetErro;
            }

            





         }

   }

   static void converteBaralhoStringChar(char String[], char baralho[53][4]){

      int i=0, 
          n=0,
          j=0;
      for (i=0; i<200; i++){

         if (String[i]==","){

            char[n][j]="\0";
               n++;
               j=0;
         }

         else
            char[n][j]=String[i];
            j++;


      }


   }