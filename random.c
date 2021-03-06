#include <stdlib.h>
#include <time.h>
#include "random.h"
#include <stdio.h>

static const int baseBag[7] = {0,1,2,3,4,5,6};
static int pieceBag[7] = {0,1,2,3,4,5,6};

int generateSequence()
{
	int i,j,temp;
	for(i=0;i<7;i++)
	{
		pieceBag[i] = 0;
		pieceBag[i]=baseBag[i];
	}
	
	for(i=0;i<7;i++)
	{
		j = i + rand() / (RAND_MAX / (7 - i) + 1);
		temp = pieceBag[j];
		pieceBag[j] = pieceBag[i];
		pieceBag[i] = temp;
	}
	
}

int initRandom()
{
	static time_t t = time(NULL);
	srand(t);
	generateSequence();
	generateSequence();
}

int generateRandom()
{
	int i,j;
	static int n = 0;
	if(n==7)
	{ 
		generateSequence();
		n=0;
	}
	for(i=0;i<7;i++)
	{
		if(pieceBag[i]!= -1)
		{
			j = pieceBag[i];
			pieceBag[i] = -1;
			n++;
			return j;
		}
	}
}
