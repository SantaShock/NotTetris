#ifndef PHYSICS_H
#define PHYSICS_H

int spawnPiece(char** Board, char** nextPieceDraw, int* spawned, int pieceStats[7]);
int updateBoard(char** Board);
int doTickDrop(char** Board, int* spawned, int* orientation, int* linesCleared);
int doRotation(char** Board, int* orientation);
int doMovement(char** Board, int* movement);
int resetBoard(char** Board);
int checkBoard();
int initPhysics(int pieceStats[7]);

#endif /* PHYSICS_H_ */