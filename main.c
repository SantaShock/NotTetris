#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "definitions.h"

#include "graphics.h"
#include "physics.h"
#include "input.h"
#include "scores.h"

int gameLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture, char** Board, char** nextPiece, TTF_Font* font)
{
	//Timings
	unsigned int lastTime = 0, currentTime = 1;
	unsigned int lastTick = 0, currentTick = 1;
	//Game Variables
	int gameOver = 0;
	int spawned = 0;
	int gameSpeed = BASE_SPEED;
	int linesCleared = 0;
	int score = 0;
	int level = 0;
	int pieceStats[7] = {0,0,0,0,0,0,0};
	//Input variables
	int orientation = 0;
	int moveDir = 0;
	int speedup = 0;
	//Text array
	char text[100];
	//DRAW BACKGROUND
	SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
	//GAME LOOP
	while(!gameOver)
	{
		//Timings
		currentTime = SDL_GetTicks();
		currentTick = SDL_GetTicks();
		//Event handle
		SDL_Event event;
		//1: RENDER
		drawBoard(renderer, Board, WINDOW_WIDTH/3, 0);
		SDL_RenderPresent(renderer);
		//2: HANLDE INPUT
		while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) gameOver = 1;
 	        else if(event.type == SDL_KEYDOWN) handleInput(event.key.keysym,&orientation,&speedup,&moveDir);
 	        else if(event.type == SDL_KEYUP) handleKeyRelease(event.key.keysym,&speedup);
    	}
		//3: PHYSICS CALCS
			//3.1: SPAWN PIECE IF NO PIECE CURRENTLY SPAWNED
    		if(!spawned)
    		{
    			spawnPiece(Board, nextPiece, &spawned, pieceStats);
    			drawNextPiece(renderer, nextPiece, 2*BLOCK_SIZE , WINDOW_HEIGHT - 6*BLOCK_SIZE);
    			drawStats(renderer,font,pieceStats);
    			drawScores(renderer,font,linesCleared,level,score);
    		}
			//3.2: DO ROTATIONS/moveDir
			if(spawned)
			{
				doRotation(Board,orientation);
				doMovement(Board,&moveDir);
			}
			//3.3: DO TICKDROP
			if((spawned) && (currentTick > lastTick + gameSpeed/(1+speedup)))
			{
				doTickDrop(Board,&spawned,&orientation, &linesCleared);
				if((linesCleared>=(level+1)*10) && (linesCleared!=0))
				{
					level++;
					gameSpeed = BASE_SPEED * pow(LEVEL_MULTIPLIER,level);
				}
				lastTick = currentTick;
			}
			//3.4: ADD NEW CALCS TO GAME STATE
			updateBoard(Board);
		//4: TIMINGS
		if(currentTime < lastTime + 16)
        {
        	SDL_Delay(currentTime-lastTime);
        }
        lastTime = currentTime;
	}
	return 1;
}

int main(int argc, char* args[])
{
//INITS
	initPhysics();
	//VARIABLES
	int i,j;
	char** Board = NULL;
	char** nextPiece = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* backgroundSurface = NULL;
	SDL_Texture* backgroundTexture = NULL;
	//allocate memory
	//array to hold data on upcoming piece
	nextPiece = (char**)malloc(4*sizeof(char*));
	for(i=0;i<4;i++) nextPiece[i] = (char*)malloc(4*sizeof(char));
	//array to hold board data
	Board = (char**)malloc(BOARD_HEIGHT*sizeof(char*));
	for(i=0;i<BOARD_HEIGHT;i++) Board[i]=(char*)malloc(BOARD_WIDTH*sizeof(char));
	//fill aray with blank spaces
	for(i=0;i<BOARD_HEIGHT;i++)
	{
		for(j=0;j<BOARD_WIDTH;j++)
		{
			Board[i][j] = ' ';
		}
	}
	if(SDL_Init(SDL_INIT_VIDEO)) exit(1);
	window = SDL_CreateWindow("NOT tetris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);
	renderer = SDL_CreateRenderer(window,-1,0);
	//init surfaces for background and for drawing the game
	backgroundSurface = SDL_LoadBMP("bg.bmp");
	if(backgroundSurface == NULL) printf("error:%s\n", SDL_GetError());
	backgroundTexture = SDL_CreateTextureFromSurface(renderer,backgroundSurface);
	SDL_FreeSurface(backgroundSurface);
	//init ttf and font
	if(TTF_Init() == -1) exit(1);
	TTF_Font* font = TTF_OpenFont(FONT_NAME,FONT_SIZE);
//TBD: start/instruction screen
//START GAME
	gameLoop(window, renderer, backgroundTexture, Board, nextPiece, font);
//TBD: game over / score submit screen
//CLEANUP
	//SDL
	if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    SDL_Quit();
    //TTF
    if (font) TTF_CloseFont(font);
    TTF_Quit();
	return 0;
}