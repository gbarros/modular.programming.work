#if ! defined( EMBARALHA_ )
#define EMBARALHA_

/*******************************************************************************
*	$MCD Módulo de definição: EMB Embaralhamento
*
*	Arquivo gerado:              EMBARALHA.h
*	Letras identificadoras:      EMB
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão  Autor   Data			Observações
*   1       gb		12/out/2013		Início desenvolvimento
*	2		nk		14/out/2013		Inclusão de funções, cabeçalhos, correções	
*
*	$ED Descrição do módulo
*	Recebe uma sequência representando baralho ordenado e retorna esta sequência
*	embaralhada.
*******************************************************************************/

#if defined( EMBARALHA_OWN )
   #define EMBARALHA_EXT
#else
   #define EMBARALHA_EXT extern
#endif

#undef EMBARALHA_EXT

/***********************************************************************
*	$TC Tipo de dados: EMB Condições de retorno
*
*	$ED Descrição do tipo
*   Condições de retorno das funções de embaralhamento.
***********************************************************************/

typedef enum {
	EMB_CondRetOK
	// Concluiu corretamente

} EMB_tpCondRet ;

/***********************************************************************
*	$FC Função: EMB
*
*	$ED Descrição da função
*
*
*	$EP Parâmetros
*                    
*
*	$FV Valor retornado
*
*
*	Assertivas
*	Entrada - 
*
*	Saída - 
*
***********************************************************************/

/********** Fim do módulo de definição: EMB Embaralhamento **********/

#else
#endif