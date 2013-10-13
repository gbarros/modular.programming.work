#if ! defined( EXTRA_ )
#define EXTRA_

/*******************************************************************************
*  $MCD Módulo de definição: EXT Célula Extra
*
*  Arquivo gerado:              EXTRA.h
*  Letras identificadoras:      EXT
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
#if defined( EXTRA_OWN )
   #define EXTRA_EXT
#else
   #define EXTRA_EXT extern
#endif

EXT_Coluna EXT_CriaColuna (void);
int EXT_ExcluirColuna(EXT_Coluna coluna);
int EXT_InserirCarta (EXT_Coluna destino, Carta carta);
int EXT_ExcluirCarta (EXT_Coluna alvo, Carta carta);
