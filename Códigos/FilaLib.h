#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


typedef struct{
	int   vetfila[5];
	int   ini, fim;
} 
FILA;

FILA f;

void inicializaFila ( FILA * pedido )
{
	pedido->ini = 0;
	pedido->fim = 0;
}

int filaCheia ( FILA * pedido ) 
{
	if ( pedido->fim == 5 )
		return 1;
	else 
		return 0;
}

int filaVazia ( FILA * pedido ) 
{
	if ( pedido->ini == pedido->fim )
		return 1;
	else 
		return 0;
}

void insereFila ( FILA * pedido, int elemento)
{
	pedido->vetfila[pedido->fim] = elemento;
	pedido->fim = pedido->fim + 1;
}

int  removeFila ( FILA * pedido )
{
	int numped;
	
	numped = pedido->vetfila[pedido->ini];
	pedido->ini = pedido->ini + 1; 
	getch ();
	return numped;
}

void exibeFila ( FILA *pedido )
{
	int i;
	printf ("\nPedidos na Fila:\n");
	for (i=pedido->ini; i<pedido->fim; i++)
		printf ("[%i]", pedido->vetfila[i]);
	 printf ("\n=====================================================");		
        getch ();
}
