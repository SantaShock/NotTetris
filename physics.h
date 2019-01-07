#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct TetrisPieces {
	char pieceID;
	unsigned int r;
	unsigned int g;
	unsigned int b;
	int boundary;
}TPiece;

#endif /* PHYSICS_H_ */