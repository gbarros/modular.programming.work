/***************************************************************************
*  $MCD Módulo de definição: EXT Extra
*
*  Arquivo gerado:              EXTRA.c
*  Letras identificadoras:      EXT
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: [INF 1301] Implementação do Jogo FreCell para fins educacionais
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    gb -	Gabriel Barros
*			   lg - Leonardo Giroto 
*			   nk - Noemie Nakamura
*
*  $HA Histórico de evolução:
*  Versão  Autor	Data			Observações
*  1       gb, nk	25/set/2013		Início desenvolvimento, definição de funções
*    
***************************************************************************/
#include <LISTA.H>

typedef LIS_tppLista EXT_Coluna;
typedef char* Carta;


public EXT_Coluna EXT_CriaColuna (void){

	return LIS_CriarLista( NULL ) ;

}

public int EXT_ExcluirColuna( EXT_Coluna coluna ){
 	
 	 LIS_DestruirLista( coluna ) ;

}


public int EXT_InserirCarta ( EXT_Coluna destino, Carta carta){

	/*Regras de inserção*/ 
	 IrFinalLista(destino) ; //torna elemento corrente o ultimo elemento
	 int deuCerto= LIS_InserirElementoApos( destino , carta ); // insere após o elemento corrente
}

public int EXT_ExcluirCarta (EXT_Coluna alvo, Carta carta){

	/*Deve-se analizar os retornos de procurar valor e talvez de ExcluirElemento*/
	LIS_ProcurarValor (alvo, carta);
	LIS_ExcluirElemento( alvo );
}



int ContarCartas (EXT_Coluna coluna){
	/* implementar contador de cartas, dica: se for um inicio=fim, senão tem que ir do 
	inicio ao fim iterando*/
}