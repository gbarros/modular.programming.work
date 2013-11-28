/***************************************************************************
*	$MCI Módulo de implementação: NPE Naipe
*
*	Arquivo gerado:              NAIPE.c
*	Letras identificadoras:      NPE
*
*	Nome da base de software:    Jogo FreeCell
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\MODULO_NAIPE.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores:   gb -	Gabriel Barros
*			   lg - Leonardo Giroto 
*			   nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão	Autor	Data			Observações
*	4		nk		16/out/2013		Correção de assertivas
*	3		nk		15/out/2013		Finalização do desenvolvimento
*	2 		lg		13/out/2013		Desenvolvimento
*	1       nk		11/out/2013		Início desenvolvimento, Criação   
***************************************************************************/
#include <stdio.h>
#include <string.h>

#define NAIPE_OWN
#include "NAIPE.h"
#undef NAIPE_OWN

static int ObterValor(Carta carta);
static char ObterNaipe(Carta carta);

/***********************************************************************
*	$FC Função: NPE &Criar Coluna
***********************************************************************/
NPE_Coluna NPE_CriarColunaNaipe(void){
	return LIS_CriarLista(NULL);
}

/***********************************************************************
*	$FC Função: NPE &Excluir Coluna
***********************************************************************/
NPE_tpCondRet NPE_DestruirColunaNaipe(NPE_Coluna coluna){
	if(coluna == NULL)
		return NPE_CondRetColunaNaoExiste;
	
	LIS_DestruirLista(coluna);
	
	return NPE_CondRetOK;
}

/***********************************************************************
*	$FC Função: NPE &Verificar Inserir Carta
***********************************************************************/
NPE_tpCondRet NPE_VerificarInserirCarta(NPE_Coluna destino, Carta carta){
	Carta cartaBase;
	char naipeCarta, naipeCartaBase;
	int valorCarta, valorCartaBase;

	valorCarta = ObterValor(carta);
	naipeCarta = ObterNaipe(carta);

	// Verifica se a carta recebida existe
	if(carta == NULL || valorCarta == -1 || naipeCarta == 'X'){
		return NPE_CondRetCartaNaoExiste;
	}

	// Verifica se a coluna recebida existe
	if(destino == NULL){
		return NPE_CondRetColunaNaoExiste;
	}
	
	// Comparar carta a inserir com carta da "base" da coluna (a de cima do bolo)
	IrFinalLista(destino);
	cartaBase = LIS_ObterValor(destino);
	
	valorCartaBase = ObterValor(cartaBase);
	naipeCartaBase = ObterNaipe(cartaBase);

	// Se for NULL, a coluna de naipe está vazia e só recebe um A's
	if(cartaBase == NULL){
		if(ObterValor(carta) != 1){
			return NPE_CondRetNaoPodeInserir;
		}
		else{
			return NPE_CondRetOK;
		}
	}

	// Se os naipes forem diferentes, não pode inserir
	if(naipeCartaBase != naipeCarta){
		return NPE_CondRetNaoPodeInserir;
	}
	// Se os naipes forem iguais, verificar se é seguinte na ordem
	else{
		// Se a carta base já for a última na ordem (K), não pode inserir
		if(valorCartaBase == 13){
			return NPE_CondRetNaoPodeInserir;
		}
		
		if(valorCarta == (valorCartaBase + 1)){
			return NPE_CondRetOK;
		}
		else{
			return NPE_CondRetNaoPodeInserir;
		}
	}
}

/***********************************************************************
*	$FC Função: NPE &Inserir Cartas Em Extra
***********************************************************************/
NPE_tpCondRet NPE_InserirCartaEmNaipe(NPE_Coluna destino, Carta carta){
	NPE_tpCondRet condRet = NPE_CondRetErroAoInserir;
	
	if(NPE_VerificarInserirCarta(destino, carta) != NPE_CondRetOK){
		return NPE_CondRetErroAoInserir;
	}
	
	IrFinalLista(destino);
	condRet = LIS_InserirElementoApos(destino, carta);

	if(condRet == NPE_CondRetOK){
		return NPE_CondRetOK;
	}
	else{
		return NPE_CondRetErroAoInserir;
	}
}

/***********************************************************************
*	$FC Função: NPE &Exibir Cartas
***********************************************************************/
NPE_tpCondRet NPE_ExibirCarta(NPE_Coluna coluna){
	Carta carta;
	
	// Verifica se a coluna existe
	if(coluna == NULL)
		return NPE_CondRetColunaNaoExiste;

	IrFinalLista(coluna);
	carta = LIS_ObterValor(coluna);

	printf("%s", carta);

	return NPE_CondRetOK;
}

static int ObterValor(Carta carta){
	if(carta == NULL)
		return -1;
	
	if(carta[0] == 'A')
		return 1;
	else if(carta[0] == '2')
		return 2;
	else if(carta[0] == '3')
		return 3;
	else if(carta[0] == '4')
		return 4;
	else if(carta[0] == '5')
		return 5;
	else if(carta[0] == '6')
		return 6;
	else if(carta[0] == '7')
		return 7;
	else if(carta[0] == '8')
		return 8;
	else if(carta[0] == '9')
		return 9;
	else if(carta[0] == '1')
		return 10;
	else if(carta[0] == 'J')
		return 11;
	else if(carta[0] == 'Q')
		return 12;
	else if(carta[0] == 'K')
		return 13;
	else
		return -1;
}
static char ObterNaipe(Carta carta){
	int val = ObterValor(carta);
	
	if(val == -1)
		return 'X';

	if(val == 10){
		if(carta[2] == 'P')
			return 'P';
		else if(carta[2] == 'C')
			return 'C';
		else if(carta[2] == 'E')
			return 'E';
		else if(carta[2] == 'O')
			return 'O';
	}
	else{
		if(carta[1] == 'P')
			return 'P';
		else if(carta[1] == 'C')
			return 'C';
		else if(carta[1] == 'E')
			return 'E';
		else if(carta[1] == 'O')
			return 'O';
	}
	return 'X';
}



