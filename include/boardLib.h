#ifndef BOARDLIB_H
#define BOARDLIB_H

#include "pieceLib.h"
#include "typedefs.h"

void copyGameBoard(GameBoard * src, GameBoard * dest) ;
void setupGameBoardDefault(GameBoard * game);
void setupGameBoardFEN(GameBoard * game, String FEN);
void printGameBoard(GameBoard * game);
void printPlayerPieces(Player * player);

#endif