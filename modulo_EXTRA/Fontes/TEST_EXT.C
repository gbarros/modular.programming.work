/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TEST_EXT.C
*  Letras identificadoras:      TEXT
*
*  Nome da base de software:    Teste automatizado do m�dulo Extra
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: FreeCell (INF1301)
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Barros, Noemie Nakamura e Leonardo Giroto
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       3      GB   16/10/2013  Desenvolvimento e verifica��o de corretude
*       2      LG   16/10/2013  Desenvolvimento
*       1      LG   15/10/2013  In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo Extra.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo Extra:
*
*     =criar              - chama a fun��o EXT_CriarColunaExtra
*     =excluir            - chama a fun��o EXT_ExcluirColunaExtra
*     =verificarinserir   - chama a fun��o EXT_VerificarInserirCarta
*     =verificarremover   - chama a fun��o EXT_VerificarRemoverCarta
*     =inserir            - chama a fun��o EXT_InserirCartaEmExtra
*     =remover            - chama a fun��o EXT_RemoverCartaDeExtra
*     =exibir             - chama a fun��o EXT_ExibirCartas
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "EXTRA.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */
static const char CRIAR_BAR_CMD               [ ] = "=criar";
static const char EXCLUIR_BAR_CMD             [ ] = "=excluir";
static const char VERIFICARINSERIR_BAR_CMD    [ ] = "=verificarinserir";
static const char VERIFICARREMOVER_BAR_CMD    [ ] = "=verificarremover";
static const char INSERIR_BAR_CMD             [ ] = "=inserir";
static const char REMOVER_BAR_CMD             [ ] = "=remover";
static const char EXIBIR_BAR_CMD              [ ] = "=exibir";


#define DIM_VT_EXT 5
#define QTD_EXT 52
#define TAMANHO 4

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

int VerificarIndex(int indexColuna);
TST_tpCondRet CarregaStringDada( char * String);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
* $FC Fun��o: TLIS &Testar lista
*
* $ED Descri��o da fun��o
* Comandos de teste espec�ficos para testar o m�dulo Extra:
*
* Comandos dispon�veis:
*   =criar    <indexColuna>
*   - Chama a fun��o EXT_CriarColunaExtra()
*
* =verificarinserir   <Coluna> <String> <CondRetEsperada>
*   - Chama a fun��o EXT_VerificarInserirCarta()
*
* =verificarremover   <Coluna> <String> <CondRetEsperada>
*   - Chama a fun��o EXT_VerificarRemoverCarta()
*
* =inserir   <Coluna> <String> <CondRetEsperada>
*   - Chama a fun��o EXT_InserirCartaEmExtra()
*
* =remover   <Coluna> <String> <CondRetEsperada>
*   - Chama a fun��o EXT_RemoverCartaDeExtra()
*
* =exibir   <Coluna> <CondRetEsperada>
*   - Chama a fun��o EXT_ExibirCartas()
*
* =excluir  <Coluna> <CondRetEsperada>
*   - Chama a fun��o EXT_ExcluirColunaExtra()
***********************************************************************/

static EXT_Coluna coluna[DIM_VT_EXT] ;
static char cartasRecebidas[QTD_EXT][TAMANHO];
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

          return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar inser��o em Extra.\n");

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

        return TST_CompararInt(CondRetEsperada,condRet,"Erro ao verificar remo��o de Extra.\n");

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

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*  $FC Fun��o: TNPE - Verificar �ndice de coluna tipo naipe
*
*  $FV Valor retornado
*     0 - indexColuna n�o vale
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
        if(entrou){ //Se n�o entrou no ultimo if
          for(i=0;i<52 && ( strlen(cartasRecebidas[i]) );i++);
            if(i==52){
              printf("Acabou a mem�ria do vetor auxilar do modulo controlador de teste");
              return TST_CondRetMemoria;
            }
            indexCarta=i;
        }
         strcpy(cartasRecebidas[indexCarta],String);
         return TST_CondRetOK;
 }

/********** Fim do m�dulo de implementa��o: TNPE Teste coluna tipo extra **********/