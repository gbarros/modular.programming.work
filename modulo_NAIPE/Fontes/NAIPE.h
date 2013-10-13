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
*	2 		lg		13/out/2013		Desenvolvimento
*
*  $ED Descrição do módulo
*
*
*******************************************************************************/
#if defined( NAIPE_OWN )
   #define NAIPE_EXT
#else
   #define NAIPE_EXT extern
#endif

public NPE_Coluna NPE_CriarColunaNaipe(void);
public int NPE_DestruirColunaNaipe(NPE_Coluna coluna);
static int ContarCartas (NPE_Coluna coluna);
public int NPE_InserirCartaEmNaipe(NPE_Coluna coluna, Carta carta);