#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>

#include "graphics.h"
#include "input.h"
#include "physics.h"

int main(int argc, char* args[])
{
	//inits outside of SDL
	int i = 0, j = 0;
	char** Board = NULL;
	Board = (char**)malloc(BOARD_HEIGHT*sizeof(char*));
	for(i=0;i<BOARD_HEIGHT;i++) Board[i]=(char*)malloc(BOARD_WIDTH*sizeof(char));

	for(i=0;i<BOARD_HEIGHT;i++)
	{
		for(j=0;j<BOARD_WIDTH;j++)
		{
			Board[i][j] = ' ';
		}
	}

	//basic SDL inits
	if(SDL_Init(SDL_INIT_VIDEO)) exit(1);
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	window = SDL_CreateWindow("NOT tetris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);
	renderer = SDL_CreateRenderer(window,-1,0);

	//init surfaces for background and for drawing the game
	SDL_Surface* backgroundSurface = NULL;
	SDL_Texture* backgroundTexture = NULL;
	backgroundSurface = SDL_LoadBMP("bg.bmp");
	if(backgroundSurface == NULL) printf("error:%s\n", SDL_GetError());
	backgroundTexture = SDL_CreateTextureFromSurface(renderer,backgroundSurface);
	SDL_FreeSurface(backgroundSurface);

	//GAME LOOP
	unsigned int lastTime = 0, currentTime;
	int done = 0;
	char pieceID;

	int gameSpeed = 100;
	unsigned int lastTick = 0, currentTick;

	int orientation = 0;
	int speedup = 0;
	float speedupMulti = 1.5;

	while (!done)
	{
		currentTime = SDL_GetTicks();
		currentTick = SDL_GetTicks();

		SDL_Event event;
		//1. RENDER
		//Copy background texture, game texture
		SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
		//draw current game state
		drawBoard(renderer, Board,WINDOW_WIDTH/3,0);
		SDL_RenderPresent(renderer);
		//2. HANDLE INPUT
		while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT) done = 1;
                    else if(event.type == SDL_KEYDOWN) handleInput(event.key.keysym,&orientation,&speedup);
                }
        printf("%d\n",orientation);
        //3. CALCULATIONS (new game state based on input, check for game over etc.)
        if(currentTick < lastTick + gameSpeed)
        {
        	//drop down 1 row
        }
        // do rotations
        //4. FPS shenanigans
        if(currentTime < lastTime + 17)
        {
        	SDL_Delay(currentTime-lastTime);
        }
        lastTime = currentTime;
	}
	//NON SDL CLEANUP
	for(i=0;i<BOARD_HEIGHT;i++)
	{
		free(Board[i]);
	}
	free(Board);

	//SDL CLEANUP
	if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}