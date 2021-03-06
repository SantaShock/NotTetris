#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "definitions.h"

#include "gameloop.h"
#include "intro.h"
#include "outro.h"
#include "physics.h"

#include "random.h"

int main(int argc, char* args[])
{
//INITS
	//VARIABLES
	int i,j;
	char** Board = NULL;
	char** nextPiece = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* backgroundSurface = NULL;
	SDL_Texture* backgroundTexture = NULL;
	SDL_Texture* sShotTexture = NULL;
	//Memeory-allocations
	//Array to hold data on upcoming piece
	nextPiece = (char**)malloc(4*sizeof(char*));
	for(i=0;i<4;i++) nextPiece[i] = (char*)malloc(4*sizeof(char));
	//Array to hold board data
	Board = (char**)malloc(BOARD_HEIGHT*sizeof(char*));
	for(i=0;i<BOARD_HEIGHT;i++) Board[i]=(char*)malloc(BOARD_WIDTH*sizeof(char));
	//Fill board-array with blank spaces
	for(i=0;i<BOARD_HEIGHT;i++)
	{
		for(j=0;j<BOARD_WIDTH;j++)
		{
			Board[i][j] = ' ';
		}
	}
	//SDL INITS
	if(SDL_Init(SDL_INIT_VIDEO)) exit(1);
	window = SDL_CreateWindow("NOTetris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);
	renderer = SDL_CreateRenderer(window,-1,0);
	//init surfaces for background and for drawing the game
	backgroundSurface = SDL_LoadBMP("bg.bmp");
	if(backgroundSurface == NULL) exit(1);
	backgroundTexture = SDL_CreateTextureFromSurface(renderer,backgroundSurface);
	SDL_FreeSurface(backgroundSurface);
	//init ttf and font
	if(TTF_Init() == -1) exit(1);
	TTF_Font* font = TTF_OpenFont(FONT_NAME,FONT_SIZE);
	if(!font) exit(1);
	//Game Variables
	//Keep track of how many of each pieces occured
	int pieceStats[7] = {0,0,0,0,0,0,0};
	//Keep track of score across stages of the game
	int score = 0;
	//Keep track if the user wants to keep playing
	int keepPlaying = 1;
	do
	{
//TBD: start/instruction screen
		if(introLoop(window,renderer,backgroundTexture,font) == 1)
//START GAME
		{
			//init game variables
			initPhysics(pieceStats);
			score = 0;
			if(gameLoop(window, renderer, backgroundTexture, Board, nextPiece, font, &score, sShotTexture, pieceStats) == 1)
//TBD: game over / score submit screen
			{
				keepPlaying = outroLoop(window,renderer,backgroundTexture,font,score);
			}
			else keepPlaying = 0;
		}
		else keepPlaying = 0;
	}while(keepPlaying==1);
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