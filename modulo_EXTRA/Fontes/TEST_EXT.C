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
*       2      LG   16/10/2013  Desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Extra.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Extra:
*
*     =criar              - chama a função EXT_CriarColunaExtra
*     =excluir            - chama a função EXT_ExcluirColunaExtra
*     =verificarinserir   - chama a função EXT_VerificarInserirCarta
*     =verificarremover   - chama a função EXT_VerificarRemoverCarta
*     =inserir            - chama a função EXT_InserirCartaEmExtra
*     =remover            - chama a função EXT_RemoverCartaDeExtra
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
* $FC Função: TLIS &Testar lista
*
* $ED Descrição da função
* Comandos de teste específicos para testar o módulo Extra:
*
* Comandos disponíveis:
*   =criar    <Coluna>
*   - Chama a função EXT_CriarColunaExtra()
*
* =verificarinserir   <Coluna> <String> <CondRetEsperada>
*   - Chama a função EXT_VerificarInserirCarta()
*
* =verificarremover   <Coluna> <String> <CondRetEsperada>
*   - Chama a função EXT_VerificarRemoverCarta()
*
* =inserir   <Coluna> <String> <CondRetEsperada>
*   - Chama a função EXT_InserirCartaEmExtra()
*
* =remover   <Coluna> <String> <CondRetEsperada>
*   - Chama a função EXT_RemoverCartaDeExtra()
*
* =exibir   <Coluna> <CondRetEsperada>
*   - Chama a função EXT_ExibirCartas()
*
* =excluir  <Coluna> <CondRetEsperada>
*   - Chama a função EXT_ExcluirColunaExtra()
***********************************************************************/

static EXT_Coluna coluna;

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {
      int  numLidos = 0;
      TST_tpCondRet condRet;
      int ColunaEnviada;
      char* StringDada;
      int CondRetEsperada;

      if (strcmp(ComandoTeste,CRIAR_BAR_CMD)==0)
      {     
        numLidos = LER_LerParametros("i",&CondRetEsperada);

        if (numLidos!=1)
           return TST_CondRetParm;

        coluna = EXT_CriarColunaExtra();

        return TST_CompararPonteiroNulo(1,coluna,"Erro ao criar coluna Extra.\n");

      }
      else if(strcmp(ComandoTeste,INSERIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&ColunaEnviada,&StringDada,&CondRetEsperada);

        if (numLidos!=3)
          return TST_CondRetParm;

        condRet = EXT_InserirCartaEmExtra(coluna,StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao inserir carta em Extra.\n");

      }
      else if(strcmp(ComandoTeste,VERIFICARINSERIR_BAR_CMD)==0)
      {
         numLidos = LER_LerParametros("isi",&ColunaEnviada,&StringDada,&CondRetEsperada);

         if (numLidos!=3)
           return TST_CondRetParm;

        condRet = EXT_VerificarInserirCarta(coluna,StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar inserção em Extra.\n");

      }
      else if(strcmp(ComandoTeste,VERIFICARREMOVER_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&ColunaEnviada,&StringDada,&CondRetEsperada);

        if (numLidos!=3)
          return TST_CondRetParm;

        condRet = EXT_VerificarRemoverCarta(coluna,StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar remoção de Extra.\n");

      }
      else if(strcmp(ComandoTeste,REMOVER_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&ColunaEnviada,&StringDada,&CondRetEsperada);

        if (numLidos!=3)
          return TST_CondRetParm;

        condRet = EXT_RemoverCartaDeExtra(coluna,StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao remover carta de Extra.\n");

      }
      else if(strcmp(ComandoTeste,EXIBIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("ii",&ColunaEnviada,&CondRetEsperada);

        if (numLidos!=2)
          return TST_CondRetParm;

        condRet = EXT_ExibirCartas(coluna);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao exibir.\n");

      }
      else if(strcmp(ComandoTeste,EXCLUIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("ii",&ColunaEnviada,&CondRetEsperada);

        if (numLidos!=2)
          return TST_CondRetParm;

        condRet = EXT_ExcluirColunaExtra(coluna);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao destruir coluna.\n");

      }
      else
      {
        return TST_CondRetErro;
      }
   }