#ifndef TYPEDEFS_H
#define TYPEDEFS_H


typedef char * String;

#define KING_INDEX 0
#define QUEEN_INDEX 1
#define ROOK_Q_INDEX 2
#define ROOK_K_INDEX 3
#define BISHOP_L_INDEX 4
#define BISHOP_D_INDEX 5
#define KNIGHT_Q_INDEX 6
#define KNIGHT_K_INDEX 7
#define PAWN_A_INDEX 8
#define PAWN_B_INDEX 9
#define PAWN_C_INDEX 10
#define PAWN_D_INDEX 11
#define PAWN_E_INDEX 12
#define PAWN_F_INDEX 13
#define PAWN_G_INDEX 14
#define PAWN_H_INDEX 15

#define NEGATIVE_INT(val) (val & 0x80000000)

typedef enum _moveType {
    CONTROL,
    MOVES_ONLY,
    CAPTURES_ONLY,
    MOVES_ALL
} pMoveType;

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





typedef struct _Piece {
    int (*getControlledSquares)(void *game, int sSquare, int *buffer);
    float baseVal;
    char name;
    Color color;
} Piece;

typedef struct _GameBoard {
    Piece **squares;
    int en_passant;
    int pieces[2][16];
    Color to_play;
    int castling[2][2];
    int turn;
    int ply_100;

    float eval;

} GameBoard;






#endif