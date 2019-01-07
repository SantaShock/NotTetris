#include <stdlib.h>
#include "random.h"

int generator()
{
	time_t t;
	srand(t);
	static int i = 0;
	int j = rand()%8;
	if(j==i) j=rand()%8;
	while(j==8) j=rand()%8;
	i = j;
	return j;
}

char randomPiece()
{
	int i = generator();
	switch(i)
	{
		case 0:
			return 'i';
		case 1:
			return 'o';
		case 2:
			return 't';
		case 3:
			return 's';
		case 4:
			return 'z';
		case 5:
			return 'j';
		case 6:
			return 'l';
	}
}