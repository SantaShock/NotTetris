#include <stdlib.h>
#include <time.h>
#include "random.h"

int initRandom()
{
	static time_t t = time(NULL);
	srand(t);
}

int generateRandom()
{
	static int i = 25;
	int j = rand()%7;
	while(j==7) 
	{
		j=rand()%7;
	}
	if(j==i) 
	{
		j=generateRandom();
	}
	i = j;
	return j;
}