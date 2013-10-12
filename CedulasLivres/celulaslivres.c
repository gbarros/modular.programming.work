
#include <LISTA.H>

typedef LIS_tppLista CLI_Coluna;
typedef char* Carta;


public CLI_Coluna CLI_CriaColuna (void){

	return LIS_CriarLista( NULL ) ;

}

public int CLI_ExcluirColuna( CLI_Coluna coluna ){
 	
 	 LIS_DestruirLista( coluna ) ;

}


public int CLI_InserirCarta ( CLI_Coluna destino, Carta carta){

	/*Regras de inserção*/ 
	 IrFinalLista(destino) ; //torna elemento corrente o ultimo elemento
	 int deuCerto= LIS_InserirElementoApos( destino , carta ); // insere após o elemento corrente
}

public int CLI_ExcluirCarta (CLI_Coluna alvo, Carta carta){

	/*Deve-se analizar os retornos de procurar valor e talvez de ExcluirElemento*/
	LIS_ProcurarValor (alvo, carta);
	LIS_ExcluirElemento( alvo );
}



int ContarCartas (CLI_Coluna coluna){
	/* implementar contador de cartas, dica: se for um inicio=fim, senão tem que ir do 
	inicio ao fim iterando*/
}