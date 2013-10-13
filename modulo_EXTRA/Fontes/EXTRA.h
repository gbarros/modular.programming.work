#if ! defined( CEL_LIVRE_ )
#define CEL_LIVRE_

/*******************************************************************************
*  $MCD Módulo de definição: CLI Célula Livre
*
*  Arquivo gerado:              CEL_LIVRE.h
*  Letras identificadoras:      CLI
*
*  Nome da base de software:    Jogo FreeCell
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Gabriel Barros, Noemie Nakamura e Leonardo Giroto
*
*  $HA Histórico de evolução:
*	Versão  Autor   Data			Observações
*	4 	    lg		13/out/2013		Desenvolvimento
*	3		nk		11/out/2013		Mudança nomenclatura, definição de restrição inicial
*   2       gb      28/set/2013		Prosseguimento do desenvolvimento
*   1       gb, nk	25/set/2013		Início desenvolvimento, definição de funções
*
*  $ED Descrição do módulo
*	
*	Implementa as Regras e Funções básicas às colunas de cartas do tipo que 
*	contém uma única carta.
*
*	Permite a criação de até 4 colunas, conforme a restrição do jogo. 
*
*   Implementa uma abstração da estrutura de dados, tornando o uso uma 
*   simples questão de conjuntos de cartas organizadas.
*
*******************************************************************************/
#if defined( CEL_LIVRE_OWN )
   #define CEL_LIVRE_EXT
#else
   #define CEL_LIVRE_EXT extern
#endif

public CLI_Coluna CLI_CriaColuna (void);
public int CLI_ExcluirColuna( CLI_Coluna coluna );
public int CLI_InserirCarta ( CLI_Coluna destino, Carta carta);
public int CLI_ExcluirCarta (CLI_Coluna alvo, Carta carta);
static int ContarCartas (CLI_Coluna coluna);
