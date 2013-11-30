// Todas as definições, semelhante a LISTA.C
//Invoca Lista.H, logo LISTA.C
// Invoca LISTA_INSTR.H

#include "LISTA.h"
#include "Generico.h"
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
    
    TST_ASSERT(pLista!=NULL);
            
    LIS_DestruirLista(pLista);

   TST_ASSERT(pLista==NULL);  

} /* Fim função: LIS  &Destruir lista INSTR */

/***************************************************************************
 *
 *  Função: LIS  &Esvaziar lista
 *  ****/

void LIS_EsvaziarListaINSTR(LIS_tppLista pLista) {

    TST_ASSERT(pLista!=NULL);
    
    LIS_EsvaziarLista(pLista); 
    
    IrInicioLista(pLista);
    
    TST_ASSERT(LIS_ObterValor(pLista)!=NULL);//Se não for Nulo então não é vazia

} /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
 *
 *  Função: LIS  &Inserir elemento antes
 *************************************************************************/

LIS_tpCondRet LIS_InserirElementoAntesINSTR(LIS_tppLista pLista, void * pValor) {
    LIS_tpCondRet resultado;
    if(pLista != NULL)
        return LIS_CondRetParam;
   resultado = LIS_InserirElementoAntes(pLista, pValor);
   TST_ASSERT(resultado!=LIS_CondRetOK);   
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
   TST_ASSERT(resultado!=LIS_CondRetOK);   
   return resultado; 

} /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
 *
 *  Função: LIS  &Excluir elemento
 *******************************************************/

LIS_tpCondRet LIS_ExcluirElementoINSTR(LIS_tppLista pLista) {
    tpElemLista * pElem;
    LIS_tpCondRet condRet;
    if (pLista == NULL){
        return LIS_CondRetParam;
    }
    if (LIS_ObterValor(pLista)==NULL){
        return LIS_CondRetListaVazia;
    } /* if */

    condRet=LIS_ExcluirElemento(pLista);

    return condRet;

} /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
 *
 *  Função: LIS  &Obter referência para o valor contido no elemento
 *  ****/

void * LIS_ObterValorINSTR(LIS_tppLista pLista) {
    void * pRetorno;
    TST_ASSERT(pLista != NULL);
    pRetorno = LIS_ObterValor(pLista);
    return pRetorno;

} /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
 *
 *  Função: LIS  &Ir para o elemento inicial
 *  ****/

void IrInicioListaINSTR(LIS_tppLista pLista) {
    
    TST_ASSERT(pLista != NULL);
    IrInicioLista(pLista);

} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
 *
 *  Função: LIS  &Ir para o elemento final
 ***********************************************************************/

void IrFinalListaINSTR(LIS_tppLista pLista) {
    TST_ASSERT(pLista != NULL);
    IrFinalLista(pLista);
} /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
 *
 *  Função: LIS  &Avançar elemento INSTR
 *******************************************************************/

LIS_tpCondRet LIS_AvancarElementoCorrenteINSTR(LIS_tppLista pLista, int numElem) {
    
    TST_ASSERT(pLista != NULL);
    
    /* Tratar lista vazia */
    if (LIS_ObterValor(pLista) == NULL) {
        return LIS_CondRetListaVazia;
    } /* fim ativa: Tratar lista vazia */
    return LIS_AvancarElementoCorrente(pLista, numElem);

} /* Fim função: LIS  &Avançar elemento INSTR */

/***************************************************************************
 *
 *  Função: LIS  &Procurar elemento contendo valor INSTR
 *******************************************************************/

LIS_tpCondRet LIS_ProcurarValorINSTR(LIS_tppLista pLista, void * pValor) {
    TST_ASSERT(pLista != NULL);

    if (LIS_ObterValor(pLista) == NULL) {
        return LIS_CondRetListaVazia;
    }

    return LIS_ProcurarValor(pLista, pValor);

} /* Fim função: LIS  &Procurar elemento contendo valor */


/********** Fim do módulo de assertivas: LIS  Lista duplamente encadeada Auto Verificável**********/


