#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "typedefs.h"
#include "boardLib.h"
#include "asciiHelper.h"
#include "pieceLib.h"
#include "engine.h"

int main() {
    printf("V2\n");
    GameBoard game, copy; // = malloc(sizeof(GameBoard));
    LL *llPtr;
    BST *DrawTable = malloc(sizeof(BST));
    //setupGameBoardDefault(&game);
    setupGameBoardFEN(&game, "rnbqkbnr/pppp1ppp/8/4p3/4Q3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 1");
    //copyGameBoard(&game, &copy);
    
    /*
    game.squares[0].piece = NULL;
    llPtr = game.players[BLACK]->pieces;
    while(llPtr && llPtr->key != 0) {
        llPtr = llPtr->next;
    }
    if(llPtr) llPtr->key = -1.0;
    */

    evaluatePosition(&game, DrawTable);
    printGameBoard(&game);
    printPlayerPieces(&game, BLACK);
    //printf("%s\n", int2alg(((Piece *)((Player *)game->players[BLACK])->pieces->data)->square->pos));
    printf("End\n");

    return 1;
}
