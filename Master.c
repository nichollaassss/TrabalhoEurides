#include <stdio.h> 
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char menu (void);
void gerenciaMenu (char opc);

char menu (void)
{
char opcao;

do
{
system ("cls");
system ("color f3");
printf ("================");
printf ("\n M A S T E R ");
printf ("\n==============");
printf ("\n1. AdmProdutos");
printf ("\n2. Pedidos");
printf ("\n0. Encerrar ");
printf ("\nSua escolha: ");
fflush (stdin); opcao = getche ();

}
while (opcao<'0' || opcao>'2');

return (opcao);
}

void gerenciaMenu (char opc)
{
switch (opc)
{
case '0': exit (0); break;
case '1': system ("AdmProdutos"); break;
case '2': system ("Atendimento"); break;
}
}

int main ()
{
char op;

setlocale(LC_ALL, "");

do
{
op = menu ();
gerenciaMenu (op);
}
while ( op!= '0');

return 0;
}
