// Todas as definições, semelhante a LISTA.C
//Invoca Lista.H, logo LISTA.C
// Invoca LISTA_INSTR.H

#include "LISTA.h"
#include <stdio.h>
#include   <assert.h>

#define LISTA_INSTR_OWN
#include "LISTA_INSTR.h"
#undef LISTA_INSTR_OWN

/***************************************************************************
 *
 *  Função: LIS  &Criar lista
 *  **********************************************************************/

LIS_tppLista LIS_CriarListaINSTR(void ( * ExcluirValor) (void * pDado)){
     LIS_tpLista * pLista = NULL;
    // Não há assertivas de entrada, é desnecessário e/ou inviável
     
    pLista = LIS_CriarLista(ExcluirValor);
    
    // Verificação de Retorno
    if(pLista==NULL )
        return NULL;
    else {
       if (pLista->pOrigemLista != NULL)
           return NULL;
       if ( pLista->pFimLista != NULL)
           return NULL;
       if(pLista->pElemCorr != NULL)
           return NULL;
       if( pLista->numElem = 0)
           return NULL;
       if ( pLista->ExcluirValor != ExcluirValor)
           return NULL;
        
    }
    return pLista;

} /* Fim função: LIS  &Criar lista INSTR */

/***************************************************************************
 *
 *  Função: LIS  &Destruir lista
 *  ************************************************************************/

void LIS_DestruirListaINSTR(LIS_tppLista pLista) {
    if(pLista == NULL){
#ifdef _DEBUG
        retornoFuncao= LIS_CondRetParam;
#endif
        return ; //??
    }
    LIS_DestruirLista(pLista);

   if(pLista != NULL){
#ifdef _DEBUG
        retornoFuncao = LIS_CondRetExecucao;
#endif
       return ;//??
   }
   else
       return pLista; //?? Null se tudo ocorreu corretamente     

} /* Fim função: LIS  &Destruir lista INSTR */

/***************************************************************************
 *
 *  Função: LIS  &Esvaziar lista
 *  ****/

void LIS_EsvaziarListaINSTR(LIS_tppLista pLista) {
    if(pLista == NULL) {
#ifdef _DEBUG
        retornoFuncao = LIS_CondRetParam;
#endif
        return; //$$CondRet
    }
    LIS_EsvaziarLista(pLista); 
// testa para condições pós execução    
#ifdef _DEBUG
    if ( retornoFuncao!= LIS_CondRetOK)
        return;
#endif
    
    IrInicioLista(pLista);
    
    if (LIS_ObterValor(pLista)!=NULL) {
#ifdef _DEBUG
        retornoFuncao = LIS_CondRetParam;
#endif
        return;//
    }
    else
#ifdef _DEBUG
        retornoFuncao = LIS_CondRetOK; // executou corretamente
#endif
        return ;// $$CondRet

} /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
 *
 *  Função: LIS  &Inserir elemento antes
 *  ****/

LIS_tpCondRet LIS_InserirElementoAntesINSTR(LIS_tppLista pLista, void * pValor) {
    LIS_tpCondRet resultado;
    if(pLista != NULL)
        return LIS_CondRetParam;
   resultado = LIS_InserirElementoAntes(pLista, pValor);
   assert(resultado==LIS_CondRetOK);   
  return resultado; 
 
} /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
 *
 *  Função: LIS  &Inserir elemento após
 *  ****/

LIS_tpCondRet LIS_InserirElementoAposINSTR(LIS_tppLista pLista, void * pValor) {
    LIS_tpCondRet resultado;
    if(pLista != NULL)
        return LIS_CondRetParam;
   resultado = LIS_InserirElementoApos(pLista, pValor);
   assert(resultado==LIS_CondRetOK);   
  return resultado; 

} /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
 *
 *  Função: LIS  &Excluir elemento
 *  ****/

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista) {

    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if (pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    } /* if */

    pElem = pLista->pElemCorr;

    /* Desencadeia à esquerda */

    if (pElem->pAnt != NULL) {
        pElem->pAnt->pProx = pElem->pProx;
        pLista->pElemCorr = pElem->pAnt;
    } else {
        pLista->pElemCorr = pElem->pProx;
        pLista->pOrigemLista = pLista->pElemCorr;
    } /* if */

    /* Desencadeia à direita */

    if (pElem->pProx != NULL) {
        pElem->pProx->pAnt = pElem->pAnt;
    } else {
        pLista->pFimLista = pElem->pAnt;
    } /* if */

    LiberarElemento(pLista, pElem);

    return LIS_CondRetOK;

} /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
 *
 *  Função: LIS  &Obter referência para o valor contido no elemento
 *  ****/

void * LIS_ObterValor(LIS_tppLista pLista) {

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if (pLista->pElemCorr == NULL) {
        return NULL;
    } /* if */

    return pLista->pElemCorr->pValor;

} /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
 *
 *  Função: LIS  &Ir para o elemento inicial
 *  ****/

void IrInicioLista(LIS_tppLista pLista) {

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pOrigemLista;

} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
 *
 *  Função: LIS  &Ir para o elemento final
 *  ****/

void IrFinalLista(LIS_tppLista pLista) {

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pFimLista;

} /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
 *
 *  Função: LIS  &Avançar elemento
 *  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista, int numElem) {

    int i;

    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    /* Tratar lista vazia */

    if (pLista->pElemCorr == NULL) {

        return LIS_CondRetListaVazia;

    } /* fim ativa: Tratar lista vazia */

    /* Tratar avançar para frente */

    if (numElem > 0) {

        pElem = pLista->pElemCorr;
        for (i = numElem; i > 0; i--) {
            if (pElem == NULL) {
                break;
            } /* if */
            pElem = pElem->pProx;
        } /* for */

        if (pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        } /* if */

        pLista->pElemCorr = pLista->pFimLista;
        return LIS_CondRetFimLista;

    }/* fim ativa: Tratar avançar para frente */

        /* Tratar avançar para trás */

    else if (numElem < 0) {

        pElem = pLista->pElemCorr;
        for (i = numElem; i < 0; i++) {
            if (pElem == NULL) {
                break;
            } /* if */
            pElem = pElem->pAnt;
        } /* for */

        if (pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        } /* if */

        pLista->pElemCorr = pLista->pOrigemLista;
        return LIS_CondRetFimLista;

    } /* fim ativa: Tratar avançar para trás */

    /* Tratar não avançar */

    return LIS_CondRetOK;

} /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
 *
 *  Função: LIS  &Procurar elemento contendo valor
 *  ****/

LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista, void * pValor) {

    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if (pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    } /* if */

    for (pElem = pLista->pElemCorr;
            pElem != NULL;
            pElem = pElem->pProx) {
        if (pElem->pValor == pValor) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        } /* if */
    } /* for */

    return LIS_CondRetNaoAchou;

} /* Fim função: LIS  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: LIS  -Liberar elemento da lista
 *
 *  $ED Descrição da função
 *     Elimina os espaços apontados pelo valor do elemento e o
 *     próprio elemento.
 *
 ***********************************************************************/

void LiberarElemento(LIS_tppLista pLista, tpElemLista * pElem) {

    if ((pLista->ExcluirValor != NULL)
            && (pElem->pValor != NULL)) {
        pLista->ExcluirValor(pElem->pValor);
    } /* if */

    free(pElem);

    pLista->numElem--;

} /* Fim função: LIS  -Liberar elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LIS  -Criar o elemento
 *
 ***********************************************************************/

tpElemLista * CriarElemento(LIS_tppLista pLista, void * pValor) {

    tpElemLista * pElem;

    pElem = (tpElemLista *) malloc(sizeof ( tpElemLista));
    if (pElem == NULL) {
        return NULL;
    } /* if */

    pElem->pValor = pValor;
    pElem->pAnt = NULL;
    pElem->pProx = NULL;

    pLista->numElem++;

    return pElem;

} /* Fim função: LIS  -Criar o elemento */

/***********************************************************************
 *
 *  $FC Função: LIS  -Limpar a cabeça da lista
 *
 ***********************************************************************/

void LimparCabeca(LIS_tppLista pLista) {

    pLista->pOrigemLista = NULL;
    pLista->pFimLista = NULL;
    pLista->pElemCorr = NULL;
    pLista->numElem = 0;

} /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de assertivas: LIS  Lista duplamente encadeada Auto Verificável**********/


