/* 
* $MCD Módulo de definição: Wrapper de Assertivas de LISTA
*       Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*       Gestor:  LES/DI/PUC-Rio
*       Autores: gb - Gabriel Barros
*                lg - Leonardo Giroto 
*		             nk - Noemie Nakamura
*     $HA Histórico de evolução:
*    Versão  Autor    Data     Observações
*      2      gb   24/nov/2013  Finalização do Wrapper 
*      1      gb   18/nov/2013 Inicio de desenvolvimento: Assertivas da LISTA
 * Created on 17 de Novembro de 2013, 12:04
 */

#if ! defined( LISTA_INSTR )
#define LISTA_INSTR

#if ! defined( LISTA_DET )
#define LISTA_DET

#if ! defined( LISTA_RET )
#define LISTA_RET

#ifdef LISTA_INSTR_OWN
   #define LISTA_INSTR_EXT
#else
   #define LISTA_INSTR_EXT extern
#endif

 #ifdef LISTA_DET_OWN
   #define LISTA_DET_EXT
#else
   #define LISTA_DET_EXT extern
#endif

 #ifdef LISTA_RET_OWN
   #define LISTA_RET_EXT
#else
   #define LISTA_RET_EXT extern
#endif

// Aqui vem as definicoes com _instr

typedef struct LIS_tagLista * LIS_tppLista;


typedef enum {
    LIS_CondRetOKINSTR,
    /* Concluiu corretamente */

    LIS_CondRetListaVaziaINSTR,
    /* A lista não contém elementos */

    LIS_CondRetFimListaINSTR,
    /* Foi atingido o fim de lista */

    LIS_CondRetNaoAchouINSTR,
    /* Não encontrou o valor procurado */

    LIS_CondRetFaltouMemoriaINSTR,
    /* Faltou memória ao tentar criar um elemento de lista */
            
    LIS_CondRetParamINSTR,
    /* Parametro de entrada errado ou NULL*/
            
    LIS_CondRetEstruturaDadosINSTR,
    /* Os dados estão corrompidos*/
   LIS_CondRetVazamentoMemoriaINSTR,
   /*Erro identificado quando há inconsistências no pareamento de dados com
     a lista de memória alocada*/
    LIS_CondRetExecucaoINSTR
    /*Erros associados a execução, possivelmente são erros 
     * de memória não identificáveis como tal*/
} LIS_tpCondRet;
   
   
   typedef enum {

         DeturpaTipoCabecaINSTR        =  1 ,
               /* Modifica o tipo da cabeça */

         DeturpaCabecaNulaINSTR        =  2 ,
               /* Anula ponteiro raiz */

         DeturpaCorrenteNuloINSTR      =  3 ,
               /* Anula ponteiro corrente */

         DeturpaRaizLixoINSTR         =  4 ,
               /* Faz raiz apontar para lixo */

         DeturpaCorrenteLixoINSTR      =  5 ,
               /* Faz corrente apontar para lixo */

         DeturpaTipoNoINSTR            =  6 ,
               /* Modifica tipo nó corrente */

         DeturparEspacoCabecaINSTR     =  7 ,
               /* Deturpa espaço da cabeca */

         DeturparEspacoNoINSTR         =  8
               /* Deturpa espaço do nó */

   } LIS_tpModosDeturpacao ;
   
   LIS_tppLista LIS_CriarListaINSTR(void(*ExcluirValor)( void * pDado));

   void LIS_DestruirListaINSTR( LIS_tppLista pLista ) ;

   void LIS_EsvaziarListaINSTR( LIS_tppLista pLista);

   LIS_tpCondRet LIS_InserirElementoAntesINSTR( LIS_tppLista pLista , void * pValor);

   LIS_tpCondRet LIS_InserirElementoAposINSTR( LIS_tppLista pLista , void * pValor);

   LIS_tpCondRet LIS_ExcluirElementoINSTR( LIS_tppLista pLista );

   void * LIS_ObterValorINSTR( LIS_tppLista pLista );

   void IrInicioListaINSTR( LIS_tppLista pLista );

   void IrFinalListaINSTR( LIS_tppLista pLista );

   LIS_tpCondRet LIS_ProcurarValorINSTR( LIS_tppLista pLista , void * pValor);


#if ! defined( LISTA_INSTR_OWN )
   #define  LIS_CriarLista              LIS_CriarListaINSTR
   #define  LIS_DestruirLista           LIS_DestruirListaINSTR
   #define  LIS_EsvaziarLista           LIS_EsvaziarListaINSTR
   #define  LIS_InserirElementoAntes    LIS_InserirElementoAntesINSTR
   #define  LIS_InserirElementoApos     LIS_InserirElementoAposINSTR
   #define  LIS_ExcluirElemento         LIS_ExcluirElementoINSTR
   #define  LIS_ObterValor              LIS_ObterValorINSTR
   #define  IrInicioLista               IrInicioListaINSTR
   #define  IrFinalLista                IrFinalListaINSTR
   #define  LIS_ProcurarValor           LIS_ProcurarValorINSTR
#endif

#if ! defined( LISTA_DET_OWN )
   #define  DeturpaTipoCabeca           DeturpaTipoCabecaINSTR
   #define  DeturpaCabecaNula           DeturpaCabecaNulaINSTR
   #define  DeturpaCorrenteNulo         DeturpaCorrenteNuloINSTR
   #define  DeturpaRaizLixo             DeturpaRaizLixoINSTR 
   #define  DeturpaCorrenteLixo         DeturpaCorrenteLixoINSTR
   #define  DeturpaTipoNo               DeturpaTipoNoINSTR
   #define  DeturparEspacoCabeca        DeturparEspacoCabecaINSTR
   #define  DeturparEspacoNo            DeturparEspacoNoINSTR
#endif

#if ! defined( LISTA_RET_OWN )
   #define  LIS_CondRetOK               LIS_CondRetOKINSTR
   #define  LIS_CondRetListaVazia       LIS_CondRetListaVaziaINSTR
   #define  LIS_CondRetFimLista         LIS_CondRetFimListaINSTR
   #define  LIS_CondRetNaoAchou         LIS_CondRetNaoAchouINSTR 
   #define  LIS_CondRetFaltouMemoria    LIS_CondRetFaltouMemoriaINSTR
   #define  LIS_CondRetParam            LIS_CondRetParamINSTR
   #define  LIS_CondRetEstruturaDados   LIS_CondRetEstruturaDadosINSTR
   #define  LIS_CondRetVazamentoMemoria LIS_CondRetVazamentoMemoriaINSTR
   #define  LIS_CondRetExecucao         LIS_CondRetExecucaoINSTR
#endif

#undef LISTA_INSTR_EXT
#endif

#undef LISTA_DET_EXT
#endif

#undef LISTA_RET_EXT
#endif