#ifndef GRAPHICS_H
#define GRAPHICS_H

int drawBoard(SDL_Renderer* renderer, char** Board, int x, int y);
int drawNextPiece(SDL_Renderer* render, char** nextPieceDraw, int x, int y);
int drawText(SDL_Renderer* renderer, TTF_Font* font, int x, int y, char text[100]);
int drawScores(SDL_Renderer* renderer, TTF_Font* font, int linesCleared, int level, int score);
int drawStats(SDL_Renderer* renderer, TTF_Font* font, int pieceStats[7]);
int captureScreen(SDL_Renderer* renderer, SDL_Texture* texture);
#endif /*GRAPHICS_H_*/