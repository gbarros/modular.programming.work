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
	EMB_CondRetBaralhoInvalido
	// Recebeu um baralho inválido

} EMB_tpCondRet ;

/***********************************************************************
*	$FC Função: EMB
*
*	$ED Descrição da função
*	Recebe um baralho completo (52 cartas, 4 naipes) ordenado e o embaralha.
*
*	$EP Parâmetros
*   bar - Baralho a ser embaralhado.                 
*
*	$FV Valor retornado
*	EMB_CondRetOK - Conseguiu embaralhar.
*	EMB_CondRetBaralhoInvalido - Recebeu um baralho inválido e não embaralhou.
*
*	Assertivas
*	Entrada - O baralho deve ser um baralho válido, isto é, completo e
*	com todas as cartas distintas.
*	Saída - Se executado corretamente, as cartas do baralho devem estar numa
*	ordem distinta da ordem natural.
***********************************************************************/

EMB_CondRet EMB_embaralha(char bar[53][4]);

/********** Fim do módulo de definição: EMB Embaralhamento **********/

#else
#endif