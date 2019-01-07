#include <stdio.h>
#include <SDL.h>
#include "graphics.h"

//Draws a singular block which makes up the tetris pieces
int drawBlock(SDL_Renderer* renderer,int x, int y)
{
	SDL_Rect block;
	block.x = x;
	block.y = y;
	block.w = BLOCK_SIZE;
	block.h = BLOCK_SIZE;
	SDL_RenderFillRect(renderer,&block);
	SDL_SetRenderDrawColor(renderer,LIGHT_GRAY);
	SDL_RenderDrawRect(renderer,&block);
	return 1;
}

int iPiece(SDL_Renderer* renderer, int x, int y, int ori)
{
	SDL_SetRenderDrawColor(renderer, CYAN);
	switch(ori)
	{
		case 0:
			drawBlock(renderer,x-BLOCK_SIZE*2,y-BLOCK_SIZE);
			drawBlock(renderer,x-BLOCK_SIZE,y-BLOCK_SIZE);
			drawBlock(renderer,x,y-BLOCK_SIZE);
			drawBlock(renderer,x+BLOCK_SIZE,y-BLOCK_SIZE);
			break;
		case 1:
			drawBlock(renderer,x,y-BLOCK_SIZE*2);
			drawBlock(renderer,x,y-BLOCK_SIZE);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y+BLOCK_SIZE);
			break;
		case 2:
			drawBlock(renderer,x-BLOCK_SIZE*2,y);
			drawBlock(renderer,x-BLOCK_SIZE,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x+BLOCK_SIZE,y);
			break;
		case 3:
			drawBlock(renderer,x-BLOCK_SIZE,y-BLOCK_SIZE*2);
			drawBlock(renderer,x-BLOCK_SIZE,y-BLOCK_SIZE);
			drawBlock(renderer,x-BLOCK_SIZE,y);
			drawBlock(renderer,x-BLOCK_SIZE,y+BLOCK_SIZE);
			break;
	}
}

int oPiece(SDL_Renderer* renderer, int x, int y, int ori)
{
	SDL_SetRenderDrawColor(renderer,YELLOW);
	drawBlock(renderer,x,y);
	drawBlock(renderer,x+BLOCK_SIZE,y);
	drawBlock(renderer,x,y+BLOCK_SIZE);
	drawBlock(renderer,x+BLOCK_SIZE,y+BLOCK_SIZE);

}

int tPiece(SDL_Renderer* renderer, int x, int y, int ori)
{
	SDL_SetRenderDrawColor(renderer,PURPLE);
	switch(ori)
	{
		case 0:
			SDL_SetRenderDrawColor(renderer,PURPLE);
			drawBlock(renderer,x,y);
			SDL_SetRenderDrawColor(renderer,PURPLE);
			drawBlock(renderer,x+BLOCK_SIZE,y);
			SDL_SetRenderDrawColor(renderer,PURPLE);
			drawBlock(renderer,x,y-BLOCK_SIZE);
			SDL_SetRenderDrawColor(renderer,PURPLE);
			drawBlock(renderer,x-BLOCK_SIZE,y);
			break;
		case 1:
			drawBlock(renderer,x,y);
			drawBlock(renderer,x+BLOCK_SIZE,y);
			drawBlock(renderer,x,y-BLOCK_SIZE);
			drawBlock(renderer,x,y+BLOCK_SIZE);
			break;
		case 2:
			drawBlock(renderer,x,y);
			drawBlock(renderer,x-BLOCK_SIZE,y);
			drawBlock(renderer,x+BLOCK_SIZE,y);
			drawBlock(renderer,x,y+BLOCK_SIZE);
			break;
		case 3:
			drawBlock(renderer,x,y);
			drawBlock(renderer,x-BLOCK_SIZE,y);
			drawBlock(renderer,x,y-BLOCK_SIZE);
			drawBlock(renderer,x,y+BLOCK_SIZE);
			break;
	}
}

int sPiece(SDL_Renderer* renderer, int x, int y, int ori)
{
	SDL_SetRenderDrawColor(renderer,GREEN);
	switch(ori)
	{
		case 0:
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			break;
		case 1:
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			break;
		case 2:
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			break;
		case 3:
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			drawBlock(renderer,x,y);
			break;
	}
}

//Draws a tetris piece based on position and piece id
int drawPiece(SDL_Renderer* renderer, int x, int y, char pieceID, int ori)
{
	switch(pieceID)
	{
		case 'i':
			iPiece(renderer,x,y,ori);
			break;
		case 'o':
			oPiece(renderer,x,y,ori);
			break;
		case 't':
			tPiece(renderer,x,y,ori);
			break;
		default:
			iPiece(renderer,x,y,ori);
			break;
	}
	return 1;
}

int evalBoard(char currentCell, unsigned int* r, unsigned int* g, unsigned int* b)
{
	switch(currentCell)
	{
		case 'i':
			*r = 0;
			*g = 255;
			*b = 255;
			return 0;
		case 'o':
			return 1;
		case 't':
			*r = 128;
			*g = 0;
			*b = 128;
			return 2;
		case 'l':
			return 3;
		case 'j':
			return 4;
		case 's':
			return 5;
		case 'z':
			return 6;
		default:
			*r = 255;
			*g = 165;
			*b = 0;
	}
}

int drawBoard(SDL_Renderer* renderer, char** Board, int x, int y)
{
	int i=0,j=0;
	unsigned int r,g,b;
	for(i=0;i<BOARD_HEIGHT;i++)
	{
		for(j=0;j<BOARD_WIDTH;j++)
		{
			evalBoard(Board[i][j],&r,&g,&b);
			SDL_SetRenderDrawColor(renderer, r,g,b,255);
			drawBlock(renderer,x+j*BLOCK_SIZE,y+i*BLOCK_SIZE);
		}
	}
	return 1;
}