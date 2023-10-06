/* --------------------------------------------------------------
 * 		 LGrep - Source file in C-Ansi
 *
 * 		 Uso: lgrep [OPTIONS] STRINGA [FILE-IN]
 *
 * 		 Ricerca la STRINGA in tutti i files contenuti
 * 		 nei percorsi elencati in FILE-IN
 *
 * 		 versione 0.20
 * 		 Autore : Biagio Angileri, manubia@tiscali.it
 *
 * 		 Note: Richiede l'uso di grep e sistema Unix
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *leggi_percorso(FILE *fi, char *dir);
void stampa_guida(void);
void esegui(char *opt, char *stringa, char *files);


main(int argc, char *argv[])
{
	char opt[50]="";
	int i=0;	/* conta le opzioni ch einiziano con '-' */

	if (argc==1) {			/* Se non ci sono argomenti */
		stampa_guida();		/* termina stampando la guida*/
		return 0;
	}
	
	/* Se c'è un solo argomento questo */
	/* ed è --help stampa la guida */
	if ((argc==2)&&(strcmp(argv[1],"--help")==0)) { 		
		stampa_guida();
		return 0;
	}
	
	/* Se c'è un solo argomento e non è --help, deve essere la STRINGA */
	if (argc==2) {
			esegui("",argv[1], "");	
			return 0;		
	}
	
	/*Se gli argomenti sono più di 2: 
	 * - se sono delle opzioni (che iniziano con '-', 
	 *   allora mettile nella stringa opt;
	 * - altrimenti opt sarà vuota; */
	if ((argc>2)&&(argv[1][0]=='-')) {
		i=1;
		while (argv[i][0]=='-') {
			strcat(opt,argv[i]);
			strcat(opt, " ");
			++i;
		}
		if (i==argc-1) esegui(opt, argv[i], ""); 
		/* eventualmente ci può essere il FILE-IN 
		 * che sarà l'ultimo, mentre STRINGA il penultimo */
		else esegui(opt, argv[i], argv[i+1]);
	}
	else esegui(opt, argv[argc-2], argv[argc-1]);
	
	return 0;
}

char *leggi_percorso(FILE *fi, char *dir)
{
	char c;
	int i=0;

	c=fgetc(fi);
	while ((c!=EOF)&&(c!='\n')) {
		dir[i]=c;
		c=fgetc(fi);
		++i;
	}
	
	if (i==0) dir[0]='\0' ;
	else {
		dir[i]='/';
		dir[i+1]='*';
		dir[i+2]='\0';
	}
}

void stampa_guida(void)
{
	printf("\n\nLGrep 0.10 : Copyright Biagio Angileri manubia@tiscali.it - 2002\n");
	printf("\nUso: lgrep [OPTIONS] STRINGA [FILE-IN]");
	printf("\nRicerca la STRINGA in tutti in tutti i file contenuti nei percorsi elencati in FILE-IN");
	printf("\n\n\tOPTIONS : Le stesse opzioni di grep\n\n");
	printf("Senza FILE-IN le directory vengono prelevati dallo standard input\n");
}

void esegui(char *opt, char *stringa, char *files)
{
	int c1, c2;
	FILE *fi;
	char lista[250]="";
	char com[]="grep ";
	char dir[230]="";

	printf("\n\nInizio della ricerca di %s\n\n", stringa);

	if (strcmp(files, "")!=0) {
		fi=fopen(files, "r");
		
		leggi_percorso(fi, dir);
		while (dir[0]!='\0') {
			strcat(lista, com);
			strcat(lista, opt);
			strcat(lista, " ");
			strcat(lista, stringa);
			strcat(lista, " ");
			strcat(lista, dir);
			
			system(lista);
			
			lista[0]='\0';
			dir[0]='\0';
			leggi_percorso(fi, dir);
		}
		fclose(fi);
	}
	else {
		strcat(lista, com);
		strcat(lista, opt);
		strcat(lista, " ");
		strcat(lista, stringa);

		system(lista);
	}
}
