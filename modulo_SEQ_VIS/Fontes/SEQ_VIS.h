#if ! defined( SEQ_VIS_ )
#define SEQ_VIS_

/*******************************************************************************
*  $MCD Módulo de definição: SV Sequência Visível
*
*  Arquivo gerado:              SEQ_VIS.c
*  Letras identificadoras:      SV
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
*	2  		lg		13/out/2013		Realização das definições
*
*  $ED Descrição do módulo
*	Implementa as regras e funções básicas às sequências visíveis de cartas.
*
*
*******************************************************************************/
#if defined( SEQ_VIS_OWN )
   #define SEQ_VIS_EXT
#else
   #define SEQ_VIS_EXT extern
#endif

public SEQ_VIS_Coluna SEQ_VIS_CriaColuna (void);
public int SEQ_VIS_ExcluirColuna(SEQ_VIS_Coluna coluna );
public int SEQ_VIS_InserirCarta (SEQ_VIS_Coluna destino, Carta carta);
public int SEQ_VIS_ExcluirCarta (SEQ_VIS_Coluna alvo, Carta carta);