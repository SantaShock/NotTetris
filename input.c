#include <SDL.h>
#include "definitions.h"

int wrapUp(int* orientation)
{
	if(*orientation+1>3) return 0;
	else return *orientation+1;
}

int wrapDown(int* orientation)
{
	if(*orientation-1<0) return 3;
	else return *orientation-1;
}

//6 basic ass keybindings: space = speedup, left/right arrows = move left or right, 
//  up/down = rotation, esc = pause
int handleInput(SDL_Keysym key, int* orientation, int* speedup, int* movement)
{
	switch(key.sym)
	{
		case SDLK_DOWN:
			*orientation = wrapDown(orientation);
			break;
		case SDLK_UP:
			*orientation = wrapUp(orientation);
			break;
		case SDLK_LEFT:
			*movement = -1;
			break;
		case SDLK_RIGHT:
			*movement = 1;
			break;
		case SDLK_SPACE:
			*speedup = 10;
			break;
		default:
			break;
	}
	return 1;
}

int handleKeyRelease(SDL_Keysym key, int* speedup)
{
	if(key.sym == SDLK_SPACE)
	{
		*speedup = 0;
		return 1;
	}
	else return 0;
}