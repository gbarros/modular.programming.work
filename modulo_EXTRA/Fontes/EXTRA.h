#if ! defined( EXTRA_ )
#define EXTRA_
/*******************************************************************************
*	$MCD Módulo de definição: EXT Extra
*
*	Arquivo gerado:              EXTRA.h
*	Letras identificadoras:      EXT
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\MODULO_EXTRA.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão  Autor   Data			Observações
*	5		nk		14/out/2013		Inclusão de cabeçalhos, assertivas, novas funções
*	4 	    lg		13/out/2013		Desenvolvimento
*	3		nk		11/out/2013		Mudança nomenclatura, definição de restrição inicial
*   2       gb      28/set/2013		Prosseguimento do desenvolvimento
*   1       gb, nk	25/set/2013		Início desenvolvimento, definição de funções
*
*	$ED Descrição do módulo
*	Implementa as regras e funções básicas às colunas de cartas do tipo que 
*	contém uma única carta.
*	Consiste numa cabeça que pertence à lista principal e que pode ser referenciada
*	por um ponteiro. Esta cabeça, por sua vez, é necessariamente composta de 4 colunas, 
*	conforme a restrição do jogo na disciplina. 
*   Uma coluna pode estar vazia, isto é, conter zero cartas. Uma coluna só pode
*	armazenar uma carta.
*******************************************************************************/

#if defined( EXTRA_OWN )
   #define EXTRA_EXT
#else
   #define EXTRA_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma coluna extra */
typedef LIS_tppLista EXT_Coluna;

/***********************************************************************
*	$TC Tipo de dados: EXT Condições de retorno
***********************************************************************/

typedef enum {
	EXT_CondRetOK,
	// Concluiu corretamente
	EXT_CondRetColunaNaoExiste,
	// Coluna inexistente
	EXT_CondRetNaoInsere,
	// Movimento de inserção não válido
	EXT_CondRetNaoRemove
	// Movimento de remoção não válido

} EXT_tpCondRet ;

/***********************************************************************
*	$FC Função: EXT &Criar Coluna
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

EXT_Coluna EXT_CriarColuna(void);

/***********************************************************************
*	$FC Função: EXT &Excluir Coluna
*
*	$ED Descrição da função
*	Deleta a coluna.
*
*	$EP Parâmetros
*   coluna - Um ponteiro para a coluna que se quer destruir.                 
*
*	$FV Valor retornado
*	EXT_CondRet OK - Conseguiu destruir.
*	EXT_CondRetColunaNaoExiste - A coluna passada como parâmentro não existe e
*	não é excluída.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro.
*
*	Saída - Se executou corretamente, destrói a coluna fornecida.
***********************************************************************/

EXT_tpCondRet EXT_ExcluirColuna(EXT_Coluna coluna);

/***********************************************************************
*	$FC Função: EXT &Verificar Inserir Carta
*
*	$ED Descrição da função
*	Valida ou não inserção de uma carta do baralho em determinada coluna.
*
*	$EP Parâmetros
*   destino - Ponteiro para a coluna a receber a carta.
*	carta - A carta a ser inserida.
*
*	$FV Valor retornado
*	EXT_CondRetOK - É possível.
*	EXT_CondRetColunaNaoExiste - A coluna passada como parâmentro não existe.
*	EXT_CondRetNaoInsere - Não é uma inserção válida.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim como
*	uma carta que pertença ao baralho.
*
*	Saída - Se executou corretamente, valida a inserção.
***********************************************************************/

EXT_tpCondRet EXT_VerificarInserirCarta(EXT_Coluna destino, Carta carta);

/***********************************************************************
*	$FC Função: EXT &Verificar Remover Carta
*
*	$ED Descrição da função
*
*	$ED Descrição da função
*	Valida ou não remoção de uma carta do baralho em determinada coluna.
*
*	$EP Parâmetros
*   origem - Ponteiro para a coluna a ter carta removida.
*	carta - A carta a ser removida
*
*	$FV Valor retornado
*	EXT_CondRetOK - É possível.
*	EXT_CondRetColunaNaoExiste - A coluna passada como parâmentro não existe.
*	EXT_CondRetNaoInsere - Não é uma remoção válida.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim como
*	uma carta que pertença ao baralho.
*
*	Saída - Se executou corretamente, valida a remoção.
***********************************************************************/

EXT_tpCondRet EXT_VerificarRemoverCarta(EXT_Coluna origem, Carta carta);

/***********************************************************************
*	$FC Função: EXT &Inserir Cartas Em Extra
*
*	$ED Descrição da função
*	Insere uma carta em determinada coluna.
*
*	$EP Parâmetros
*   destino - Coluna onde se quer inserir a carta.
*	carta - Carta a qual se quer inserir.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim
*	como uma carta.
*
*	Saída - Se executou corretamente, irá inserir a carta desejada na
*	coluna desejada.
***********************************************************************/

EXT_tpCondRet EXT_InserirCartaEmExtra(EXT_Coluna destino, Carta carta);

/***********************************************************************
*	$FC Função: EXT &Remover Cartas De Extra
*
*	$ED Descrição da função
*	Remove uma carta de determinada coluna.
*
*	$EP Parâmetros
*   origem - Coluna de onde se quer remover a carta.
*	carta - Carta a qual se quer inserir.
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro, assim
*	como uma carta.
*
*	Saída - Se executou corretamente, irá remover a carta desejada da
*	coluna desejada. A coluna da qual foi removida passará a ter uma
*	"carta nula" (0).
***********************************************************************/

EXT_tpCondRet EXT_InserirCartaEmExtra(EXT_Coluna destino, Carta carta);

/***********************************************************************
*	$FC Função: EXT &Exibir Cartas
*
*	$ED Descrição da função
*	Exibe todas as cartas das 4 colunas tipo extra.
*
*	$EP Parâmetros
*   coluna - Coluna cujas cartas serão exibidas.                 
*
*	Assertivas
*	Entrada - Deve-se passar uma coluna existente como parâmetro. 
*
*	Saída - Se executou corretamente, irá exibir todas as cartas presentes
*	na coluna escolhida na ordem em que estão dispostas.
***********************************************************************/

void EXT_ExibirCartas(EXT_Coluna coluna);

#undef EXTRA_EXT

/********** Fim do módulo de definição: EXT Extra **********/

#else
#endif