#ifndef INPUT_H
#define INPUT_H

int handleInput(SDL_Keysym key, int* orientation, int* speedup, int* movement);
int handleKeyRelease(SDL_Keysym key, int* speedup);

#endif /* INPUT_H_ */