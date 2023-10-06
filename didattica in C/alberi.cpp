/*****************************************************************
 *
 *              ALBERI BINARI e loro gestione
 *
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef int tipo;           /* tipo dei dati memorizzati nell'albero */

struct AB {
            tipo info;              /* dato memorizzato */
            int count;              /* numero di volte di immissione del dato*/
            struct AB *sx,*dx;      /* figli del nodo */
};

typedef struct AB nodo;
typedef nodo *palbero;

void inizializza(palbero *temproot);
int alberovuoto(palbero temproot);
int ricerca(palbero temproot, tipo elem);
int ricerca_ord(palbero temproor, tipo elem);
void cancella_ord(palbero *temproot, tipo elem);
void inserisci_ord(palbero *temproot, tipo elem);
void stampa_preord_sx(palbero temproot);
void stampa_ord(palbero temproot);


void main(void)
{
	palbero root;
	tipo elem;
	char ins='\n';

	inizializza(&root);
	if (alberovuoto(root)) printf("\nAlbero inizializzato correttamente");
	else printf("\nAlbero non inizializzato");

	printf("\n\nIndica l'elemento da inserire o modificare, precedendolo da:");
	printf("\n'i' se è da inserire in ordine");
	printf("\n'd' se è da cancellare");
	printf("\n's' se è da cercare");
	printf("\n'c' se è da cercare con l'algoritmo di ricerca binaria");
	printf("\n'p' per stampare l'albero in preordine sinistro");
   	printf("\n'P' per stampare l'albero in modo ordinato");
	printf("\n'x' per uscire\n\n");

	while (ins!='x') {
	  scanf(" %c", &ins);
	  switch (ins) {
		case 'i' : scanf("%d", &elem);
                   inserisci_ord(&root, elem);
                   break;
		case 's' : {
                    scanf("%d", &elem);
					if (!ricerca(root, elem)) printf("\nNon trovato\n\n");
					else printf("\nElemento trovato\n\n");
					break;
				 }
        case 'c' : {
                    scanf("%d", &elem);
					if (!ricerca_ord(root, elem)) printf("\nNon trovato\n\n");
					else printf("\nElemento trovato\n\n");
					break;
				 }
		case 'd' : {
                    scanf("%d", &elem);
					if (ricerca_ord(root,elem)) cancella_ord(&root, elem);
					else printf("\nElemento non trovato\n\n");
					break;
				 }
		case 'p' : {
					printf("\n\nInizio albero\n");
					stampa_preord_sx(root);
					printf("\n\nFine albero\n\n");
                    break;
				 }
        case 'P' : {
					printf("\n\nInizio albero\n");
					stampa_ord(root);
					printf("\n\nFine albero\n\n");
				 }
		default :  ;
	  }
	}
}

/*------------------------------inizializza-------------------------------*/
void inizializza(palbero *temproot)
{
    *temproot=NULL;
}

/*-----------------------------alberovuoto---------------------------------*/
int alberovuoto(palbero temproot)
{
    if (temproot==NULL) return 1;
    else return 0;
}

/*------------------------------ricerca-----------------------------------*/
int ricerca(palbero temproot, tipo elem)
{
    if (temproot==NULL) return 0;
    else if (temproot->info==elem) return 1;
        else return (ricerca(temproot->sx, elem) ||
                        ricerca(temproot->dx, elem));
}
/*---------------------------ricerca_ord---------------------------------*/
/*Ricerca l'elemento elem nell'albero ordinato puntato da temproor */
int ricerca_ord(palbero temproot, tipo elem)
{
    if (temproot->info==elem) return 1;
    else if(temproot==NULL) return 0;
    else if(temproot->info < elem) return ricerca_ord(temproot->dx, elem);
    else return ricerca_ord(temproot->sx, elem);
}

/*--------------------------inserisci_ord--------------------------------*/
/* Inserisce l'elemento elem nell'albero ordinato puntato da temproot,
    mantenendolo ordianto */
void inserisci_ord(palbero *temproot, tipo elem)
{
    if (*temproot==NULL) {
        *temproot=(palbero) malloc(sizeof(nodo));
        (*temproot)->info=elem;
        (*temproot)->dx=NULL;
        (*temproot)->sx=NULL;
        (*temproot)->count=1;
    }
    else if ((*temproot)->info==elem)
        (*temproot)->count++;   /*elemento ripetuto*/
    else if ((*temproot)->info > elem)
            inserisci_ord(&((*temproot)->sx), elem);
    else if ((*temproot)->info < elem)
            inserisci_ord(&((*temproot)->dx), elem);

}

/*---------------------------stampa_preord_sx-----------------------*/
/* Stampa gli elementi dell'albero visitandolo in preordine sinistro,
    cioè stampa la radice dell'albero, seguita dalla visita del sotto-
    albero di sinistra seguita a sua volta dalla visita del sottoalbero
    di destra. */

void stampa_preord_sx(palbero temproot)
{
    if (temproot!=NULL) {
        printf(" %d \n", temproot->info);
        stampa_preord_sx(temproot->sx);
        stampa_preord_sx(temproot->dx);
    }
}

/*-----------------------------stampa_ord------------------------------*/
/* Stampa il contenuto dell'albero in modo ordinato: ad ogni nodo viene
stampato prima il sotto albero di sinistra, quindi l'elemento del nodo in
esame e quindi il sottoalbero di destra */
void stampa_ord(palbero temproot)
{
    if (temproot!=NULL) {
        stampa_ord(temproot->sx);
        printf(" %d ripetuto %d volta/e\n", temproot->info, temproot->count);
        stampa_ord(temproot->dx);
    }
}

/*-----------------------------------cancella_ord-----------------------*/
/* Cancella un elemento da un albero ordinato mantenendolo tale */
void cancella_ord(palbero *temproot, tipo elem)
{
    nodo *nodo_da_canc, *padre, *figlio, *temp;

    if (*temproot!=NULL)
        if ((*temproot)->info > elem)
            cancella_ord(&((*temproot)->sx), elem);
        else if ((*temproot)->info < elem)
            cancella_ord(&((*temproot)->dx), elem);
        else {/* allora il nodo contiene l'elemento cercato */
            nodo_da_canc=*temproot; /* si memorizza il puntatore al nodo da canc*/
            if (nodo_da_canc->sx==NULL) {
                *temproot=nodo_da_canc->dx;
                free(nodo_da_canc);
            }
            else if (nodo_da_canc->dx==NULL) {
                *temproot=nodo_da_canc->sx;
                free(nodo_da_canc);
            }
            else /* il nodo da eliminare ha entrambi i figli */
                if (nodo_da_canc->dx->sx==NULL) {
                    /* Se il figlio destro del nodo da eliminare non ha
                    figlio sinistro allora è esso stesso che deve rimpiazzare il
                    nodo da eliminare */
                    nodo_da_canc->info=nodo_da_canc->dx->info;
                    temp=nodo_da_canc->dx;
                    nodo_da_canc->dx=nodo_da_canc->dx->dx;
                    free(temp);
                }
                else {
                    /* In caso contrario si cerca il nodo più a sinistra del
                    sottoalbero di destra del nodo da eliminare: esso rimpiazzerà
                    il nodo da eliminare e sarà distrutto */
                    padre=nodo_da_canc;
                    figlio=nodo_da_canc->dx;
                    while (figlio->sx!=NULL) {
                        padre=figlio;
                        figlio=figlio->sx;
                    }
                    nodo_da_canc->info=figlio->info;
                    /* Viene rimpiazzata l'informazione del nodo da eliminare
                    con il contentuto del nodo che lo dovrà rimpiazzare */
                    padre->sx=figlio->sx;
                    free(figlio);
                }
}




}





