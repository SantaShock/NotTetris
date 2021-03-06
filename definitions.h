#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//Dimension parameters
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH WINDOW_HEIGHT*1.5

#define BOARD_HEIGHT 25
#define BOARD_WIDTH 10

#define BLOCK_SIZE (WINDOW_HEIGHT/20)

//Colors
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

//Font parameters
#define FONT_NAME "slkscr.ttf"
//#define FONT_SIZE (BLOCK_SIZE*6/5)
#define FONT_SIZE 50
#define TEXT_COLOR 123,123,123
#define TEXT_GREEN 5,255,5
#define TEXT_RED 255,5,5
#define TEXT_BLUE 5,5,255
#define TEXT_YELLOW 255,255,0
#define TEXT_PURPLE 128,0,128
#define TEXT_ORANGE 255,165,0
#define TEXT_CYAN 0,255,255

//Score/FileIO parameters
#define SCORE_FILE_NAME "scores.dat"
#define SAVED_SCORES_AMOUNT 20

//Game speed parameters
#define BASE_SPEED 500
#define SPEEDUP_MULTIPLIER 10
#define LEVEL_MULTIPLIER 0.90

//Spawn position of new pieces
#define SPAWNOFFSETX 3
#define SPAWNOFFSETY 21

#endif /* DEFINITIONS_H */