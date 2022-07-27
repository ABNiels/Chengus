#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "boardLib.h"
#include "typedefs.h"
#include "asciiHelper.h"
#include "pieceLib.h"

#define SET_ARCHETYPE(val, fn, n, c, pos) ({\
    archetype = malloc(sizeof(Piece));\
    archetype->baseVal = val;\
    archetype->getControlledSquares = fn;\
    archetype->name = n;\
    archetype->color = c;\
    game->squares[pos] = archetype;\
})

#define CREATE_ARCHETPE(val, fn, n, c, pos) ({\
    archetype[pos] = malloc(sizeof(Piece));\
    archetype[pos]->baseVal = val;\
    archetype[pos]->getControlledSquares = fn;\
    archetype[pos]->name = n;\
    archetype[pos]->color = c;\
})

/*
void copyGameBoard(GameBoard * src, GameBoard * dest) {
    dest->squares = malloc(sizeof(Square)*64);
    
    dest->castling[WHITE][KINGSIDE] = src->castling[WHITE][KINGSIDE];
    dest->castling[BLACK][KINGSIDE] = src->castling[BLACK][KINGSIDE];
    dest->castling[WHITE][QUEENSIDE] = src->castling[WHITE][QUEENSIDE];
    dest->castling[BLACK][QUEENSIDE] = src->castling[BLACK][QUEENSIDE];

    int i;
    for(i=0; i<64; i++) {
        dest->squares[i].piece = src->squares[i].piece;
        dest->squares[i].board = dest;
        dest->squares[i].pos = i;
    }

    if(src->en_passant) {
        dest->en_passant = &(dest->squares[src->en_passant->pos]);
    } else {
        dest->en_passant = NULL;
    }

    dest->players = src->players;
    dest->turn = src->turn;
}

*/


void setupGameBoardFEN(GameBoard * game, String FEN) {
    
    char *FENPtr = FEN;    
    game->squares = (Piece **)calloc(64, sizeof(Piece *));
    memset(game->pieces[0], -1, sizeof(int)*16);
    memset(game->pieces[1], -1, sizeof(int)*16);
    Piece *archetype[12];
    CREATE_ARCHETPE(999, getControlledSquares_King, 'K', WHITE, 0);
    CREATE_ARCHETPE(8, getControlledSquares_Queen, 'Q', WHITE, 1);
    CREATE_ARCHETPE(5, getControlledSquares_Rook, 'R', WHITE, 2);
    CREATE_ARCHETPE(3, getControlledSquares_Bishop, 'B', WHITE, 3);
    CREATE_ARCHETPE(3, getControlledSquares_Knight, 'N', WHITE, 4);
    CREATE_ARCHETPE(1, getControlledSquares_Pawn, 'P', WHITE, 5);
    CREATE_ARCHETPE(999, getControlledSquares_King, 'k', BLACK, 6);
    CREATE_ARCHETPE(8, getControlledSquares_Queen, 'q', BLACK, 7);
    CREATE_ARCHETPE(5, getControlledSquares_Rook, 'r', BLACK, 8);
    CREATE_ARCHETPE(3, getControlledSquares_Bishop, 'b', BLACK, 9);
    CREATE_ARCHETPE(3, getControlledSquares_Knight, 'n', BLACK, 10);
    CREATE_ARCHETPE(1, getControlledSquares_Pawn, 'p', BLACK, 11);



    int pos = 0, whitePieceIndex=0, blackPieceIndex=0;
    while (*FENPtr != ' ') {
        char curChar = (*FENPtr++);
        if (isUpper(curChar) || isLower(curChar)) {
            switch (curChar) {
                case 'n': //Knight
                case 'b': //Bishop
                case 'r': //Rook
                case 'q': //Queen
                case 'p': //Pawn
                    game->pieces[BLACK][++blackPieceIndex] = pos;
                    switch(curChar) {
                        case 'p':
                            game->squares[pos] = archetype[11];
                            break;
                        case 'n':
                            game->squares[pos] = archetype[10];
                            break;
                        case 'b':
                            game->squares[pos] = archetype[9];
                            break;
                        case 'r':
                            game->squares[pos] = archetype[8];
                            break;
                        case 'q':
                            game->squares[pos] = archetype[7];
                            break;
                    }
                    break;
                case 'k': //King
                    game->pieces[BLACK][0] = pos;
                    game->squares[pos] = archetype[6];
                    break;
                case 'N':
                case 'B': 
                case 'R':
                case 'P':
                case 'Q':
                    game->pieces[WHITE][++whitePieceIndex] = pos;
                    switch(curChar) {
                        case 'P':
                            game->squares[pos] = archetype[5];
                            break;
                        case 'N':
                            game->squares[pos] = archetype[4];
                            break;
                        case 'B':
                            game->squares[pos] = archetype[3];
                            break;
                        case 'R':
                            game->squares[pos] = archetype[2];
                            break;
                        case 'Q':
                            game->squares[pos] = archetype[1];
                            break;
                    }
                    break;
                case 'K':
                    game->pieces[WHITE][0] = pos;
                    game->squares[pos] = archetype[0];
                    break;

                default:
                    printf("Invalid FEN\n");
                    exit(3);
                    break;
            }
            pos += 1;
        }
        else if (curChar == '/') {
           
        }
        else if (isNumber(curChar)) {  
            pos += toNumber(curChar);
        }
    }

    FENPtr++;

    game->turn = (*FENPtr == 'w') ? WHITE : BLACK;

    FENPtr += 2;
    game->castling[BLACK][KINGSIDE] = 0;
    game->castling[BLACK][QUEENSIDE] = 0;
    game->castling[WHITE][KINGSIDE] = 0;
    game->castling[WHITE][QUEENSIDE] = 0;
    
    while(*FENPtr != ' ') {
        char curChar = (*FENPtr++);
        switch (curChar) {
            case 'k':
                game->castling[BLACK][KINGSIDE] = 1;
                break;
            case 'K':
                game->castling[WHITE][KINGSIDE] = 1;
                break;
            case 'q':
                game->castling[BLACK][QUEENSIDE] = 1;
                break;
            case 'Q':
                game->castling[WHITE][QUEENSIDE] = 1;
                break;
        }
    }
    FENPtr++;
    //printf("\n%c\n", *FENPtr);
    if(*FENPtr != '-') {
        char alg[2] = {(*FENPtr), (*++FENPtr)};
        game->en_passant = alg2int(alg);
    }
    else {
        game->en_passant = -1;
    }
}

void setupGameBoardDefault(GameBoard * game) {
    game->squares = (Piece **)calloc(64, sizeof(Piece *));
    game->to_play = WHITE;
    game->ply_100 = 0;
    game->turn = 0;
    game->en_passant = -1;
    game->castling[WHITE][KINGSIDE] = 1;
    game->castling[BLACK][KINGSIDE] = 1;
    game->castling[WHITE][QUEENSIDE] = 1;
    game->castling[BLACK][QUEENSIDE] = 1;
    

    Piece *archetype;
    game->pieces[WHITE][ROOK_Q_INDEX] = 56;
    SET_ARCHETYPE(5, getControlledSquares_Rook, 'R', WHITE, 56);
    game->pieces[WHITE][KNIGHT_Q_INDEX] = 57;
    SET_ARCHETYPE(3, getControlledSquares_Knight, 'N', WHITE, 57);
    game->pieces[WHITE][BISHOP_D_INDEX] = 58;
    SET_ARCHETYPE(3, getControlledSquares_Bishop, 'B', WHITE, 58);
    game->pieces[WHITE][QUEEN_INDEX] = 59;
    SET_ARCHETYPE(9, getControlledSquares_Queen, 'Q', WHITE, 59);
    game->pieces[WHITE][KING_INDEX] = 60;
    SET_ARCHETYPE(999, getControlledSquares_King, 'K', WHITE, 60);
    game->pieces[WHITE][BISHOP_L_INDEX] = 61;
    game->squares[61] = game->squares[58];
    game->pieces[WHITE][KNIGHT_K_INDEX] = 62;
    game->squares[62] = game->squares[57];
    game->pieces[WHITE][ROOK_K_INDEX] = 63;
    game->squares[63] = game->squares[56];
    game->pieces[WHITE][PAWN_A_INDEX] = 48;
    SET_ARCHETYPE(1, getControlledSquares_Pawn, 'P', WHITE, 48);
    game->pieces[WHITE][PAWN_B_INDEX] = 49;
    game->squares[49] = game->squares[48];
    game->pieces[WHITE][PAWN_C_INDEX] = 50;
    game->squares[50] = game->squares[48];
    game->pieces[WHITE][PAWN_D_INDEX] = 51;
    game->squares[51] = game->squares[48];
    game->pieces[WHITE][PAWN_E_INDEX] = 52;
    game->squares[52] = game->squares[48];
    game->pieces[WHITE][PAWN_F_INDEX] = 53;
    game->squares[53] = game->squares[48];
    game->pieces[WHITE][PAWN_G_INDEX] = 54;
    game->squares[54] = game->squares[48];
    game->pieces[WHITE][PAWN_H_INDEX] = 55;
    game->squares[55] = game->squares[48];
    

    game->pieces[BLACK][ROOK_Q_INDEX] = 0;
    SET_ARCHETYPE(5, getControlledSquares_Rook, 'r', BLACK, 0);
    game->pieces[BLACK][KNIGHT_Q_INDEX] = 1;
    SET_ARCHETYPE(3, getControlledSquares_Knight, 'n', BLACK, 1);
    game->pieces[BLACK][BISHOP_D_INDEX] = 2;
    SET_ARCHETYPE(3, getControlledSquares_Bishop, 'b', BLACK, 2);
    game->pieces[BLACK][QUEEN_INDEX] = 3;
    SET_ARCHETYPE(9, getControlledSquares_Queen, 'q', BLACK, 3);
    game->pieces[BLACK][KING_INDEX] = 4;
    SET_ARCHETYPE(999, getControlledSquares_King, 'k', BLACK, 4);
    game->pieces[BLACK][BISHOP_L_INDEX] = 5;
    game->squares[5] = game->squares[2];
    game->pieces[BLACK][KNIGHT_K_INDEX] = 6;
    game->squares[6] = game->squares[1];
    game->pieces[BLACK][ROOK_K_INDEX] = 7;
    game->squares[7] = game->squares[0];
    game->pieces[BLACK][PAWN_A_INDEX] = 8;
    SET_ARCHETYPE(1, getControlledSquares_Pawn, 'p', BLACK, 8);
    game->pieces[BLACK][PAWN_B_INDEX] = 9;
    game->squares[9] = game->squares[8];
    game->pieces[BLACK][PAWN_C_INDEX] = 10;
    game->squares[10] = game->squares[8];
    game->pieces[BLACK][PAWN_D_INDEX] = 11;
    game->squares[11] = game->squares[8];
    game->pieces[BLACK][PAWN_E_INDEX] = 12;
    game->squares[12] = game->squares[8];
    game->pieces[BLACK][PAWN_F_INDEX] = 13;
    game->squares[13] = game->squares[8];
    game->pieces[BLACK][PAWN_G_INDEX] = 14;
    game->squares[14] = game->squares[8];
    game->pieces[BLACK][PAWN_H_INDEX] = 15;
    game->squares[15] = game->squares[8];
}

void printGameBoard(GameBoard * game) {
    char toPrint; 
    printf("%s to play - Evaluation: %f", (game->turn == WHITE)? "White" : "Black", game->eval);
    /*
    printf("Castling Rights: ");
    if(game->castling[WHITE][KINGSIDE]) printf("K");
    if(game->castling[WHITE][QUEENSIDE]) printf("Q");
    if(game->castling[BLACK][KINGSIDE]) printf("k");
    if(game->castling[BLACK][QUEENSIDE]) printf("q");
    printf("\n");
    */
    for(char i=0; i<64; i++) {
        if(i%8 == 0) {
            printf("\n");
        }
        if(game->squares[i]) {
            printf("%c", game->squares[i]->name);
        }
        else {
            printf("-");
        }
    }
    printf("\n");
}

void printPlayerPieces(GameBoard *game, Color color) {
    for(int i=0; i<16; i++) {
        if(!NEGATIVE_INT(game->pieces[color][i])) {
            printf("%c, ", game->squares[game->pieces[color][i]]->name);
        }
    }
    printf("\n");
}