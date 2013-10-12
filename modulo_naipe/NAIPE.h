#if ! defined( NAIPE_ )
#define NAIPE_

/*******************************************************************************
*  $MCD Módulo de definição: NPE Naipe
*
*  Arquivo gerado:              NAIPE.h
*  Letras identificadoras:      NPE
*
*  Nome da base de software:    Jogo FreeCell
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: [INF 1301] Implementação do Jogo FreCell para fins educacionais
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Gabriel Barros, Noemie Nakamura e Leonardo Giroto
*
*  $HA Histórico de evolução:
*	Versão  Autor   Data			Observações
*	1		nk		11/out/2013		Criação do módulo com suas definições
*
*  $ED Descrição do módulo
*     Implementa as Regras e Funções básicas às colunas de cartas do tipo que 
*    contém uma única carta.
*
*	  Permite a criação de até 4 colunas, conforme a restrição do jogo. 
*
*     Implementa uma abstração da estrutura de dados, tornando o uso uma 
*   simples questão de conjuntos de cartas organizadas.
*
*******************************************************************************/
#if defined( NAIPE_OWN )
   #define NAIPE_EXT
#else
   #define NAIPE_EXT extern
#endif