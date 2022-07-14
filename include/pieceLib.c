#include "pieceLib.h"
#include "typedefs.h"

#include <stdlib.h>
#include <stdio.h>
//#include "boardLib.h"

#define SHIFT_UP(pos) pos -= 8
#define SHIFT_DOWN(pos) pos += 8
#define SHIFT_LEFT(pos) (pos%8==0)? 100: pos -= 1
#define SHIFT_RIGHT(pos) (pos%8==7)? 100: pos += 1
#define SHIFT_UP_RIGHT(pos) (pos%8==7)? 100: pos -= 7
#define SHIFT_UP_LEFT(pos) (pos%8==0)? 100: pos -= 9
#define SHIFT_DOWN_RIGHT(pos) (pos%8==7)? 100: pos += 9
#define SHIFT_DOWN_LEFT(pos) (pos%8==0)? 100: pos += 7
#define SHIFT_UP_UP_LEFT(pos) (pos%8==0)? 100: pos -= 17
#define SHIFT_UP_UP_RIGHT(pos) (pos%8==7)? 100: pos -= 15
#define SHIFT_UP_LEFT_LEFT(pos) (pos%8==0)? 100: pos -= 10
#define SHIFT_UP_RIGHT_RIGHT(pos) (pos%8==7)? 100: pos -= 6
#define SHIFT_DOWN_DOWN_LEFT(pos) (pos%8==0)? 100: pos += 15
#define SHIFT_DOWN_DOWN_RIGHT(pos) (pos%8==7)? 100: pos += 17
#define SHIFT_DOWN_LEFT_LEFT(pos) (pos%8==0)? 100: pos += 6
#define SHIFT_DOWN_RIGHT_RIGHT(pos) (pos%8==7)? 100: pos += 10


#define SHIFTED_UP(pos) pos - 8
#define SHIFTED_DOWN(pos) pos + 8
#define SHIFTED_LEFT(pos) (pos%8==0)? 100: pos - 1
#define SHIFTED_RIGHT(pos) (pos%8==7)? 100: pos + 1
#define SHIFTED_UP_RIGHT(pos) (pos%8==7)? 100: pos - 7
#define SHIFTED_UP_LEFT(pos) (pos%8==0)? 100: pos - 9
#define SHIFTED_DOWN_RIGHT(pos) (pos%8==7)? 100: pos + 9
#define SHIFTED_DOWN_LEFT(pos) (pos%8==0)? 100: pos + 7
#define SHIFTED_UP_UP_LEFT(pos) (pos%8==0)? 100: pos - 17
#define SHIFTED_UP_UP_RIGHT(pos)(pos%8==7)? 100:  pos - 15
#define SHIFTED_UP_LEFT_LEFT(pos) (pos%8==0)? 100: pos - 10
#define SHIFTED_UP_RIGHT_RIGHT(pos) (pos%8==7)? 100: pos - 6
#define SHIFTED_DOWN_DOWN_LEFT(pos) (pos%8==0)? 100: pos + 15
#define SHIFTED_DOWN_DOWN_RIGHT(pos) (pos%8==7)? 100: pos + 17
#define SHIFTED_DOWN_LEFT_LEFT(pos) (pos%8==0)? 100: pos + 6
#define SHIFTED_DOWN_RIGHT_RIGHT(pos) (pos%8==7)? 100: pos + 10



#define insertSquareLL(list, pos) {         \
        if(list == NULL) {                  \
            list = malloc(sizeof(LL));      \
            list->prev = NULL;              \
        }                                   \
        else {                              \
            list->next = malloc(sizeof(LL));\
            list->next->prev = list;        \
            list = list->next;              \
        }                                   \
        list->key = (float)pos;             \
        list->next = NULL;                  \
                                            \
        }                                   \


#define ON_BOARD(pos) (pos <= 63 && pos >= 0)


LL * getControlledSquares_Pawn(GameBoard * game, int square) {
    LL *pSquares = NULL;
    Color color = game->squares[square].piece->player->color;
    if(color == WHITE) {
        if(ON_BOARD(SHIFTED_UP_LEFT(square))) {
            insertSquareLL(pSquares, SHIFTED_UP_LEFT(square))
        }
        if(ON_BOARD(SHIFTED_UP_RIGHT(square))) {
            insertSquareLL(pSquares, SHIFTED_UP_RIGHT(square))
        }
    }
    else {
        
        if(ON_BOARD(SHIFTED_DOWN_LEFT(square))) {
            insertSquareLL(pSquares, SHIFTED_DOWN_LEFT(square))
        }
        if(ON_BOARD(SHIFTED_DOWN_RIGHT(square))) {
            insertSquareLL(pSquares, SHIFTED_DOWN_RIGHT(square))
        }
    }

    return pSquares;
}

LL * getControlledSquares_Rook(GameBoard * game, int square) {
    LL *pSquares = NULL;
    int curSquare;
    Color pieceColor =  game->squares[square].piece->player->color;

    printf("Made it %i\n", square);
    printf("---------\n");
    curSquare = SHIFTED_UP(square);
    while(ON_BOARD(curSquare)) {
        printf("%i\n", curSquare);
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_UP(curSquare);
            continue;
        }
        else if(game->squares[curSquare].piece->player->color != pieceColor) {
            insertSquareLL(pSquares, curSquare);
            break;
        }
        break;
    }

    printf("---------\n");
    curSquare = SHIFTED_LEFT(square);
    while(ON_BOARD(curSquare)) {
        printf("%i\n", curSquare);
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_LEFT(curSquare);
            continue;
        }
        else if(game->squares[curSquare].piece->player->color != pieceColor) {
            insertSquareLL(pSquares, curSquare);
            break;
        }
        break;
    }


    printf("---------\n");
    curSquare = SHIFTED_RIGHT(square);
    while(ON_BOARD(curSquare)) {
        printf("%i\n", curSquare);
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_RIGHT(curSquare);
            continue;
        }
        else if(game->squares[curSquare].piece->player->color != pieceColor) {
            insertSquareLL(pSquares, curSquare);
            break;
        }
        break;
    }

    printf("---------\n");
    curSquare = SHIFTED_DOWN(square);
    while(ON_BOARD(curSquare)) {
        printf("%i\n", curSquare);
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_DOWN(curSquare);
            continue;
        }
        else if(game->squares[curSquare].piece->player->color != pieceColor) {
            insertSquareLL(pSquares, curSquare);
            break;
        }
        break;
    }
    
    printf("---------\n");
    return pSquares;
}

LL * getControlledSquares_Bishop(GameBoard * game, int square) {
    LL *pSquares = NULL;
    return pSquares;
}

LL * getControlledSquares_Knight(GameBoard * game, int square) {
    LL *pSquares = NULL;

    if(ON_BOARD(SHIFTED_DOWN_DOWN_LEFT(square))) {
        insertSquareLL(pSquares, SHIFTED_DOWN_DOWN_LEFT(square))
    }

    if(ON_BOARD(SHIFTED_DOWN_LEFT_LEFT(square))) {
        insertSquareLL(pSquares, SHIFTED_DOWN_LEFT_LEFT(square))
    }

    if(ON_BOARD(SHIFTED_DOWN_DOWN_RIGHT(square))) {
        insertSquareLL(pSquares, SHIFTED_DOWN_DOWN_RIGHT(square))
    }

    if(ON_BOARD(SHIFTED_DOWN_RIGHT_RIGHT(square))) {
        insertSquareLL(pSquares, SHIFTED_DOWN_RIGHT_RIGHT(square))
    }

    if(ON_BOARD(SHIFTED_UP_UP_LEFT(square))) {
        insertSquareLL(pSquares, SHIFTED_UP_UP_LEFT(square))
    }

    if(ON_BOARD(SHIFTED_UP_LEFT_LEFT(square))) {
        insertSquareLL(pSquares, SHIFTED_UP_LEFT_LEFT(square))
    }

    if(ON_BOARD(SHIFTED_UP_UP_RIGHT(square))) {
        insertSquareLL(pSquares, SHIFTED_UP_UP_RIGHT(square))
    }

    if(ON_BOARD(SHIFTED_UP_RIGHT_RIGHT(square))) {
        insertSquareLL(pSquares, SHIFTED_UP_RIGHT_RIGHT(square))
    }

    return pSquares;
}

LL * getControlledSquares_King(GameBoard * game, int square) {
    LL *pSquares = NULL;
    
    if(ON_BOARD(SHIFTED_UP(square))) {
        insertSquareLL(pSquares, SHIFTED_UP(square))
    }
    if(ON_BOARD(SHIFTED_UP_RIGHT(square))) {
        insertSquareLL(pSquares, SHIFTED_UP_RIGHT(square))
    }
    if(ON_BOARD(SHIFTED_RIGHT(square))) {
        insertSquareLL(pSquares, SHIFTED_RIGHT(square))
    }
    if(ON_BOARD(SHIFTED_DOWN_RIGHT(square))) {
        insertSquareLL(pSquares, SHIFTED_DOWN_RIGHT(square))
    }
    if(ON_BOARD(SHIFTED_DOWN(square))) {
        insertSquareLL(pSquares, SHIFTED_DOWN(square))
    }
    if(ON_BOARD(SHIFTED_DOWN_LEFT(square))) {
        insertSquareLL(pSquares, SHIFTED_DOWN_LEFT(square))
    }
    if(ON_BOARD(SHIFTED_LEFT(square))) {
        insertSquareLL(pSquares, SHIFTED_LEFT(square))
    }
    if(ON_BOARD(SHIFTED_UP_LEFT(square))) {
        insertSquareLL(pSquares, SHIFTED_UP_LEFT(square))
    }
    return pSquares;
}

LL * getControlledSquares_Queen(GameBoard * game, int square) {
    LL *pSquares = NULL;
    return pSquares;
}