#ifndef PIECES_H
#define PIECES_H

typedef struct TetrisPieces /* holds information of the tetris pieces */
{
	char ID;
	int x;
	int y;
	int orientation;
	int shape[16][4];
}TPiece;

int initPieces();
TPiece* getNewPiece(int pieceStats[7]);

#endif /* PIECES_H */