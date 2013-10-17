/***************************************************************************
*	$MCI Módulo de implementação: TSV Teste coluna tipo sequência visível
*
*	Arquivo gerado:              TEST_SV.c
*	Letras identificadoras:      TSV
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\MODULO_SEQ_VIS.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*   Versão  Autor	Data			Observações
*	2		nk		16/out/2013		Finalização desenvolvimento
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

#include	"SEQ_VIS.h"

static const char CRIAR_COL_CMD		[ ] = "=criar"		;
static const char VERIFICAR_INS_CMD	[ ] = "=verins"		;
static const char VERIFICAR_REM_CMD	[ ] = "=verrem"		;
static const char INSERIR_COL_CMD	[ ] = "=inserir"	;
static const char REMOVER_COL_CMD	[ ] = "=remover"	;
static const char EXIBIR_COL_CMD	[ ] = "=exibir"		;
static const char DESTRUIR_COL_CMD	[ ] = "=destruir"	;
static const char POPULAR_COL_CMD	[ ] = "=popul"		;

#define DIM_VT_SV 8
#define TAM 4
#define QTD_SV 52

static SV_Coluna colunas[DIM_VT_SV] ;

/***** Protótipos das funções encapsuladas no módulo *****/

int VerificarIndex(int indexColuna);
TST_tpCondRet CarregaStringDada(char *String);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*	$FC Função: TSV &Testar sequências visíveis
*
*	$ED Descrição da função
*	Comandos de teste específicos para testar o módulo sequências visíveis.
*   Podem ser criadas até 8 colunas tipo sequência visível.
*   As colunas são conhecidas pelo seu índice de 0 a 7.
*   
*	Comandos disponíveis:
*   =criar		<indexColuna>
*		- Chama a função SV_CriarColunaSeqVis()
*
*	=verins		<indexColuna> <String> <CondRet>
*		- Chama a função SV_VerificarInserirCarta()
*
*	=verrem		<indexColuna> <String> <CondRet>
*		- Chama a função SV_VerificarRemoverCarta()
*
*	=inserir	<indexColuna> <String> <CondRet>
*		- Chama a função SV_InserirCartaEmSeqVis()
*
*	=remover	<indexColuna> <String> <CondRet>
*		- Chama a função SV_RemoverCartaDeSeqVis()
*
*	=popul		<indexColuna> <String> <CondRet>
*		- Chama a função SV_PopularSeqVis()
*
*	=exibir		<indexColuna> <CondRet>
*		- Chama a função SV_ExibirCartas()
*
*	=destruir	<indexColuna> <CondRet>
*		- Chama a função SV_ExcluirColunaSeqVis()
***********************************************************************/

static SV_Coluna colunas[DIM_VT_SV] ;
static char cartasRecebidas[QTD_SV][TAM];
static int indexCarta=0;

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste){

	/*Inicialização das condições de retorno obtida e esperar com qualquer coisa */	
	SV_tpCondRet CondRetObtida   = SV_CondRetOK;
	SV_tpCondRet CondRetEsperada = SV_CondRetColunaNaoExiste;

	int  numLidos = -1 ;
    int  indexColuna = -1 ;

	char cartaDada[TAM];

	// Teste de SV Criar Coluna
	if(strcmp(ComandoTeste, CRIAR_COL_CMD) == 0){
		numLidos = LER_LerParametros("ii", &indexColuna, &CondRetEsperada);

		if((numLidos != 2) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		colunas[indexColuna] =  SV_CriarColunaSeqVis();

		return TST_CompararPonteiroNulo(1, colunas[indexColuna], "Retorno errado ao criar coluna.\n") ;
	}

	// Teste de SV Verificar Inserir Carta Em Coluna
	else if(strcmp(ComandoTeste, VERIFICAR_INS_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		if (CarregaStringDada(cartaDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

		CondRetObtida = SV_VerificarInserirCarta(colunas[indexColuna],cartasRecebidas[indexCarta]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao verificar inserir.\n") ;
	}

	// Teste de SV Verificar Remover Carta De Coluna
	else if(strcmp(ComandoTeste, VERIFICAR_REM_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		if (CarregaStringDada(cartaDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

		CondRetObtida = SV_VerificarRemoverCarta(colunas[indexColuna], cartasRecebidas[indexCarta]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao verificar inserir.\n") ;
	}

	// Teste de SV Inserir Carta Em Coluna
	else if(strcmp(ComandoTeste, INSERIR_COL_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		if (CarregaStringDada(cartaDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

		CondRetObtida = SV_InserirCartaEmSeqVis(colunas[indexColuna], cartasRecebidas[indexCarta]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao inserir.\n");
	}

	// Teste de SV Exibir Cartas
	else if(strcmp(ComandoTeste, EXIBIR_COL_CMD) == 0){
		numLidos = LER_LerParametros("ii", &indexColuna, &CondRetEsperada);

		if((numLidos != 2) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		CondRetObtida = SV_ExibirCartas(colunas[indexColuna]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao exibir.\n");
	}

	// Teste de SV Excluir Coluna
	else if(strcmp(ComandoTeste, EXIBIR_COL_CMD) == 0){
		numLidos = LER_LerParametros("ii", &indexColuna, &CondRetEsperada);

		if((numLidos != 2) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		CondRetObtida = SV_ExcluirColunaSeqVis(colunas[indexColuna]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao destruir coluna.\n");
	}

	// Teste de SV Popular Coluna
	else if(strcmp(ComandoTeste, POPULAR_COL_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		if (CarregaStringDada(cartaDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

		CondRetObtida = SV_PopularSeqVis(colunas[indexColuna], cartasRecebidas[indexCarta]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao destruir coluna.\n");
	}
	
	return TST_CondRetNaoConhec;
}

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*  $FC Função: TSV - Verificar índice de coluna tipo sequência visível
*
*  $FV Valor retornado
*     0 - inxArvore não vale
*     1 - inxArvore vale
***********************************************************************/
int VerificarIndex(int indexColuna){
	if((indexColuna < 0) || (indexColuna)){
		return 0;
	}
	return 1 ;
}

TST_tpCondRet CarregaStringDada( char * String){
   int i, entrou=1;

     for(i=0;i<52;i++){

           if (strcmp(String,cartasRecebidas[i])==0){
             indexCarta=i;
             entrou=0;
             break;
           }
        }
        if(entrou){ //Se não entrou no ultimo if
          for(i=0;i<52 && ( strlen(cartasRecebidas[i]) );i++);
            if(i==52){
              printf("Acabou a memória do vetor auxilar do modulo controlador de teste");
              return TST_CondRetMemoria;
            }
            indexCarta=i;
        }
         strcpy(cartasRecebidas[indexCarta],String);
         return TST_CondRetOK;
 }

/********** Fim do módulo de implementação: TSV Teste coluna tipo sequência visível **********/

