/*hashtable.c
Esercitazione del 18/03/2002
Testo: Creare un dizionario mediante tabella hash di parole estratte da un
qualsiasi file di testo. Si devono considerare parole di almeno due caratteri e
non considerare la punteggiatura o altri caratteri speciali. Inoltre non deve essere fatta distinzione tra minuscolo e maiuscolo.
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

unsigned char hash(char *str)
{
 unsigned char h=0;
 while(*str!='\0') h+= (unsigned char) toupper(*str++);
 return(h);
};

typedef struct nodo{
 char * parola;
 struct nodo *succ;
}nodo;

typedef nodo *tabellahash[256];

void Inizializza(tabellahash tabella);
int LeggiParola(FILE *fp,char *tmpstr);
void CreaTabella(tabellahash tabella, char *filename);
void StampaTabella(tabellahash tabella);

main(int argc,char *argv[])
{
 tabellahash tabella;
 
 Inizializza(tabella);
 CreaTabella(tabella,argv[1]);
 StampaTabella(tabella);
 getch();

}



void Inizializza(tabellahash tabella)
{
  int i;
  
  for(i=0;i<256;i++) (tabella[i])=NULL;
}

int LeggiParola(FILE *fp,char *tmpstr)
{
 int i=0;
 char c;
 
 do{
  c=fgetc(fp);
  c=toupper(c);
  tmpstr[i]=c;
  i++;
 } while(!feof(fp) && c>='A' && c<='Z');
 tmpstr[i-1]='\0';
 if(i-1<2) return(1);  /*se la stringa Š vuota o ha meno di 2 car ritorna 1 */
 return(0);
}

void CreaTabella(tabellahash tabella, char *filename)
{
 FILE* fp;
 char tmpstr[500];
 nodo  *pnodo,*newnodo;
 unsigned char index;
 int esiste=0;

 if((fp=fopen(filename,"r"))==NULL) exit(0);
 
 while(!feof(fp)){
  /*fscanf(fp,"%s",tmpstr);*/
  esiste=LeggiParola(fp,tmpstr);
  index=hash(tmpstr);
  pnodo=tabella[index];

  while(pnodo!=NULL && !esiste) {
   if(strcmp(tmpstr,pnodo->parola)==0) esiste=1;
   pnodo=pnodo->succ;
  }

  if(!esiste){
    newnodo=(nodo*) malloc(sizeof(nodo));
    (newnodo->succ)=tabella[index];
    (newnodo->parola) = (char*)malloc(sizeof(char)*strlen(tmpstr));
    strcpy(newnodo->parola,tmpstr);
    tabella[index]=newnodo;
  }
 }
 fclose(fp);
}

void StampaTabella(tabellahash tabella)
{
 int i;
 nodo* pnodo;

 clrscr();
 for(i=0;i<256;i++){
  printf("\nIndice hash %d ---------------------------\n",i);
  pnodo=tabella[i];
  while(pnodo!=NULL) {
    printf("%s ",pnodo->parola);
    pnodo=pnodo->succ;
  }
  if((i+1)%10==0) getche();
 }

}