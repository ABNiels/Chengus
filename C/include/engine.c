#include "engine.h"
#include "typedefs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "asciiHelper.h"

#define MAX(a, b) (a>b)? a:b

static const float centerControl[64] = {
    0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,
    0.5,	0.577,	0.577,	0.577,	0.577,	0.577,	0.577,	0.5,
    0.5,	0.577,	0.707,	0.707,	0.707,	0.707,	0.577,	0.5,
    0.5,	0.577,	0.707,	1,	    1,  	0.707,	0.577,	0.5,
    0.5,	0.577,	0.707,	1,	    1,	    0.707,	0.577,	0.5,
    0.5,	0.577,	0.707,	0.707,	0.707,	0.707,	0.577,	0.5,
    0.5,	0.577,	0.577,	0.577,	0.577,	0.577,	0.577,	0.5,
    0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,	0.5,
    };
static const float kingControl[8] = { 1.5, 1.19, 0.95, 0.75, 0.6, 0.47, 0.38, 0.3, };

float evaluatePosition(GameBoard * game, BST * DrawTable) {
    float material[2] = {0,0};
    float control[2] = {0,0};
    
    int controlBuffer[27];
    register int controlIndex = 0;
    int temp, index, kingOffset;

    int kingPos[2] = {game->pieces[WHITE][0], game->pieces[BLACK][0]};

    for(int i=0; i<16; i++) {
        index = game->pieces[WHITE][i];
        if(index >= 0) {
            // Material
            material[WHITE] += game->squares[index]->baseVal;

            
            // Board Control
            
            memset(controlBuffer, -1, sizeof(int)*27);
            temp = game->squares[index]->getControlledSquares(game, index, controlBuffer);
            controlIndex = 0;
            while(controlIndex <= 27) {
                temp = controlBuffer[controlIndex];
                if(temp == -1) break;
                kingOffset = kingPos[BLACK] - temp;
                control[WHITE] += centerControl[temp] + kingControl[MAX(abs(kingOffset)/8, abs(kingOffset)%8)];
                ++controlIndex;
            }
            
            // King safety
            // Initiative
            // Weak squares / outposts
            // trapped pieces
            // space
            // passed pawns
            
        }
    }
    for(int i=0; i<16; i++) {
        index = game->pieces[BLACK][i];
        if(index >= 0) {
            // Material
            material[BLACK] += game->squares[index]->baseVal;

            
            // Board Control
            
            memset(controlBuffer, -1, sizeof(int)*27);
            temp = game->squares[index]->getControlledSquares(game, index, controlBuffer);
            controlIndex = 0;
            while(controlIndex <= 27) {
                temp = controlBuffer[controlIndex];
                if(temp == -1) break;
                kingOffset = kingPos[WHITE] - temp;
                control[BLACK] += centerControl[temp] + kingControl[MAX(abs(kingOffset)/8, abs(kingOffset)%8)];
                ++controlIndex;
            }
            
            // King safety
            // Initiative
            // Weak squares / outposts
            // trapped pieces
            // space
            // passed pawns
            
        }
    }


    game->eval = material[WHITE] - material[BLACK] + (control[WHITE] - control[BLACK])/40;
    return material[WHITE] - material[BLACK];
}

