#ifndef SCORES_H
#define SCORES_H

typedef struct scores
{
	char name[100];
	int score;
}TScore;

int saveScore(char* text, int score, TScore* List);
int loadScores(TScore* List);

#endif /* SCORES_H */