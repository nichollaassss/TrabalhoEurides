#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "LibDriveThru.h"
#include "FilaLib.h"

typedef struct 
{
        int num, cod, quant;
        char nprod[20];                 
}PEDIDO;

FILA f;
REGISTRO r;
PEDIDO p;
float TOTAL;
int ITENS;

char menu ();
void gerenciaOpcoes (char escolha);
void cardapio (void);
int buscaNoArq (int c);
void pedido (void);
void pagamento (void);
void lerDados (void);
void GravarPedido (void);
void LerPedido (void);
void fila (void);
void CondPag (char pag);
void cartao (void);
void dinheiro (void);
void pix (void);

int buscaNoArq (int c)
{
    int flag = 0;

    Arq = fopen (ARQPRODUTOS,"r");
    if (Arq == NULL)
    {
       msgProdutosDatNaoExiste();
       exit (0);
    }
    while (!feof(Arq))
    {
          fread (&reg, sizeof (reg), 1, Arq);
          if (!feof(Arq))
          if (reg.codprod == c)
          {
              flag = 1;
              break;
          }
    }
    fclose (Arq);

return (flag);
}

void GravarPedido ()
{
	FILE * Arq;	
    
    Arq = fopen ("PEDIDOS.DAT", "a");
	if (Arq == NULL )
	{
		printf ("\nErro ao abrir PEDIDOS.DAT");
		printf ("\nRetorno de fopen = %p--->NULL", Arq);
		getch();
		exit(0);
	}
	fwrite ( &p, sizeof(p), 1, Arq );
	fclose(Arq);
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

     while ( !feof(Arq) )
     {
           fread ( &r, sizeof(r), 1, Arq );
           if ( !feof(Arq) )
           {
               printf ("\n%3i\t%-70s\tR$%12.2f", r.codprod, r.nomeprod, r.valorprod);
           }
     }

fclose(Arq);
}

char menu ()
{
     char opcao;

     system ("cls");
     do
     {
            system ("cls");
            system ("color 04");
            printf ("=============================");
            printf ("\n BEM VINDO(A) AO DRIVE THRU ");
            printf ("\n=============================");
            printf ("\n1. Cardapio");
            printf ("\n2. Fazer pedido");
            printf ("\n3. Fila de espera");
            printf ("\n0. Encerrar ");
            printf ("\nSua escolha: ");
            fflush (stdin); opcao = getche ();

      }
      while (opcao<'0' || opcao>'3');

return (opcao);
}

void gerenciaOpcoes (char escolha)
{
     switch (escolha)
     {
            case '0': exit (0);         break;
            case '1': cardapio ();      break;
            case '2': pedido ();        break;
            case '3': fila ();          break;
     }
}

void cardapio (void)
{
     system ("cls");
     printf ("\t\t\t\t\tCARDAPIO");
     printf ("\n===============================================================================================");
     lerDados();
     printf ("\n===============================================================================================");
     getch();
}

void pedido (void)
{
     char opcao;
     
     TOTAL = 0;
     ITENS = 0;
     
     FILE *Arq = fopen("PEDIDOS.DAT", "w");
     if (Arq == NULL) 
     {
        printf("\nErro ao limpar PEDIDOS.DAT");
        getch();
        exit(1);
     }
     fclose(Arq); 
     p.num = p.num + 1;
     system ("cls");
     printf ("\t\t\t\t\tCARDAPIO");
     printf ("\n===============================================================================================");
     lerDados();
     printf ("\n===============================================================================================");
     do
     {
       printf ("\nQual o código do produto que deseja? ");
       fflush (stdin); scanf ("%i", &p.cod);
       if ( buscaNoArq(p.cod) == true )
       {
          strcpy(p.nprod, reg.nomeprod);
          printf ("\nQuantas unidades de %s você deseja?", reg.nomeprod);
          fflush (stdin); scanf ("%i", &p.quant);
          TOTAL = TOTAL + p.quant*reg.valorprod;
          ITENS = ITENS + p.quant;
          printf ("\nTotal parcial: %.2f", TOTAL);
          getch ();
       }
       else
       {
         printf ("\nProduto com código %i não encontrado", p.cod);
       }
         GravarPedido();
         printf ("\nPressione qualquer tecla diferente de 0 para adicionar mais itens!");
         fflush (stdin);  scanf ("%c", &opcao);
     }
     while ( opcao != '0');
     if (ITENS > 6)
     {
        insereFila(&f, p.num);        
     }
     pagamento();
}

void pagamento (void)
{
     char pag;
     
     system ("cls");
     printf ("\n\t\tRESUMO DO SEU PEDIDO");
     printf ("\n=====================================================");
     printf ("\nCODIGO\t\tPRODUTO\t\tQUANTIDADE\tVALOR");
     FILE * Arq;	
	 Arq = fopen ("PEDIDOS.DAT", "r");
	 if (Arq == NULL )
	 {
		printf ("\nErro ao ler PEDIDOS.DAT");
		printf ("\nRetorno de fopen = %p--->NULL", Arq);
		getch();
		exit(0);
	 }
	 while ( !feof(Arq) )
	 {
		fread ( &p, sizeof(p), 1, Arq );
		if ( !feof(Arq) )
		{	
               (buscaNoArq(p.cod));
               printf ("\n%3i\t\t%-20s\t%i\t%.2f", p.cod, p.nprod, p.quant, reg.valorprod*p.quant);
	    }
  }
  fclose(Arq);
  printf ("\n=====================================================");
  printf ("\n\t\tVALOR TOTAL: %.2f", TOTAL);
  printf ("\n=====================================================");
  do
  {
         printf ("\n\nPedido Num: %i", p.num);
         printf ("\n\nQual será a forma de pagamento?");
         printf ("\n1. Cartão de crédito/débito");
         printf ("\n2. Pix");
         printf ("\n3. Dinheiro");
         printf ("\nSua escolha: ");
         fflush (stdin);  scanf ("%c", &pag);
  }
  while (pag < '1' || pag > '3' );      
  CondPag (pag);
}

void CondPag (char pagamento)
{        
     switch (pagamento)
     {
            case '1':  cartao ();       break;
            case '2':  dinheiro();      break;
            case '3':  pix();           break;
     }
}
void cartao (void)
{
     printf ("\nEm construção");
     getch();
}
void dinheiro (void)
{
     printf ("\nEm construção");
     getch ();
}
void pix (void)
{
     printf ("\nEm construção");
     getch ();     
}

void fila (void)
{
     system ("cls");
     printf ("\n\t\tFILA DE ESPERA");
     printf ("\n=====================================================");
     exibeFila (&f);     
     printf ("\n=====================================================");
}

int main ()
{
    char op;

    setlocale (LC_ALL, "");
    inicializaFila(&f);

    do
    {
       op = menu();
       gerenciaOpcoes(op);
    }
    while (op != '0');

return 0;
}
