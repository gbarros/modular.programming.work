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
 *   6       lg   01/dez/2013 Função de deturpação e Verifica Lista
 *   5       gb   24/nov/2013 Inicio da inserção dos códigos de AutoVerificação
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

#define LISTA_OWN
#include "LISTA.h"
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


/********DADOS encaspulados no módulo *******/

#ifdef _DEBUG
static char EspacoLixo[ 256 ] =
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
/* Espaço de dados lixo usado ao testar */

#endif
/******* Elementos de Controle da Lista de Espaços Alocados****/
static int estaInicializado=0; //0 se nunca foi criado e 1 se já foi
static LIS_tppLista memAlocada=NULL;


/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento(LIS_tppLista pLista,tpElemLista * pElem);

static tpElemLista * CriarElemento(LIS_tppLista pLista,void * pValor);

static void LimparCabeca(LIS_tppLista pLista);
static void DeletarElementoLEA(tpElemLista pElem);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: LIS  &Criar lista
 *  ****/

LIS_tppLista LIS_CriarLista(void ( * ExcluirValor) (void * pDado)) {

    LIS_tpLista * pLista = NULL;
    LIS_tpCondRet condRet;   
    // Verifica se já foi criado a lista de espaços alocados e cria
    if (estaInicializado==0){
        memAlocada= (LIS_tppLista*) malloc(sizeof(LIS_tppLista));
        if (memAlocada==NULL){
            return NULL;
        }
        else{
            estaInicializado=1;
            LimparCabeca(memAlocada);
            memAlocada->ExcluirValor=NULL;            
        }
    }
   pLista = (LIS_tpLista *) malloc(sizeof ( LIS_tpLista));
    if (pLista == NULL) {
        return NULL;
    } /* if */

    LimparCabeca(pLista); 

    pLista->ExcluirValor = ExcluirValor;
    // Inclui esta Cabeça na Lista memAlocada
    IrFinalLista(memAlocada);
    condRet= LIS_InserirElementoApos(pLista);
    
/* Se não estiver em modo _DEBUG o erro não será tratado
 *  então o jogo deve ser abortado */    
#ifndef _PENSAR
    assert(condRet==LIS_CondRetOK);
#else
    retornoFuncao=condRet
#endif
    return pLista;

} /* Fim função: LIS  &Criar lista */

/***************************************************************************
 *
 *  Função: LIS  &Destruir lista
 *  *********************************************************************/

void LIS_DestruirLista(LIS_tppLista pLista) {

    LIS_EsvaziarLista(pLista);
    // Retira da lista de memória alocada
    LIS_ProcurarValor(memAlocada, pLista);
    LIS_ExcluirElemento(memAlocada);
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
    tpElemLista * pElem;
    /* Criar elemento a inserir antes */

    pElem = CriarElemento(pLista, pValor);
    if (pElem == NULL) {
        return LIS_CondRetFaltouMemoria;
    } /* if */

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

    /* Criar elemento a inerir após */

    pElem = CriarElemento(pLista, pValor);
    if (pElem == NULL) {
        return LIS_CondRetFaltouMemoria;
    } /* if */

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

    tpElemLista * pElem;

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

    if ((pLista->ExcluirValor != NULL)
            && (pElem->pValor != NULL)) {
        pLista->ExcluirValor(pElem->pValor);
    } /* if */
    
    free(pElem);

    pLista->numElem--;

} /* Fim função: LIS  -Liberar elemento da lista */
 /***********************************************************
  *
  *  $FC Função: LIS- Deletar elemento da Lista de Espaços Alocados
  * 
  *  $ED Descrição da Função:
  *    Retira o elemento da lista e libera o mesmo, sem contanto dar free()
  *    para o conteudo que o mesmo apontava (outro elemneto ou uma cabeça)
  * 
  *********************************************************/
LIS_tpCondRet DeletarElementoLEA(tpElemLista pValor){
    tpElemLista pElem;
    int bAchou;
    if (estaInicializado) {
        return LIS_CondRetExecucao;
    } 
    /* Inicia a busca pelo pElem */
        IrInicioLista(memAlocada);
    for (pElem = memAlocada->pElemCorr;
            pElem != NULL;
            pElem = pElem->pProx) {
        if (pElem->pValor == pValor) {
            memAlocada->pElemCorr = pElem;
            bAchou =1;
        }
    }
     if (!bAchou){
         return LIS_CondRetVazamentoMemoria;
     }
    
    /*Inicia a Deletamento*/
    pElem = memAlocada->pElemCorr;

    /* Desencadeia à esquerda */

    if (pElem->pAnt != NULL) {
        pElem->pAnt->pProx = pElem->pProx;
        memAlocada->pElemCorr = pElem->pAnt;
    } else {
        memAlocada->pElemCorr = pElem->pProx;
        memAlocada->pOrigemLista = memAlocada->pElemCorr;
    } /* if */

    /* Desencadeia à direita */

    if (pElem->pProx != NULL) {
        pElem->pProx->pAnt = pElem->pAnt;
    } else {
        memAlocada->pFimLista = pElem->pAnt;
    } /* if */
    
    return LIS_CondRetOK;
}/* Fim função: DeletarElemento LEA */

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

/****************************************
 *
 *  $FC Função : LIS - Deturpa os paramentros
 *  e a memória alocada de uma LISTA
 * 
 ****************************************/

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
        pLista->pOrigemLista = (LIS_tpLista*)(EspacoLixo);
    }

    // Anula ponteiro para o próximo elemento

    else if( tpModo == DeturpaAnulaProxElem )
    {
        pLista->pProx = NULL;
    }

    // Faz elemento corrente apontar para lixo

    else if ( tpModo == DeturpaCorrenteLixo )
    {
        pLista->pElemCorr = (LIS_tpLista*)(EspacoLixo);
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

    // Atribui valor de tamanho 1 byte maior do que o alocado
    
    else if( tpModo == DeturpaValor )
    {
        memcpy( &( pLista->pElemCorr->valor ) , "<<<<<" , 5 ) ;
    }
    
    else
    {
       return;
   }
  
    return;
}

/*******************************************************
 *
 * $FC Função: LIS - Verifica a integridade de uma LISTA
 * 
 ****************************************************/

 LIS_tpCondRet VerificaLista(LIS_tppLista cabecaLista)
{
    tpElemLista * pElem; 
    int i;

    if(cabecaLista == NULL)
    {
        TST_NotificarFalha( "Tentativa de verificar uma lista nula." );
        return LIS_CondRetEstruturaDados;
    } 

    while(i)
    {
        LIS_AvancarElementoCorrente(cabecaLista,1);
        i++;
    }

    if(i != numElem )
    {
        TST_NotificarFalha( "Quantidade de elementos na lista não condiz com a real." );
        return LIS_CondRetEstruturaDados;
    }

    pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )); 

    if ( pElem == NULL ) 
    { 
        TST_NotificarFalha( "Vazamento de memória." );
        return LIS_CondRetEstruturaDados;
    } 

    if(cabecaLista->pElemCorr != cabecaLista->pFimLista && cabecaLista->pElemCorr == NULL)
    {
        TST_NotificarFalha( "Lista possui elemento desencadeado." );
        return LIS_CondRetEstruturaDados;
    }

    if ( ! CED_VerificarEspaco(cabecaLista,NULL) )
    {
        TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
        return LLIS_CondRetEstruturaDados;
    } 

    return LIS_CondRetOK;
}
 
 /********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/