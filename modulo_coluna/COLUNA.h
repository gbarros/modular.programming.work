#if ! defined( COLUNA_ )
#define COLUNA_

/*******************************************************************************
*  $MCD Módulo de definição: COL Coluna
*
*  Arquivo gerado:              COLUNA.h
*  Letras identificadoras:      COL
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
*	1		nk		11/out/2013		Criação do módulo com suas definições
*
*  $ED Descrição do módulo
*	Implementa as regras e funções básicas às colunas de cartas.
*
*
*******************************************************************************/
#if defined( COLUNA_OWN )
   #define COLUNA_EXT
#else
   #define COLUNA_EXT extern
#endif