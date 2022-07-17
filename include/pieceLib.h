#ifndef PIECELIB_H
#define PIECELIB_H

#include "typedefs.h"
LL * getControlledSquares_Pawn(void * game, int sSquare);
LL * getControlledSquares_Rook(void * game, int sSquare);
LL * getControlledSquares_Bishop(void * game, int sSquare);
LL * getControlledSquares_Knight(void * game, int sSquare);
LL * getControlledSquares_King(void * game, int sSquare);
LL * getControlledSquares_Queen(void * game, int sSquare);

#endif