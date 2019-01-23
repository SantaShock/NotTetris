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

int calculateScore(int* currentLinesCleared,int* score, int level, int dropStreak)
{
	switch(*currentLinesCleared)
	{
		case 0:
			return 1;
		case 1:
			*score += 40 * (level+1) + dropStreak;
			break;
		case 2:
			*score += 100 *(level+1) + dropStreak;
			break;
		case 3:
			*score += 300 *(level+1) + dropStreak;
			break;
		case 4:
			*score += 1200*(level+1) + dropStreak;
			break;
	}
	*currentLinesCleared = 0;
	return 1;
}

int countDown(SDL_Window* window, SDL_Renderer* renderer,TTF_Font* font)
{
	char text[100];
	sprintf(text,"  3 ");
    drawText(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,text);
    SDL_RenderPresent(renderer);
	SDL_Delay(BASE_SPEED);
	sprintf(text,"  2 ");
    drawText(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,text);
    SDL_RenderPresent(renderer);
	SDL_Delay(BASE_SPEED);
	sprintf(text,"  1 ");
    drawText(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,text);
    SDL_RenderPresent(renderer);
	SDL_Delay(BASE_SPEED);
	sprintf(text," GO! ");
    drawText(renderer,font,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,text);
    SDL_RenderPresent(renderer);
	SDL_Delay(BASE_SPEED);
	return 1;
}

int gameLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture, char** Board, char** nextPiece, TTF_Font* font, int* score, SDL_Texture* sShotTexture)
{
	//Timings
	unsigned int lastTime = 0, currentTime = 1;
	unsigned int lastTick = 0, currentTick = 1;
	//Event handle
	SDL_Event event;
	//Game Variables
	int gameOver = 0;
	int doPause = 0;
	int spawned = 0;
	int gameSpeed = BASE_SPEED;
	int currentLinesCleared = 0;
	int totalLinesCleared = 0;
	int currentSoftDrop = 0;
	int level = 0;
	int pieceStats[7] = {0,0,0,0,0,0,0};
	//Input variables
	int orientation = 0;
	int moveDir = 0;
	int speedup = 0;
	int receivedInput = 0;
	//Text array
	char text[100];
	//DRAW BACKGROUND
	SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);
	//Reset Arrays
	resetBoard(Board);
	//GAME LOOP
	countDown(window,renderer,font);
	while(!gameOver)
	{
		//Timings
		currentTime = SDL_GetTicks();
		currentTick = SDL_GetTicks();
		//1: RENDER
		drawBoard(renderer, Board, WINDOW_WIDTH/3, 0);
		SDL_RenderPresent(renderer);
		//2: HANLDE INPUT
		while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return -1;
 	        else if(event.type == SDL_KEYDOWN) handleInput(event.key.keysym,&orientation,&speedup,&moveDir,&doPause);
 	        else if(event.type == SDL_KEYUP) handleKeyRelease(event.key.keysym,&speedup);
    	}
    	//2.5: PAUSE
    	if(doPause)
    	{
    		sprintf(text,"GAME PAUSED");
    		drawText(renderer,font,WINDOW_WIDTH/4*3,0,text);
    	}
    	else
    	{
    		sprintf(text,"            ");
    		drawText(renderer,font,WINDOW_WIDTH/4*3,0,text);
		//3: PHYSICS CALCS
			//3.1: SPAWN PIECE IF NO PIECE CURRENTLY SPAWNED
    		if(!spawned)
    		{
    			printf("spawning\n");
    			spawnPiece(Board, nextPiece, &spawned, pieceStats);
    			//Update text everytime a new piece is spawned
    			drawNextPiece(renderer, nextPiece, 2*BLOCK_SIZE , WINDOW_HEIGHT - 6*BLOCK_SIZE);
    			drawStats(renderer,font,pieceStats);
    			drawScores(renderer,font,totalLinesCleared,level,*score);
    			//Reset soft drop streak with every new piece
    			currentSoftDrop = 0;
    			//Check if the newest piece is hitting the top
    			gameOver = checkBoard();
    		}
			//3.2: DO ROTATIONS/moveDir
			if(spawned)
			{
				doRotation(Board,&orientation);
				doMovement(Board,&moveDir);
			}
			//3.3: DO TICKDROP
			if((spawned) && (currentTick > lastTick + gameSpeed/(1+speedup)))
			{
				doTickDrop(Board,&spawned,&orientation, &currentLinesCleared);
				//Increment soft drop streak
				if(speedup) currentSoftDrop++;
				//If lines have been cleared, update the score
				if(currentLinesCleared)
				{
					totalLinesCleared += currentLinesCleared;
					calculateScore(&currentLinesCleared,score,level,currentSoftDrop);
				}
				//Raise level for every 10 lines have been cleared
				if((totalLinesCleared>=(level+1)*10) && (totalLinesCleared!=0))
				{
					level++;
					gameSpeed = BASE_SPEED * pow(LEVEL_MULTIPLIER,level);
				}
				//Timing
				lastTick = currentTick;
			}
			//3.4: ADD NEW CALCS TO GAME STATE
			updateBoard(Board);
		}
		//4: TIMINGS, 60 fps target
		if(currentTime < lastTime + 16)
        {
        	SDL_Delay(currentTime-lastTime);
        }
        lastTime = currentTime;
	}
	//get screen pixel data for outro
	captureScreen(renderer,sShotTexture);
	return 1;
}
