#ifndef PIECELIB_H
#define PIECELIB_H

#include "typedefs.h"
LL * getControlledSquares_Pawn(GameBoard * game, int sSquare);
LL * getControlledSquares_Rook(GameBoard * game, int sSquare);
LL * getControlledSquares_Bishop(GameBoard * game, int sSquare);
LL * getControlledSquares_Knight(GameBoard * game, int sSquare);
LL * getControlledSquares_King(GameBoard * game, int sSquare);
LL * getControlledSquares_Queen(GameBoard * game, int sSquare);

#endif