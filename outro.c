#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>

#include "definitions.h"

#include "gameloop.h"
#include "graphics.h"
#include "physics.h"
#include "input.h"
#include "scores.h"


int removeLast(char* text)
{
	int i = 0;
	for(i=0;i<100;i++)
	{
		if((text[i]=='\0') && (i!=0))
		{
			text[i-1] = '\0';
			return 1;
		}
	}
	return 0;
}

int showPrompt(SDL_Renderer* renderer, TTF_Font* font,int score, char text[100], char inputText[100])
{
	sprintf(text,"GAME OVER!");
	drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*6/18,text,'r',40);
	sprintf(text,"Your score: %d",score);
	drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*8/18,text,' ',25);		
	sprintf(text,"Enter your name:");
	drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*10/18,text,' ',25);
	drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*11/18,inputText,' ',25);
}

int showHighscores(SDL_Renderer* renderer, TTF_Font* font, int highScore, int lowScore, TScore* Highscores)
{
	char text[100];
	sprintf(text,"HIGHSCORES");
	drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*2/18,text,'r',40);
	sprintf(text,"Press ESC to quit, press SPACEBAR to play again");
	drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*16/18,text,' ',25);

	int i;
	for(i=highScore;i<lowScore+1;i++)
	{
		//sprintf(text,"%d): %s: %6d",i,"NAME",0);
		sprintf(text,"%d): %s: %6d",i,Highscores[i-1].name,Highscores[i-1].score);
		drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*(i+3-highScore+1)/18,text,' ',20);
	}
}

int outroLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture, TTF_Font* font, int score)
{
	int go = 0;
	int promptDone = 0;
	SDL_Event event;
	char text[100];
	char inputText[100];
	int cursor;
	int i = 0;
	int highScore = 1;
	int lowScore = 10;
	for(i=0;i<100;i++)
	{
		inputText[i]='\0';
	}
	SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
	SDL_StartTextInput();
	TScore* Highscores = (TScore*)malloc(SAVED_SCORES_AMOUNT*sizeof(TScore));
	if(!Highscores) exit(1);
	while(!go)
	{
		SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
		if(!promptDone)
		{
			showPrompt(renderer,font,score,text,inputText);
		}
		else
		{
			showHighscores(renderer,font, highScore,lowScore, Highscores);
		}
		SDL_RenderPresent(renderer);
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				go = -1;
			else if(event.type == SDL_KEYDOWN)
			{
				if(!promptDone)
				{
					if((event.key.keysym.sym == SDLK_BACKSPACE) && (cursor>0))
					{
						removeLast(inputText);
						cursor--;
					}
					else if((event.key.keysym.sym == SDLK_RETURN) && (cursor>0))
					{
						loadScores(Highscores);
						saveScore(inputText,score,Highscores);
						promptDone = 1;
					}
				}
				else
				{
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						go = -1;
					}
					else if(event.key.keysym.sym == SDLK_SPACE)
					{
						go = 1;
					}
					else if((event.key.keysym.sym == SDLK_UP) && (highScore>1))
					{
						highScore--;
						lowScore--;
					}
					else if((event.key.keysym.sym == SDLK_DOWN) && (lowScore<SAVED_SCORES_AMOUNT))
					{
						highScore++;
						lowScore++;
					}
				}
			}
			else if(event.type == SDL_TEXTINPUT)
			{
				strcat(inputText,event.text.text);
				cursor++;
			}
		}
	}
	//CLEANUP
	SDL_StopTextInput();
	free(Highscores);
	return go;
}