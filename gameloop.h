#ifndef GAMELOOP_H
#define GAMELOOP_H

int gameLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture, char** Board, char** nextPiece, TTF_Font* font, int* score, SDL_Texture* sShotTexture);

#endif /* GAMELOOP_H */