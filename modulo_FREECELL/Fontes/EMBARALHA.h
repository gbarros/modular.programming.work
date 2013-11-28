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
*	3		lg		14/out/2013		Ajuste condições de retorno
*	4		gb		15/out/2013     Implementação do código
*	5 		lg 		16/out/2013		Ajuste das condições de retorno e cabeçalhos
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

#define QTD 52
#define TAMANHO 4
/***********************************************************************
*	$TC Tipo de dados: EMB Condições de retorno
*
*	$ED Descrição do tipo
*   Condições de retorno das funções de embaralhamento.
***********************************************************************/

typedef enum {
	EMB_CondRetOK,
	// Concluiu corretamente
	EMB_CondRetBaralhoInvalido,
	// Recebeu um baralho inválido
	EMB_CondRetErroNoEmbaralhamento,
	// Erro na função de embaralhamento 
	EMB_CondRetErroNaReferencia,
	// Erro no caminho para o baralho de referência
} EMB_tpCondRet ;

/***********************************************************************
*	$FC Função: EMB_Embaralha
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
* 	EMB_CondRetErroNoEmbaralhamento - Deu erro na função que executa o
*	embaralhamento.
*	EMB_CondRetErroNaReferencia - O caminho para o baralho de referência está
*	errado.
*
*	Assertivas
*	Entrada - O baralho deve ser um baralho válido, isto é, completo e
*	com todas as cartas distintas.
*	Saída - Se executado corretamente, as cartas do baralho devem estar numa
*	ordem distinta da ordem natural.
***********************************************************************/

EMB_tpCondRet EMB_Embaralha(char bar[QTD][TAMANHO]);

/********** Fim do módulo de definição: EMB Embaralhamento **********/

#else
#endif