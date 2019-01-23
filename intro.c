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

int introLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture, TTF_Font* font)
{
	int go = 0;
	SDL_Event event;
	char text[100];
	SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
	while(!go)
	{
		sprintf(text,"INSTRUCTIONS");
		drawText(renderer,font,50,50,text);
		sprintf(text,"Rotate: Q/E");
		drawText(renderer,font,50,100,text);
		sprintf(text,"Move: Left/Right arrow");
		drawText(renderer,font,50,150,text);
		sprintf(text,"Speed up: Spacebar");
		drawText(renderer,font,50,200,text);
		sprintf(text,"Press Spacebar to start!");
		drawText(renderer,font,50,300,text);
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) 
				return -1;
			else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
				go = 1;
		}	
	}
	return 1;
}