/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TEST_EXT.C
*  Letras identificadoras:      TEXT
*
*  Nome da base de software:    Teste automatizado do módulo Extra
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: FreeCell (INF1301)
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Barros, Noemie Nakamura e Leonardo Giroto
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1      LG   15/10/2013  Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Extra.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Extra:
*
*     =criar              - chama a função EXT_CriarColuna
*     =excluir            - chama a função EXT_ExcluirColuna
*     =verificarinserir   - chama a função EXT_VerificarInserirCarta
*     =verificarremover   - chama a função EXT_VerificarRemoverCarta
*     =inserir            - chama a função EXT_InserirCartaEmExtra
*     =remover            - chama a função EXT_RemoverCartaEmExtra
*     =exibir             - chama a função EXT_ExibirCartas
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "EXTRA.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_BAR_CMD                 "=criar"
#define     EXCLUIR_BAR_CMD               "=excluir"
#define     VERIFICARINSERIR_BAR_CMD      "=verificarinserir"
#define     VERIFICARREMOVER_BAR_CMD      "=verificarremover"
#define     INSERIR_BAR_CMD               "=inserir"
#define     REMOVER_BAR_CMD               "=remover"
#define     EXIBIR_BAR_CMD                "=exibir"

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
 // Something goes here...
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {
      int  numLidos = 0;
      TST_tpCondRet condRet;
      LIS_tppLista coluna;
      int ColunaEnviada;
      char* StringDada;
      int CondRetEsperada;


      if (strcmp(ComandoTeste,CRIAR_BAR_CMD)==0)
      {     
        // numLidos = LER_LerParametros("ii",&CondRetEsperada,&ValorDado); // -q

        // if (numLidos!=2)
           // return TST_CondRetParm;

        coluna = EXT_CriarColuna();

        if (condRet != CondRetOK)
           return TST_CondRetErro;

        return TST_CondRetOK;
      }
      else if(strcmp(ComandoTeste,INSERIR_BAR_CMD)==0)
      {
        // numLidos = LER_LerParametros("is",&CondRetEsperada,&StringDada); // -q²

        // if (numLidos!=2)
          // return TST_CondRetParm;

        condRet = EXT_InserirCartaEmExtra(coluna,carta1);

        if (condRet != CondRetOK)
           return TST_CondRetErro;

        condRet = EXT_InserirCartaEmExtra(coluna,NULL);

        if (condRet != CondRetCartaInvalida)
           return TST_CondRetErro;

        condRet = EXT_InserirCartaEmExtra(NULL,carta1);

        if (condRet != CondRetColunaInexistente)
           return TST_CondRetErro;

        return TST_CondRetOK;

      }
      else if(strcmp(ComandoTeste,VERIFICARINSERIR_BAR_CMD)==0)
      {
         numLidos = LER_LerParametros("isi",&ColunaEnviada,&StringDada,&CondRetEsperada);

         if (numLidos!=3)
           return TST_CondRetParm;

        condRet = EXT_VerificarInserirCarta(ColunaEnviada,StringDada);

        if (condRet != CondRetEsperada)
           return TST_CondRetErro;

        return TST_CondRetOK;

      }
      else if(strcmp(ComandoTeste,VERIFICARREMOVER_BAR_CMD)==0)
      {
        // numLidos = LER_LerParametros("is",&CondRetEsperada,&StringDada); // -q²

        // if (numLidos!=2)
          // return TST_CondRetParm;
      }
      else if(strcmp(ComandoTeste,REMOVER_BAR_CMD)==0)
      {
        // numLidos = LER_LerParametros("is",&CondRetEsperada,&StringDada); // -q²

        // if (numLidos!=2)
          // return TST_CondRetParm;
      }
      else if(strcmp(ComandoTeste,EXIBIR_BAR_CMD)==0)
      {
        // numLidos = LER_LerParametros("is",&CondRetEsperada,&StringDada); // -q²

        // if (numLidos!=2)
          // return TST_CondRetParm;
      }
      else if(strcmp(ComandoTeste,EXCLUIR_BAR_CMD)==0)
      {
        // numLidos = LER_LerParametros("is",&CondRetEsperada,&StringDada); // -q²

        // if (numLidos!=2)
          // return TST_CondRetParm;

        //condRet = EXT_ExcluirColunaExtra(coluna);

        // if (condRet != CondRetOK)
           //return TST_CondRetErro;

        // return TST_CondRetOK;
      }
      else
      {
        return TST_CondRetErro;
      }
   }