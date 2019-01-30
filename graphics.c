#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "definitions.h"
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
	SDL_SetRenderDrawColor(renderer,DARK_GRAY);
	SDL_RenderDrawRect(renderer,&block);
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
			*r = 255;
			*g = 255;
			*b = 0;
			return 1;
		case 't':
			*r = 128;
			*g = 0;
			*b = 128;
			return 2;
		case 'l':
			*r = 255;
			*g = 165;
			*b = 0;
			return 3;
		case 'j':
			*r = 5;
			*g = 5;
			*b = 255;
			return 4;
		case 's':
			*r = 5;
			*g = 255;
			*b = 5;
			return 5;
		case 'z':
			*r = 255;
			*g = 5;
			*b = 5;
			return 6;
		case 'x':
			*r = 200;
			*g = 200;
			*b = 200;
			return 7;
		default:
			*r = 110;
			*g = 110;
			*b = 110;
			return -1;
	}
}

int drawBoard(SDL_Renderer* renderer, char** Board, int x, int y)
{
	int i,j;
	unsigned int r,g,b;
	for(i=BOARD_HEIGHT-1;i>-1;i--)
	{
		for(j=BOARD_WIDTH-1;j>-1;j--)
		{
			evalBoard(Board[i][j],&r,&g,&b);
			SDL_SetRenderDrawColor(renderer, r,g,b,255);
			drawBlock(renderer,x+j*BLOCK_SIZE,WINDOW_HEIGHT-(y+(i+1)*BLOCK_SIZE));
		}
	}
	return 1;
}

int drawNextPiece(SDL_Renderer* renderer, char** nextPieceDraw, int x, int y)
{
	int i,j;
	unsigned int r,g,b;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			evalBoard(nextPieceDraw[i][j],&r,&g,&b);
			SDL_SetRenderDrawColor(renderer,r,g,b,255);
			drawBlock(renderer,x+j*BLOCK_SIZE,WINDOW_HEIGHT-(y+(4-i)*BLOCK_SIZE));
		}
	}
	return 1;
}

int drawText(SDL_Renderer* renderer, TTF_Font* font, int x, int y, char text[100])
{
	int i;
	//inits
	SDL_Color Test = {TEXT_COLOR};
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text,Test);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer,surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = 0;

	for(i=0;i<100;i++)
	{
		if(text[i]=='\0')
		{
			Message_rect.w = i*20;
			break;	
		}
	}
	if(Message_rect.w == 0) Message_rect.w = 100;
	Message_rect.h = 50;
	//erase previous stuff
	SDL_SetRenderDrawColor(renderer,DARK_GRAY);
	SDL_RenderFillRect(renderer,&Message_rect);
	//draw text
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	//cleanup
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}


int drawTextSettings(SDL_Renderer* renderer, TTF_Font* font, int x, int y, char text[100], char color, int fontSize)
{
	int i;
	//color
	SDL_Color textColor;
	switch(color)
	{
		case 'g':
			textColor = {TEXT_GREEN};
			break;
		case 'r':
			textColor = {TEXT_RED};
			break;
		case 'b':
			textColor = {TEXT_BLUE};
			break;
		case 'y':
			textColor = {TEXT_YELLOW};
			break;
		case 'p':
			textColor = {TEXT_PURPLE};
			break;
		case 'o':
			textColor = {TEXT_ORANGE};
			break;
		case 'c':
			textColor = {TEXT_CYAN};
			break;
		default:
			textColor = {TEXT_COLOR};
			break;
	}
	//inits
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text,textColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer,surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.w = 0;

	for(i=0;i<100;i++)
	{
		if(text[i]=='\0')
		{
			Message_rect.w = i*(fontSize*6/6);
			break;	
		}
	}
	//if(Message_rect.w == 0) Message_rect.w = 100;
	Message_rect.h = 2*fontSize;
	Message_rect.x = x - (Message_rect.w/2);
	Message_rect.y = y - (Message_rect.h/2);
	//draw text
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	//cleanup
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

int drawScores(SDL_Renderer* renderer, TTF_Font* font, int linesCleared, int level, int score)
{
	char text[100];
	//LEFT SIDE

	sprintf(text,"LEVEL: %d", level);
	drawText(renderer,font,2*WINDOW_WIDTH/3+2*FONT_SIZE,FONT_SIZE*2,text);

	sprintf(text,"LINES: %d",linesCleared);
	drawText(renderer,font,2*WINDOW_WIDTH/3+2*FONT_SIZE,FONT_SIZE*4,text);

	sprintf(text,"SCORE: %d", score);
	drawText(renderer,font,2*WINDOW_WIDTH/3+2*FONT_SIZE,FONT_SIZE*6,text);

}

char translateIntToChar(int n)
{
	char ch;
	switch(n)
	{
		case 0:
			ch = 'i';
			break;
		case 1:
			ch = 'o';
			break;
		case 2:
			ch = 't';
			break;
		case 3:
			ch = 's';
			break;
		case 4:
			ch = 'z';
			break;
		case 5:
			ch = 'j';
			break;
		case 6:
			ch = 'l';
			break;
	}
	return ch;
}

int drawStats(SDL_Renderer* renderer, TTF_Font* font, int pieceStats[7])
{
	//RIGHT SIDE
	int i = 0;
	char ch = ' ';
	char text[100];
	strcpy(text,"NEXT");
	drawText(renderer,font,2*BLOCK_SIZE,5,text);
	sprintf(text,"STATS");
	drawText(renderer,font,2*BLOCK_SIZE,WINDOW_HEIGHT/3,text);
	for(i=0;i<7;i++)
	{
		sprintf(text,"%c: %d",translateIntToChar(i),pieceStats[i]);
		drawText(renderer,font,2*BLOCK_SIZE + 20,WINDOW_HEIGHT/3+FONT_SIZE*(i+1),text);
	}
}

int captureScreen(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0,WINDOW_WIDTH,WINDOW_HEIGHT,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
	SDL_RenderReadPixels(renderer,NULL,SDL_PIXELFORMAT_ARGB8888, surface->pixels,surface->pitch);
	texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	return 1;
}
