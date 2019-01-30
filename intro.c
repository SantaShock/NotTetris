#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "definitions.h"

#include "gameloop.h"
#include "graphics.h"
#include "physics.h"
#include "input.h"

int cycleColor(char* color)
{
	char colors[7] = {'g','r','b','y','p','o','c'};
	int i;
	for(i=0;i<7;i++)
	{
		if(colors[i] == *color)
		{
			if(i==6) *color = colors[0];
			else *color = colors[i+1];
			break;
		}
	}
	return 1;
}

int introLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture, TTF_Font* font)
{
	int go = 0;
	int i = 0;
	SDL_Event event;
	char text[100];
	char color = 'r';
	SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
	while(!go)
	{
		if(i == 150)
		{
			cycleColor(&color);
			i=0;
		}
		sprintf(text,"NoTetris");
		drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*1/11,text,color,50);
		sprintf(text,"CONTROLS:");
		drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*3/11,text,' ',35);
		sprintf(text,"Rotate: Q/E");
		drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*4/11,text,' ',25);
		sprintf(text,"Move: Left/Right arrow");
		drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*6/11,text,' ',25);
		sprintf(text,"Speed up: Spacebar");
		drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*8/11,text,' ',25);
		sprintf(text,"Press Spacebar to start!");
		drawTextSettings(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT*10/11,text,' ',25);
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) 
				return -1;
			else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
				go = 1;
		}	
		i++;
	}
	return 1;
}