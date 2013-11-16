#define BARALHO 52

typedef char* Carta;

int FC_ExibirMesa(void *mesa)
{
	int i, valor, colunaOrigem, colunaDestino;

	IrInicioLista(mesa);

	printf("Extra:\n");

	EX_ExibirCartas(&mesa);

	LIS_AvancarElementoCorrente(mesa,1);

	printf("Naipe:\n");

	NP_ExibirCartas(&mesa);

	LIS_AvancarElementoCorrente(mesa,1);

	printf("Colunas:\n");

	NP_ExibirCartas(&mesa);

	printf("Menu:\n");
	printf("O que deseja fazer?\n");
	printf("1. Transferir\n2. Desistir\n");
	scanf("%d",valor);

	if(valor == 2)
	{
		return FC_Desistir();
	}
	else
	{
		printf("Indique a carta que deseja transferir, o número da coluna fonte e o número da coluna destino.");
		scanf("%s,%d,%d",Carta,colunaOrigem,colunaDestino);
		return FC_MoverCarta(Carta,colunaOrigem,colunaDestino);
	}

}