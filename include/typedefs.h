#ifndef TYPEDEFS_H
#define TYPEDEFS_H


typedef char * String;



typedef enum _pType {
    pawn = 'p',
    bishop = 'b',
    knight = 'n',
    rook = 'r',
    queen = 'q',
    king = 'k'
} pType;

typedef enum _Color {
    WHITE,
    BLACK
} Color;

typedef enum _Side {
    QUEENSIDE,
    KINGSIDE
} Side;




typedef struct _BST {
    void *data;
    struct _BST *left, *right;
} BST;

typedef struct _LL {
    void *data;
    float key;
    struct _LL *next, *prev;
} LL;




typedef struct _Player {
    LL *pieces;
    Color color;
} Player;

typedef struct _Piece {
    Player *player;
    LL * (*getControlledSquares)(void * game, int sSquare);
    float baseVal;
    pType name;
    void *square;
} Piece;

typedef struct _Square {
    Piece *piece;
    int pos;
    void *board;
} Square;

typedef struct _GameBoard {
    Square *squares;
    Player **players;
    Square *en_passant;
    Color turn;
    int castling[2][2];

    float eval;

} GameBoard;






#endif