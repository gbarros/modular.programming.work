/***************************************************************************
*	$MCI Módulo de implementação: TNPE Teste coluna tipo naipe
*
*	Arquivo gerado:              TEST_NPE.c
*	Letras identificadoras:      TNPE
*
*	Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*   Versão  Autor	Data			Observações
*   1       nk		15/out/2013		Criação script, desenvolvimento
*
*	$ED Descrição do módulo
*   Este móodulo contém as funções específicas para o teste de um módulo.
*   Mais especificamente, contém a função que interpreta os comandos de
*   teste que exercitarão as funções do módulo em teste.
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.h"
#include    "GENERICO.h"
#include    "LERPARM.h"

#include	"NAIPE.h"

static const char CRIAR_COL_CMD		[ ] = "=criar"		;
static const char VERIFICAR_INS_CMD	[ ] = "=verif"		;
static const char INSERIR_COL_CMD	[ ] = "=inserir"	;
static const char EXIBIR_COL_CMD	[ ] = "=exibir"		;
static const char DESTRUIR_COL_CMD	[ ] = "=destruir"	;

#define DIM_VT_NPE 4


/***** Protótipos das funções encapsuladas no módulo *****/

int VerificarIndex(int indexColuna);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*	$FC Função: TLIS &Testar lista
*
*	$ED Descrição da função
*	Comandos de teste específicos para testar o módulo árvore:
*   Podem ser criadas até 4 colunas tipo naipe.
*   As colunas são conhecidas pelo seu índice de 0 a 3.
*   
*	Comandos disponíveis:
*   =criar		<indexColuna>
*		- Chama a função NPE_CriarColunaNaipe()
*
*	=vervaz		<indexColuna> <String> <CondRet>
*		- Chama a função NPE_VerificarInserirCarta()
*
*	=vercom		<indexColuna> <String> <CondRet>
*		- Chama a função NPE_VerificarInserirCarta()
*
*	=insvaz		<indexColuna> <String> <CondRet>
*		- Chama a função NPE_InserirCartaEmNaipe()
*
*	=inscom		<indexColuna> <String> <CondRet>
*		- Chama a função NPE_InserirCartaEmNaipe()
*
*	=exibir		<indexColuna> <CondRet>
*		- Chama a função NPE_ExibirCarta()
*
*	=destruir	<indexColuna> <CondRet>
*		- Chama a função NPE_DestruirColunaNaipe()
***********************************************************************/
static NPE_Coluna colunas[DIM_VT_NPE] ;

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste){

	/*Inicialização das condições de retorno obtida e esperar com qualquer coisa */	
	NPE_tpCondRet CondRetObtida   = NPE_CondRetOK;
	NPE_tpCondRet CondRetEsperada = NPE_CondRetColunaNaoExiste;

	int  numLidos = -1 ;
    int  indexColuna = -1 ;
	
	char cartaDada[4];

	// Teste de NPE Criar Coluna
	if(strcmp(ComandoTeste, CRIAR_COL_CMD) == 0){
		numLidos = LER_LerParametros("i", &indexColuna);

		if((numLidos != 1) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		colunas[indexColuna] =  NPE_CriarColunaNaipe();

		return TST_CompararPonteiroNulo(1, colunas[indexColuna], "Retorno errado ao criar coluna.\n") ;
	}

	// Teste de NPE Verificar Inserir Carta Em Coluna
	else if(strcmp(ComandoTeste, VERIFICAR_INS_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);
		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		CondRetObtida = NPE_VerificarInserirCarta(colunas[indexColuna], cartaDada);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao verificar inserir.\n") ;
	}

	// Teste de NPE Inserir Carta Em Coluna
	else if(strcmp(ComandoTeste, INSERIR_COL_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		CondRetObtida = NPE_InserirCartaEmNaipe(colunas[indexColuna], cartaDada);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao inserir.\n");
	}

	//// Teste de NPE Verificar Inserir Carta Em Coluna Com Carta
	//else if(strcmp(ComandoTeste, VERIFICAR_INSCOM_CMD) == 0){
	//	numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

	//	if((numLidos != 3) || !VerificarIndex(indexColuna))
	//		return TST_CondRetParm;

	//	CondRetObtida = NPE_VerificarInserirCarta(colunas[indexColuna], cartaDada);

	//	return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao verificar inserir.\n");
	//}

	//// Teste de NPE Inserir Carta Em Coluna Com Carta
	//else if(strcmp(ComandoTeste, INSERIR_COLCOM_CMD) == 0){
	//	numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

	//	if((numLidos != 3) || !VerificarIndex(indexColuna))
	//		return TST_CondRetParm;

	//	CondRetObtida = NPE_InserirCartaEmNaipe(colunas[indexColuna], cartaDada);

	//	return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao inserir.\n");
	//}

	// Teste de NPE Exibir Carta
	else if(strcmp(ComandoTeste, EXIBIR_COL_CMD) == 0){
		numLidos = LER_LerParametros("ii", &indexColuna, &CondRetEsperada);

		if((numLidos != 2) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		CondRetObtida = NPE_ExibirCarta(colunas[indexColuna]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao exibir.\n");
	}

	// Teste de NPE Destruir Coluna
	else if(strcmp(ComandoTeste, DESTRUIR_COL_CMD) == 0){
		numLidos = LER_LerParametros("ii", &indexColuna, &CondRetEsperada);

		if((numLidos != 2) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		CondRetObtida = NPE_DestruirColunaNaipe(colunas[indexColuna]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao destruir coluna.\n");
	}
	
	return TST_CondRetNaoConhec;
}

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*  $FC Função: TNPE - Verificar índice de coluna tipo naipe
*
*  $FV Valor retornado
*     0 - inxArvore não vale
*     1 - inxArvore vale
***********************************************************************/
int VerificarIndex(int indexColuna){
	if((indexColuna < 0) || (indexColuna > DIM_VT_NPE)){
		return 0;
	}
	return 1 ;
}

/********** Fim do módulo de implementação: TNPE Teste coluna tipo naipe **********/

