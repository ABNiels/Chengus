#include <stdlib.h>
#include <stdio.h>

#include "boardLib.h"
#include "typedefs.h"
#include "asciiHelper.h"
#include "pieceLib.h"

#define ROOK_ARCHETYPE {    \
    piece->name = rook;     \
    piece->getControlledSquares = getControlledSquares_Rook; \
    piece->baseVal = 5;     \
    }
#define KNIGHT_ARCHETYPE {  \
    piece->name = knight;   \
    piece->getControlledSquares = getControlledSquares_Knight; \
    piece->baseVal = 3;     \
    }
#define BISHOP_ARCHETYPE {  \
    piece->name = bishop;   \
    piece->getControlledSquares = getControlledSquares_Bishop; \
    piece->baseVal = 3;     \
    }
#define QUEEN_ARCHETYPE {   \
    piece->name = queen;    \
    piece->getControlledSquares = getControlledSquares_Queen; \
    piece->baseVal = 9;     \
    }
#define KING_ARCHETYPE {    \
    piece->name = king;     \
    piece->getControlledSquares = getControlledSquares_King; \
    piece->baseVal = 999;   \
    }
#define PAWN_ARCHETYPE {    \
    piece->name = pawn;     \
    piece->getControlledSquares = getControlledSquares_Pawn; \
    piece->baseVal = 1;     \
    }

#define ADD_PIECE(archetype, space) {\
    piece = malloc(sizeof(Piece));  \
    archetype;                      \
    piece->player = player;         \
                                    \
    square = malloc(sizeof(Square));\
    square->board = game;           \
    square->piece = piece;          \
    square->pos = space;            \
                                    \
    piece->square = square;         \
    game->squares[space] = (*square);  \
                                    \
    list->data = piece;             \
    list->key = (float)space;              \
                                    \
    list->next = malloc(sizeof(LL));\
    list->next->prev = list;        \
    list = list->next;              \
    list->next = NULL;              \
    }


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



void setupGameBoardFEN(GameBoard * game, String FEN) {
    
    char *FENPtr = FEN;    
    game->squares = malloc(sizeof(Square)*64);
    game->players = malloc(sizeof(Player *)*2);
    Piece *piece;
    Square *square;

    Player *player = NULL;
    LL *list = NULL;

    game->players[WHITE] = malloc(sizeof(Player));
    game->players[WHITE]->color = WHITE;
    game->players[WHITE]->pieces = malloc(sizeof(LL)); 
    game->players[WHITE]->pieces->next = NULL;

    game->players[BLACK] = malloc(sizeof(Player));
    game->players[BLACK]->color = BLACK;
    game->players[BLACK]->pieces = malloc(sizeof(LL));
    game->players[BLACK]->pieces->next = NULL;

    int pos = 0;
    while (*FENPtr != ' ') {
        char curChar = (*FENPtr++);
        if (isUpper(curChar) || isLower(curChar)) {
            player = (isUpper(curChar)) ? game->players[WHITE] : game->players[BLACK];
            list = player->pieces;
            while (list->next) {
                list = list->next;
            }
            switch (toLower(curChar)) {
                case 'n': //Knight
                    ADD_PIECE(KNIGHT_ARCHETYPE, pos);
                    break;
                case 'b': //Bishop
                    ADD_PIECE(BISHOP_ARCHETYPE, pos);
                    break;
                case 'r': //Rook
                    ADD_PIECE(ROOK_ARCHETYPE, pos);
                    break;
                case 'q': //Queen
                    ADD_PIECE(QUEEN_ARCHETYPE, pos);
                    break;
                case 'p': //Pawn
                    ADD_PIECE(PAWN_ARCHETYPE, pos);
                    break;
                case 'k': //King
                    ADD_PIECE(KING_ARCHETYPE, pos);
                    list = list->prev;
                    list->next = player->pieces;
                    player->pieces->prev = list;
                    if(list->prev) {
                        list->prev->next = malloc(sizeof(LL));
                        list->prev->next->next = NULL;
                        list->prev->next->prev = list->prev;
                        list->prev = NULL;
                    }
                    player->pieces = list;
                    break;
                default:
                    break;
            }
            pos += 1;
        }
        else if (curChar == '/') {
           
        }
        else if (isNumber(curChar)) {    
            int max = pos+toNumber(curChar);
            for (; pos<max; pos++) {
                square = malloc(sizeof(Square));
                square->board = game;
                square->piece = NULL;

                game->squares[pos] = *square;
            }
        }
    }
    list = game->players[WHITE]->pieces;
    while (list->next) {
        list = list->next;
    }
    list->prev->next = NULL;
    list = game->players[BLACK]->pieces;
    while (list->next) {
        list = list->next;
    }
    list->prev->next = NULL;

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
        game->en_passant = &(game->squares[alg2int(alg)]);
    }
    else {
        game->en_passant = NULL;
    }
    
}


void setupGameBoardDefault(GameBoard * game) {
    game->squares = malloc(sizeof(Square)*64);
    game->turn = WHITE;
    game->en_passant = NULL;
    game->castling[WHITE][KINGSIDE] = 1;
    game->castling[BLACK][KINGSIDE] = 1;
    game->castling[WHITE][QUEENSIDE] = 1;
    game->castling[BLACK][QUEENSIDE] = 1;
    Piece *piece;
    Square *square;

    Player *player = malloc(sizeof(Player));
    LL *list = malloc(sizeof(LL));
    player->pieces = list;
    player->color = WHITE;
    game->players = malloc(sizeof(Player *)*2);
    game->players[WHITE] = player;
    player->color = WHITE;
    
    
    ADD_PIECE(KING_ARCHETYPE, 4);

    ADD_PIECE(ROOK_ARCHETYPE, 0);
    
    ADD_PIECE(KNIGHT_ARCHETYPE, 1);
    
    ADD_PIECE(BISHOP_ARCHETYPE, 2);
    
    ADD_PIECE(QUEEN_ARCHETYPE, 3);
    
    ADD_PIECE(BISHOP_ARCHETYPE, 5);
    
    ADD_PIECE(KNIGHT_ARCHETYPE, 6);
    
    ADD_PIECE(ROOK_ARCHETYPE, 7);
    
    ADD_PIECE(PAWN_ARCHETYPE, 8);
    
    ADD_PIECE(PAWN_ARCHETYPE, 9);
    
    ADD_PIECE(PAWN_ARCHETYPE, 10);
    
    ADD_PIECE(PAWN_ARCHETYPE, 11);
    
    ADD_PIECE(PAWN_ARCHETYPE, 12);
    
    ADD_PIECE(PAWN_ARCHETYPE, 13);
    
    ADD_PIECE(PAWN_ARCHETYPE, 14);
    
    ADD_PIECE(PAWN_ARCHETYPE, 15);
    
    list->prev->next = NULL;


    player = malloc(sizeof(Player));
    list = malloc(sizeof(LL));
    player->pieces = list;
    player->color = BLACK;
    game->players[BLACK] = player;
    
    
    ADD_PIECE(KING_ARCHETYPE, 60);

    ADD_PIECE(ROOK_ARCHETYPE, 56);
    
    ADD_PIECE(KNIGHT_ARCHETYPE, 57);
    
    ADD_PIECE(BISHOP_ARCHETYPE, 58);
    
    ADD_PIECE(QUEEN_ARCHETYPE, 59);
    
    
    ADD_PIECE(BISHOP_ARCHETYPE, 61);
    
    ADD_PIECE(KNIGHT_ARCHETYPE, 62);
    
    ADD_PIECE(ROOK_ARCHETYPE, 63);
    
    ADD_PIECE(PAWN_ARCHETYPE, 55);
    
    ADD_PIECE(PAWN_ARCHETYPE, 54);
    
    ADD_PIECE(PAWN_ARCHETYPE, 53);
    
    ADD_PIECE(PAWN_ARCHETYPE, 52);
    
    ADD_PIECE(PAWN_ARCHETYPE, 51);
    
    ADD_PIECE(PAWN_ARCHETYPE, 50);
    
    ADD_PIECE(PAWN_ARCHETYPE, 49);
    
    ADD_PIECE(PAWN_ARCHETYPE, 48);
    
    list->prev->next = NULL;
    
    for (char i=16; i<48; i++) {

        square = malloc(sizeof(Square));
        square->board = game;
        square->piece = NULL;

        game->squares[i] = *square;
    }
    
}

void printGameBoard(GameBoard * game) {
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
        if(game->squares[i].piece) {
            printf("%c", game->squares[i].piece->name);
        }
        else {
            printf("-");
        }
    }
    printf("\n");
}

void printPlayerPieces(Player * player) {
    LL * ptr = player->pieces;
    while(ptr) {
        if(ptr->key >= 0) {
            printf("%c, ", ((Piece *)ptr->data)->name);
        }
        ptr = ptr->next;
    }
    printf("\n");
}