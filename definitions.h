#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH WINDOW_HEIGHT*1.5

#define BOARD_HEIGHT 25
#define BOARD_WIDTH 10

#define BLOCK_SIZE (WINDOW_HEIGHT/20)

#define BLACK 0,0,0,255
#define WHITE 255,255,255,255
#define DARK_GRAY 95,95,95,255
#define LIGHT_GRAY 110,110,110,255

#define GREEN 5,255,5,255 // S piece
#define RED 255,5,5,255 // Z piece
#define BLUE 5,5,255,255 // J piece
#define YELLOW 255,255,0,255 // O piece
#define PURPLE 128,0,128,255// T piece
#define ORANGE 255,165,0,255// L piece
#define CYAN 0,255,255,255// I piece

#define FONT_NAME "slkscr.ttf"
#define FONT_SIZE (BLOCK_SIZE+5)
#define TEXT_COLOR 123,123,123

#define BASE_SPEED 500
#define SPEEDUP_MULTIPLIER 10
#define LEVEL_MULTIPLIER 0.80

#endif /* DEFINITIONS_H */