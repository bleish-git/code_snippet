/*****************************************************************
 *
 * 		Compito di Calcolatori Elettronici
 * 			19 luglio 2002
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

typedef struct {
				int index;
				char scacchiera[8][8];
				int npedinera;	 /*numero di ped nere in gioco*/
				int npedibianca; /*numero di ped bianche in gioco*/
				int ndamanera;	 /*numero di dame nere in gioco*/
				int ndamabianca; /*numero di dame bianche in gioco*/
		} stato_scacchiera;

FILE *stato;

stato_scacchiera nuovo;

void inizializza(void);
void draw(stato_scacchiera temp);
void store(void);
void CLEAR(void);
void SCACCHIERA(void);
void PEDINERA(int riga, int col);
void DAMANERA(int riga, int col);
void PEDIBIANCA(int riga, int col);
void DAMABIANCA(int riga, int col);

int sposta(int x0, int y0, int x1, int y1, char giocatore);
void gioca(void);
int status(void);
void riporta(int n);


/**************************** M A I N *************************************/
void main(void)
{
	stato=fopen("c:\\partita.bin","wb+");

	inizializza();	/*Inizializza la scacchiera e il gioco*/
	store(); 		/*e memorizza il nuovo stato inizializzato*/

	gioca();
	fclose(stato);
	getch();
}

/*-------------------------------inizializza-------------------------------*/
void inizializza(void)
{
	int i,j;

	for (i=0; i<8; ++i)
		for(j=0; j<8; ++j)
			nuovo.scacchiera[i][j]='\0';

	nuovo.index=0;
	nuovo.npedinera=12;
	nuovo.npedibianca=12;
	nuovo.ndamanera=0;
	nuovo.ndamabianca=0;

	for (i=0; i<8; ++i)
		for(j=0; j<3; ++j) {
			if ((i+j)%2==0)  nuovo.scacchiera[i][j]='b';
			else  nuovo.scacchiera[i][j+5]='n';
		}

	draw(nuovo);
}

/*--------------------------------draw----------------------------------*/
void draw(stato_scacchiera temp)
{
	int i,j;

	CLEAR();
	SCACCHIERA();

	for (i=0; i<8; i++)
		for(j=0; j<8; ++j)
			switch (temp.scacchiera[i][j]) {
				case 'b' : PEDIBIANCA(i,j);
						   break;
				case 'n' : PEDINERA(i,j);
						   break;
				case 'N' : DAMANERA(i,j);
						   break;
				case 'B' : DAMANERA(i,j);
						   break;
				default  : break;
			}

	gotoxy(1,25); printf("Situazione scacchiera dopo la mossa %d             ", temp.index);
}

/*----------------------------store-----------------------------*/
void store(void)
{
	fwrite(&nuovo, sizeof(stato_scacchiera),1,stato);
}

/*--------------------------CLEAR------------------------------*/
void CLEAR(void)
{
	clrscr();
	//system("clear"); /* Nei sistemi UNIX pulisce il terminale*/
}

/*-------------------------SCACCHIERA-------------------------*/
void SCACCHIERA(void)
{
	printf(" лл0лл  1  лл2лл  3  лл4лл  5  лл6лл  7	  Menu delle scelte.\n");
	printf("0ллллл     ллллл     ллллл     ллллл\n");
	printf(" ллллл     ллллл     ллллл     ллллл      -1 per aggiornare\n");
	printf("      ллллл     ллллл     ллллл     ллллл\n");
	printf("1     ллллл     ллллл     ллллл     ллллл -2 seguito da n per visualizzare\n");
	printf("      ллллл     ллллл     ллллл     ллллл    la tavola alla n-esima mosssa\n");
	printf(" ллллл     ллллл     ллллл     ллллл         o da -n per riportare la situaz\n");
	printf("2ллллл     ллллл     ллллл     ллллл         a n mosse precedenti\n");
	printf(" ллллл     ллллл     ллллл     ллллл\n");
	printf("      ллллл     ллллл     ллллл     ллллл le coordinate riga x colonna\n");
	printf("3     ллллл     ллллл     ллллл     ллллл\n");
	printf("      ллллл     ллллл     ллллл     ллллл -100 per uscire.\n");
	printf(" ллллл     ллллл     ллллл     ллллл	 \n");
	printf("4ллллл     ллллл     ллллл     ллллл	 	    Ped  bianche: %d\n",
			nuovo.npedibianca);
	printf(" ллллл     ллллл     ллллл     ллллл	 	    Dame bianche: %d\n",
			nuovo.ndamabianca);
	printf("      ллллл     ллллл     ллллл     ллллл	    Ped  nere: %d\n",
			nuovo.npedinera);
	printf("5     ллллл     ллллл     ллллл     ллллл	    Dame nere: %d\n",
			nuovo.ndamanera);
	printf("      ллллл     ллллл     ллллл     ллллл\n");
	printf(" ллллл     ллллл     ллллл     ллллл\n");
	printf("6ллллл     ллллл     ллллл     ллллл\n");
	printf(" ллллл     ллллл     ллллл     ллллл\n");
	printf("      ллллл     ллллл     ллллл     ллллл\n");
	printf("7     ллллл     ллллл     ллллл     ллллл\n");
	printf("      ллллл     ллллл     ллллл     ллллл\n");
}


/*--------------------------PEDINERA----------------------*/
void PEDINERA(int riga, int col)
{
	gotoxy(col*5+3,riga*3+2);
	printf(" n ");
}

/*--------------------------PEDIBIANCA----------------------*/
void PEDIBIANCA(int riga, int col)
{
	gotoxy(col*5+3,riga*3+2);
	printf(" b ");
}

/*--------------------------DAMANERA----------------------*/
void DAMANERA(int riga, int col)
{
	gotoxy(col*5+3,riga*3+2);
	printf(" N ");
}

/*-------------------------DAMABIANCA----------------------*/
void DAMABIANCA(int riga, int col)
{
	gotoxy(col*5+3,riga*3+2);
	printf(" B ");
}

/*********************FUNZIONI PRINCIPALI*******************/
/*-----------------------gioca------------------------------*/
void gioca(void)
{
	int x0,x1,y0,y1;       /* le coordinate dei punti di inizio e arrivo*/
	char giocatore='b';    /* indica il giocatore che sta giocando;
								iniziano le pedine bianche */
	int flag;

	do {
		gotoxy(47,20); printf("                                  ");
		gotoxy(47,21); printf("                                  ");
		gotoxy(47,20);
		printf("Giocano le pedine %s", (giocatore=='b' ?
										"bianche" : "nere"));
		gotoxy(47,21);

		scanf(" %d", &x0);
		if (x0==-1) {
			draw(nuovo);
			continue;
		}
		else if (x0==-100) break;



		gotoxy(50,21);
		scanf("%d" , &y0);

		if (x0==-2) {           /* Riporta la y0  mossa precedente o */
			riporta(y0);        /* la mostra la situazione alla mossa */
			continue;           /* y0-esima, a seconda se y0 ш positiva */
		}				        /* o negativa, rispettivamente */

		gotoxy(53,21);
		scanf("%d", &x1);
		gotoxy(57,21);
		scanf("%d", &y1);

		gotoxy(1,25);
		if (x0>8 || y0>8 || x1>8 || y1>8) {
			printf("Coordinate errate. Inserire riga-colonna.Riprova");
			getch();
			continue;
		}

		flag=sposta(x0, y0, x1, y1, giocatore);

		switch (flag) {
			case 0 :    printf("Inizio e fine coincidono, riprova             ");
						break;
			case -1:    printf("Mossa non consentita. Riprova.                ");
						break;
			case 1 :    printf("Mossa effettuata.                             ");
						giocatore= (giocatore=='b') ? 'n' : 'b';
						nuovo.index++;
						store();
						break;
			case 2 :    printf("Spostata pedina e mangiata pedina avversaria  ");
						giocatore=(giocatore=='b') ? 'n' : 'b';
						nuovo.index++;
						store();
						break;
			case 3 :    printf("Pedina in dama                                ");
						nuovo.index++;
						store();
						break;
			case 5 :    printf("Pedina in dama e mangiata pedina avversaria   ");
						nuovo.index++;
						store();
						break;
		}
	} while (status()==0);

	gotoxy(1,25);
	printf("Partita conclusa. Vince il %s          ", (status()<0 ? "bianco" : "nero"));
}

/*--------------------------status---------------------------------------*/
int status(void)
{
	if (nuovo.npedinera==0 && nuovo.ndamanera==0) return -1;
	else if (nuovo.npedibianca==0 && nuovo.ndamabianca==0) return 1;
		else return 0;
}

/*-----------------------------sposta----------------------------------*/
int sposta(int x0, int y0, int x1, int y1, char giocatore)
{
	int tipo=1;
	int dx, dy;

	/* analizziamo prima gli errori di immissione coordinate*/
	if (nuovo.scacchiera[x0][y0]=='\0' || giocatore!=tolower(nuovo.scacchiera[x0][y0]))
		return -1;

	/* analizziamo adesso la correttezza della destinazione */
	if (((x1+y1)%2)!=0) return -1;
	if (nuovo.scacchiera[x1][y1]!='\0') return -1;

	if (x0==x1 && y0==y1) return 0;

	/* a seconda del tipo di pedina in (xo,y0) si vede ora la correttezza del
		suo movimento */


	tipo = (nuovo.scacchiera[x0][y0]=='b' || nuovo.scacchiera[x0][y0]=='n')? 1 : 2;
	dx=x1-x0;
	dy=y1-y0;

	switch (tipo) {
		case 1 :
					if (giocatore=='b' && dy==1 && abs(dx)==1) {
						if (y1==7) {
							tipo=tipo*3;
							nuovo.npedibianca--;
							nuovo.ndamabianca++;
						}
						nuovo.scacchiera[x0][y0]='\0';
						nuovo.scacchiera[x1][y1]=( tipo >1 ? 'B' : 'b');
						return tipo;
					}
					else if (giocatore=='n' && dy==-1 && abs(dx)==1) {
							if (y1==0) {
								tipo=tipo*3;
								nuovo.ndamanera++;
								nuovo.npedinera--;
							}
							nuovo.scacchiera[x0][y0]='\0';
							nuovo.scacchiera[x1][y1]= (tipo >1? 'N': 'n');
							return tipo;
						}
						else if  (giocatore=='b' && dy==2 && abs(dx)==2 &&
									nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]=='n'){
								if (y1==7) {
									tipo=tipo*5;
									nuovo.npedibianca--;
									nuovo.ndamabianca++;
								}
								else tipo=tipo*2;
								nuovo.scacchiera[x0][y0]='\0';
								nuovo.scacchiera[x1][y1]= (tipo >2 ? 'B' : 'b');
								nuovo.npedinera--;
								nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]='\0';
								return tipo;
							}
							else if  (giocatore=='n' && dy==-2 && abs(dx)==2 &&
										nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]=='b'){
									if (y1==0) {
										tipo=tipo*5;
										nuovo.npedinera--;
										nuovo.ndamanera++;
									}
									else tipo=tipo*2;
									nuovo.scacchiera[x0][y0]='\0';
									nuovo.scacchiera[x1][y1]= (tipo >2 ? 'N' : 'n');
									nuovo.npedibianca--;
									nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]='\0';
									return tipo;
								}
								else return -1;
								break;

		case 2 :    if ((dy==-1 || dy==1) && abs(dx)==1) {
						nuovo.scacchiera[x0][y0]='\0';
						nuovo.scacchiera[x1][y1]= (giocatore =='b' ? 'B': 'N');
						return 1;
					}
					else if ((dy==2 || dy==-2) && giocatore=='b' && abs(dx)==2 &&
						toupper(nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2])=='N') {
							if (nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]=='n')
								nuovo.npedinera--;
							else nuovo.ndamanera--;
							nuovo.scacchiera[x0][y0]='\0';
							nuovo.scacchiera[x1][y1]='B';
							nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]='\0';
							return 2;
						}
						else if ((dy==2 || dy==-2) && giocatore=='n' && abs(dx)==2 &&
							toupper(nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2])=='B') {
								if (nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]=='b')
									nuovo.npedibianca--;
								else nuovo.ndamabianca--;
								nuovo.scacchiera[x0][y0]='\0';
								nuovo.scacchiera[x1][y1]='N';
								nuovo.scacchiera[(x0+x1)/2][(y0+y1)/2]='\0';
								return 2;
							}
							else return -1;
	}
}
/*------------------------------riporta------------------------------*/
void riporta(int n)
{
	stato_scacchiera temp;

	if (n>0) {
		fseek(stato, n*sizeof(stato_scacchiera), SEEK_SET);
		fread(&temp,sizeof(stato_scacchiera),1,stato);
		draw(temp);
	}
	else {
		fseek(stato, (long) (n-1)*sizeof(stato_scacchiera), SEEK_END);
		fread(&temp, sizeof(stato_scacchiera),1, stato);
		draw(temp);
	}
	getch();
	fseek(stato, 0, SEEK_END);

}

/*------------------------------------NOTE-----------------------------------
Stringa di modo per l'apertura di un file

 String     Description
______________________________________________________________________________
   r   | Open for reading only
   w   | Create for writing
	   | If a file by that name already exists, it will be overwritten.
   a   | Append; open for writing at end of file, or create for
	   | writing if the file does not exist.
   r+  | Open an existing file for update (reading and writing)
   w+  | Create a new file for update (reading and writing).
	   | If a file by that name already exists, it will be overwritten.
   a+  | Open for append; open for update at the end of the file, or
	   | create if the file does not exist.

- To specify that a given file is being opened or created in text mode,
  append "t" to the string (rt, w+t, etc.).
- To specify binary mode, append "b" to the string (wb, a+b, etc.).

----------------------------------------------------------------------------*/