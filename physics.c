#include <stdlib.h>
#include "physics.h"
#include "definitions.h"
#include "pieces.h"

#include <stdio.h>

static int** Landed;
static TPiece* activePiece = NULL;
static TPiece* nextPiece = NULL;

int initPhysics()
{
	initPieces();
	int i,j;
	int trash[7];
	Landed = (int**)malloc(BOARD_HEIGHT*sizeof(int*));
	for(i=0;i<BOARD_HEIGHT;i++) Landed[i]=(int*)malloc(BOARD_WIDTH*sizeof(int));

	for(i=0;i<BOARD_HEIGHT;i++)
	{
		for(j=0;j<BOARD_WIDTH;j++)
		{
			Landed[i][j] = 0;
		}
	}
	nextPiece = getNewPiece(trash);
}

int updateBoard(char** Board)
{
	int i,j;
	//clear out previous position
	for(i=0;i<BOARD_HEIGHT;i++)
	{
		for(j=0;j<BOARD_WIDTH;j++)
		{
			if((Board[i][j]!=' ') && (Landed[i][j]==0)) 
			{
				Board[i][j] = ' ';
			}
		}
	}
	//add new piece to the grid
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i+activePiece->y-3>=0)
			{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1)
					Board[i+activePiece->y-3][j+activePiece->x]=activePiece->ID;
			}
		}
	}
}

int spawnPiece(char** Board, char** nextPieceDraw, int* spawned, int pieceStats[7])
{
	int i,j;
	activePiece = nextPiece;
	nextPiece = getNewPiece(pieceStats);
	//pass data of next piece back
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			nextPieceDraw[i][j] = ' ';
			if(nextPiece->shape[i][j] == 1)
				nextPieceDraw[i][j] = nextPiece->ID;
		}
	}
	*spawned = 1;
	return 1;
}

int checkRight(char** Board)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if((i+activePiece->y-3>=0) && (j+activePiece->x >= 0) && (j+activePiece->x <= 9))
			{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1)
				{
					if(Landed[activePiece->y+i-3][activePiece->x+j+1])
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int checkLeft(char** Board)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if((i+activePiece->y-3>=0) && (j+activePiece->x >= 0) && (j+activePiece->x <= 9))
			{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1)
				{
					if(Landed[activePiece->y+i-3][activePiece->x+j-1])
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int checkMoveCollision(char** Board, int movement)
{
	int lx = 3;
	int rx = 0;
	int i,j;
	if(movement == -1)
	{
		//find left-most block
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1)
				{
					if(lx > j) lx = j;
				}
			}
		}
		if((activePiece->x-1+lx<0) || (checkLeft(Board))) 
		{
			return 1;
		}
		else 
			return 0;
	}
	if(movement == 1)
	{
		//find right-most block
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1)
				{
					if(rx < j) rx = j;
				}
			}
		}
		if((activePiece->x+1+rx>9) || (checkRight(Board)))
			return 1;
		else
			return 0;
	}
}

int doMovement(char** Board, int* movement)
{
	if((*movement == 1) && (!checkMoveCollision(Board, *movement)))
	{
		activePiece->x++;
		*movement = 0;
		return 1;
	}	
	if((*movement == -1) && (!checkMoveCollision(Board,*movement)))
	{
		activePiece->x--;
		*movement = 0;
		return 1;
	}
}

int checkRotateCollision(char** Board, int newOrientation)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(activePiece->shape[3-i+newOrientation*4][j] == 1)
				if(Landed[activePiece->y+i-3][activePiece->x+j])
					return 1;
		}
	}
	return 0;
}


int doRotation(char** Board, int* newOrientation)
{
	if(!checkRotateCollision(Board, *newOrientation))
	{
		activePiece->orientation=*newOrientation;
		return 1;
	}
	else 
	{
		*newOrientation=activePiece->orientation;
		return 0;
	}
}

int checkBelow(int orientation)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if((i+activePiece->y-3>=0) && (j+activePiece->x >= 0) && (j+activePiece->x <= 9))
			{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1)
				{
					if(Landed[activePiece->y+i-3-1][activePiece->x+j])
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int checkDropCollision(char** Board, int orientation)
{
	int i,j;
	int lowesty = 0;
	//find the lowest y coordinate block
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1)
				{
					if(lowesty < 3-i) lowesty = 3-i;
				}
		}
	}
	if((activePiece->y-lowesty-1 < 0) || (checkBelow(orientation))) 
	{
		return 1;
	}
	else return 0;
}

int addActiveToLanded()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if((i+activePiece->y-3>=0) && (j+activePiece->x >= 0) && (j+activePiece->x <= 9))
			{
				if(activePiece->shape[3-i+activePiece->orientation*4][j]==1) 
				{
					Landed[i+activePiece->y-3][j+activePiece->x]=1;
				}
			}
		}
	}
}

int swapBoard(char** Board, int row)
{
	char* temp;
	temp = Board[row+1];
	Board[row+1] = Board[row];
	Board[row] = temp;
	return 1;
}

int swapLanded(int row)
{
	int* temp;
	temp = Landed[row+1];
	Landed[row+1] = Landed[row];
	Landed[row] = temp;
	return 1;
}

int clearRow(char** Board,int row)
{
	//clear row
	int i;
	for(i=0;i<BOARD_WIDTH;i++)
	{
		Landed[row][i] = 0;
	}
	//move rest of the array down
	int j;
	for(i=row;i<BOARD_HEIGHT-1;i++)
	{
		swapLanded(i);
		swapBoard(Board,i);
	}
	return 1;
}

int checkRowClear(char** Board)
{
	int i,j;
	int clear;
	int clearcount = 0;
	for(i=0;i<BOARD_HEIGHT;i++)
	{
		clear = 1;
		for(j=0;j<BOARD_WIDTH;j++)
		{
			if(Landed[i][j] == 1) 
			{
				continue;
			}
			else clear = 0;
		}
		if(clear) 
		{
			clearRow(Board,i);
			i--;
			clearcount++;
		}
	}
	return clearcount;
}

int doTickDrop(char** Board, int* spawned, int* orientation, int* linesCleared)
{
	//if there is an active piece and theres no collision below, drop it
	if((activePiece!=NULL) && (!checkDropCollision(Board, *orientation)))
	{
		activePiece->y--;
	}
	//if there is a collection below, request new spawn and reset orientation
	//also add piece to the Landed array
	else 
	{
		*spawned = 0;
		*orientation = 0;
		addActiveToLanded();
		*linesCleared = checkRowClear(Board);
	}
}

int checkBoard()
{
	int i;
	for(i=0;i<BOARD_WIDTH;i++)
	{
		if(Landed[20][i] == 1) return 1;
	}
	return 0;
}