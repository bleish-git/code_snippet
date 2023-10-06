/* ******************************************************************
 *
 *                          LISTE DINAMICHE
 *
 ********************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
				int val;
				struct EL *next;
			   } lista;
typedef lista *plista;

void inizializza(plista *temp);
int lista_vuota(plista mia);
int ricerca(plista mia, int elem);
void ins_up(plista *mia, int elem);
void ins_down(plista *mia, int elem);
void cancella(plista *mia, int elem);
void stampa(plista mia);


int main(void)
{
	plista nuova;
	int elem;
	char ins='\n';

	inizializza(&nuova);
	if (lista_vuota(nuova)) printf("\nLista inizializzata correttamente");
	else printf("\nLista non inizializzata");

	printf("\nIndica l'elemento da inserire o modificare, precedendolo da:");
	printf("\n'u' se Š da inserire in testa");
	printf("\n'd' se Š da inserire in coda");
	printf("\n'c' se Š da cancellare");
	printf("\n's' se Š da cercare");
	printf("\n'p' per stampare la lista");
	printf("\n'x' per uscire\n\n");

	while (ins!='x') {
	  scanf(" %c %d", &ins, &elem);
	  switch (ins) {
		case 'u' : ins_up(&nuova, elem); break;
		case 'd' : ins_down(&nuova, elem); break;
		case 's' : {
					if (!ricerca(nuova, elem)) printf("\nNon trovato\n\n");
					else printf("\nElemento trovato\n\n");
					break;
				 }
		case 'c' : {
					if (ricerca(nuova,elem)) cancella(&nuova, elem);
					else printf("\nElemento non trovato\n\n");
					break;
				 }
		case 'p' : {
					printf("\n\nInizio lista\n");
					stampa(nuova);
					printf("\n\nFine lista\n\n");
				 }
		default :  ;
	  }
	}
	return 0;
}


void inizializza(plista *temp)
{
	*temp=NULL;
}

int lista_vuota(plista mia)
{
	return (mia==NULL)? 1 : 0;
}

/* ricerca sequenziale di un elemento */
int ricerca(plista mia, int elem)
{
	int trovato=0;
	lista *cursore;

	if (!lista_vuota(mia)){
		cursore=mia;
		while (trovato==0 && cursore!=NULL) {
			trovato=(cursore->val==elem);
			cursore=cursore->next;
		}
	}
	return trovato;
}
void ins_up(plista *mia, int elem)
{
	lista *punt;

	punt=malloc(sizeof(lista));

	punt->val=elem;
	punt->next=*mia;
	*mia=punt;
}

void ins_down(plista *mia, int elem)
{
	if (*mia==NULL) {
					lista *punt;

					punt=malloc(sizeof(lista));

					punt->val=elem;
					punt->next=NULL;

					*mia=punt;
	}
	else ins_down(&((*mia)->next), elem);
}

void cancella(plista *mia, int elem)
{
	lista *punt;

	if(lista_vuota(*mia)==0)
		if ((*mia)->val==elem) {
			punt=*mia;
			*mia=(*mia)->next;
			free(punt);
		}
		else cancella(&((*mia)->next), elem);
}
void stampa(plista mia)
{
	if (mia==NULL) return;
	else {
		  printf("\n %d", mia->val);
		  stampa(mia->next);
	}
}