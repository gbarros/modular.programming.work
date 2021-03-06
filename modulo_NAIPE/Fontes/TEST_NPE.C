/***************************************************************************
*	$MCI M�dulo de implementa��o: TNPE Teste coluna tipo naipe
*
*	Arquivo gerado:              TEST_NPE.c
*	Letras identificadoras:      TNPE
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\MODULO_NAIPE.BSW
*
*	Projeto: [INF 1301] Implementa��o do Jogo FreeCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Hist�rico de evolu��o:
*   Vers�o  Autor	Data			Observa��es
*	2		nk		16/out/2013		Corre��es, finaliza��o do desenvolvimento
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

#include	"NAIPE.h"

static const char CRIAR_COL_CMD		[ ] = "=criar"		;
static const char VERIFICAR_INS_CMD	[ ] = "=verif"		;
static const char INSERIR_COL_CMD	[ ] = "=inserir"	;
static const char EXIBIR_COL_CMD	[ ] = "=exibir"		;
static const char DESTRUIR_COL_CMD	[ ] = "=destruir"	;

#define DIM_VT_NPE 4


/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

int VerificarIndex(int indexColuna);
TST_tpCondRet CarregaStringDada( char * String);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*	$FC Fun��o: TNPE &Testar naipe
*
*	$ED Descri��o da fun��o
*	Comandos de teste espec�ficos para testar o m�dulo naipe.
*   Podem ser criadas at� 4 colunas tipo naipe.
*   As colunas s�o conhecidas pelo seu �ndice de 0 a 3.
*   
*	Comandos dispon�veis:
*   =criar		<indexColuna>
*		- Chama a fun��o NPE_CriarColunaNaipe()
*
*	=vervaz		<indexColuna> <String> <CondRet>
*		- Chama a fun��o NPE_VerificarInserirCarta()
*
*	=vercom		<indexColuna> <String> <CondRet>
*		- Chama a fun��o NPE_VerificarInserirCarta()
*
*	=insvaz		<indexColuna> <String> <CondRet>
*		- Chama a fun��o NPE_InserirCartaEmNaipe()
*
*	=inscom		<indexColuna> <String> <CondRet>
*		- Chama a fun��o NPE_InserirCartaEmNaipe()
*
*	=exibir		<indexColuna> <CondRet>
*		- Chama a fun��o NPE_ExibirCarta()
*
*	=destruir	<indexColuna> <CondRet>
*		- Chama a fun��o NPE_DestruirColunaNaipe()
***********************************************************************/
static NPE_Coluna colunas[DIM_VT_NPE];
static char cartasRecebidas[52][4];
static int indexCarta=0;

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste){

	/*Inicializa��o das condi��es de retorno obtida e esperar com qualquer coisa */	
	NPE_tpCondRet CondRetObtida   = NPE_CondRetOK;
	NPE_tpCondRet CondRetEsperada = NPE_CondRetColunaNaoExiste;

	int  numLidos = -1 ;
    int  indexColuna = -1 ;
	
	char cartaDada[4];

	// Teste de NPE Criar Coluna
	if(strcmp(ComandoTeste, CRIAR_COL_CMD) == 0){
		numLidos = LER_LerParametros("ii",&indexColuna,&CondRetEsperada);

		if((numLidos != 2) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		colunas[indexColuna] =  NPE_CriarColunaNaipe();

		return TST_CompararPonteiroNulo(1, colunas[indexColuna], "Retorno errado ao criar coluna.\n") ;
	}

	// Teste de NPE Verificar Inserir Carta Em Coluna
	else if(strcmp(ComandoTeste, VERIFICAR_INS_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);
		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		if (CarregaStringDada(cartaDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

		CondRetObtida = NPE_VerificarInserirCarta(colunas[indexColuna],cartasRecebidas[indexCarta]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao verificar inserir.\n") ;
	}

	// Teste de NPE Inserir Carta Em Coluna
	else if(strcmp(ComandoTeste, INSERIR_COL_CMD) == 0){
		numLidos = LER_LerParametros("isi", &indexColuna, cartaDada, &CondRetEsperada);

		if((numLidos != 3) || !VerificarIndex(indexColuna))
			return TST_CondRetParm;

		if (CarregaStringDada(cartaDada)==TST_CondRetMemoria){
            return TST_CondRetMemoria;
          }

		CondRetObtida = NPE_InserirCartaEmNaipe(colunas[indexColuna],cartasRecebidas[indexCarta]);

		return TST_CompararInt(CondRetEsperada, CondRetObtida, "Retorno errado ao inserir.\n");
	}

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

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*  $FC Fun��o: TNPE - Verificar �ndice de coluna tipo naipe
*
*  $FV Valor retornado
*     0 - inxArvore n�o vale
*     1 - inxArvore vale
***********************************************************************/
int VerificarIndex(int indexColuna){
	if((indexColuna < 0) || (indexColuna > DIM_VT_NPE)){
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
        if(entrou){ //Se n�o entrou no ultimo if
          for(i=0;i<52 && ( strlen(cartasRecebidas[i]) );i++);
            if(i==52){
              return TST_CondRetMemoria;
            }
            indexCarta=i;
        }
         strcpy(cartasRecebidas[indexCarta],String);
         return TST_CondRetOK;
 }

/********** Fim do m�dulo de implementa��o: TNPE Teste coluna tipo naipe **********/

