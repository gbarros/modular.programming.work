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
*       3      GB   16/10/2013  Desenvolvimento e verificação de corretude
*       2      LG   16/10/2013  Desenvolvimento
*       1      LG   15/10/2013  Início do desenvolvimento
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
static const char CRIAR_BAR_CMD               [ ] = "=criar";
static const char EXCLUIR_BAR_CMD             [ ] = "=excluir";
static const char VERIFICARINSERIR_BAR_CMD    [ ] = "=verificarinserir";
static const char VERIFICARREMOVER_BAR_CMD    [ ] = "=verificarremover";
static const char INSERIR_BAR_CMD             [ ] = "=inserir";
static const char REMOVER_BAR_CMD             [ ] = "=remover";
static const char EXIBIR_BAR_CMD              [ ] = "=exibir";


#define DIM_VT_EXT 5

/***** Protótipos das funções encapsuladas no módulo *****/

int VerificarIndex(int indexColuna);
TST_tpCondRet CarregaStringDada( char * String);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
* $FC Função: TLIS &Testar lista
*
* $ED Descrição da função
* Comandos de teste específicos para testar o módulo Extra:
*
* Comandos disponíveis:
*   =criar    <indexColuna>
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
static char cartasRecebidas[52][4];
static int indexCarta=0;

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {
      int  numLidos = -1;
      TST_tpCondRet condRet;
	    int indexColuna = -1;
      //int i=0, entrou=1;

      char StringDada[DIM_VT_EXT];
      int CondRetEsperada=0;

      if (strcmp(ComandoTeste,CRIAR_BAR_CMD)==0)
      {     
        numLidos = LER_LerParametros("ii",&indexColuna,&CondRetEsperada);

        if (numLidos!=2 || !VerificarIndex(indexColuna))
           return TST_CondRetParm;

        coluna[indexColuna] = EXT_CriarColunaExtra();

        return TST_CompararPonteiroNulo(1,coluna[indexColuna],"Erro ao criar coluna Extra.\n");

      }
      else if(strcmp(ComandoTeste,INSERIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);

        if (numLidos!=3 || !VerificarIndex(indexColuna))
          return TST_CondRetParm;
      
          if (CarregaStringDada( StringDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

        condRet = EXT_InserirCartaEmExtra(coluna[indexColuna],cartasRecebidas[indexCarta]);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao inserir carta em Extra.\n");

      }
      else if(strcmp(ComandoTeste,VERIFICARINSERIR_BAR_CMD)==0)
      {
         numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);
          if (CarregaStringDada( StringDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

         if (numLidos!=3 || !VerificarIndex(indexColuna))
           return TST_CondRetParm;

          condRet = EXT_VerificarInserirCarta(coluna[indexColuna],cartasRecebidas[indexCarta]);

          return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar inserção em Extra.\n");

      }
      else if(strcmp(ComandoTeste,VERIFICARREMOVER_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);
        if (numLidos!=3 || !VerificarIndex(indexColuna))
          return TST_CondRetParm;

        if (CarregaStringDada( StringDada)==TST_CondRetMemoria){
          return TST_CondRetMemoria;
        }

        condRet = EXT_VerificarRemoverCarta(coluna[indexColuna],cartasRecebidas[indexCarta]);

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar remoção de Extra.\n");

      }
      else if(strcmp(ComandoTeste,REMOVER_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("isi",&indexColuna,StringDada,&CondRetEsperada);

        if (numLidos!=3 || !VerificarIndex(indexColuna))
          return TST_CondRetParm;

        if (CarregaStringDada( StringDada)==TST_CondRetMemoria){
          return TST_CondRetMemoria;
        }

        condRet = EXT_RemoverCartaDeExtra(coluna[indexColuna],cartasRecebidas[indexCarta]);

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
*     0 - indexColuna não vale
*     1 - indexColuna vale
***********************************************************************/
int VerificarIndex(int indexColuna){
	if((indexColuna < 0) || (indexColuna > DIM_VT_EXT)){
		return 0;
	}
	return 1 ;
}

TST_tpCondRet CarregaStringDada( char * String){
   int i, entrou=1;

     for(i=0;i<52;i++){

           if (strcmp(String,cartasRecebidas[i])==0){
             indexCarta=i;
             entrou=0;
             break;
           }
        }
        if(entrou){ //Se não entrou no ultimo if
          for(i=0;i<52 && ( strlen(cartasRecebidas[i]) );i++);
            if(i==52){
              printf("Acabou a memória do vetor auxilar do modulo controlador de teste");
              return TST_CondRetMemoria;
            }
            indexCarta=i;
        }
         strcpy(cartasRecebidas[indexCarta],String);
         return TST_CondRetOK;
 }

/********** Fim do módulo de implementação: TNPE Teste coluna tipo extra **********/