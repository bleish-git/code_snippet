#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int i;

	for( i=1; i<256; ++i) printf("\n %d  %3x - %c",i, i,i);
	getchar();
}
