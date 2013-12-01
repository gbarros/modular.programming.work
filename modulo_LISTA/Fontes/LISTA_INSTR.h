/* 
* $MCD Módulo de definição: Wrapper de Assertivas de LISTA
*       Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*       Gestor:  LES/DI/PUC-Rio
*       Autores: gb - Gabriel Barros
*                lg - Leonardo Giroto 
*		 nk - Noemie Nakamura
*     $HA Histórico de evolução:
*    Versão  Autor    Data     Observações
*      1      GB   24/nov/2013 Inicio de desenvolvimento: Assertivas da LISTA
 * Created on 17 de Novembro de 2013, 12:04
 */

#if ! defined( LISTA_INSTR )
#define LISTA_INSTR

#ifdef LISTA_INSTR_OWN
   #define LISTA_INSTR_EXT
#else
   #define LISTA_INSTR_EXT extern
#endif

// Aqui vem as definicoes com _instr

typedef struct LIS_tagLista * LIS_tppLista;


typedef enum {
    LIS_CondRetOK,
    /* Concluiu corretamente */

    LIS_CondRetListaVazia,
    /* A lista não contém elementos */

    LIS_CondRetFimLista,
    /* Foi atingido o fim de lista */

    LIS_CondRetNaoAchou,
    /* Não encontrou o valor procurado */

    LIS_CondRetFaltouMemoria,
    /* Faltou memória ao tentar criar um elemento de lista */
            
    LIS_CondRetParam,
    /* Parametro de entrada errado ou NULL*/
            
    LIS_CondRetEstruturaDados,
    /* Os dados estão corrompidos*/
   LIS_CondRetVazamentoMemoria,
   /*Erro identificado quando há inconsistências no pareamento de dados com
     a lista de memória alocada*/
    LIS_CondRetExecucao
    /*Erros associados a execução, possivelmente são erros 
     * de memória não identificáveis como tal*/
} LIS_tpCondRet;
   
   
   typedef enum {

         DeturpaTipoCabeca        =  1 ,
               /* Modifica o tipo da cabeça */

         DeturpaCabecaNula        =  2 ,
               /* Anula ponteiro raiz */

         DeturpaCorrenteNulo      =  3 ,
               /* Anula ponteiro corrente */

         DeturpaRaizLixo          =  4 ,
               /* Faz raiz apontar para lixo */

         DeturpaCorrenteLixo      =  5 ,
               /* Faz corrente apontar para lixo */

         DeturpaTipoNo            =  6 ,
               /* Modifica tipo nó corrente */

         DeturpaValor             =  7 ,
               /* Atribui valor de tamanho 1 byte maior do que o alocado */

         DeturparEspacoCabeca     =  8 ,
               /* Deturpa espaço da cabeca */

         DeturparEspacoNo         =  9
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



#ifndefined( LISTA_INSTR_OWN )
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

#undef LISTA_INSTR_EXT

#endif
