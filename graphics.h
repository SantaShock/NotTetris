#ifndef GRAPHICS_H
#define GRAPHICS_H

#define WINDOW_HEIGHT 601
#define WINDOW_WIDTH 900

#define BOARD_HEIGHT 25
#define BOARD_WIDTH 10

#define BLACK 0,0,0,255
#define WHITE 255,255,255,255
#define LIGHT_GRAY 95,95,95,100
#define DARK_GRAY 45,45,45,150

#define GREEN 5,255,5,255 // S piece
#define RED 255,5,5,255 // Z piece
#define BLUE 5,5,255,255 // J piece
#define YELLOW 255,255,0,255 // O piece
#define PURPLE 128,0,128,255// T piece
#define ORANGE 255,165,0,255// L piece
#define CYAN 0,255,255,255// I piece

/*
PIECES:
I:
****
O:
**
**
T:
 *
***
S:
 **
**
Z:
**
 **
J:
*
***
L:
  *
***
*/

#define BLOCK_SIZE 30

int drawPiece(SDL_Renderer* renderer, int x, int y, char pieceID, int orientation);
int drawBoard(SDL_Renderer* renderer, char** Board, int x, int y);

#endif /*GRAPHICS_H_*/
