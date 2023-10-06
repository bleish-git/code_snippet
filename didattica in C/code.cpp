/***************************************************************************
 *
 *                        LE CODE
 *                     strutture FIFO
 *
 ***************************************************************************/
#include <stdlib.h>
#include <stdio.h>

typedef int tipo;

struct CD {
            tipo info;
            struct CD *next;
};

typedef struct CD elem_coda;
typedef elem_coda *coda;


void inizializza(coda *nuova, coda *fine);
int codavuota(coda nuova);
void push(coda *nuova, coda *fine, tipo elem);
void pop(coda *nuova);
tipo fronte(coda nuova);


void main(void)
{
    coda nuova; /* puntatore alla fronte della coda */
    coda fine;  /* puntatore alla fine della coda */
	tipo elem;
	char ins='\n';

	inizializza(&nuova, &fine);
	if (codavuota(nuova)) printf("\nCoda inizializzata correttamente");
	else printf("\nCoda non inizializzata");

	printf("\n\nIndica l'operazione da eseguire:");
	printf("\n'i' seguito dall'elemento da inserire in coda");
	printf("\n'd' per cancellare il prox elemento");
	printf("\n'p' per restituire il prox elemento in coda");
	printf("\n'x' per uscire\n\n");

	while (ins!='x') {
	  scanf(" %c", &ins);
	  switch (ins) {
		case 'i' : scanf("%d", &elem);
                   push(&nuova, &fine, elem);
                   break;
		case 'd' : {
                    if (codavuota(nuova)) printf("\nCoda vuota!\n");
                    else pop(&nuova);
					break;
				 }
		case 'p' : {
                    if (codavuota(nuova)) printf("\nCoda vuota!\n");
                    else {
                        printf("\n\nPrimo elemento in coda:");
                        fronte(nuova);
                        printf("\n\n");
                    }
                    break;
				 }
		default :  ;
	  }
	}


}

void inizializza(coda *nuova, coda *fine)
{
    *nuova=NULL;
    *fine=NULL;
}

int codavuota(coda nuova)
{
    if (nuova==NULL) return 1;
    else return 0;
}

/*---------------------------push--------------------------------*/
/* Inserisce in coda un elem */
void push(coda *nuova,coda *fine, tipo elem)
{
    coda temp;

    temp=(coda) malloc(sizeof(elem_coda));

    temp->info=elem;
    temp->next=NULL;
    if (*nuova==NULL)  *nuova=temp;
    else (*fine)->next=temp;
    *fine=temp;
}

/*----------------------------pop------------------------------*/
/* Elimina il primo elemento della coda, cioè la fronte */
void pop(coda *nuova)
{
    coda temp;

    temp=*nuova;
    (*nuova)=temp->next;
    free(temp);
}

/*---------------------------fronte-------------------------------*/
/*  Restituise il primo elemento in coda */
tipo fronte(coda nuova)
{
    printf("\n%d", nuova->info);
    return nuova->info;
}



