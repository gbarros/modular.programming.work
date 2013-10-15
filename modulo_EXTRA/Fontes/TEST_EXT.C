/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "EXTRA.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_BAR_CMD       "=criar"
#define     EXCLUIR_BAR_CMD     "=excluir"

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string  CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {
      char carta = 0;
      int  numLidos = 0;
      TST_tpCondRet CondRet;

      if (strcmp(ComandoTeste,CRIAR_BAR_CMD)==0)
      {     
        numLidos = LER_LerParametros("ii",&CondRetEsperada,&ValorDado); // -q

        if (numLidos!=2)
           return TST_CondRetParm;

        CondRet = EXT_CriarColunaExtra(carta);

        if (CondRet != CondRetOK)
           return TST_CondRetErro;

        return TST_CondRetOK;
      }
      else if(strcmp(ComandoTeste,EXCLUIR_BAR_CMD)==0)
      {
        numLidos = LER_LerParametros("is",&CondRetEsperada,&StringDada); // -q²

        if (numLidos!=2)
          return TST_CondRetParm;

        CondRet = EXT_ExcluirColunaExtra(XXX); // -q³

        if (CondRet != CondRetOK)
           return TST_CondRetErro;

        return TST_CondRetOK;
      }

   }