/*
PPAR TP1: Question 4
Group: Ishan Tiwari & Shashi Mohan Reddy Ravula
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>
int main()
	{
	/*Table of words */
	char *charArray[3][2] = {
				{"rennes","paris"},
				{"nantes","dinan"},
				{"malo","michel"}
				};
	char *temp;
	int i,j,k,countnum = 0,numvow=0,m,l,count,me,nb;  
	printf("Hello\n");  

	omp_set_num_threads(4);

	#pragma omp parallel shared(charArray) private(i,j,k,l,m)
	{
	me = omp_get_thread_num();
        nb = omp_get_num_threads();

	#pragma omp for schedule(dynamic) 
	for (i=0; i<3; i++)
	{	
		for (j=0; j<2; j++)
		{
		int size = strlen(charArray[i][j]);
		
		temp = malloc(sizeof(charArray[i][j]));
		temp = charArray[i][j];
		printf("Word is %s and the size of the word is %d\n",charArray[i][j],size);
		
		/* Calculating the vowels in the word */
		for (k=0; k<size; k++)
			{
				if(temp[k] == 'a' | temp[k] == 'e' | temp[k] == 'i' | temp[k] == 'o' | temp[k] == 'u')
				{
				numvow++;
				}
			}
		
		printf("No. of vowels are %d and no. of characters are %d\n",numvow,size);
		numvow=0;

		/* Calculating the number of recurrences of a letter in the word */
		for (l=0; l<size; l++)
			{
			char c = temp[l];
			count=0;
				for (m=0; m<size; m++)
				{
					if(c==temp[m])
					{
					count++;
					}
				
				}
			printf("In the word %s : char %c has %d occurrences\n",charArray[i][j],c,count);
			}
		}
	}}
}
