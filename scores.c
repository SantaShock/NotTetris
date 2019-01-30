#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "scores.h"

int readList(TScore* List)
{
	FILE* fp = NULL;
	fp = fopen(SCORE_FILE_NAME,"r+");
	if(!fp) return 0;
	fread(List,sizeof(TScore),SAVED_SCORES_AMOUNT,fp);
	rewind(fp);
	fclose(fp);
	return 1;
}

int writeList(TScore* List)
{
	FILE* fp = NULL;
	fp = fopen(SCORE_FILE_NAME,"w+");
	if(!fp) return 0;
	fwrite(List,sizeof(TScore),SAVED_SCORES_AMOUNT,fp);
	rewind(fp);
	fclose(fp);
	return 1;
}

int insertScore(char* name, int score, TScore* List, int position)
{
	TScore copy[SAVED_SCORES_AMOUNT];

	if(position>=20) return 1;

	for(int i = 0; i<SAVED_SCORES_AMOUNT-1;i++)
	{
		if(i<position)
		{
			copy[i] = List[i];
		}
		else if(i==position)
		{
			copy[i].score = score;
			strcpy(copy[i].name,name);
		}
		else if(i>position)
		{
			copy[i] = List[i-1];
		}
	}
	for(int i=0;i<SAVED_SCORES_AMOUNT;i++)
	{
		List[i] = copy[i];
	}
	return 1;
}

int saveScore(char* text, int score, TScore* List)
{
	//compare current score to list
	//find position to insert
	int i;
	int pos = 0;
	for(i=0;i<SAVED_SCORES_AMOUNT;i++)
	{
		if(score>=List[i].score)
		{
			pos = i;
			break;
		}
		pos = i;
	}
	//insert element
	insertScore(text,score,List,pos);

	//save list to file
	writeList(List);
	return 1;
}

int loadScores(TScore* List)
{
	readList(List);
	return 1;
}