/***************************************************************************
 *
 *                     LE PILE o STACK
 *                     strutture LIFO
 *
 ***************************************************************************/
#include <stdlib.h>
#include <stdio.h>

typedef int tipo;

struct PL {
            tipo info;
            struct PL *prec;
};

typedef struct PL elem_pila;
typedef elem_pila *pila;


void inizializza(pila *nuova);
int pilavuota(pila nuova);
void push(pila *nuova, tipo elem);
void pop(pila *nuova);
tipo top(pila nuova);


void main(void)
{
    pila stack;
	tipo elem;
	char ins='\n';

	inizializza(&stack);
	if (pilavuota(stack)) printf("\nStack inizializzato correttamente");
	else printf("\nStack non inizializzato");

	printf("\n\nIndica l'operazione da eseguire:");
	printf("\n'i' seguito dall'elemento da inserire in cima");
	printf("\n'd' per cancellare l'elemento in cima");
	printf("\n'p' per restituire l'elemento in cima senza eliminarlo");
	printf("\n'x' per uscire\n\n");

	while (ins!='x') {
	  scanf(" %c", &ins);
	  switch (ins) {
		case 'i' : scanf("%d", &elem);
                   push(&stack, elem);
                   break;
		case 'd' : {
                    pop(&stack);
					break;
				 }
		case 'p' : {
					printf("\n\nElemento in cima:");
                    top(stack);
                    printf("\n\n");
                    break;
				 }
		default :  ;
	  }
	}


}

void inizializza(pila *nuova)
{
    *nuova=NULL;
}

int pilavuota(pila nuova)
{
    if (nuova==NULL) return 1;
    else return 0;
}

/*-----------------------------push--------------------------------*/
/* Inserisce un elemento in cima alla pila */
void push(pila *nuova, tipo elem)
{
    pila temp;

    temp=(pila) malloc(sizeof(elem_pila));

    temp->info=elem;
    temp->prec=*nuova;

    *nuova=temp;
}
/*--------------------------------pop------------------------------*/
/* Elimina l'elemento in cima alla pila */
void pop(pila *nuova)
{
    pila temp;

    if (pilavuota(*nuova)) printf("\n\nPila vuota\n");
    else {
        temp=*nuova;
        *nuova=temp->prec;
        free(temp);
    }
}
/* ------------------------------top--------------------------------*/
/* Restituisce l'elemento in cima alla pila, senza eliminarlo */
tipo top(pila nuova)
{
    if (pilavuota(nuova)) printf("\n\n!!!!!PILA VUOTA!!!!");
    else {
        printf("\n%d", nuova->info);
        return nuova->info;
    }
}
