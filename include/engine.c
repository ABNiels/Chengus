#include "engine.h"
#include "typedefs.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) (a>b)? a:b

static const float centerControl[64] = {
    0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,
    0.5,	0.577,	0.577,	0.577,	0.577,	0.577,	0.577,	0.5,
    0.5,	0.577,	0.707,	0.707,	0.707,	0.707,	0.577,	0.5,
    0.5,	0.577,	0.707,	1,	1,	0.707,	0.577,	0.5,
    0.5,	0.577,	0.707,	1,	1,	0.707,	0.577,	0.5,
    0.5,	0.577,	0.707,	0.707,	0.707,	0.707,	0.577,	0.5,
    0.5,	0.577,	0.577,	0.577,	0.577,	0.577,	0.577,	0.5,
    0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,
    };
static const float kingControl[8] = { 1, 0.93, 0.86, 0.79, 0.74, 0.68, 0.63, 0.58, };

float evaluatePosition(GameBoard * game, BST * DrawTable) {
    float material[2] = {0,0};
    float control[2] = {0,0};

    LL *posPtr = NULL;
    LL *piecePtr = game->players[WHITE]->pieces;
    int kingPos[2] = {(int)game->players[WHITE]->pieces->key, (int)game->players[BLACK]->pieces->key };

    while(piecePtr) {
        if(piecePtr->key >=0) {
            // Material
            material[WHITE] += ((Piece *)piecePtr->data)->baseVal;

            
            // Board Control
            posPtr = ((Piece *)piecePtr->data)->getControlledSquares(game, piecePtr->key);    
            while(posPtr && posPtr->prev) {
                control[WHITE] += centerControl[(int)posPtr->key] + kingControl[MAX(kingPos[BLACK]/8 - (int)posPtr->key/8, kingPos[BLACK]%8 - (int)posPtr->key%8)];
                posPtr = posPtr->prev;
                free(posPtr->next);
            }

            if(posPtr) {
                control[WHITE] += centerControl[(int)posPtr->key];
                control[WHITE] += kingControl[MAX(kingPos[BLACK]/8 - (int)posPtr->key/8, kingPos[BLACK]%8 - (int)posPtr->key%8)];
                free(posPtr);
            }

            // King safety
            // Initiative
            
        }
        piecePtr = piecePtr->next;
    }


    posPtr = NULL;
    piecePtr = game->players[BLACK]->pieces;
    while(piecePtr) {
        if(piecePtr->key >=0) {
            // Material
            material[BLACK] += ((Piece *)piecePtr->data)->baseVal;

            
            // Center Control
            posPtr = ((Piece *)piecePtr->data)->getControlledSquares(game, piecePtr->key);
            while(posPtr && posPtr->prev) {
                control[BLACK] += centerControl[(int)posPtr->key] + kingControl[MAX(kingPos[WHITE]/8 - (int)posPtr->key/8, kingPos[WHITE]%8 - (int)posPtr->key%8)];
                posPtr = posPtr->prev;
                free(posPtr->next);
            }

            if(posPtr) {
                control[BLACK] += centerControl[(int)posPtr->key] + kingControl[MAX(kingPos[WHITE]/8 - (int)posPtr->key/8, kingPos[WHITE]%8 - (int)posPtr->key%8)];;
                free(posPtr);
            }
            
        }
        piecePtr = piecePtr->next;
    }

    game->eval = material[WHITE] - material[BLACK] + (control[WHITE] /(control[WHITE] + control[BLACK]) - 0.5);
    return material[WHITE] - material[BLACK];
}

