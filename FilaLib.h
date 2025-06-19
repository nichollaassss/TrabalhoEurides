/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* CONSTANTES */
#define  MAXFILA   5

/* TIPOS PRÉ-DEFINIDOS */
typedef struct{
	int   vetfila[MAXFILA];
	int   ini, fim;
} 
FILA;

/* FUNÇÕES */
void inicializaFila (FILA * algo){
	algo->ini = 0;
	algo->fim = 0;
}

int filaCheia ( FILA * algo ) 
{
	if ( algo->fim == MAXFILA )
		return 1;
	else 
		return 0;
}

int filaVazia ( FILA * algo ) 
{
	if ( algo->ini == algo->fim )
		return 1;
	else 
		return 0;
}

void insereFila ( FILA * algo, int elemento)
{
	algo->vetfila[algo->fim] = elemento; /* coloca o elemento */
	algo->fim = algo->fim + 1; /* incrementa o fim da fila */
}

int  removeFila ( FILA * algo )
{
	int nped;
	nped = algo->vetfila[algo->ini];
	algo->ini = algo->ini + 1;
	return nped; 
}

void exibeFila (FILA *algo)
{
	int i;
	printf ("\nElementos enfileirados:\n");
	for (i=algo->ini; i<algo->fim; i++)
		printf ("[%i]", algo->vetfila[i]);
		getch ();
}
