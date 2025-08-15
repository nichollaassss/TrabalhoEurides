#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "LibDriveThru.h"
#include "FilaLib.h"
#include "PagamentosLib.h"

typedef struct 
{
        int cod, quant;
        char nprod[20];                 
}PEDIDO;

PEDIDO p;
int ITENS;

char menu (void);
void gerenciaOpcoes (char escolha);
void cardapio (void);
int buscaNoArq (int c);
int pedido (void);
void pagamento (void);
void lerDados (void);
void GravarPedido (void);
void LerPedido (void);
void fila (void);
void CondPag (char pag);

char menu (void)
{
     char opcao;

     system ("cls");
     do
     {
            system ("cls");
            system ("color 04");
            printf ("===============================================");
            printf ("\n BEM VINDO(A) AO DRIVE THRU DO MICKEY & DONALD ");
            printf ("\n===============================================");
            printf ("\n1. Cardapio");
            printf ("\n2. Fazer pedido");
            printf ("\n3. Fila de espera");
            printf ("\n4. Pagamentos");
            printf ("\n5. Cartões");
            printf ("\n0. Encerrar ");
            printf ("\n===============================================");
            printf ("\nSua escolha: ");
            fflush (stdin); opcao = getche ();

      }
      while (opcao<'0' || opcao>'5');

return (opcao);
}

void gerenciaOpcoes (char escolha)
{
     switch (escolha)
     {
            case '0': exit (0);                   break;
            case '1': cardapio ();                break;
            case '2': pedido ();                  break;
            case '3': fila ();                    break;
            case '4': LerPagamento ();  getch (); break;
            case '5': LerCartao();      getch (); break;
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

int pedido (void)
{
     char opcao;
     int queue;
     
     pay.TOTAL = 0;
     ITENS = 0;
     
     FILE *Arq = fopen("PEDIDOS.DAT", "w"); fclose(Arq); 
     pay.num = pay.num + 1;
     
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
          do
          {
                          printf ("\nQuantas unidades de %s você deseja?", reg.nomeprod);
                          fflush (stdin); scanf ("%i", &p.quant);
          }
          while (p.quant == 0);                
          pay.TOTAL = pay.TOTAL + p.quant*reg.valorprod;
          ITENS = ITENS + p.quant;
          printf ("\nTotal parcial: %.2f", pay.TOTAL);
          getch ();
          GravarPedido();
          printf ("\nPressione qualquer tecla diferente de 0 para adicionar mais itens!");
          fflush (stdin);  scanf ("%c", &opcao);
       }
       else
       {
         printf ("\nProduto com código %i não encontrado", p.cod);
       }
     }
     while ( opcao != '0');
     if (ITENS > 6)
     {
        queue = filaCheia(&f);
        if (queue == 1)
        {
           printf ("\nImpossivel adicionar pedido a fila!"); 
           getch ();
           return (1);
        }      
        else
        {
            insereFila(&f, pay.num);
            band = 1;
        }        
     }
     pagamento();
}

void pagamento (void)
{
     
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
  printf ("\n\t\tVALOR TOTAL: %.2f", pay.TOTAL);
  printf ("\n=====================================================");
  do
  {
         printf ("\n\nPedido Num: %i", pay.num);
         printf ("\n\nQual será a forma de pagamento?");
         printf ("\n1. Cartão de crédito");
         printf ("\n2. Cartão de débito");
         printf ("\n3. Pix");
         printf ("\n4. Dinheiro");
         printf ("\nSua escolha: ");
         fflush (stdin);  scanf ("%c", &pag);
  }
  while (pag < '1' || pag > '4' );      
  CondPag (pag);
}

void CondPag (char pagamento)
{        
     switch (pagamento)
     {
            case '1': case '2': cartao (pagamento);       break;
            case '3':  pix(pagamento);                    break;
            case '4':  dinheiro(pagamento);               break;
     }
}

void fila (void)
{
     char choose;
     int fil;
     
     system ("cls");
     printf ("\n\t\tFILA DE ESPERA");
     printf ("\n=====================================================");
     exibeFila (&f);
     fil = filaCheia(&f);
     if (fil == 1)
     {
        do
        {
               printf ("\nDeseja esvaziar a fila?[S = Sim e N = Não]");
               printf ("\nSua escolha: ");
               fflush (stdin);  scanf ("%c", &choose);
        }
        while (choose != 'S' && choose != 'N');
        switch (choose)
        {
            case 'S': inicializaFila(&f); printf ("\nFila esvaziada!"); getch ();  break;
            case 'N':                                                              break;       
        }      
     }
     
}

void GravarPedido (void)
{
	FILE * Arq;	
    
    Arq = fopen ("PEDIDOS.DAT", "a");
	if (Arq == NULL )
	{
		printf ("\nErro ao abrir PEDIDOS.DAT");
		getch();
		exit(0);
	}
	fwrite ( &p, sizeof(p), 1, Arq );
	fclose(Arq);
}

int main ()
{
    char op;

    setlocale (LC_ALL, "");
    FILE *Arq = fopen("PAGAMENTOS.DAT", "w"); FILE *arq = fopen("CARTOES.DAT", "w"); fclose (Arq); fclose (arq);
    inicializaFila(&f);

    do
    {
       op = menu();
       gerenciaOpcoes(op);
    }
    while (op != '0');

return 0;
}
