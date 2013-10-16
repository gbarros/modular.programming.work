#if ! defined( SEQ_VIS_ )
#define SEQ_VIS_
/*******************************************************************************
*	$MCD Módulo de definição: SV Sequência Visível
*
*	Arquivo gerado:              SEQ_VIS.c
*	Letras identificadoras:      SV
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\MODULO_SEQ_VIS.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão  Autor   Data			Observações
*	4		lg		14/out/2013		Atualização de condições de retorno e ajustes
*	3		nk		14/out/2013		Inclusão de cabeçalhos, assertivas, novas funções
*	2  		lg		13/out/2013		Realização das definições
*	1		nk		11/out/2013		Criação do módulo com suas definições
*
*	$ED Descrição do módulo
*	Implementa as regras e funções básicas às sequências visíveis de cartas.
*	Consiste numa cabeça que pertence à lista principal e que pode ser referenciada
*	por um ponteiro. A lista principal terá 8 cabeças deste tipo.
*   Uma coluna pode estar vazia, isto é, conter zero cartas. Uma coluna pode conter
*	várias cartas.
*******************************************************************************/

#if defined( SEQ_VIS_OWN )
   #define SEQ_VIS_EXT
#else
   #define SEQ_VIS_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma sequência visível */
typedef char* Carta;
typedef LIS_tppLista SV_Coluna;

/***********************************************************************
*	$TC Tipo de dados: SV Condições de retorno
***********************************************************************/

typedef enum {
	SV_CondRetOK,
	// Concluiu corretamente
	SV_CondRetColunaNaoExiste,
	// Coluna inexistente
	SV_CondRetCartaNaoExiste,
	// Carta inexistente
	SV_CondRetColunaVazia,
	// Coluna está vazia
	SV_CondRetNaoPodeInserir,
	// Movimento de inserção não válido
	SV_CondRetNaoPodeRemover,
	// Movimento de remoção não válido
	SV_CondRetErroAoInserir,
	// Erro ao inserir carta na coluna
	SV_CondRetErroAoRemover,
	// Erro ao remover carta da coluna
	SV_CondRetErroAoExibir
	// Erro ao exibir as cartas da coluna
} SV_tpCondRet;

/***********************************************************************
*	$FC Função: SV &Criar Coluna
*
*	$ED Descrição da função
*	Cria uma coluna (cabeça de lista) vazia.
*               
*	$FV Valor retornado
*	SV_Coluna - Ponteiro para coluna criada.
*
*	Assertivas
*	Entrada - Não existem entradas. 
*
*	Saída - Deve retornar um ponteiro para a nova coluna. 
*			Se não, retorna NULL.
***********************************************************************/

SV_Coluna SV_CriarColunaSeqVis(void); 

/***********************************************************************
*	$FC Função: SV &Excluir Coluna
*
*	$ED Descrição da função
*	Deleta a coluna.
*
*	$EP Parâmetros
*   coluna - Um ponteiro para a coluna que se quer destruir.                 
*
*	$FV Valor retornado
*	SV_CondRetOK - Conseguiu destruir.
*	SV_CondRetColunaInexistente - A coluna passada como parâmentro não existe
*	e, portanto, não é excluída.
*	SV_CondRetColunaNaoFoiDestruida - Erro ao destruir a coluna.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro.
*
*	Saída - Se executou corretamente, destrói a coluna fornecida.
***********************************************************************/

SV_tpCondRet SV_ExcluirColunaSeqVis(SV_Coluna coluna);

/***********************************************************************
*	$FC Função: SV &Verificar Inserir Carta
*
*	$ED Descrição da função
*	Valida ou não inserção de uma carta do baralho em determinada coluna.
*
*	$EP Parâmetros
*   destino - Ponteiro para a coluna a receber a carta.
*	carta - A carta a ser inserida.
*
*	$FV Valor retornado
*	SV_CondRetOK - É possível.
*	SV_CondRetColunaInexistente - A coluna passada como parâmentro não existe.
*	SV_CondRetNaoInsere - Não é uma inserção válida.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim como
*	uma carta que pertença ao baralho.
*
*	Saída - Se executou corretamente, valida a inserção.
***********************************************************************/

SV_tpCondRet SV_VerificarInserirCarta(SV_Coluna destino, Carta carta);

/***********************************************************************
*	$FC Função: SV &Verificar Remover Carta
*
*	$ED Descrição da função
*	Valida ou não remoção de uma carta do baralho em determinada coluna.
*
*	$EP Parâmetros
*   origem - Ponteiro para a coluna a ter carta removida.
*	carta - A carta a ser removida
*
*	$FV Valor retornado
*	SV_CondRetOK - É possível.
*	SV_CondRetColunaInexistente - A coluna passada como parâmentro não existe.
*	SV_CondRetNaoInsere - Não é uma remoção válida.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim como
*	uma carta que pertença ao baralho.
*
*	Saída - Se executou corretamente, valida a remoção.
***********************************************************************/

SV_tpCondRet SV_VerificarRemoverCarta(SV_Coluna origem, Carta carta);

/***********************************************************************
*	$FC Função: SV &Inserir Cartas Em Sequência Visível
*
*	$ED Descrição da função
*	Insere uma carta em determinada coluna.
*
*	$EP Parâmetros
*   destino - Coluna onde se quer inserir a carta.
*	carta - Carta a qual se quer inserir.
*
*	$FV Valor retornado
*	???
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim
*	como uma carta.
*
*	Saída - Se executou corretamente, irá inserir a carta desejada na
*	coluna desejada.
***********************************************************************/

SV_tpCondRet SV_InserirCartaEmSeqVis(SV_Coluna destino, Carta carta);

/***********************************************************************
*	$FC Função: SV &Remover Cartas De Sequência Visível
*
*	$ED Descrição da função
*	Remove uma carta de determinada coluna.
*
*	$EP Parâmetros
*   origem - Coluna de onde se quer remover a carta.
*	carta - Carta a qual se quer inserir.
*
*	$FV Valor retornado
*	???
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim
*	como uma carta.
*
*	Saída - Se executou corretamente, irá remover a carta desejada da
*	coluna desejada. A coluna da qual foi removida passará a ter sua
*	última carta apontando para NULL.
***********************************************************************/

SV_tpCondRet SV_RemoverCartaDeSeqVis(SV_Coluna alvo, Carta carta);

/***********************************************************************
*	$FC Função: SV &Exibir Cartas
*
*	$ED Descrição da função
*	Exibe todas as cartas de determinada coluna tipo sequência visível.
*
*	$EP Parâmetros
*   coluna - Coluna cujas cartas serão exibidas.                 
*
*	$FV Valor retornado
*	???
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro. 
*
*	Saída - Se executou corretamente, irá exibir todas as cartas presentes
*	na coluna escolhida na ordem em que estão dispostas.
***********************************************************************/

void SEQ_VIS_ExibirCartas(EXT_Coluna coluna);

#undef SEQ_VIS_EXT

/********** Fim do módulo de definição: SEQ_VIS Sequência Visível **********/

#else
#endif