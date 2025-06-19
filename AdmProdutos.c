#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

typedef   struct
{
	int		codprod;
	char	descrprod[50];
	float	custoprod;
}
CARDAPIO;

CARDAPIO vet[10] = { {1, "X-Tudo", 23.90}, {2, "X-Bacon", 20.90}, {3, "X-Burguer", 15.90}, {4, "X-Egg", 17.90}, {5, "Batata frita", 12.90}, {6, "Coca-Cola", 8.90}, {7, "Pepsi Twist", 7.90}, {8, "Guarana", 7.90}, {9, "Milk-shake", 14.90}, {10, "Casquinha", 3.90}};
CARDAPIO r;

void capturaDados (void);
void gravarDados( void );
void lerDados (void);
char menu (void);
void gerencia(char opc);
void cadastroDefault (void);

void capturaDados (void)
{
	printf ("\nDigite o código: ");
	fflush(stdin); scanf ("%i", &r.codprod);
	printf ("\nDigite a descrição do produto: ");
	fflush(stdin); gets(r.descrprod);
	printf ("\nDigite o custo unitário do produto: ");
	fflush(stdin); scanf ("%f", &r.custoprod);
}

void gravarDados( void )
{
	FILE * Arq;	
	Arq = fopen ("PRODUTOS.DAT", "a");
	if (Arq == NULL )
	{
		printf ("\nErro ao abrir PRODUTOS.DAT");
		printf ("\nRetorno de fopen = %p--->NULL", Arq);
		getch();
		exit(0);
	}
	else
	{
		printf ("\nPRODUTOS.DAT alocado em: %p", Arq);
		getch();
	}
	fwrite ( &r, sizeof(r), 1, Arq );
	fclose(Arq);
	printf ("\nDados gravados com sucesso");
	getch();
}

void lerDados (void)
{
	FILE * Arq;	
	Arq = fopen ("PRODUTOS.DAT", "r");
	if (Arq == NULL )
	{
		printf ("\nErro ao ler PRODUTOS.DAT");
		printf ("\nRetorno de fopen = %p--->NULL", Arq);
		getch();
		exit(0);
	}
	else
	{
		printf ("\nPRODUTOS.DAT aberto para leitura: %p", Arq);
		getch();
	}
	while ( !feof(Arq) )
	{
		fread ( &r, sizeof(r), 1, Arq );
		if ( !feof(Arq) )
		{	
		    printf ("\n%3i\t%-100s\tR$%12.2f", r.codprod, r.descrprod, r.custoprod);
	    }
	}
	fclose(Arq);
	getch();
}

char menu (void)
{   char opc;
    do
    {	system("cls");
		printf ("\n  ADM DE PRODUTOS");
		printf ("\n=================");
		printf ("\n 1. CADASTRA");
		printf ("\n 2. CONSULTA");
		printf ("\n 3. CADASTRO DEFAULT");
		printf ("\n 0. ENCERRA ");
		printf ("\n------------");
		printf ("\nSUA ESCOLHA: "); 
		fflush (stdin); opc=getche();
	}while ( opc<'0' || opc>'3' );
	return (opc);
}

void gerencia(char opc)
{	switch (opc)
	{
		case '0': exit(0); break;
		case '1':
			{
				capturaDados();
    			gravarDados();	
			}
		break;
		case '2': lerDados(); break;
		case '3': cadastroDefault(); break;
	}
}

void cadastroDefault (void)
{
	FILE *Arq, *Relat;
	int i;
	Arq = fopen ("PRODUTOS.DAT" , "w");
	if ( Arq == NULL)
	{
		printf ("erro"); getch(); exit(0);
	}
	Relat = fopen ("RELATPRODUTOS.TXT" , "w");
	if ( Relat == NULL)
	{
		printf ("erro ao gerar RELATPRODUTOS.TXT"); getch(); exit(0);
	}
	fwrite (vet, sizeof(vet), 1, Arq);
	fclose(Arq);
	printf ("\nDados default cadastrados em PRODUTOS.DAT");
	getch();
	fprintf (Relat, "\n  ADM DE PRODUTOS");
	for (i=0; i<10; i++)
		fprintf (Relat, "\n%3i\t%-100s\tR$%12.2f", vet[i].codprod, vet[i].descrprod, vet[i].custoprod);
	fclose (Relat);
	system ("notepad RELATPRODUTOS.TXT");
}
int 	main()
{	char op;
	setlocale(LC_ALL, "");
	do
	{
		op = menu();
		gerencia (op);
	}
	while (op!='0');
	return 0;
}
