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

#define DIM_VT_EXT 5

/***** Protótipos das funções encapsuladas no módulo *****/

int VerificarIndex(int indexColuna);

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

static EXT_Coluna coluna[DIM_VT_EXT] ;

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {
      int  numLidos = -1;
      TST_tpCondRet condRet;
	  int indexColuna = -1;
      char* StringDada = '\0';
      int CondRetEsperada;

      if (strcmp(ComandoTeste,CRIAR_BAR_CMD)==0)
      {     
        numLidos = LER_LerParametros("i",&CondRetEsperada);

        if (numLidos!=1 || !VerificarIndex(indexColuna))
           return TST_CondRetParm;

        coluna[indexColuna] = EXT_CriarColunaExtra();

        return TST_CompararPonteiroNulo(1,coluna[indexColuna],"Erro ao criar coluna Extra.\n");

      }
      else if(strcmp(ComandoTeste,INSERIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);

        if (numLidos!=3 || !VerificarIndex(indexColuna))
          return TST_CondRetParm;

        condRet = EXT_InserirCartaEmExtra(coluna[indexColuna],StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao inserir carta em Extra.\n");

      }
      else if(strcmp(ComandoTeste,VERIFICARINSERIR_BAR_CMD)==0)
      {
         numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);

         if (numLidos!=3 || !VerificarIndex(indexColuna))
           return TST_CondRetParm;

        condRet = EXT_VerificarInserirCarta(coluna[indexColuna],StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar inserção em Extra.\n");

      }
      else if(strcmp(ComandoTeste,VERIFICARREMOVER_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);

        if (numLidos!=3 || !VerificarIndex(indexColuna))
          return TST_CondRetParm;

        condRet = EXT_VerificarRemoverCarta(coluna[indexColuna],StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar remoção de Extra.\n");

      }
      else if(strcmp(ComandoTeste,REMOVER_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);

        if (numLidos!=3 || !VerificarIndex(indexColuna))
          return TST_CondRetParm;

        condRet = EXT_RemoverCartaDeExtra(coluna[indexColuna],StringDada);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao remover carta de Extra.\n");

      }
      else if(strcmp(ComandoTeste,EXIBIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("ii",&indexColuna,&CondRetEsperada);

        if (numLidos!=2|| !VerificarIndex(indexColuna))
          return TST_CondRetParm;

        condRet = EXT_ExibirCartas(coluna[indexColuna]);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao exibir.\n");

      }
      else if(strcmp(ComandoTeste,EXCLUIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("ii",&indexColuna,&CondRetEsperada);

        if (numLidos!=2|| !VerificarIndex(indexColuna))
          return TST_CondRetParm;

        condRet = EXT_ExcluirColunaExtra(coluna[indexColuna]);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao destruir coluna.\n");

      }
	return TST_CondRetNaoConhec;
}

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*  $FC Função: TNPE - Verificar índice de coluna tipo naipe
*
*  $FV Valor retornado
*     0 - inxArvore não vale
*     1 - inxArvore vale
***********************************************************************/
int VerificarIndex(int indexColuna){
	if((indexColuna < 0) || (indexColuna > DIM_VT_EXT)){
		return 0;
	}
	return 1 ;
}

/********** Fim do módulo de implementação: TNPE Teste coluna tipo extra **********/