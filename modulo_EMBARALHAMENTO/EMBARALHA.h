#if ! defined( EMBARALHA_ )
#define EMBARALHA_

/*******************************************************************************
*  $MCD Módulo de definição: EMB Embaralhamento
*
*  Arquivo gerado:              EMBARALHA.h
*  Letras identificadoras:      EMB
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
*   1       gb		12/out/2013		Início desenvolvimento, definição de funções
*
*	$ED Descrição do módulo
*	Recebe uma sequência representando baralho ordenado e retorna esta sequência
*	embaralhada.
*
*******************************************************************************/
#if defined( EMBARALHA_OWN )
   #define EMBARALHA_EXT
#else
   #define EMBARALHA_EXT extern
#endif
