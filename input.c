#include <SDL.h>

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
int handleInput(SDL_Keysym key, int* orientation, int* speedup)
{
	*speedup = 0;

	switch(key.sym)
	{
		case SDLK_LEFT:
			*orientation = wrapDown(orientation);
			break;
		case SDLK_RIGHT:
			*orientation = wrapUp(orientation);
			break;
		default:
			break;
	}
	return 1;
}