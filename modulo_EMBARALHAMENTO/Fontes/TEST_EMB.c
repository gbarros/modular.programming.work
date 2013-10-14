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

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "EMBARALHA.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     EMBRALHAR_BAR_CMD       "=criar"


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

         char baralho [53][4]={"A","2", "3","4","5","6","7","8","10","J","Q","K",
         "A","2", "3","4","5","6","7","8","10","J","Q","K",
         "A","2", "3","4","5","6","7","8","10","J","Q","K",
         "A","2", "3","4","5","6","7","8","10","J","Q","K","0"};

         char baralho2 [53][4]={"A","2", "3","4","5","6","7","8","10","J","Q","K",
         "A","2", "3","4","5","6","7","8","10","J","Q","K",
         "A","2", "3","4","5","6","7","8","10","J","Q","K",
         "A","2", "3","4","5","6","7","8","10","J","Q","K","0"};


         char ValorEsperado = '?'  ;
         char ValorObtido   = '!'  ;
         char ValorDado     = '\0' ;
         int  numLidos=0;
         TST_tpCondRet CondRet;
         int CondRetObtido   = 0 ;
        int CondRetEsperada = 0 ;
         if (strcmp(ComandoTeste, EMBRALHAR_BAR_CMD)){
            
            numLidos = LER_lerParametros("ii",&CondRetEsperada, &ValorDado);
            if (numLidos!=2){
               return TST_CondRetParm;
            }

            CondRet= EBL_embaralha(baralho);

            if (CondRet!=CondRetEsperada){
               return TST_CondRetErro;
            }
            return TST_CondRetOK;


         }


   }
   static TST_CompararInt(int a, int b){

      return a-b;
   }