/* **************************************************************
 *
 *		Matrici bidimensionali 2
 *		allocate dinamicamente
 *
 ****************************************************************/
/*Questo sorgente e' preferibile a matrici.c */

#include <stdio.h>
#include <stdlib.h>

typedef int *righe;         /* questo è array di interi corrispondente alle righe*/
typedef righe *matrice;	   /* questo è un array di puntatori alle righe */

void leggimatrice(matrice temp, int r, int c);
void stampamatrice(matrice temp, int n, int m);
void somma(matrice *temp, matrice a, matrice b, int n, int m);
void allocamatrice(matrice *temp, int n, int m);

main(void)
{
	matrice mat1, mat2, ris;
	int n,m;

	printf("\nInserire l'ordine della matrice n,m: ");
	scanf(" %d,%d", &n,&m);

	allocamatrice(&mat1, n, m);
	allocamatrice(&mat2, n, m);
	allocamatrice(&ris, n, m);
	leggimatrice(mat1, n,m);
	leggimatrice(mat2, n,m);

	somma(&ris, mat1, mat2, n, m);

	stampamatrice(ris, n, m);
	printf("\n\n");

	return 0;
}

void leggimatrice(matrice temp, int r, int c)
{
	int i, j;

	printf("\nInserire gli elementi della matrice, riga per riga\n\n ");

	for(i=0; i<r; ++i)
		for(j=0; j<c; ++j)
			scanf(" %d", (*(temp+i)+j));
}

void stampamatrice(matrice temp, int n, int m)
{
	int i, j;

	printf("\n\n-");
	for(i=0; i<n; ++i) {
		printf("\n");
		for(j=0; j<m; ++j)
			printf("%6d", temp[i][j]);
	}
}

void somma(matrice *temp, matrice a, matrice b, int n, int m)
{
	int i, j;

	for(i=0; i<n; ++i)
		for(j=0; j<m; ++j)
			(*temp)[i][j]=a[i][j]+b[i][j];
}

void allocamatrice(matrice *temp, int n, int m)
{
	int i, j;

	*temp=(matrice) malloc(n*sizeof(righe));
	for (i=0; i<n; ++i)
		(*temp)[i]=(righe) malloc(m*sizeof(int));
}
