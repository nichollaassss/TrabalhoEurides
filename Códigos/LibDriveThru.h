#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define  true         1
#define  false        0

typedef struct
{
	int 	codprod;
	char    nomeprod[50];
	float   valorprod;
}
REGISTRO;

REGISTRO reg;
REGISTRO r;

int buscaNoArq (int c)
{
    int flag = 0;
    FILE *Arq;

    Arq = fopen ("PRODUTOS.DAT","r");
    if (Arq == NULL)
    {
       printf ("\nNão foi possível abrir PRODUTOS.DAT");
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

void lerDados (void)
{
     FILE * Arq;
     Arq = fopen ("PRODUTOS.DAT", "r");
     if (Arq == NULL )
     {
        printf ("\nErro ao ler PRODUTOS.DAT");
        getch();
        exit(0);
     }

     while ( !feof(Arq) )
     {
           fread ( &r, sizeof(r), 1, Arq );
           if ( !feof(Arq) )
           {
               printf ("\n%3i\t%-70s\tR$%.2f", r.codprod, r.nomeprod, r.valorprod);
           }
     }

fclose(Arq);
}
