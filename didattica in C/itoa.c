#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int x=10; /* numero da convertire */
	
	int resto, quoto;
	int i=0, j=0;
	char t; 
	char ris[3]="", temp[3]="";

	quoto=x;
	do {
		resto=quoto%10;
		t=(char) resto+'0';
		quoto=quoto/10;
		ris[i]=t;
		++i;
	} while (quoto!=0);
	ris[i]='\0';
	temp[i]='\0';
	for (j=0; j<i; ++j)
		temp[j]=ris[i-j-1];
	
	printf("\n\nstringa : %s", temp);
	getchar();
}
