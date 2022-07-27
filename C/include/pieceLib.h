#ifndef PIECELIB_H
#define PIECELIB_H

#include "typedefs.h"
int getControlledSquares_Pawn(void * game, int sSquare, int *buffer);
int getControlledSquares_Rook(void * game, int sSquare, int *buffer);
int getControlledSquares_Bishop(void * game, int sSquare, int *buffer);
int getControlledSquares_Knight(void * game, int sSquare, int *buffer);
int getControlledSquares_King(void * game, int sSquare, int *buffer);
int getControlledSquares_Queen(void * game, int sSquare, int *buffer);

#endif