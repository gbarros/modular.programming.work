/* 
 * File:   LISTA_INSTR.h
 * Author: Gabriel
 *
 * Created on 17 de Novembro de 2013, 12:04
 */

#if ! defined( LISTA_INSTR )
#define LISTA_INSTR

#ifdef LISTA_INSTR_OWN
   #define LISTA_INSTR_EXT
#else
   #define LISTA_INSTR_EXT extern
#endif

typedef struct tagElemLista {
    void * pValor;
    /* Ponteiro para o valor contido no elemento */

    struct tagElemLista * pAnt;
    /* Ponteiro para o elemento predecessor */

    struct tagElemLista * pProx;
    /* Ponteiro para o elemento sucessor */

} tpElemLista;

typedef struct LIS_tagLista {
    tpElemLista * pOrigemLista;
    /* Ponteiro para a origem da lista */

    tpElemLista * pFimLista;
    /* Ponteiro para o final da lista */

    tpElemLista * pElemCorr;
    /* Ponteiro para o elemento corrente da lista */

    int numElem;
    /* Número de elementos da lista */

    void ( * ExcluirValor) (void * pValor);
    /* Ponteiro para a função de destruição do valor contido em um elemento */

} LIS_tpLista;




// Aqui vem as definicoes com _instr




#if !defined( LISTA_INSTR_OWN )


   #define  Somar  SomarInstr




#endif

#undef LISTA_INSTR_EXT

#endif
