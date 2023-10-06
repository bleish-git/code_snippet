#include<stdlib.h>
#include<stdio.h>
#include <conio.h>

typedef enum{BIANCO,GRIGIO,NERO} colore;

typedef struct arco{
int label;
struct arco* succ_arco;
}arco;
typedef arco* lista_archi;

typedef struct vertice{
int label;
colore col;
lista_archi adiacenti;
struct vertice* succ_vert;
}vertice;
typedef vertice* grafo;

void CreaGrafo(grafo *g,char* filename);
void StampaLista(lista_archi l, char* str);
void StampaGrafo(grafo g,char* str);
void InserisciInCoda(lista_archi* l,int label);
int EstraiTesta(lista_archi* l);
vertice* TrovaVertice(grafo g, int label);
void ColoraVertice(grafo *g, int label, colore col);
void Bfs(grafo g, int partenza);
arco* TrovaPercorsoMinimo(grafo g, int partenza,int arrivo);


int main()
{
 grafo g;
 lista_archi percorso;
 int arrivo=0,partenza=5;

 while(1){
   CreaGrafo(&g,"grafo.dat");
   clrscr(); StampaGrafo(g,"grafo:");
   /*Bfs(g,partenza);*/
   printf("\n\nInserisci la partenza: "); scanf("%d",&partenza);
   if(partenza==-1) return(1);
   percorso = TrovaPercorsoMinimo(g,partenza,arrivo);
   StampaLista(percorso,"\nPercorso minimo -> ");
 }
 
}


void CreaGrafo(grafo *g, char *filename)
{
 FILE *pf;
 vertice *pv,*newvertice;
 char c; int i;

 pv=NULL;
 if((pf=fopen(filename,"r"))==NULL) exit(-1);

 c=fgetc(pf);
 while(!feof(pf)){
   newvertice=(vertice *) malloc(sizeof(vertice));
   newvertice->label=c-'0';
   newvertice->col=BIANCO;
   newvertice->adiacenti=NULL;
   newvertice->succ_vert=pv;
   pv=newvertice;
   while((c=fgetc(pf))!='\n'){
     InserisciInCoda(&newvertice->adiacenti,c-'0');
   }
   c=fgetc(pf);
 }
 *g=pv;
}

void StampaLista(lista_archi l, char* str)
{
  if(strcmp(str,"")) printf("\n%s ",str);
  while(l!=NULL){
    printf("%d ",l->label);
    l=l->succ_arco;
  }
  getch();
}

void StampaGrafo(grafo g,char* str)
{
  if(strcmp(str,"")) printf("\n%s\n",str);
  while(g!=NULL){
    printf("\n(%d) ",g->label);
    /*if(g->col==BIANCO) printf("(BIANCO) ->");
    else if(g->col==GRIGIO) printf("(GRIGIO) ->");
    else printf("(NERO)   ->"); */
    StampaLista(g->adiacenti,"");
    g=g->succ_vert;
  }
  getch();
}


void InserisciInCoda(lista_archi* l,int label){
  arco* newarco,*pa;
  newarco=(arco*) malloc(sizeof(arco));
  newarco->label=label;
  newarco->succ_arco=NULL;
  if(*l==NULL) *l=newarco;
  else{
    pa=*l;
    while(pa->succ_arco!=NULL) pa=pa->succ_arco;
    pa->succ_arco=newarco;
  }  
}

int EstraiTesta(lista_archi* l)
{
 int label;
 arco* pa;

 label=(*l)->label;
 pa=*l;
 *l=(*l)->succ_arco;
 free(pa);
 return(label);
}

vertice* TrovaVertice(grafo g, int label)
{
 while(g->label!=label) g=g->succ_vert;
 return(g);
}

void ColoraVertice(grafo *g, int label, colore col)
{
 vertice *pv;

 pv=*g;
 while(pv->label!=label) pv=pv->succ_vert;
 pv->col=col;
}

/* bfs */
void Bfs(grafo g, int partenza)
{
 vertice *pv,*pv2;
 lista_archi q,pa;
 char str[20];
 int label,livello=0;

 q=NULL;
 InserisciInCoda(&q,partenza);
 while(q!=NULL){
    sprintf(str,"step %d ",livello); StampaLista(q,str);
    label=EstraiTesta(&q);
    ColoraVertice(&g,label, GRIGIO);
    pv=TrovaVertice(g,label);
    pa=pv->adiacenti;
    livello++;
    while(pa!=NULL){
      pv2=TrovaVertice(g,pa->label);
      if(pv2->col==BIANCO){
        InserisciInCoda(&q,pv2->label);
        ColoraVertice(&g,pv2->label, GRIGIO);
      }
      pa=pa->succ_arco;
    }
    ColoraVertice(&g, pv->label,NERO);
 }
 /*StampaGrafo(g," ");*/
}

/* Trova percorso minimo */
arco* TrovaPercorsoMinimo(grafo g, int partenza,int arrivo)
{
 vertice *pv,*pv2; lista_archi q,pa,pa2,percorso;
 char str[20]; int i,j,label,livello,nliv_curr,nliv_succ;

 q=NULL; percorso=NULL; livello=0; nliv_curr=1; nliv_succ=0;
 InserisciInCoda(&q,partenza);

 while(q!=NULL){
  for(j=0;j<nliv_curr;j++){
    sprintf(str,"[liv. %d] coda ->",livello); StampaLista(q,str);

    for(i=0;i<=livello;i++){
      label=EstraiTesta(&q);
      InserisciInCoda(&percorso,label);
    }
    StampaLista(percorso,"     percorso -> ");
    if(label==arrivo) return(percorso);
    ColoraVertice(&g,label, GRIGIO);
    pv=TrovaVertice(g,label);
    pa=pv->adiacenti;
    while(pa!=NULL){
      pv2=TrovaVertice(g,pa->label);
      if(pv2->col==BIANCO){
        pa2=percorso;
        for(i=0;i<=livello;i++){
          InserisciInCoda(&q,pa2->label);
          pa2=pa2->succ_arco;
        }
        nliv_succ++;
        InserisciInCoda(&q,pv2->label);
        ColoraVertice(&g,pv2->label, GRIGIO);
      }
      pa=pa->succ_arco;
    }
    for(i=0;i<=livello;i++) label=EstraiTesta(&percorso);
   }
   livello++; nliv_curr=nliv_succ; nliv_succ=0;
   ColoraVertice(&g, pv->label,NERO);
 }
}

