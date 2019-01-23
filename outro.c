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

int saveScore(char* text, int score)
{
	return 1;
}

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
	drawText(renderer,font,WINDOW_WIDTH/3,WINDOW_HEIGHT/2,text);
	sprintf(text,"Your score: %d",score);
	drawText(renderer,font,WINDOW_WIDTH/3,WINDOW_HEIGHT/2+50,text);		sprintf(text,"Enter your name:");
	drawText(renderer,font,WINDOW_WIDTH/3,WINDOW_HEIGHT/2+100,text);
	drawText(renderer,font,WINDOW_WIDTH/3,WINDOW_HEIGHT/2+150,inputText);
}

int showHighscores(SDL_Renderer* renderer, TTF_Font* font)
{
	char text[100];
	sprintf(text,"HIGHSCORES");
	drawText(renderer,font,WINDOW_WIDTH/3,WINDOW_HEIGHT/10,text);
	sprintf(text,"Press ESC to quit, press SPACEBAR to play again");
	drawText(renderer,font,WINDOW_WIDTH/5,WINDOW_HEIGHT/10*9,text);

	int i;
	for(i=1;i<8;i++)
	{
		sprintf(text,"%d): %s: %6d",i,"NAME",0);
		drawText(renderer,font,WINDOW_WIDTH/3,WINDOW_HEIGHT/11*(i+1),text);
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
	for(i=0;i<100;i++)
	{
		inputText[i]='\0';
	}
	SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
	SDL_StartTextInput();
	while(!go)
	{
		SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
		if(!promptDone)
		{
			showPrompt(renderer,font,score,text,inputText);
		}
		else
		{
			showHighscores(renderer,font);
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
							saveScore(inputText,score);
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
				}
			}
			else if(event.type == SDL_TEXTINPUT)
			{
				strcat(inputText,event.text.text);
				cursor++;
			}
		}
	}
	SDL_StopTextInput();
	return go;
}