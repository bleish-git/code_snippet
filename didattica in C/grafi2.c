/**************************************************************************
 *
 *                              GRAFI ORIENTATI
 *                              e loro gestione
 *
 **************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char  tipo[10];

struct A {                    /* Definisce la lista dei successori*/
            tipo info;
            struct A *next;
};

typedef struct A lista;
typedef lista *plista;

struct NG {                 /* Definisce la lista dei nodi di un grafo */
            tipo info;
            struct NG *proxnodo;
            lista *succ;
};
typedef struct NG nodo;
typedef nodo *pnodo;

/* Tipo coda di pnodo */
struct CD {
            pnodo info;
            struct CD *next;
};

typedef struct CD elem_coda;
typedef elem_coda *coda;

/* tipo matrice bidimensionale */
typedef int *righe;         /* questo è array di interi corrispondente alle riga*/
typedef righe *matrice;	   /* questo è un array di puntatori alle righe */


/* Funzioni che gestiscono il tipo nodo */
void inizializza(pnodo *grafo);
pnodo ricerca_nodo(pnodo grafo, tipo elem);
void inserisci_nodo(pnodo *grafo, tipo elem);
void cancella_nodo(pnodo *grafo, tipo elem);
void stampa(pnodo grafo);
void bfs(pnodo grafo);
void dfs(pnodo grafo, plista *visitati);
int ricerca_cammino(pnodo temp, tipo elem, tipo elem2);

/* Funzioni che gestiscono il tipo lista */
void lins_down(plista *temp, tipo elem);
void collega(pnodo *grafo, tipo elem1, tipo elem2);
void cancella_arco(pnodo *grafo, tipo elem1, tipo elem2);
void lcancella(plista *temp, tipo elem);
void lcancella_successori(plista *temp);
int ricerca_arco(pnodo temp, tipo elem, tipo elem2);
void lstampa(pnodo grafo);
int lricerca(plista mia, tipo elem);

/* Funzioni che gestiscono il tipo coda */
void inizializza_coda(coda *nuova, coda *fine);
int codavuota(coda nuova);
void push(coda *nuova, coda *fine, pnodo elem);
void pop(coda *nuova);
pnodo fronte(coda nuova);

/* Funzioni che gestiscono il tipo matrice bidimensionale*/
void allocamatrice(matrice *temp, int n, int m);

/* Altre funzioni*/
int lricerca(plista mia, tipo elem);
int contanodi(pnodo grafo);

void main(void)
{
    pnodo grafo, temp;
	tipo elem, elem2;
	char ins='\n';

	inizializza(&grafo);

	printf("\n\nIndica l'operazione da eseguire:");
	printf("\n'i' seguito dal nodo da inserire nel grafo");
    printf("\n'I' seguito da due nodi per collegarli con arco");
	printf("\n'd' seguito da un nod per cancellarlo con tutti i suoi colleg.");
	printf("\n'D' seguito da due nodi per cancellare l'arco che li collega");
	printf("\n's' seguito da un nodo per cercarlo nel grafo");
	printf("\n'S' seguito da due nodi per cercare l'arco corrispondente");
	printf("\n'p' per stampare il grafo");
    printf("\n'b' per visitare il grafo in ampiezza");
    printf("\n'v' per visitare il grafo in profondità");
	printf("\n'c' seguito da due nodi per vedere se sono collegati");	
	printf("\n'x' per uscire\n\n");

	while (ins!='x') {
	  scanf(" %c", &ins);
	  switch (ins) {
		case 'i' :
                    scanf("%s", elem);
                    inserisci_nodo(&grafo, elem);
                    break;
        case 'I' :
                    scanf("%s", elem);
                    scanf("%s", elem2);
                    collega(&grafo, elem, elem2);
                    break;
		case 'd' :
                    scanf("%s", elem);
                    cancella_nodo(&grafo, elem);
					break;
        case 'D' :
                    scanf("%s", elem);
                    scanf("%s", elem2);
                    cancella_arco(&grafo, elem, elem2);
					break;
        case 's' :
                    scanf("%s", elem);
                    if (ricerca_nodo(grafo, elem)==NULL)
                        printf("\nElemento non trovato\n");
                    else printf("\nElemento trovato.\n");
                    break;
        case 'S' :

                    scanf("%s", elem);
                    scanf("%s", elem2);
                    if (ricerca_arco(grafo, elem, elem2)!=0)
                        printf("\nNodo %s punta a %s\n", elem, elem2);
					else 
						printf("\nArco non trovato");
                    break;
		case 'p' :
                    printf("\n\nInizio:");
                    stampa(grafo);
                    printf("\n\n");
                    break;
        case 'b' :
                    printf("\n\nVisita in ampiezza:\n");
                    bfs(grafo);
                    printf("\n\n");
                    break;
        case 'v' :  {
                    plista visitati=NULL;

                    printf("\n\nNumero nodi %d\n", contanodi(grafo));
                    printf("\nVisita in profondità:\n");
                    dfs(grafo, &visitati);
                    printf("\n\n");
                    break;
					}
		case 'c' :	
					scanf("%s", elem);
					scanf("%s", elem2);
					if (ricerca_cammino(grafo, elem, elem2)!=0)
						printf("\nEsiste cammino che va da %s a %s.\n", elem, elem2);
					else
						printf("\nNon esite cammino\n");
					break;
		default :  ;
	  }
	}
}

void inizializza(pnodo *grafo)
{
    *grafo=NULL;
}
/*------------------------------ricerca_nodo-------------------------------*/
/* Ricerca nel grafo il nodo chiamato elem, visitando la lista di nodi puntata
 * da grafo e restituendone il puntatore in caso di esito positivo */
pnodo ricerca_nodo(pnodo grafo, tipo elem)
{
    if (grafo==NULL) return NULL;
    else if (strcmp(grafo->info,elem)==0) return grafo;
    else return ricerca_nodo(grafo->proxnodo, elem);
}
/*-----------------------------collega---------------------------------------*/
/* Supponendo il grafo orientato, viene creato un arco orientato da
 * elem1 a elem2 */
void collega(pnodo *grafo, tipo elem1, tipo elem2)
{
    pnodo temp1;

    if ((temp1=ricerca_nodo(*grafo, elem1))==NULL ||
                        ricerca_nodo(*grafo, elem2)==NULL)
        printf("\n\nUno dei due nodi non è stato trovato.\n");
    else
        lins_down(&(temp1->succ), elem2);
}

/*--------------------------------lins_down------------------------------------*/
/* Inserisce un elemento in coda alla lista dei successori*/
void lins_down(plista *temp, tipo elem)
{
    if (*temp==NULL) {
                        lista *punt;

                        punt=(lista *) malloc(sizeof(lista));
                        strcpy(punt->info,elem);
                        punt->next=NULL;
                        *temp=punt;
    }
    else lins_down(&((*temp)->next), elem);
}

/*---------------------------cancella_arco------------------------------------*/
/* Cancella, se esiste, l'arco che va da elem1 a elem2 */
void cancella_arco(pnodo *grafo, tipo elem1, tipo elem2)
{
    pnodo temp1;

    if ((temp1=ricerca_nodo(*grafo, elem1))==NULL ||
                        ricerca_nodo(*grafo, elem2)==NULL)
        printf("\n\nUno dei due nodi non è stato trovato");
    else lcancella(&(temp1->succ),elem2);
}

/*------------------------------lcancella-----------------------------------*/
/* cancella un elemento, se esiste, dalla lista dei successori */
void lcancella(plista *temp, tipo elem)
{
    lista *punt;

    if (*temp!=NULL)
        if (strcmp((*temp)->info,elem)==0) {
            punt=*temp;
            *temp=(*temp)->next;
            free(punt);
        }
        else lcancella(&((*temp)->next), elem);
}

/*------------------------------inserisci_nodo----------------------------*/
/* Inserisci un nuovo nodo nel grafo, chiamandolo elem */
void inserisci_nodo(pnodo *grafo, tipo elem)
{
	if (*grafo==NULL) {
					nodo *punt;

					punt=(nodo *) malloc(sizeof(lista));

					strcpy(punt->info,elem);
					punt->proxnodo=NULL;
                    punt->succ=NULL;

					*grafo=punt;
	}
	else inserisci_nodo(&((*grafo)->proxnodo), elem);
}

/*----------------lcancella_successori---------------------------------*/
/* Cancella la lista dei successori relativa a un nodo, ovvero tutti gli
    archi da esso uscenti */
void lcancella_successori(plista *temp)
{
    lista *punt;

    while ((*temp)!=NULL) {
            punt=*temp;
            *temp=punt->next;
            free(punt);
    }
}

/*------------------------------ricerca_arco-----------------------*/
/* Ricerca un arco diretto verso un particolare nodo, */
int ricerca_arco(pnodo grafo, tipo elem, tipo elem2)
{
    pnodo temp;
	int trovato=0;
	lista *cursore;


    if ((temp=ricerca_nodo(grafo, elem))!=NULL && ricerca_nodo(grafo, elem2)!=NULL ) { 
			cursore=temp->succ;
			while (trovato==0 && cursore!=NULL) {
				if (strcmp(cursore->info,elem2)==0) trovato=1;
				cursore=cursore->next;
			}
	}
	return trovato;
}

/*-------------------------------cancella_nodo-------------------------*/
/* Cancella un nodo dal grafo, cioè dalla lista dei nodi, e tutti gli
    archi entranti e uscenti.
   L'algoritmo scorre la lista dei nodi; se trova il nodo in questione lo cancella
   con tutta la sua lista dei successori; se il nodo non è quello da cancellare,
   visita la sua lista dei successori per cercare se vi è il nodo da cancellare
   e , eventualmente, per cancellarlo.
*/
void cancella_nodo(pnodo *grafo, tipo elem)
{
    pnodo temp;
	
	if(*grafo!=NULL) {
		if (strcmp((*grafo)->info,elem)==0) {
			temp=*grafo;
			*grafo=(*grafo)->proxnodo;
			lcancella_successori(&(temp->succ));
			free(temp);
			cancella_nodo(grafo, elem);
		}
		else {
			lcancella(&((*grafo)->succ),elem);
			cancella_nodo(&((*grafo)->proxnodo), elem);
		}
	}
}
/*------------------------lstampa-----------------------------------*/
/* Stampa la lista dei successori di un determianto nodo */
void lstampa(pnodo grafo)
{
    plista punt;

    punt=grafo->succ;
    while (punt!=NULL)  {
        printf(" (%s) --- ", punt->info);
        punt=punt->next;
    }
}
/*------------------------stampa----------------------------------*/
/* Stampa i nodi di un grafo, seguiti dalla lista dei successori */
void stampa(pnodo grafo)
{
    while (grafo!=NULL) {
        printf("\n(%s) -->", grafo->info);
        lstampa(grafo);
        grafo=grafo->proxnodo;
    }
}

/*---------------------------------bfs-----------------------------------*/
/* Visita in ampiezza (Breadth First Search) , cioè, partendo dal un nodo I
    si visitino tutti i suoi successori, poi tutti i successori dei successori
    e così via
    Algoritmo:
        visita il grafo G partendo da nodo I:
            inserisci I nella coda;
            finché la coda non è vuota
            esegui:
                estrai il primo elemento J dalla coda;
                analizza J e marcalo 'visitato';
                metti nella coda tutti i successori di J non 'visitati'
            fine.

  La visa ampiezza può essere pensata come una visita di livello: viene analiz-
  zato il primo livello, poi tutti gli elementi del secondo e così via
*/
void bfs(pnodo grafo)
{
    coda nuova;
    coda fine;
    pnodo j;
    plista p;
    plista visitati=NULL;

    inizializza_coda(&nuova, &fine);
    push(&nuova, &fine, grafo);
    while (!codavuota(nuova)) {
        j=fronte(nuova);
        pop(&nuova);
        lins_down(&visitati, j->info);
        printf("(%s)-- ", j->info);
        p=j->succ;
        while (p!=NULL){
            if (!lricerca(visitati, p->info))
                push(&nuova, &fine, ricerca_nodo(grafo, p->info));
            p=p->next;
        }
    }
}

/*-------------------------------dfs------------------------------------*/
/* Visita in profondità il grafo (Depth First Search), cioè analizza il nodo
    di partenza I e, per ogni successore S di I, si visita, con lo stesso
    metodo, il grafo partendo da S.
    Al contrario degli alberi, in un grafo è possibile, seguendo gli archi,
    ritornare ad un nodo già analizzato, in particolare se esistono cicli
    nel grafo. Per evitare che l'algoritmo di visita entri in un ciclo infinito
    è necessario controllare che il nodo di volta in volta considerato non
    si stato già analizzato.
    Algoritmo:
        visita in profondità il grafo G partendo dal nodo I:
            analizza I e marcalo 'visitato';
            finché ci sono successori di I non visitati( sia S il prox)
                visita in profondita G partendo da S.
*/
void dfs(pnodo grafo, plista *visitati)
{
    plista s;
    static pnodo inizio; /* punta all'inizio del grafo */

    if (*visitati==NULL) inizio=grafo;

    printf(" %s --", grafo->info);
    lins_down(visitati, grafo->info);
    s=grafo->succ;
    while (s!=NULL && lricerca(*visitati, s->info)==0) {
        dfs(ricerca_nodo(inizio, s->info), visitati);
        s=s->next;
    }
}

/*--------------------------altre funzioni-----------------------------*/
/**/
void inizializza_coda(coda *nuova, coda *fine)
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
void push(coda *nuova,coda *fine, pnodo elem)
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
pnodo fronte(coda nuova)
{
    return nuova->info;
}

/*------------------------allocamatrice---------------------------*/
void allocamatrice(matrice *temp, int n, int m)
{
	int i, j;

	*temp=(matrice) malloc(n*sizeof(righe));
	for (i=0; i<n; ++i)
		(*temp)[i]=(righe) malloc(m*sizeof(int));

	for (i=0; i<n; ++i)
		for(j=0; j<m; ++j)
			(*temp)[i][j]=0;
}

/*---------------------------contanodi--------------------------------*/
int contanodi(pnodo grafo)
{
    int i=0;

    while (grafo!=NULL){
        i++;
        grafo=grafo->proxnodo;
    }
    return i;
}
/*------------------------lricerca---------------------------------*/
/* ricerca sequenziale di un elemento */
int lricerca(plista mia, tipo elem)
{
	int trovato=0;
	lista *cursore;

	if (mia!=NULL){
		cursore=mia;
		while (trovato==0 && cursore!=NULL) {
			trovato=!strcmp(cursore->info,elem);
			cursore=cursore->next;
		}
	}
	return trovato;
}

/*-------------------------------ricerca_cammino---------------------*/
int ricerca_cammino(pnodo temp, tipo elem, tipo elem2)
{
	int n;
	int i, j;
	int livello=0;
	matrice mat;
	pnodo cursore;
	plista lcur;

	n=contanodi(temp);
	allocamatrice(&mat, n, n);

	cursore=temp;
	while (cursore!=NULL) {
		i=0;


}
