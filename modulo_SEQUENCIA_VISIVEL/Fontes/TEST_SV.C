/***************************************************************************
*	$MCI M�dulo de implementa��o: TSV Teste coluna tipo sequ�ncia vis�vel
*
*	Arquivo gerado:              TEST_SV.c
*	Letras identificadoras:      TSV
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\MODULO_SEQ_VIS.BSW
*
*	Projeto: [INF 1301] Implementa��o do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Hist�rico de evolu��o:
*   Vers�o  Autor	Data			Observa��es
*	2		nk		16/out/2013		Finaliza��o desenvolvimento
*   1       nk		15/out/2013		Cria��o script, desenvolvimento
*
*	$ED Descri��o do m�dulo
*   Este m�odulo cont�m as fun��es espec�ficas para o teste de um m�dulo.
*   Mais especificamente, cont�m a fun��o que interpreta os comandos de
*   teste que exercitar�o as fun��es do m�dulo em teste.
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

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

int VerificarIndex(int indexColuna);
TST_tpCondRet CarregaStringDada(char *String);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*	$FC Fun��o: TSV &Testar sequ�ncias vis�veis
*
*	$ED Descri��o da fun��o
*	Comandos de teste espec�ficos para testar o m�dulo sequ�ncias vis�veis.
*   Podem ser criadas at� 8 colunas tipo sequ�ncia vis�vel.
*   As colunas s�o conhecidas pelo seu �ndice de 0 a 7.
*   
*	Comandos dispon�veis:
*   =criar		<indexColuna>
*		- Chama a fun��o SV_CriarColunaSeqVis()
*
*	=verins		<indexColuna> <String> <CondRet>
*		- Chama a fun��o SV_VerificarInserirCarta()
*
*	=verrem		<indexColuna> <String> <CondRet>
*		- Chama a fun��o SV_VerificarRemoverCarta()
*
*	=inserir	<indexColuna> <String> <CondRet>
*		- Chama a fun��o SV_InserirCartaEmSeqVis()
*
*	=remover	<indexColuna> <String> <CondRet>
*		- Chama a fun��o SV_RemoverCartaDeSeqVis()
*
*	=popul		<indexColuna> <String> <CondRet>
*		- Chama a fun��o SV_PopularSeqVis()
*
*	=exibir		<indexColuna> <CondRet>
*		- Chama a fun��o SV_ExibirCartas()
*
*	=destruir	<indexColuna> <CondRet>
*		- Chama a fun��o SV_ExcluirColunaSeqVis()
***********************************************************************/

static SV_Coluna colunas[DIM_VT_SV] ;
static char cartasRecebidas[QTD_SV][TAM];
static int indexCarta=0;

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste){

	/*Inicializa��o das condi��es de retorno obtida e esperar com qualquer coisa */	
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

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao verificar remover.\n") ;
	}

	else if(strcmp(ComandoTeste, REMOVER_COL_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		if (CarregaStringDada(cartaDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

		CondRetObtida = SV_RemoverCartaDeSeqVis(colunas[indexColuna], cartasRecebidas[indexCarta]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao verificar remover.\n") ;
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
	else if(strcmp(ComandoTeste, DESTRUIR_COL_CMD) == 0){
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

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*  $FC Fun��o: TSV - Verificar �ndice de coluna tipo sequ�ncia vis�vel
*
*  $FV Valor retornado
*     0 - inxArvore n�o vale
*     1 - inxArvore vale
***********************************************************************/
int VerificarIndex(int indexColuna){
	if((indexColuna < 0) || (indexColuna > DIM_VT_SV)){
		return 0;
	}
	return 1 ;
}

TST_tpCondRet CarregaStringDada( char * String){
   int i, entrou=1;

     for(i=0;i<QTD_SV;i++){

           if (strcmp(String,cartasRecebidas[i])==0){
             indexCarta=i;
             entrou=0;
             break;
           }
        }
        if(entrou){ //Se n�o entrou no ultimo if
          for(i=0;i<QTD_SV && ( strlen(cartasRecebidas[i]) );i++);
            if(i==QTD_SV){
              printf("Acabou a mem�ria do vetor auxilar do modulo controlador de teste");
              return TST_CondRetMemoria;
            }
            indexCarta=i;
        }
         strcpy(cartasRecebidas[indexCarta],String);
         return TST_CondRetOK;
 }

/********** Fim do m�dulo de implementa��o: TSV Teste coluna tipo sequ�ncia vis�vel **********/

