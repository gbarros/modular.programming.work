/***************************************************************************
*	$MCD Módulo de definição: EXT Extra
*
*	Arquivo gerado:              EXTRA.c
*	Letras identificadoras:      EXT
*
*	Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*	Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*	Projeto: [INF 1301] Implementação do Jogo FreCell para fins educacionais
*	Gestor:  LES/DI/PUC-Rio
*	Autores: gb - Gabriel Barros
*			 lg - Leonardo Giroto 
*			 nk - Noemie Nakamura
*
*	$HA Histórico de evolução:
*	Versão  Autor	Data			Observações
*	1       gb, nk	25/set/2013		Início desenvolvimento, definição de funções
*	2 		lg		13/out/2013		Continuação do desenvolvimento
*	3		nk		14/out/2013		Correção de nomenclatura, novas funções
*	4		lg		14/out/2013		Desenvolvimento
*	5		lg		15/out/2013		Desenvolvimento
*   6       gb      16/out/2013     Desenvolvimento
*    
***************************************************************************/
#define EXTRA_OWN
#include "EXTRA.h"
#include <stdio.h>
#include <string.h>
#undef EXTRA_OWN

static int ObterValor(Carta carta);
static char ObterNaipe(Carta carta);
static char REF []= " "; //Referencia para espaço vazio


/***************************************************************************
*  Função: EXT  &Criar Coluna
***************************************************************************/

EXT_Coluna EXT_CriarColunaExtra(void)
{
	LIS_tppLista extraHead;
	LIS_tpCondRet retornoCriaLista;
	int i;

	extraHead = LIS_CriarLista(NULL);

	if(extraHead == NULL)
	{
		return NULL;
	}

	for(i=0;i<4;i++)
	{
		retornoCriaLista = LIS_InserirElementoApos(extraHead,REF);
		if(retornoCriaLista != LIS_CondRetOK){
			LIS_DestruirLista(extraHead);
			return NULL;

		}
	}

	return extraHead;

}

/***************************************************************************
*  Função: EXT  &Excluir Coluna
***************************************************************************/

EXT_tpCondRet EXT_ExcluirColunaExtra(EXT_Coluna coluna)
{
	if(coluna==NULL)
		return EXT_CondRetColunaInexistente;

	LIS_DestruirLista(coluna);

	return EXT_CondRetOK;
}

/***************************************************************************
*  Função: EXT  &Verificar Inserir Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarInserirCarta(EXT_Coluna destino, Carta carta)
{
	int i=4;
	static int CONTA=0;

	if(destino == NULL)
		return EXT_CondRetColunaInexistente;
	// verifica se a carta é válida
	if(carta == NULL || (ObterValor(carta)== -1)|| (ObterNaipe(carta)=='X') )
		return EXT_CondRetCartaInvalida;

	IrFinalLista(destino);

	while(i)
	{
		if(LIS_ObterValor(destino)==REF){ //vê se não há elemento na posição
			printf("\n ABSSSSSS    |%s|  %d  &   %d \n", LIS_ObterValor(destino),i, CONTA++ );
			return EXT_CondRetOK;
		}
		else
			LIS_AvancarElementoCorrente(destino,-1); //vê próximo elemento da lista
		i--;
	}

	return EXT_CondRetNaoPodeInserir;
}

/***************************************************************************
*  Função: EXT  &Verificar Remover Carta
***************************************************************************/

EXT_tpCondRet EXT_VerificarRemoverCarta(EXT_Coluna origem, Carta carta)
{
	LIS_tpCondRet retornoVerificaRemover;

	if(origem== NULL)
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe

	// verifica se a carta é válida
	if(carta == NULL || (ObterValor(carta)== -1)|| (ObterNaipe(carta)=='X'))

		return EXT_CondRetCartaInvalida; 

	  IrInicioLista(origem);

	retornoVerificaRemover = LIS_ProcurarValor(origem,carta); // procura a carta na coluna

	printf("\n\n retornoVerificaRemover: %d  ", retornoVerificaRemover);

	if(retornoVerificaRemover == LIS_CondRetNaoAchou)

		return EXT_CondRetNaoPodeRemover; // se a carta não estiver na coluna

	else if(retornoVerificaRemover == LIS_CondRetListaVazia)

		return EXT_CondRetNaoPodeRemover; // se a coluna estiver vazia

	else
		return EXT_CondRetOK;

}

/***************************************************************************
*  Função: EXT  &Inserir Carta Em Extra
***************************************************************************/

EXT_tpCondRet EXT_InserirCartaEmExtra(EXT_Coluna destino, Carta carta)
{
	LIS_tpCondRet retornoInserir;
	EXT_tpCondRet possivelInserir;
	printf("\n ENDERECO: %x  \n",destino );
	if(destino == NULL){
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe
	}
  else{
		if(carta == NULL || (ObterValor(carta)== -1)|| (ObterNaipe(carta)=='X')){

			return EXT_CondRetCartaInvalida; // verifica se a carta é válida
		}
		else{
			possivelInserir = EXT_VerificarInserirCarta(destino,carta); // chama função para verificar se a inserção é possível

			printf("\n Possivel? %d \n ", possivelInserir);

			if(possivelInserir == EXT_CondRetOK) // se a inserção for possível
			{
				IrFinalLista(destino); //torna elemento corrente o ultimo elemento
				printf ("\n\n\n EU SOU A CARTA DA VEZ: %s \n",carta);

				retornoInserir = LIS_InserirElementoApos(destino,carta); // insere após o elemento corrente

				if(retornoInserir == LIS_CondRetOK)
					return EXT_CondRetOK;
				else
					EXT_CondRetNaoPodeInserir;
			}
			else{

				return EXT_CondRetNaoPodeInserir;

			}
		}
	}
	return EXT_CondRetNaoPodeInserir;
}

/***************************************************************************
*  Função: EXT  &Remover Carta De Extra
***************************************************************************/

EXT_tpCondRet EXT_RemoverCartaDeExtra(EXT_Coluna origem, Carta carta)
{
	LIS_tpCondRet retornoRemover,
				  retornoInserir;
	EXT_tpCondRet possivelRemover;
	printf("\n ENDERECO: %x  \n",origem );
	if(origem== NULL){
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe
	}
	else{
		if(carta == NULL || (ObterValor(carta)== -1)|| (ObterNaipe(carta)=='X')){

			return EXT_CondRetCartaInvalida; // verifica se a carta é válida
		}
		else{
			//possivelRemover = ; // chama função que vê se é possível remover
			possivelRemover=EXT_VerificarRemoverCarta(origem,carta);
			printf("\n\n\n Passei %d\n",possivelRemover);
			if(possivelRemover == EXT_CondRetOK) {   // se a Remocao for possível
				retornoRemover = LIS_ExcluirElemento(origem); // se estiver, exclui a carta da coluna

				printf("\n\n\n\n\nAqui deu o erro  %d", retornoRemover);

				if(retornoRemover == LIS_CondRetOK)
				{
					retornoInserir = LIS_InserirElementoApos(origem,REF);
					if(retornoInserir == LIS_CondRetOK)
						return EXT_CondRetOK;
					else
						return EXT_CondRetErroRemocao;
				}
				else
					return EXT_CondRetErroRemocao;
			}
			else
				return EXT_CondRetErroRemocao;
		}
	}	
}

/***************************************************************************
*  Função: EXT  &Exibir Carta
***************************************************************************/

EXT_tpCondRet EXT_ExibirCartas(EXT_Coluna coluna)
{
	int i;
	LIS_tpCondRet avancarCondRet;
	char *valor;

	if(coluna == NULL)
		return EXT_CondRetColunaInexistente; // verifica se a coluna existe
	IrFinalLista(coluna); // garantir que pegaremos os valores desde o início
	printf("\n\nExtra:   \n");
	for(i=0;i<4;i++)
	{
		valor = LIS_ObterValor(coluna);

		if(valor == NULL)
			break;
		
		printf("[ |%s| ] ",valor);

		avancarCondRet = LIS_AvancarElementoCorrente(coluna,-1);
		if (avancarCondRet == LIS_CondRetFimLista)
			break;
	}

	printf("\n");
	return EXT_CondRetOK;
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
