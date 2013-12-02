/***************************************************************************
*  $MCD Módulo de implementação: SV Sequência Visível
*
*  Arquivo gerado:              SEQ_VIS.c
*  Letras identificadoras:      SV
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: [INF 1301] Implementação do Jogo FreeCell para fins educacionais
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    gb -	Gabriel Barros
*			   lg - Leonardo Giroto 
*			   nk - Noemie Nakamura
*
*  $HA Histórico de evolução:
*   Versão  Autor	Data			Observações
*	5		nk		28/nov/2013		Correções
*	4		nk		16/out/2013		Correções, finalização do desenvolvimento
*	3		lg		14/out/2013		Continuação do desenvolvimento
*	2		nk		14/out/2013		Correção de nomenclatura, novas funções
*	1 		lg		13/out/2013		Criação e início do desenvolvimento do módulo
*    
***************************************************************************/
#define SEQ_VIS_OWN
#include "seq_vis.h"
#undef SEQ_VIS_OWN

#include <stdio.h>
#include <string.h>

static int ObterValor(Carta carta);
static char ObterNaipe(Carta carta);
static char ObterCor(Carta carta);

/***************************************************************************
*  Função: SV  &Criar Coluna
***************************************************************************/
SV_Coluna SV_CriarColunaSeqVis(void){
	return LIS_CriarLista(NULL);
}

/***************************************************************************
*  Função: SV  &Excluir Coluna
***************************************************************************/

SV_tpCondRet SV_ExcluirColunaSeqVis(SV_Coluna coluna){
	if(coluna == NULL)
		return SV_CondRetColunaNaoExiste;
	
	LIS_DestruirLista(coluna);
	
	return SV_CondRetOK;
}

/***************************************************************************
*  Função: SV  &Verificar Inserir Carta
***************************************************************************/
SV_tpCondRet SV_VerificarInserirCarta(SV_Coluna destino, Carta carta){
	Carta cartaBase;
	// Verifica se a carta recebida existe
	if(carta == NULL || ObterValor(carta) == -1 || ObterNaipe(carta) == 'X')
		return SV_CondRetCartaNaoExiste;

	// Verifica se a coluna recebida existe
	if(destino == NULL)
		return SV_CondRetColunaNaoExiste;
	
	// Comparar carta a inserir com carta da "base" da coluna (a de cima do bolo)
	IrFinalLista(destino);
	cartaBase = (Carta)LIS_ObterValor(destino); 

	// Se for NULL, a coluna está vazia e pode receber qualquer carta válida
	if(cartaBase == NULL){
		return SV_CondRetOK;
	}

	// Se já tiver uma carta, comparar valores e cores
	
	// Se as cores forem iguais, não pode inserir
	if(ObterCor(carta) == ObterCor(cartaBase)){
		return SV_CondRetNaoPodeInserir;
	}
	else{
		// Se a carta base já for um A's, não pode inserir
		if(ObterValor(cartaBase) == 1){
			return SV_CondRetNaoPodeInserir;
		}
		// Se a carta a inserir não for antecessora à carta base em numeral,
		// não pode inserir
		else if(ObterValor(cartaBase) != (ObterValor(carta) + 1)){
			return SV_CondRetNaoPodeInserir;
		}
		else
			return SV_CondRetOK;
	}

}

/***************************************************************************
*  Função: SV  &Verificar Remover Carta
***************************************************************************/

SV_tpCondRet SV_VerificarRemoverCarta(SV_Coluna origem, Carta carta){
	int resBusca, resAvanco = -1;
	Carta cartaCorr, cartaCopia = carta;

	// Verifica se a carta recebida existe
	if(carta == NULL || ObterValor(carta) == -1 || ObterNaipe(carta) == 'X')
		return SV_CondRetCartaNaoExiste;

	// Verifica se a coluna recebida existe
	if(origem == NULL)
		return SV_CondRetColunaNaoExiste;

	//Verificar se a coluna está vazia
	if(LIS_ObterValor(origem) == NULL)
		return SV_CondRetColunaVazia;

	// Verifica se a carta recebida pertence à coluna
	IrInicioLista(origem);
	resBusca = LIS_ProcurarValor(origem, carta);



	if(resBusca == LIS_CondRetNaoAchou || resBusca == LIS_CondRetListaVazia){
		return SV_CondRetNaoPodeRemover;
	}
	if(LIS_AvancarElementoCorrente(origem, 1)==LIS_CondRetFimLista)
	{
		return SV_CondRetOK;
	}
 	LIS_AvancarElementoCorrente(origem, -1);//retornando para o elemento correto
	// Dado que uma carta válida foi encontrada, só é possível removê-la se
	// todas as cartas debaixo podem também ser removidas
	cartaCorr = (Carta)LIS_ObterValor(origem);
	while(resAvanco != LIS_CondRetFimLista){

		resAvanco = LIS_AvancarElementoCorrente(origem, 1);

		cartaCopia = (Carta)LIS_ObterValor(origem);


		if((ObterValor(cartaCopia) == (ObterValor(cartaCorr) - 1)) && (ObterCor(cartaCorr) != ObterCor(cartaCopia)))
			cartaCorr=cartaCopia;
		else if (strcmp(cartaCorr,cartaCopia)==0){
			return SV_CondRetOK;
		}
		else{
			return SV_CondRetNaoPodeRemover;

		}
	}
	return SV_CondRetOK;
	
}

/***************************************************************************
*  Função: SV  &Inserir Carta Em Sequência Visível
***************************************************************************/
SV_tpCondRet SV_InserirCartaEmSeqVis(SV_Coluna destino, Carta carta){
	int resIns;
	SV_tpCondRet condRet = SV_CondRetErroAoInserir;
	
	if(SV_VerificarInserirCarta(destino, carta) != SV_CondRetOK){
		return SV_CondRetErroAoInserir;
	}
	
	IrFinalLista(destino);
	resIns = LIS_InserirElementoApos(destino, carta);
	
	if(resIns == SV_CondRetOK){
		return SV_CondRetOK;
	}
	else{

		return SV_CondRetErroAoInserir;
	}
}

/***************************************************************************
*  Função: SV  &Remover Carta De Sequêncial Visível
***************************************************************************/
SV_tpCondRet SV_RemoverCartaDeSeqVis(SV_Coluna origem, Carta carta){
	int resAvanco, resExclusao;
	SV_tpCondRet condRet = SV_CondRetErroAoRemover;
	
	if(SV_VerificarRemoverCarta(origem, carta) != SV_CondRetOK){
		return SV_CondRetErroAoRemover;
	}

	// Primeiro fazer o elemento corrente ser o elemento a ser excluído
	IrInicioLista(origem);
	while(LIS_ObterValor(origem) != carta){
		resAvanco = LIS_AvancarElementoCorrente(origem, 1);
	}
	resExclusao = LIS_ExcluirElemento(origem);

	if(resExclusao == SV_CondRetOK){
		return SV_CondRetOK;
	}
	else
		return SV_CondRetErroAoRemover;
}

/***********************************************************************
*	Função: SV &Popular Sequência Visível
***********************************************************************/

SV_tpCondRet SV_PopularSeqVis(SV_Coluna destino, Carta carta){
	int resIns;
	SV_tpCondRet resPop = SV_CondRetErroAoInserir;
	
	// Verifica se a carta recebida existe
	if(carta == NULL || ObterValor(carta) == -1 || ObterNaipe(carta) == 'X')
		return SV_CondRetCartaNaoExiste;

	// Verifica se a coluna recebida existe
	if(destino == NULL)
		return SV_CondRetColunaNaoExiste;

	IrFinalLista(destino);
	resIns = LIS_InserirElementoApos(destino, carta);
	if(resIns == LIS_CondRetOK)
		return SV_CondRetOK;
	else
		return resPop;
}

/***************************************************************************
*  Função: SV  &Exibir Cartas
***************************************************************************/
SV_tpCondRet SV_ExibirCartas(SV_Coluna coluna){
	int resAvanco = -1;
	Carta carta;
	
	// Verifica se a coluna existe
	if(coluna == NULL)
		return SV_CondRetColunaNaoExiste;

	IrInicioLista(coluna);
	while(resAvanco != LIS_CondRetFimLista){
		carta = (Carta)LIS_ObterValor(coluna);
		printf("%s\t", carta);
		resAvanco = LIS_AvancarElementoCorrente(coluna, 1);
	}
	return SV_CondRetOK;
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
static char ObterCor(Carta carta){
	char naipe = ObterNaipe(carta);

	if(naipe == 'C' || naipe == 'O')
		return 'V';
	else if(naipe == 'P' || naipe == 'E')
		return 'P';
	else
		return 'N';
}
