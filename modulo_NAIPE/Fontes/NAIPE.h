#if ! defined( NAIPE_ )
#define NAIPE_
/*******************************************************************************
*	$MCD Módulo de definição: NPE Naipe
*
*	Arquivo gerado:              NAIPE.h
*	Letras identificadoras:      NPE
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\MODULO_NAIPE.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão  Autor   Data			Observações
*	3		nk		14/out/2013		Inclusão de cabeçalhos, assertivas, novas funções
*	2 		lg		13/out/2013		Desenvolvimento
*	1		nk		11/out/2013		Criação do módulo com suas definições
*
*	$ED Descrição do módulo
*	Implementa as regras e funções básicas às colunas de carta do tipo que recebe
*	as cartas de um mesmo naipe em ordem crescente.
*	Consiste numa cabeça que pertence à lista principal e que pode ser referenciada
*	por um ponteiro. A lista principal terá 4 cabeças deste tipo.
*   Uma coluna pode estar vazia, isto é, conter zero cartas. Uma coluna pode conter
*	até 13 cartas do mesmo naipe. Uma coluna não tem um naipe definido até a primeira
*	carta ser inserida.
*******************************************************************************/

#if defined( NAIPE_OWN )
   #define NAIPE_EXT
#else
   #define NAIPE_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma coluna naipe */
typedef LIS_tppLista NPE_Coluna;
typedef char* Carta;

/***********************************************************************
*	$TC Tipo de dados: EXT Condições de retorno
***********************************************************************/

typedef enum {
	NPE_CondRetOK,
	// Concluiu corretamente
	NPE_CondRetColunaNaoExiste,
	// Coluna inexistente
	NPE_CondRetCartaNaoExiste,
	// Carta inexistente
	NPE_CondRetNaoPodeInserir,
	// Movimento de inserção não válido
	NPE_CondRetErroAoInserir,
	// Erro ao inserir carta na coluna
	NPE_CondRetErroAoExibir
	// Erro ao exibir as cartas das colunas de Extra
} NPE_tpCondRet ;

/***********************************************************************
*	$FC Função: NPE &Criar Coluna
*
*	$ED Descrição da função
*	Cria uma coluna (cabeça de lista) vazia.
*               
*	$FV Valor retornado
*	Se executou corretamente, retorna um ponteiro para a coluna criada.
*	Se ocorrer algum erro retorna NULL.
*
*	Assertivas
*	Entrada - Não existem. 
*
*	Saída - Deve retornar um ponteiro para a nova coluna. 
*			Se não, retorna NULL.
***********************************************************************/

NPE_Coluna NPE_CriarColunaNaipe(void);

/***********************************************************************
*	$FC Função: NPE &Excluir Coluna
*
*	$ED Descrição da função
*	Deleta a coluna.
*
*	$EP Parâmetros
*   coluna - Um ponteiro para a coluna que se quer destruir.                 
*
*	$FV Valor retornado
*	NPE_CondRet OK - Conseguiu destruir a coluna.
*	NPE_CondRetColunaInexistente - A coluna passada como parâmentro não existe
*   e, portanto não é excluída.
*	NPE_CondRetColunaNaoFoiDestruida - A coluna não foi destruída devido a
* 	um erro na função.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro.
*
*	Saída - Se executou corretamente, destrói a coluna fornecida.
*			Se não, retorna que a coluna não pôde ser destruída.
***********************************************************************/

NPE_tpCondRet NPE_DestruirColunaNaipe(NPE_Coluna coluna);

/***********************************************************************
*	$FC Função: NPE &Verificar Inserir Carta
*
*	$ED Descrição da função
*	Valida ou não inserção de uma carta do baralho em determinada coluna.
*
*	$EP Parâmetros
*   destino - Ponteiro para a coluna a receber a carta.
*	carta - A carta a ser inserida.
*
*	$FV Valor retornado
*	NPE_CondRetOK - É possível inserir a carta.
*	NPE_CondRetColunaNaoExiste - A coluna passada como parâmentro não existe.
*	NPE_CondRetCartaNaoExiste - A carta recebida não pertence ao baralho.
*	NPE_CondRetNaoPodeInserir - Não é uma inserção válida.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim como
*	uma carta que pertença ao baralho.
*
*	Saída - Se executou corretamente, valida a inserção. Caso contrário, 
*	retorna  a impossibilidade de inserção da carta na coluna.
***********************************************************************/
NPE_tpCondRet NPE_VerificarInserirCarta(NPE_Coluna destino, Carta carta);

/***********************************************************************
*	$FC Função: NPE &Inserir Carta
*
*	$ED Descrição da função
*	Insere uma carta em determinada coluna tipo naipe.
*
*	$EP Parâmetros
*   destino - Coluna onde se quer inserir a carta.
*	carta - Carta a qual se quer inserir.
*
*	$FV Valor retornado
*	NPE_CondRetOK - Inserção Realizada.
*	NPE_CondRetColunaNaoExiste - A coluna passada como parâmentro não existe.
*	NPE_CondRetCartaNaoExiste - A carta recebida não pertence ao baralho.
*	NPE_CondRetErroAoInserir - Erro na função que insere.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim
*	como uma carta.
*
*	Saída - Se executou corretamente, irá inserir a carta desejada na
*	coluna desejada. Caso contrário, retorna erro na inserção.
***********************************************************************/

NPE_tpCondRet NPE_InserirCartaEmNaipe(NPE_Coluna destino, Carta carta);

/***********************************************************************
*	$FC Função: NPE &Exibir Carta
*
*	$ED Descrição da função
*	Exibe a carta base (a carta no topo do bolo) de uma coluna tipo naipe.
*
*	$EP Parâmetros
*   coluna - Coluna cujas carta será exibida.
*
*	$FV Valor retornado
*	NPE_CondRetOK - Exibiu a carta.
*	NPE_CondRetColunaNaoExiste - A coluna passada como parâmentro não existe.
*	NPE_CondRetErroAoExibir - Erro na exibição.             
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro. 
*
*	Saída - Se executou corretamente, irá exibir todas a última carta que foi
*	inserida nesta coluna.
***********************************************************************/

NPE_tpCondRet NPE_ExibirCarta(NPE_Coluna coluna);

#undef NAIPE_EXT

/********** Fim do módulo de definição: NPE Naipe **********/

#else
#endif