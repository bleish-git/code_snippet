/* **************************************************************
 *
 *		Matrici bidimensionali
 *		allocate dinamicamente
 *
 ****************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

typedef int *righe;         /* questo Š un array di interi corrispondente alle riga*/
typedef righe *matrice;	   /* questo Š un array di puntatori alle righe */

matrice leggimatrice(int r, int c);
void stampamatrice(matrice temp, int n, int m);
matrice somma(matrice a, matrice b, int n, int m);

main(void)
{
	matrice mat1, mat2, ris;
	int n,m;

	printf("\nInserire l'ordine della matrice n,m: ");
	scanf(" %d,%d", &n,&m);

	mat1=leggimatrice(n,m);
	mat2=leggimatrice(n,m);

	ris=somma(mat1, mat2, n, m);

	stampamatrice(ris, n, m);
	printf("\n\n");

	return 0;
}

matrice leggimatrice(int r, int c)
{
	int i, j;
	matrice temp;

	temp=(matrice) malloc(r*sizeof(righe));
	for (i=0; i<r; ++i)
		temp[i]=(righe) malloc(c*sizeof(int));

	printf("\nInserire gli elementi della matrice, riga per riga\n\n ");

	for(i=0; i<r; ++i)
		for(j=0; j<c; ++j)
			scanf(" %d", (*(temp+i)+j));

	return temp;
}

void stampamatrice(matrice temp, int n, int m)
{
	int i, j;

	printf("\n\n");
	for(i=0; i<n; ++i) {
		printf("\n");
		for(j=0; j<m; ++j)
			printf("%6d", temp[i][j]);
	}
}

matrice somma(matrice a, matrice b, int n, int m)
{
	int i, j;
	matrice temp;

	temp=(matrice) malloc(n*sizeof(righe));
	for (i=0; i<n; ++i)
		temp[i]=(righe) malloc(m*sizeof(int));

	for(i=0; i<n; ++i)
		for(j=0; j<m; ++j)
			temp[i][j]=a[i][j]+b[i][j];

	return temp;
}


