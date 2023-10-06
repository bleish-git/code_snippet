#include <stdio.h>

main(void)
{
	float eps=1.0;

	do
		eps=eps/2;
	while (eps+1.0>1.0);

	eps=eps*2;

	printf("\n\nPer questa macchina il valore di eps = %g ", eps);
	getchar();

	return 0;
}

