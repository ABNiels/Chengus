#include "pieceLib.h"
#include "typedefs.h"
#include "asciiHelper.h"
#include <stdlib.h>
#include <stdio.h>
//#include "boardLib.h"

#define SHIFT_UP(pos) pos -= 8
#define SHIFT_DOWN(pos) pos += 8
#define SHIFT_LEFT(pos) pos = (pos%8==0)? 100: pos - 1
#define SHIFT_RIGHT(pos) pos = (pos%8==7)? 100: pos + 1
#define SHIFT_UP_RIGHT(pos) pos = (pos%8==7)? 100: pos - 7
#define SHIFT_UP_LEFT(pos) pos = (pos%8==0)? 100: pos - 9
#define SHIFT_DOWN_RIGHT(pos) pos = (pos%8==7)? 100: pos + 9
#define SHIFT_DOWN_LEFT(pos) pos = (pos%8==0)? 100: pos + 7
#define SHIFT_UP_UP_LEFT(pos) pos = (pos%8==0)? 100: pos - 17
#define SHIFT_UP_UP_RIGHT(pos) pos = (pos%8==7)? 100: pos - 15
#define SHIFT_UP_LEFT_LEFT(pos) pos = (pos%8<=1)? 100: pos - 10
#define SHIFT_UP_RIGHT_RIGHT(pos) pos = (pos%8>=6)? 100: pos - 6
#define SHIFT_DOWN_DOWN_LEFT(pos) pos = (pos%8==0)? 100: pos + 15
#define SHIFT_DOWN_DOWN_RIGHT(pos) pos = (pos%8==7)? 100: pos + 17
#define SHIFT_DOWN_LEFT_LEFT(pos) pos = (pos%8<=1)? 100: pos + 6
#define SHIFT_DOWN_RIGHT_RIGHT(pos) pos = (pos%8>=6)? 100: pos + 10

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
#define SHIFTED_UP_LEFT_LEFT(pos) (pos%8<=1)? 100: pos - 10
#define SHIFTED_UP_RIGHT_RIGHT(pos) (pos%8 >= 6)? 100: pos - 6
#define SHIFTED_DOWN_DOWN_LEFT(pos) (pos%8==0)? 100: pos + 15
#define SHIFTED_DOWN_DOWN_RIGHT(pos) (pos%8==7)? 100: pos + 17
#define SHIFTED_DOWN_LEFT_LEFT(pos) (pos%8<=1)? 100: pos + 6
#define SHIFTED_DOWN_RIGHT_RIGHT(pos)(pos%8 >= 6)? 100: pos + 10



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
        list->key = pos;                    \
        list->next = NULL;                  \
                                            \
        }                                   \

       // printf("%s\n", int2alg(list->key));  \

#define ON_BOARD(pos) (pos <= 63 && pos >= 0)


LL * getControlledSquares_Pawn(void * gamePtr, int square) {
    GameBoard *game = (GameBoard *)gamePtr;
    LL *pSquares = NULL;
    Color color = game->squares[square].piece->player->color;
    int curSquare;

    if(color == WHITE) {
        curSquare = SHIFTED_UP_LEFT(square);
        if(ON_BOARD(curSquare)) {
            insertSquareLL(pSquares, curSquare)
        }
        curSquare = SHIFTED_UP_RIGHT(square);
        if(ON_BOARD(curSquare)) {
            insertSquareLL(pSquares, curSquare)
        }
    }
    else {
        curSquare = SHIFTED_DOWN_LEFT(square);
        if(ON_BOARD(curSquare)) {
            insertSquareLL(pSquares, curSquare)
        }
        curSquare = SHIFTED_DOWN_RIGHT(square);
        if(ON_BOARD(curSquare)) {
            insertSquareLL(pSquares, curSquare)
        }
    }

    return pSquares;
}

LL * getControlledSquares_Rook(void * gamePtr, int square) {
    GameBoard *game = (GameBoard *)gamePtr;
    LL *pSquares = NULL;
    int curSquare;
    Color pieceColor =  game->squares[square].piece->player->color;

    curSquare = SHIFTED_UP(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_UP(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;

    }

    
    curSquare = SHIFTED_LEFT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_LEFT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }


    curSquare = SHIFTED_RIGHT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_RIGHT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }

    curSquare = SHIFTED_DOWN(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_DOWN(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }
    
    return pSquares;
}

LL * getControlledSquares_Bishop(void * gamePtr, int square) {    
    GameBoard *game = (GameBoard *)gamePtr;
    LL *pSquares = NULL;
    int curSquare;
    Color pieceColor =  game->squares[square].piece->player->color;

    curSquare = SHIFTED_UP_LEFT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_UP_LEFT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;

    }

    curSquare = SHIFTED_DOWN_LEFT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_DOWN_LEFT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }

    curSquare = SHIFTED_UP_RIGHT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_UP_RIGHT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }

    curSquare = SHIFTED_DOWN_RIGHT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_DOWN_RIGHT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }
    
    return pSquares;
}

LL * getControlledSquares_Knight(void * gamePtr, int square) {
    GameBoard *game = (GameBoard *)gamePtr;
    LL *pSquares = NULL;
    int curSquare;

    curSquare = SHIFTED_DOWN_DOWN_LEFT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }

    curSquare = SHIFTED_DOWN_DOWN_RIGHT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }

    curSquare = SHIFTED_DOWN_LEFT_LEFT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }

    curSquare = SHIFTED_DOWN_RIGHT_RIGHT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }
    
    curSquare = SHIFTED_UP_UP_LEFT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }
    
    curSquare = SHIFTED_UP_UP_RIGHT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }
    
    curSquare = SHIFTED_UP_LEFT_LEFT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }
    
    curSquare = SHIFTED_UP_RIGHT_RIGHT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare);
    }
    return pSquares;
}

LL * getControlledSquares_King(void * gamePtr, int square) {
    GameBoard *game = (GameBoard *)gamePtr;
    LL *pSquares = NULL;
    int curSquare;

    curSquare = SHIFTED_UP(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares,curSquare)
    }    
    curSquare = SHIFTED_UP_RIGHT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare)
    }    
    curSquare = SHIFTED_RIGHT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare)
    }
    curSquare = SHIFTED_DOWN_RIGHT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare)
    }
    curSquare = SHIFTED_DOWN(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare)
    }    
    curSquare = SHIFTED_DOWN_LEFT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare)
    }    
    curSquare = SHIFTED_LEFT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare)
    }    
    curSquare = SHIFTED_UP_LEFT(square);
    if(ON_BOARD(curSquare)) {
        insertSquareLL(pSquares, curSquare)
    }

    return pSquares;
}

LL * getControlledSquares_Queen(void * gamePtr, int square) {    GameBoard *game = (GameBoard *)gamePtr;
    LL *pSquares = NULL;
    int curSquare;
    Color pieceColor =  game->squares[square].piece->player->color;

    curSquare = SHIFTED_UP(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_UP(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;

    }
    
    curSquare = SHIFTED_LEFT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_LEFT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }

    curSquare = SHIFTED_RIGHT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_RIGHT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }

    curSquare = SHIFTED_DOWN(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_DOWN(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }
    
    curSquare = SHIFTED_UP_LEFT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_UP_LEFT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;

    }

    curSquare = SHIFTED_DOWN_LEFT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_DOWN_LEFT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }

    curSquare = SHIFTED_UP_RIGHT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_UP_RIGHT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }

    curSquare = SHIFTED_DOWN_RIGHT(square);
    while(ON_BOARD(curSquare)) {
        if(!game->squares[curSquare].piece) {
            insertSquareLL(pSquares, curSquare);
            SHIFT_DOWN_RIGHT(curSquare);
            continue;
        }
        insertSquareLL(pSquares, curSquare);
        break;
    }
    
    return pSquares;
}