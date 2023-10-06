/*****************************************************************
 *
 * 		Compito di Calcolatori Elettronici
 * 			18 gennaio 2001
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

unsigned long fibonacci[MAX];

void leggi(char t[]);
void metti_incolonna(char t[]);
void inizializza(char t[]);
void stampa(char t[]);
unsigned long valore(char temp[]);
void init_fib();

int simplified(char t[]);

void full_adder(char a[], char b[], char c[]);
void half_adder(int i, char a[], char b[], char c[]);


void main(void)
{
    char a[MAX];
    char b[MAX];
    char c[MAX];

    init_fib();
	inizializza(c);

    leggi(a);
    leggi(b);

    full_adder(a,b,c);

    printf("\n\nRisultato della somma di:");
	stampa(a);
    stampa(b);
	printf("\n________________________________");
    stampa(c);

    scanf(" %s", a);
}

/******DEFINIZIONI DELLE FUNZIONI PRINCIPALI**************/
/*---------------------simplified---------------------
 * semplifica l'addendo inserito innanzitutto per velocizzare
 * l'esecuzione e sopratutto per far funzionare l'algoritmo
 * di full_adder() 
*/
int simplified(char t[])
{
    int i;
    int flag=0; /* controlla se il processo di semplificazione
                produce un disordine, per esempio in 1001011 si
                avrebbe 1001100, dove la semplificazione produce
                una nuova coppia 11 */

    for (i=0; i<MAX-2 ; ++i) {
        if (t[i]=='0' && t[i+1]=='1' && t[i+2]=='1') {
            t[i]='1';
            t[i+2]='0';
            t[i+1]='0';
            if (i>0 && t[i-1]=='1') { flag=1; break;}
        }
    }
    if (flag==1) return simplified(t);
    else return 0;
}
/*------------------------full_adder---------------------
 * Si occupa della somma vera e propria dei due operandi*/
void full_adder(char a[], char b[], char c[])
{
    int i;

    simplified(a);
    simplified(b);

    for (i=MAX-1; i>=0; --i)
        half_adder(i, a, b, c);
    simplified(c);
}

/* ------------------half_adder-------------------------
 * In analogia al circuito combinatorio, esegue la somma tra due
 * bit, agendo in modo ricorsivo nel caso si generi un riporto
 * da sommare alle cifre precedenti*/
void half_adder(int i, char a[], char b[], char c[])
{
    char temp[MAX];
    char alias_c[MAX];
    int occupato=0;  /* 0=falso; controlla se la posizione in cui si va a
                        sommare è già presente un 1 per via di una somma
                        precedente; se ciò risulta vero il suo valore
                        viene impostato al valore di tale offset occupato*/

    if (a[i]!=b[i]) {
        if (c[i]=='1') occupato=i;
        else c[i]='1';
    }

    /* è sicuro, dopo la semplificazione, se a[i] e b[i] sono uguali a 1, che
    a[i+1], b[i+1] e a[i-1], b[i-1] sono nulli; nulla si può dire su a[i-2] e
    b[i-2] che sommandosi possono dare c[i-2]!='0' per cui deve essere
    controllato tale valore*/
    if (a[i]==b[i] && a[i]=='1') {
        c[i-1]='1';
        c[i]='0';
        if (i==MAX-2) {
                        if (c[i+1]=='1') occupato=i+1;
                        else c[i+1]='1';
        }
        else if (c[i+2]=='0') c[i+2]='1';
             else occupato=i+2;
    }

    if (occupato!=0) {
        simplified(c);
        strcpy(alias_c, c);
        inizializza(temp);
        temp[occupato]='1';
        half_adder(occupato, alias_c, temp, c);
    }
}

/******************FUNZIONI MINORI**********************/
unsigned long valore(char temp[])
{
	int i;
	unsigned long val=0;

	for (i=0; i<MAX ; ++i)
		if (temp[MAX-i-1]=='1') val+=fibonacci[i+1];

	return val;
}

/*---------------------init_fib()---------------------
 * Inizializza il vettore di MAX elementi fibonacci[], memorizzando
 * nelle sue celle i primi MAX numeri di Fibonacci*/
void init_fib()
{
	int i=0;
	
	for (i=0; i<MAX; ++i)
		fibonacci[i]=0;
	fibonacci[0]=1;
	fibonacci[1]=1;
	
	for (i=2; i<MAX; ++i)
		fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
}
/*----------------------leggi-----------------------*/
void leggi(char t[])
{
    printf("\nInserisci addendo  -> ");
    scanf(" %s", t);
    metti_incolonna(t);
}

/*-----------------metti_incolonna-----------------*/
void metti_incolonna(char t[])
{
    char temp[MAX];
    int i;
    int lun;

    strcpy(temp, t);

    lun=strlen(t);
    inizializza(t);

    for(i=0 ; i<=lun ; ++i)
        t[MAX-lun+i]=temp[i];
}

/*---------------------inizializza-----------------------*/
void inizializza(char t[])
{
    int i;

    for (i=0; i<MAX; ++i)
        t[i]='0';

    t[MAX]='\0';
}

/*--------------------stampa--------------------------*/
void stampa(char t[])
{
    int i=0;

	printf("\n");
	while (t[i]=='0') ++i;
    while (i<MAX)  {
        printf("%c", (t[i]));
        ++i;
    }
	printf("\t%15u\n", valore(t));
}

