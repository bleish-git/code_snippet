/************************************************************************
 *
 *                  Compito di Calcolatori elettronici
 *                              05/01/1999
 *
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*----------------var globali -------------------*/
int valore[90];

/*------------------prototipi------------------*/
void codifica(int n, FILE *fi, FILE *fo);
void decodifica(int n, FILE *fi, FILE *fo);

void inizializza(void);
char ricerca(int val);
int stringtoi(char *vett, int i);
void itostring(int x, char *temp, int pos);
int media(int *temp, int n);


/*--------------------------------- MAIN -------------------------------------*/
void main(void)
{
    int n;          /*lunghezza della parte*/
    char scelta;
    FILE *pfi;
    FILE *pfo;

    if ((pfi=fopen("inizio.txt","rt+"))==NULL) {
        puts("\n\n\Errore - Non è stato possibile aprire un file");
        exit(1);
    }
    if ((pfo=fopen("uscita.txt","wt+"))==NULL) {
        puts("\n\n\Errore - Non è stato possibile aprire un file");
        exit(1);
    }
    printf("\n\nScegliere tra codifica e decodifica (c/d) ");
    scelta=getchar();
    printf("\n\nIndicare la chiave -->");
    scanf(" %d", &n);

    inizializza();
	switch (scelta) {
        case 'c' :
        case 'C' :  codifica(n, pfi, pfo);
                    break;
        case 'd' :
        case 'D' :  decodifica(n, pfi, pfo);
                    break;
        default  :  printf("\nScelta non consentita. Riprova");
    }

    getchar();
}

/*--------------------------codifica------------------------------*/
void codifica(int n, FILE *pfi, FILE *pfo)
{
    int *parte;
    char *pcod;
    int m;
    int i=0;
   	char temp;

    parte= (int *) malloc(n*sizeof(int));
    pcod=(char *) malloc((3*n+3)*sizeof(int));

    do {
        i=0;
        while (i<n && (temp=fgetc(pfi))!=EOF) {
            parte[i]=valore[(int)temp - (int)' '];
            ++i;
        }
        if (i==0 && feof(pfi)) break;
        if (i<n)
            for(; i<n; ++i)
				parte[i]=valore[0];

		m=media(parte, n);

		itostring(m, pcod, 0);

        for (i=3; i<3*n+3; i+=3)
            itostring(parte[(i/3)-1]-m, pcod, i);
        fprintf(pfo, "%s\n", pcod);
    } while (!feof(pfi));
}
/*-----------------------------decodifica--------------------------*/
void decodifica(int n, FILE *pfi, FILE *pfo)
{
    int parte;
    char *pcod;
    int m;
    int i;

    pcod=(char *) malloc((3*n+3)*sizeof(int));

    while (!feof(pfi)) {
        i=0;
        while (i<3*n+3 && (pcod[i]=fgetc(pfi))!=EOF)
            i++;

        if (pcod[i]==EOF) break;

        m=stringtoi(pcod, 0);

        for(i=3; i<3*n+3; i+=3) {
			parte=stringtoi(pcod, i)+m;
			fputc(ricerca(parte), pfo);
		}
        fgetc(pfi); /* salta il carattere di newline*/
	}
}
/*---------------------------ricerca----------------------------------*/
/* Restituisce il carattere a cui corrisponde il particolare valore intero
* e positivo val */
char ricerca(int val)
{
	int i=0;

	while (valore[i]!=val)
		++i;

	return (char) i+32;
}

/*-----------------------inizializza------------------------------*/
/* Inizializza il vettore valore[], recuperando i valori dal file
* key.txt */
void inizializza(void)
{
	int i=0;

	for(i=0; i<90; ++i)
		valore[i]=i+5;
}

/*------------------------------strintoi------------------------------*/
/* Questa funzione restituisce il numero intero segnato in forma di stringa
* memorizzato nelle tre posizioni adiacenti del vettore vett da i a +2 */
int stringtoi(char *vett, int i)
{
    int ret;
    ret=10*((int)vett[i+1]-'0')+ (int) vett[i+2]-'0';
	if (vett[i]=='+') return ret;
	else return -ret;
}


/*-----------------------------------itostring---------------------------------*/
/* La funzione restiruisce in formato stringa di tre caratteri con segno, il numero
* intero x memorizzandolo nell'array puntato da temp iniziando dalle posizioni
* pos, pos+1 e pos+1. Si suppone che il numero intero sia positivo e minore di 100 */
void itostring(int x, char *temp, int pos)
{
	int decina, unita;
	int segno;

	if (x<0) segno=-1;
	else segno=1;

	decina=abs(x)/10;
	unita=abs(x)%10;

	temp[pos]= (segno >0) ? '+' : '-';
	temp[pos+1]= (char) (decina + (int) '0');
	temp[pos+2]= (char) (unita + (int) '0');
}
/*-----------------------------------media-------------------------------*/
/* Restiruisce la media di tutti gli n elementi contenuti nell'array temp */
int media(int *temp, int n)
{
	int i=0;
	int somma=0;

	for (i=0; i<n; ++i)
		somma+=temp[i];

	return somma/n;
}

/* -----------------------NOTA ---------------------------*/
/* La funzione feof(), definita in stdio.h, restituisce un valore
    nullo se nelle precedenti operazioni sul file si è ritrovato un errore
    o un end_of_file (EOF).
    Per questo motivo non è stata utilizzata negli argomenti dei cicli
    while o for, in quanto se non viene compiuta una operazione di
    lettura sul file con riscontro di EOF il ciclo verrà eseguito cmq.
    Diversamente fgetc(), restituisce EOF in caso si riscontra un errore
    o la fine del file, mentre si esegue la lettura */

