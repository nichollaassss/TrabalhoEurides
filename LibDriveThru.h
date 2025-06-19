/* Bibliotecas */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

/* Constantes */
#define  ARQPRODUTOS  "PRODUTOS.DAT"
#define  ARQRELATORIO "RELAT.TXT"
#define  true         1
#define  false        0

/* Tipos pr�-definidos */
typedef struct
{
	int 	codprod;
	char    nomeprod[50];
	float   valorprod;
}
REGISTRO;

/* Vari�veis de mem�ria */
FILE *Arq;
FILE *Rel;
REGISTRO reg;

/* Fun��es */
void msgErroAbrirProdutosDat (void)
{
	system("cls");
	printf("\nERRO AO ABRIR PRODUTOS.DAT");
	getch();
	exit(0);
}

void msgProdutosDatNaoExiste (void)
{
	system("cls");
	printf("\nPRODUTOS.DAT N�O EXISTE");
	getch();
}

void msgErroAbrirProdutosDatLeitura(void)
{
	system("cls");
	printf("\nERRO AO ABRIR PRODUTOS.DAT PARA LEITURA");
	getch();
	exit(0);
}

void msgErroGerarRelatorio(void)
{
	system("cls");
	printf("\nERRO AO GERAR ARQUIVO DE RELAT�RIO [%s]", ARQRELATORIO);
	getch();
	exit(0);
}

int resgataCodigo (void)
{
	REGISTRO r; 
	long tamanhoArquivo;
	FILE *A = fopen(ARQPRODUTOS, "r");
	if (A==NULL)
	{
		msgProdutosDatNaoExiste();
		return (0);
	}
	else
	{
		/* Move o ponteiro do arquivo para o final */
    	fseek(A, 0, SEEK_END);
    	/* obt�m a posi��o atual do ponteiro, 
		   que � o tamanho do arquivo em bytes */
    	tamanhoArquivo = ftell(A);
    	/* Fecha o arquivo */
    	fclose(A);
		/* Calcula a quantidade de registros no arquivo */
    	if (tamanhoArquivo == 0) /* Verifica se o arquivo est� vazio */
    		return (tamanhoArquivo);
		else
			return (tamanhoArquivo/sizeof(REGISTRO));
	}
}

int resgataCodigoSequencial (void)
{
	REGISTRO r; 
	int cont=0;
	FILE *A = fopen(ARQPRODUTOS, "r");
	if (A==NULL)
	{
		msgProdutosDatNaoExiste();
		return (0);
	}
	else
	{
		while (!feof(A))
		{
			fread(&r, sizeof(r), 1, A);
			if (!feof(A))
			{
				printf ("\n[%03i][%-50s][R$%.2f]", 
				r.codprod, r.nomeprod, r.valorprod);
				cont++;
			}
		}
		fclose(A);
		printf ("\n------>�ltimo c�digo = %i", cont); getch();
		return (cont);
	}
}
