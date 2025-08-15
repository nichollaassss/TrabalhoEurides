#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct 
{
        int num; 
        char pag[30];
        float TOTAL;                 
}PAGAMENTOS;

typedef struct
{
     char numcard[17];
     int numped;   
}CARTAO;

CARTAO c;
PAGAMENTOS pay;
char card[17];
char pag;
int band;

void cartao (char pag);
void dinheiro (char pag);
void pix (char pag);
void GravarPagamento ();
void LerPagamento ();
void CadastraCartao ();
void LerCartao ();
void Leve ();

void cartao (char pago)
{
     int i, flag;
     
     switch (pago)
     {
            case '1':  strcpy(pay.pag, "Crt de crédito"); break;
            case '2':  strcpy(pay.pag, "Crt de débito");  break;
     }       
     do
     {
            flag = 1;
            printf ("\nInsira os 16 dígitos do seu cartão: ");
            fflush (stdin);   scanf ("%s", &card);
            if (strlen(card) != 16)
            {
                      printf ("\nQuantidade de digitos incorreta!");
                      getch ();
                      flag = 0;                  
            } 
            else
            {
                      for (i=0; i<16; i++)
                      {
                              if(card[i]<'0'||card[i]>'9')
                              {
                                     printf ("\nDigitos invalidos!");
                                     flag = 0; 
                                     break;                         
                              }
                      }
            if (flag == 1)
            printf ("\nPEDIDO CONFIRMADO!");
            CadastraCartao();
            getch ();
            }   
     }  
     while (flag == 0);  
     GravarPagamento ();   
     if (band != 1)
        Leve (); 
}
void dinheiro (char pago)
{
     printf ("\nPEDIDO CONFIRMADO!");
     getch ();
     strcpy(pay.pag, "Dinheiro");
     GravarPagamento ();
     if (band != 1)
        Leve ();
}
void pix (char pago)
{
     printf ("\nPEDIDO CONFIRMADO!");
     getch ();   
     strcpy(pay.pag, "Pix         ");  
     GravarPagamento ();
     if (band != 1)
        Leve ();
}

void Leve (void)
{
     system ("cls");
     switch (pag)
     {
            case '1': case '2':  system ("color 05"); printf ("\nPedido pago com %s", pay.pag); printf ("\nLEVE SEU PEDIDO!"); getch ();       break;  
            case '3': system ("color 01"); printf ("\nPedido pago com %s", pay.pag); printf("\nLEVE SEU PEDIDO!"); getch ();                   break; 
            case '4': system ("color 02"); printf ("\nPedido pago com %s", pay.pag); printf("\nLEVE SEU PEDIDO!"); getch ();                   break;           
     }
     
}

void GravarPagamento (void)
{
	FILE * Arq;	
    
    Arq = fopen ("PAGAMENTOS.DAT", "a");
	if (Arq == NULL )
	{
		printf ("\nErro ao abrir PAGAMENTOS.DAT");
		getch();
		exit(0);
	}
	fwrite ( &pay, sizeof(pay), 1, Arq );
	fclose(Arq);
}

void LerPagamento (void)
{
     FILE * Arq;
     
     system ("cls");
     printf ("Num do pedido\tForm de pagamento\tTotal");
     printf ("\n===================================================");
     Arq = fopen ("PAGAMENTOS.DAT", "r");
     if (Arq == NULL )
     {
        printf ("\nErro ao ler PAGAMENTOS.DAT");
        getch();
        exit(0);
     }

     while ( !feof(Arq) )
     {
           fread ( &pay, sizeof(pay), 1, Arq );
           if ( !feof(Arq) )
           {
               printf ("\n%5i\t\t%s\t\tR$%.2f", pay.num, pay.pag, pay.TOTAL);
           }
     }
     printf ("\n===================================================");
fclose(Arq);
}

void CadastraCartao (void)
{
     FILE * Arq;
     int i;	
    
     c.numped = pay.num;
     strcpy (c.numcard, card);
     for (i=4; i<=11; i++)
     {
         c.numcard[i] = '*';    
     }
     Arq = fopen ("CARTOES.DAT", "a");
	 if (Arq == NULL )
	 {
		     printf ("\nErro ao abrir CARTOES.DAT");
		     getch();
		     exit(0);
     }
	 fwrite ( &c, sizeof(c), 1, Arq );
	 fclose(Arq);   
}

void LerCartao (void)
{
     FILE * Arq;
     
     system ("cls");
     printf ("Num do pedido\tNum do cartao");
     printf ("\n====================================");
     Arq = fopen ("CARTOES.DAT", "r");
     if (Arq == NULL )
     {
        printf ("\nErro ao ler CARTOES.DAT");
        getch();
        exit(0);
     }

     while ( !feof(Arq) )
     {
           fread ( &c, sizeof(c), 1, Arq );
           if ( !feof(Arq) )
           {
               printf ("\n%i\t\t%s", c.numped, c.numcard);
           }
     }
     printf ("\n====================================");
fclose(Arq);
}
