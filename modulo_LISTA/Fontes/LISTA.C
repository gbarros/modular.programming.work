/***************************************************************************
 *  $MCI Módulo de implementação: LIS Lista duplamente encadeada Autoverificável
 *
 *  Arquivo gerado:              LISTA.c
 *  Letras identificadoras:      LIS
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: avs
 *            gb
 *
 *  $HA Histórico de evolução:
 *  Versão  Autor    Data     Observações
 *   8       lg   01/dez/2013 Função de deturpação
 *   7       gb   30/nov/2013 Correções e intrumentação CESPEDIN
 *   6       gb   24/nov/2013 Continuação e lista de espaços alocados
 *   5       gb   18/nov/2013 Inicio da inserção dos códigos de AutoVerificação
 *   4       avs  01/fev/2006 criar linguagem script simbólica
 *   3       avs  08/dez/2004 uniformização dos exemplos
 *   2       avs  07/jul/2003 unificação de todos os módulos em um só projeto
 *   1       avs  16/abr/2003 início desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
#include "Generico.h"
#include "CESPDIN.H"
#include "CONTA.H"
#include "LISTA_INSTR.h"
#include "IdTiposEspaco.def"
#else
#include "LISTA.h"
#endif

#define LISTA_OWN

#include "TST_ESPC.H"
#undef LISTA_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: LIS Elemento da lista
 *
 *
 ***********************************************************************/

typedef struct tagElemLista {
    void * pValor;
    /* Ponteiro para o valor contido no elemento */

    struct tagElemLista * pAnt;
    /* Ponteiro para o elemento predecessor */

    struct tagElemLista * pProx;
    /* Ponteiro para o elemento sucessor */
    struct LIS_tagLista * pCabeca;
    /* Ponteiro para a Cabeca da Lista a qual o no pertence */

} tpElemLista;

/***********************************************************************
 *
 *  $TC Tipo de dados: LIS Descritor da cabeça de lista
 *
 *
 ***********************************************************************/

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

typedef enum{
    LIS_CabecaLista,
  /*Tipo da cabeca da Lista*/          
    LIS_ElemLista
  /*Tipo do Elemento Lista*/
};


/********DADOS encaspulados no módulo *******/

#ifdef _DEBUG
static char EspacoLixo[ 256 ] =
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
/* Espaço de dados lixo usado ao testar */

#endif

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento(LIS_tppLista pLista,tpElemLista * pElem);

static tpElemLista * CriarElemento(LIS_tppLista pLista,void * pValor);

static void LimparCabeca(LIS_tppLista pLista);

static LIS_tpCondRet VerificaElementoLista(LIS_tppLista cabecaLista,tpElemLista elemLista, int* count);

/*****  Código das funções exportadas pelo módulo  *****/

LIS_tpCondRet VerificaLista(LIS_tppLista cabecaLista);

/***************************************************************************
 *
 *  Função: LIS  &Criar lista
 *  ****/

LIS_tppLista LIS_CriarLista(void ( * ExcluirValor) (void * pDado)) {

    LIS_tpLista * pLista = NULL;
   pLista = (LIS_tpLista *) malloc(sizeof ( LIS_tpLista));
    if (pLista == NULL) {
        return NULL;
    } /* if */
#ifdef _DEBUG
   CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca) ;
#endif
    LimparCabeca(pLista); 

    pLista->ExcluirValor = ExcluirValor;
    
    return pLista;

} /* Fim função: LIS  &Criar lista */

/***************************************************************************
 *
 *  Função: LIS  &Destruir lista
 *  *********************************************************************/

void LIS_DestruirLista(LIS_tppLista pLista) {

    LIS_tpCondRet condRetVerifica;
    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return;

    LIS_EsvaziarLista(pLista);
    free(pLista);

} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
 *
 *  Função: LIS  &Esvaziar lista
 ***************************************************************************/

void LIS_EsvaziarLista(LIS_tppLista pLista) {

    tpElemLista * pElem;
    tpElemLista * pProx;
    LIS_tpCondRet cRetorno;
    LIS_tpCondRet condRetVerifica;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return;

#ifndef _PENSAR
    cRetorno=VerificaLista(pLista);
    assert(cRetorno==LIS_CondRetOK);
#else 
    retornoFuncao= cRetorno;
    if (cRetorno!=LIS_CondRetOK){
        return;
    }
#endif
    
    pElem = pLista->pOrigemLista;
    while (pElem != NULL) {
        pProx = pElem->pProx;
        LiberarElemento(pLista, pElem);
        pElem = pProx;
    } /* while */

    LimparCabeca(pLista);

} /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
 *
 *  Função: LIS  &Inserir elemento antes
 *  **********************************************/

LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista, void * pValor) {
    
    LIS_tpCondRet condRetVerifica;
    tpElemLista * pElem;
    
    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return condRetVerifica;
    
    /* Criar elemento a inserir antes */

    pElem = CriarElemento(pLista, pValor);

    /* Encadear o elemento antes do elemento corrente */

    if (pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    } else {
        if (pLista->pElemCorr->pAnt != NULL) {
            pElem->pAnt = pLista->pElemCorr->pAnt;
            pLista->pElemCorr->pAnt->pProx = pElem;
        } else {
            pLista->pOrigemLista = pElem;
        } /* if */

        pElem->pProx = pLista->pElemCorr;
        pLista->pElemCorr->pAnt = pElem;
    } /* if */

    pLista->pElemCorr = pElem;

    return LIS_CondRetOK;

} /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
 *
 *  Função: LIS  &Inserir elemento após
 ****************************************************/

LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista, void * pValor) {

    tpElemLista * pElem;
    LIS_tpCondRet condRetVerifica;


    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return condRetVerifica;

    /* Criar elemento a inserir após */

    pElem = CriarElemento(pLista, pValor);

    /* Encadear o elemento após o elemento */

    if (pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    } else {
        if (pLista->pElemCorr->pProx != NULL) {
            pElem->pProx = pLista->pElemCorr->pProx;
            pLista->pElemCorr->pProx->pAnt = pElem;
        } else {
            pLista->pFimLista = pElem;
        } /* if */

        pElem->pAnt = pLista->pElemCorr;
        pLista->pElemCorr->pProx = pElem;

    } /* if */

    pLista->pElemCorr = pElem;

    return LIS_CondRetOK;

} /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
 *
 *  Função: LIS  &Excluir elemento
 ***************************************************/

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista) {

    LIS_tpCondRet condRetVerifica;
    tpElemLista * pElem;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return condRetVerifica;

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
 ***************************************************************/

void * LIS_ObterValor(LIS_tppLista pLista) {

    if (pLista->pElemCorr == NULL) {
        return NULL; // Lista Vazia
    } /* if */
    return pLista->pElemCorr->pValor;

} /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
 *
 *  Função: LIS  &Ir para o elemento inicial
 *  ****/

void IrInicioLista(LIS_tppLista pLista) {

    LIS_tpCondRet condRetVerifica;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return;

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

    LIS_tpCondRet condRetVerifica;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return;

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

    LIS_tpCondRet condRetVerifica;
    int i;
    tpElemLista * pElem;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return condRetVerifica;

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

    LIS_tpCondRet condRetVerifica;
    tpElemLista * pElem;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return condRetVerifica;

    IrInicioLista(pLista);
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

    LIS_tpCondRet condRetVerifica;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return;

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
    
#ifndef _DEBUG
    assert(pElem!=NULL);
#else
    TST_ASSERT(pElem!=NULL);
    CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoNo ) ;
#endif
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

    LIS_tpCondRet condRetVerifica;

    condRetVerifica = VerificaLista(pLista);
    if(condRetVerifica != LIS_CondRetOK)
        return;

    pLista->pOrigemLista = NULL;
    pLista->pFimLista = NULL;
    pLista->pElemCorr = NULL;
    pLista->numElem = 0;

} /* Fim função: LIS  -Limpar a cabeça da lista */

/****************************************
 *
 *  $FC Função : LIS - Deturpa os paramentros
 *  e a memória alocada de uma LISTA
 * 
 ****************************************/

#ifdef _DEBUG

void DeturpaLista( LIS_tppLista  pLista, LIS_tpModosDeturpacao tpModo){
    
    // LIS_tpCondRet condRet; 
    // condRet= LIS_CondRetOK;

    if ( pLista == NULL )
    {
        return;
    }

    // Modifica o tipo da cabeça

    if( tpModo == DeturpaTipoCabeca )
    {
        CED_DefinirTipoEspaco(pLista,CED_ID_TIPO_VALOR_NULO);
    }

    // Modifica o tipo de elemento corrente

    else if( tpModo == DeturpaTipoNo )
    {
        CED_DefinirTipoEspaco(pLista->pElemCorr,CED_ID_TIPO_VALOR_NULO);
    }

    // Anula o ponteiro para a cabeça

    else if( tpModo == DeturpaCabecaNula  )
    {
        pLista->pOrigemLista = NULL;
    }

    // Faz raíz apontar para lixo

    else if( tpModo == DeturpaRaizLixo )
    {
        pLista->pOrigemLista = (tpElemLista*)(EspacoLixo);
    }

    // Faz elemento corrente apontar para lixo

    else if ( tpModo == DeturpaCorrenteLixo )
    {
        pLista->pElemCorr = (tpElemLista*)(EspacoLixo);
    }

    // Anula elemento corrente
    
    else if( tpModo == DeturpaCorrenteNulo )
    {
        pLista->pElemCorr = NULL;
    }

    // Deturpa o espaço da cabeça

    else if( tpModo == DeturparEspacoCabeca )
    {
        memcpy( ((char*)(pLista)) - 15 , "????" , 4 ) ;

    }

    // Deturpa o espaço de elemento corrente

    else if( tpModo == DeturparEspacoNo )
    {
        memcpy( ((char*)(pLista->pElemCorr)) - 15 , "????" , 4 ) ;
    }
    
    else
    {
       return;
   }
  
    return;
}

#endif

/*******************************************************
 *
 * $FC Função: LIS - Verifica a integridade de uma LISTA
 *
 *  $ED Descrição da Função:
 *    A função executa uma checagem completa de todas as assertivas, sejam 
 * funcionais ou não. São verificados:
 *  Integridade da cabeça: +se os ponteiros são de elementos próprios
 *                         +se o numero de elementos condiz
 *                         +se não há elementos desencadiados não liberados
 *                                                                (memory Leak)
 *  Integridade do nó:     +se o nó está corretamente encadiado
 *                         +se o nó pertence a lista em que está 
 ***********************************************************************/


 LIS_tpCondRet VerificaLista(LIS_tppLista cabecaLista){
     int qtdElems=0; //Contador de elementos
 /*Testa os ponteiros quanto ao tipo apontado*/
#ifdef _DEBUG

    if( cabecaLista==NULL)
    {
        CNT_Contar("CabecaListaInvalida",663);
        TST_NotificarFalha( "Tentou verificar cabeça inexistente.");
        return LIS_CondRetParam;
    }

     CED_MarcarEspacoAtivo(cabecaLista);
     
     if (TST_CompararInt(LIS_CabecaLista,
        CED_ObterTipoEspaco(cabecaLista->pElemCorr),
             "Tipo Errado apontado na cabeca" )!=TST_CondRetOK)
    {                
        CNT_Contar("ErroTipoCorrente",674);
        return LIS_CondRetEstruturaDados;
    }

     else if (TST_CompararInt(LIS_CabecaLista,
        CED_ObterTipoEspaco(cabecaLista->pOrigemLista),
       "Tipo Errado apontado na cabeca" )!=TST_CondRetOK)
     { 
        CNT_Contar("ErroTipoCabeca",682);              
        return LIS_CondRetEstruturaDados;
     }

     else if (TST_CompararInt(LIS_CabecaLista,
        CED_ObterTipoEspaco(cabecaLista->pFimLista),
       "Tipo Errado apontado na cabeca" )!=TST_CondRetOK)
    {  
       CNT_Contar("ErroTipoFinal",690);             
        return LIS_CondRetEstruturaDados;
    }

#endif     
     // condRet = VerificaElementoLista(cabecaLista,cabecaLista->pOrigemLista,
    //      &qtdElems);
     if(cabecaLista->numElem!=qtdElems){
#ifdef _DEBUG
        CNT_Contar("ErroNumElementos",699);
        TST_NotificarFalha("Erro numero de Elementos");
#endif
         return LIS_CondRetEstruturaDados;
     }  
     
    return LIS_CondRetOK;
}
/*******************************************************
 *
 * $FC Função: LIS - Verifica a integridade de um Elemento da LISTA
 *
 *  $ED Descrição da Função:
 *    A função executa uma checagem completa de todos os Elementos, recursivamente
 *
 *****************************************************************************/
 #ifdef _DEBUG
 
 LIS_tpCondRet VerificaElementoLista(LIS_tppLista cabecaLista,tpElemLista elemLista, int* count){
     LIS_tpCondRet condRet;

     CED_MarcarEspacoAtivo(elemLista.pValor);

     if (elemLista.pValor == NULL){
        CNT_Contar("ElementoNULL",723);
        return LIS_CondRetOK;
     }
     *count++;
     condRet= VerificaElementoLista(cabecaLista,elemLista,count );
     if (condRet!= LIS_CondRetOK)
     {
        CNT_Contar("ErroComElemento",730);
        return LIS_CondRetEstruturaDados;
     }
    else if ((elemLista.pAnt->pProx) != elemLista.pValor )
    {
        CNT_Contar("ErroPonteiroElemAnterior",735);
        return LIS_CondRetEstruturaDados;
    }
    else if(elemLista.pProx->pAnt != elemLista.pValor )
    {
        CNT_Contar("ErroPonteiroProxElem",740);
        return LIS_CondRetEstruturaDados;
    }
    else if(elemLista.pCabeca != cabecaLista)
    {
        CNT_Contar("ErroPonteiroCabeca",745);
        return LIS_CondRetEstruturaDados;
    }
    else if (TST_CompararInt(LIS_ElemLista,CED_ObterTipoEspaco(elemLista.pValor),"Tipo Errado" ) != TST_CondRetOK){
        CNT_Contar("ErroTipoElem",749);
        return LIS_CondRetEstruturaDados;
    }

    CNT_Contar("VerificarElemOK",753);
    return LIS_CondRetOK;
 }

  #endif
 /********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

