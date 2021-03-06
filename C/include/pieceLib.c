#include "pieceLib.h"
#include "typedefs.h"
#include "asciiHelper.h"
#include <stdlib.h>
#include <stdio.h>
#include "boardLib.h"

static const int MOVES_RIGHT[][8] = {
    {1, 2, 3, 4, 5, 6, 7, -1},
    {2, 3, 4, 5, 6, 7, -1, -1},
    {3, 4, 5, 6, 7, -1, -1, -1},
    {4, 5, 6, 7, -1, -1, -1, -1},
    {5, 6, 7, -1, -1, -1, -1, -1},
    {6, 7, -1, -1, -1, -1, -1, -1},
    {7, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {9, 10, 11, 12, 13, 14, 15, -1},
    {10, 11, 12, 13, 14, 15, -1, -1},
    {11, 12, 13, 14, 15, -1, -1, -1},
    {12, 13, 14, 15, -1, -1, -1, -1},
    {13, 14, 15, -1, -1, -1, -1, -1},
    {14, 15, -1, -1, -1, -1, -1, -1},
    {15, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {17, 18, 19, 20, 21, 22, 23, -1},
    {18, 19, 20, 21, 22, 23, -1, -1},
    {19, 20, 21, 22, 23, -1, -1, -1},
    {20, 21, 22, 23, -1, -1, -1, -1},
    {21, 22, 23, -1, -1, -1, -1, -1},
    {22, 23, -1, -1, -1, -1, -1, -1},
    {23, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {25, 26, 27, 28, 29, 30, 31, -1},
    {26, 27, 28, 29, 30, 31, -1, -1},
    {27, 28, 29, 30, 31, -1, -1, -1},
    {28, 29, 30, 31, -1, -1, -1, -1},
    {29, 30, 31, -1, -1, -1, -1, -1},
    {30, 31, -1, -1, -1, -1, -1, -1},
    {31, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {33, 34, 35, 36, 37, 38, 39, -1},
    {34, 35, 36, 37, 38, 39, -1, -1},
    {35, 36, 37, 38, 39, -1, -1, -1},
    {36, 37, 38, 39, -1, -1, -1, -1},
    {37, 38, 39, -1, -1, -1, -1, -1},
    {38, 39, -1, -1, -1, -1, -1, -1},
    {39, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {41, 42, 43, 44, 45, 46, 47, -1},
    {42, 43, 44, 45, 46, 47, -1, -1},
    {43, 44, 45, 46, 47, -1, -1, -1},
    {44, 45, 46, 47, -1, -1, -1, -1},
    {45, 46, 47, -1, -1, -1, -1, -1},
    {46, 47, -1, -1, -1, -1, -1, -1},
    {47, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {49, 50, 51, 52, 53, 54, 55, -1},
    {50, 51, 52, 53, 54, 55, -1, -1},
    {51, 52, 53, 54, 55, -1, -1, -1},
    {52, 53, 54, 55, -1, -1, -1, -1},
    {53, 54, 55, -1, -1, -1, -1, -1},
    {54, 55, -1, -1, -1, -1, -1, -1},
    {55, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {57, 58, 59, 60, 61, 62, 63, -1},
    {58, 59, 60, 61, 62, 63, -1, -1},
    {59, 60, 61, 62, 63, -1, -1, -1},
    {60, 61, 62, 63, -1, -1, -1, -1},
    {61, 62, 63, -1, -1, -1, -1, -1},
    {62, 63, -1, -1, -1, -1, -1, -1},
    {63, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
};

static const int MOVES_LEFT[][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {0, -1, -1, -1, -1, -1, -1, -1},
    {1, 0, -1, -1, -1, -1, -1, -1},
    {2, 1, 0, -1, -1, -1, -1, -1},
    {3, 2, 1, 0, -1, -1, -1, -1},
    {4, 3, 2, 1, 0, -1, -1, -1},
    {5, 4, 3, 2, 1, 0, -1, -1},
    {6, 5, 4, 3, 2, 1, 0, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {8, -1, -1, -1, -1, -1, -1, -1},
    {9, 8, -1, -1, -1, -1, -1, -1},
    {10, 9, 8, -1, -1, -1, -1, -1},
    {11, 10, 9, 8, -1, -1, -1, -1},
    {12, 11, 10, 9, 8, -1, -1, -1},
    {13, 12, 11, 10, 9, 8, -1, -1},
    {14, 13, 12, 11, 10, 9, 8, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {16, -1, -1, -1, -1, -1, -1, -1},
    {17, 16, -1, -1, -1, -1, -1, -1},
    {18, 17, 16, -1, -1, -1, -1, -1},
    {19, 18, 17, 16, -1, -1, -1, -1},
    {20, 19, 18, 17, 16, -1, -1, -1},
    {21, 20, 19, 18, 17, 16, -1, -1},
    {22, 21, 20, 19, 18, 17, 16, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {24, -1, -1, -1, -1, -1, -1, -1},
    {25, 24, -1, -1, -1, -1, -1, -1},
    {26, 25, 24, -1, -1, -1, -1, -1},
    {27, 26, 25, 24, -1, -1, -1, -1},
    {28, 27, 26, 25, 24, -1, -1, -1},
    {29, 28, 27, 26, 25, 24, -1, -1},
    {30, 29, 28, 27, 26, 25, 24, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {32, -1, -1, -1, -1, -1, -1, -1},
    {33, 32, -1, -1, -1, -1, -1, -1},
    {34, 33, 32, -1, -1, -1, -1, -1},
    {35, 34, 33, 32, -1, -1, -1, -1},
    {36, 35, 34, 33, 32, -1, -1, -1},
    {37, 36, 35, 34, 33, 32, -1, -1},
    {38, 37, 36, 35, 34, 33, 32, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {40, -1, -1, -1, -1, -1, -1, -1},
    {41, 40, -1, -1, -1, -1, -1, -1},
    {42, 41, 40, -1, -1, -1, -1, -1},
    {43, 42, 41, 40, -1, -1, -1, -1},
    {44, 43, 42, 41, 40, -1, -1, -1},
    {45, 44, 43, 42, 41, 40, -1, -1},
    {46, 45, 44, 43, 42, 41, 40, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {48, -1, -1, -1, -1, -1, -1, -1},
    {49, 48, -1, -1, -1, -1, -1, -1},
    {50, 49, 48, -1, -1, -1, -1, -1},
    {51, 50, 49, 48, -1, -1, -1, -1},
    {52, 51, 50, 49, 48, -1, -1, -1},
    {53, 52, 51, 50, 49, 48, -1, -1},
    {54, 53, 52, 51, 50, 49, 48, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {56, -1, -1, -1, -1, -1, -1, -1},
    {57, 56, -1, -1, -1, -1, -1, -1},
    {58, 57, 56, -1, -1, -1, -1, -1},
    {59, 58, 57, 56, -1, -1, -1, -1},
    {60, 59, 58, 57, 56, -1, -1, -1},
    {61, 60, 59, 58, 57, 56, -1, -1},
    {62, 61, 60, 59, 58, 57, 56, -1},
};

const static int MOVES_UP[][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {0, -1, -1, -1, -1, -1, -1, -1},
    {1, -1, -1, -1, -1, -1, -1, -1},
    {2, -1, -1, -1, -1, -1, -1, -1},
    {3, -1, -1, -1, -1, -1, -1, -1},
    {4, -1, -1, -1, -1, -1, -1, -1},
    {5, -1, -1, -1, -1, -1, -1, -1},
    {6, -1, -1, -1, -1, -1, -1, -1},
    {7, -1, -1, -1, -1, -1, -1, -1},

    {8, 0, -1, -1, -1, -1, -1, -1},
    {9, 1, -1, -1, -1, -1, -1, -1},
    {10, 2, -1, -1, -1, -1, -1, -1},
    {11, 3, -1, -1, -1, -1, -1, -1},
    {12, 4, -1, -1, -1, -1, -1, -1},
    {13, 5, -1, -1, -1, -1, -1, -1},
    {14, 6, -1, -1, -1, -1, -1, -1},
    {15, 7, -1, -1, -1, -1, -1, -1},

    {16, 8, 0, -1, -1, -1, -1, -1},
    {17, 9, 1, -1, -1, -1, -1, -1},
    {18, 10, 2, -1, -1, -1, -1, -1},
    {19, 11, 3, -1, -1, -1, -1, -1},
    {20, 12, 4, -1, -1, -1, -1, -1},
    {21, 13, 5, -1, -1, -1, -1, -1},
    {22, 14, 6, -1, -1, -1, -1, -1},
    {23, 15, 7, -1, -1, -1, -1, -1},

    {24, 16, 8, 0, -1, -1, -1, -1},
    {25, 17, 9, 1, -1, -1, -1, -1},
    {26, 18, 10, 2, -1, -1, -1, -1},
    {27, 19, 11, 3, -1, -1, -1, -1},
    {28, 20, 12, 4, -1, -1, -1, -1},
    {29, 21, 13, 5, -1, -1, -1, -1},
    {30, 22, 14, 6, -1, -1, -1, -1},
    {31, 23, 15, 7, -1, -1, -1, -1},

    {32, 24, 16, 8, 0, -1, -1, -1},
    {33, 25, 17, 9, 1, -1, -1, -1},
    {34, 26, 18, 10, 2, -1, -1, -1},
    {35, 27, 19, 11, 3, -1, -1, -1},
    {36, 28, 20, 12, 4, -1, -1, -1},
    {37, 29, 21, 13, 5, -1, -1, -1},
    {38, 30, 22, 14, 6, -1, -1, -1},
    {39, 31, 23, 15, 7, -1, -1, -1},

    {40, 32, 24, 16, 8, 0, -1, -1},
    {41, 33, 25, 17, 9, 1, -1, -1},
    {42, 34, 26, 18, 10, 2, -1, -1},
    {43, 35, 27, 19, 11, 3, -1, -1},
    {44, 36, 28, 20, 12, 4, -1, -1},
    {45, 37, 29, 21, 13, 5, -1, -1},
    {46, 38, 30, 22, 14, 6, -1, -1},
    {47, 39, 31, 23, 15, 7, -1, -1},

    {48, 40, 32, 24, 16, 8, 0, -1},
    {49, 41, 33, 25, 17, 9, 1, -1},
    {50, 42, 34, 26, 18, 10, 2, -1},
    {51, 43, 35, 27, 19, 11, 3, -1},
    {52, 44, 36, 28, 20, 12, 4, -1},
    {53, 45, 37, 29, 21, 13, 5, -1},
    {54, 46, 38, 30, 22, 14, 6, -1},
    {55, 47, 39, 31, 23, 15, 7, -1},

};

static const int MOVES_DOWN[][8] = {
    {8, 16, 24, 32, 40, 48, 56, -1},
    {9, 17, 25, 33, 41, 49, 57, -1},
    {10, 18, 26, 34, 42, 50, 58, -1},
    {11, 19, 27, 35, 43, 51, 59, -1},
    {12, 20, 28, 36, 44, 52, 60, -1},
    {13, 21, 29, 37, 45, 53, 61, -1},
    {14, 22, 30, 38, 46, 54, 62, -1},
    {15, 23, 31, 39, 47, 55, 63, -1},

    {16, 24, 32, 40, 48, 56, -1, -1},
    {17, 25, 33, 41, 49, 57, -1, -1},
    {18, 26, 34, 42, 50, 58, -1, -1},
    {19, 27, 35, 43, 51, 59, -1, -1},
    {20, 28, 36, 44, 52, 60, -1, -1},
    {21, 29, 37, 45, 53, 61, -1, -1},
    {22, 30, 38, 46, 54, 62, -1, -1},
    {23, 31, 39, 47, 55, 63, -1, -1},

    {24, 32, 40, 48, 56, -1, -1, -1},
    {25, 33, 41, 49, 57, -1, -1, -1},
    {26, 34, 42, 50, 58, -1, -1, -1},
    {27, 35, 43, 51, 59, -1, -1, -1},
    {28, 36, 44, 52, 60, -1, -1, -1},
    {29, 37, 45, 53, 61, -1, -1, -1},
    {30, 38, 46, 54, 62, -1, -1, -1},
    {31, 39, 47, 55, 63, -1, -1, -1},

    {32, 40, 48, 56, -1, -1, -1, -1},
    {33, 41, 49, 57, -1, -1, -1, -1},
    {34, 42, 50, 58, -1, -1, -1, -1},
    {35, 43, 51, 59, -1, -1, -1, -1},
    {36, 44, 52, 60, -1, -1, -1, -1},
    {37, 45, 53, 61, -1, -1, -1, -1},
    {38, 46, 54, 62, -1, -1, -1, -1},
    {39, 47, 55, 63, -1, -1, -1, -1},

    {40, 48, 56, -1, -1, -1, -1, -1},
    {41, 49, 57, -1, -1, -1, -1, -1},
    {42, 50, 58, -1, -1, -1, -1, -1},
    {43, 51, 59, -1, -1, -1, -1, -1},
    {44, 52, 60, -1, -1, -1, -1, -1},
    {45, 53, 61, -1, -1, -1, -1, -1},
    {46, 54, 62, -1, -1, -1, -1, -1},
    {47, 55, 63, -1, -1, -1, -1, -1},

    {48, 56, -1, -1, -1, -1, -1, -1},
    {49, 57, -1, -1, -1, -1, -1, -1},
    {50, 58, -1, -1, -1, -1, -1, -1},
    {51, 59, -1, -1, -1, -1, -1, -1},
    {52, 60, -1, -1, -1, -1, -1, -1},
    {53, 61, -1, -1, -1, -1, -1, -1},
    {54, 62, -1, -1, -1, -1, -1, -1},
    {55, 63, -1, -1, -1, -1, -1, -1},

    {56, -1, -1, -1, -1, -1, -1, -1},
    {57, -1, -1, -1, -1, -1, -1, -1},
    {58, -1, -1, -1, -1, -1, -1, -1},
    {59, -1, -1, -1, -1, -1, -1, -1},
    {60, -1, -1, -1, -1, -1, -1, -1},
    {61, -1, -1, -1, -1, -1, -1, -1},
    {62, -1, -1, -1, -1, -1, -1, -1},
    {63, -1, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
};

static const int MOVES_UP_RIGHT[][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {1, -1, -1, -1, -1, -1, -1, -1},
    {2, -1, -1, -1, -1, -1, -1, -1},
    {3, -1, -1, -1, -1, -1, -1, -1},
    {4, -1, -1, -1, -1, -1, -1, -1},
    {5, -1, -1, -1, -1, -1, -1, -1},
    {6, -1, -1, -1, -1, -1, -1, -1},
    {7, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {9, 2, -1, -1, -1, -1, -1, -1},
    {10, 3, -1, -1, -1, -1, -1, -1},
    {11, 4, -1, -1, -1, -1, -1, -1},
    {12, 5, -1, -1, -1, -1, -1, -1},
    {13, 6, -1, -1, -1, -1, -1, -1},
    {14, 7, -1, -1, -1, -1, -1, -1},
    {15, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {17, 10, 3, -1, -1, -1, -1, -1},
    {18, 11, 4, -1, -1, -1, -1, -1},
    {19, 12, 5, -1, -1, -1, -1, -1},
    {20, 13, 6, -1, -1, -1, -1, -1},
    {21, 14, 7, -1, -1, -1, -1, -1},
    {22, 15, -1, -1, -1, -1, -1, -1},
    {23, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {25, 18, 11, 4, -1, -1, -1, -1},
    {26, 19, 12, 5, -1, -1, -1, -1},
    {27, 20, 13, 6, -1, -1, -1, -1},
    {28, 21, 14, 7, -1, -1, -1, -1},
    {29, 22, 15, -1, -1, -1, -1, -1},
    {30, 23, -1, -1, -1, -1, -1, -1},
    {31, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {33, 26, 19, 12, 5, -1, -1, -1},
    {34, 27, 20, 13, 6, -1, -1, -1},
    {35, 28, 21, 14, 7, -1, -1, -1},
    {36, 29, 22, 15, -1, -1, -1, -1},
    {37, 30, 23, -1, -1, -1, -1, -1},
    {38, 31, -1, -1, -1, -1, -1, -1},
    {39, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {41, 34, 27, 20, 13, 6, -1, -1},
    {42, 35, 28, 21, 14, 7, -1, -1},
    {43, 36, 29, 22, 15, -1, -1, -1},
    {44, 37, 30, 23, -1, -1, -1, -1},
    {45, 38, 31, -1, -1, -1, -1, -1},
    {46, 39, -1, -1, -1, -1, -1, -1},
    {47, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {49, 42, 35, 28, 21, 14, 7, -1},
    {50, 43, 36, 29, 22, 15, -1, -1},
    {51, 44, 37, 30, 23, -1, -1, -1},
    {52, 45, 38, 31, -1, -1, -1, -1},
    {53, 46, 39, -1, -1, -1, -1, -1},
    {54, 47, -1, -1, -1, -1, -1, -1},
    {55, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

};

static const int MOVES_UP_LEFT[][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {0, -1, -1, -1, -1, -1, -1, -1},
    {1, -1, -1, -1, -1, -1, -1, -1},
    {2, -1, -1, -1, -1, -1, -1, -1},
    {3, -1, -1, -1, -1, -1, -1, -1},
    {4, -1, -1, -1, -1, -1, -1, -1},
    {5, -1, -1, -1, -1, -1, -1, -1},
    {6, -1, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {8, -1, -1, -1, -1, -1, -1, -1},
    {9, 0, -1, -1, -1, -1, -1, -1},
    {10, 1, -1, -1, -1, -1, -1, -1},
    {11, 2, -1, -1, -1, -1, -1, -1},
    {12, 3, -1, -1, -1, -1, -1, -1},
    {13, 4, -1, -1, -1, -1, -1, -1},
    {14, 5, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {16, -1, -1, -1, -1, -1, -1, -1},
    {17, 8, -1, -1, -1, -1, -1, -1},
    {18, 9, 0, -1, -1, -1, -1, -1},
    {19, 10, 1, -1, -1, -1, -1, -1},
    {20, 11, 2, -1, -1, -1, -1, -1},
    {21, 12, 3, -1, -1, -1, -1, -1},
    {22, 13, 4, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {24, -1, -1, -1, -1, -1, -1, -1},
    {25, 16, -1, -1, -1, -1, -1, -1},
    {26, 17, 8, -1, -1, -1, -1, -1},
    {27, 18, 9, 0, -1, -1, -1, -1},
    {28, 19, 10, 1, -1, -1, -1, -1},
    {29, 20, 11, 2, -1, -1, -1, -1},
    {30, 21, 12, 3, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {32, -1, -1, -1, -1, -1, -1, -1},
    {33, 24, -1, -1, -1, -1, -1, -1},
    {34, 25, 16, -1, -1, -1, -1, -1},
    {35, 26, 17, 8, -1, -1, -1, -1},
    {36, 27, 18, 9, 0, -1, -1, -1},
    {37, 28, 19, 10, 1, -1, -1, -1},
    {38, 29, 20, 11, 2, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {40, -1, -1, -1, -1, -1, -1, -1},
    {41, 32, -1, -1, -1, -1, -1, -1},
    {42, 33, 24, -1, -1, -1, -1, -1},
    {43, 34, 25, 16, -1, -1, -1, -1},
    {44, 35, 26, 17, 8, -1, -1, -1},
    {45, 36, 27, 18, 9, 0, -1, -1},
    {46, 37, 28, 19, 10, 1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {48, -1, -1, -1, -1, -1, -1, -1},
    {49, 40, -1, -1, -1, -1, -1, -1},
    {50, 41, 32, -1, -1, -1, -1, -1},
    {51, 42, 33, 24, -1, -1, -1, -1},
    {52, 43, 34, 25, 16, -1, -1, -1},
    {53, 44, 35, 26, 17, 8, -1, -1},
    {54, 45, 36, 27, 18, 9, 0, -1},

};

static const int MOVES_DOWN_RIGHT[][8] = {
    {9, 18, 27, 36, 45, 54, 63, -1},
    {10, 19, 28, 37, 46, 55, -1, -1},
    {11, 20, 29, 38, 47, -1, -1, -1},
    {12, 21, 30, 39, -1, -1, -1, -1},
    {13, 22, 31, -1, -1, -1, -1, -1},
    {14, 23, -1, -1, -1, -1, -1, -1},
    {15, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {17, 26, 35, 44, 53, 62, -1, -1},
    {18, 27, 36, 45, 54, 63, -1, -1},
    {19, 28, 37, 46, 55, -1, -1, -1},
    {20, 29, 38, 47, -1, -1, -1, -1},
    {21, 30, 39, -1, -1, -1, -1, -1},
    {22, 31, -1, -1, -1, -1, -1, -1},
    {23, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {25, 34, 43, 52, 61, -1, -1, -1},
    {26, 35, 44, 53, 62, -1, -1, -1},
    {27, 36, 45, 54, 63, -1, -1, -1},
    {28, 37, 46, 55, -1, -1, -1, -1},
    {29, 38, 47, -1, -1, -1, -1, -1},
    {30, 39, -1, -1, -1, -1, -1, -1},
    {31, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {33, 42, 51, 60, -1, -1, -1, -1},
    {34, 43, 52, 61, -1, -1, -1, -1},
    {35, 44, 53, 62, -1, -1, -1, -1},
    {36, 45, 54, 63, -1, -1, -1, -1},
    {37, 46, 55, -1, -1, -1, -1, -1},
    {38, 47, -1, -1, -1, -1, -1, -1},
    {39, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {41, 50, 59, -1, -1, -1, -1, -1},
    {42, 51, 60, -1, -1, -1, -1, -1},
    {43, 52, 61, -1, -1, -1, -1, -1},
    {44, 53, 62, -1, -1, -1, -1, -1},
    {45, 54, 63, -1, -1, -1, -1, -1},
    {46, 55, -1, -1, -1, -1, -1, -1},
    {47, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {49, 58, -1, -1, -1, -1, -1, -1},
    {50, 59, -1, -1, -1, -1, -1, -1},
    {51, 60, -1, -1, -1, -1, -1, -1},
    {52, 61, -1, -1, -1, -1, -1, -1},
    {53, 62, -1, -1, -1, -1, -1, -1},
    {54, 63, -1, -1, -1, -1, -1, -1},
    {55, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {57, -1, -1, -1, -1, -1, -1, -1},
    {58, -1, -1, -1, -1, -1, -1, -1},
    {59, -1, -1, -1, -1, -1, -1, -1},
    {60, -1, -1, -1, -1, -1, -1, -1},
    {61, -1, -1, -1, -1, -1, -1, -1},
    {62, -1, -1, -1, -1, -1, -1, -1},
    {63, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

};

static const int MOVES_DOWN_LEFT[][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {8, -1, -1, -1, -1, -1, -1, -1},
    {9, 16, -1, -1, -1, -1, -1, -1},
    {10, 17, 24, -1, -1, -1, -1, -1},
    {11, 18, 25, 32, -1, -1, -1, -1},
    {12, 19, 26, 33, 40, -1, -1, -1},
    {13, 20, 27, 34, 41, 48, -1, -1},
    {14, 21, 28, 35, 42, 49, 56, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {16, -1, -1, -1, -1, -1, -1, -1},
    {17, 24, -1, -1, -1, -1, -1, -1},
    {18, 25, 32, -1, -1, -1, -1, -1},
    {19, 26, 33, 40, -1, -1, -1, -1},
    {20, 27, 34, 41, 48, -1, -1, -1},
    {21, 28, 35, 42, 49, 56, -1, -1},
    {22, 29, 36, 43, 50, 57, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {24, -1, -1, -1, -1, -1, -1, -1},
    {25, 32, -1, -1, -1, -1, -1, -1},
    {26, 33, 40, -1, -1, -1, -1, -1},
    {27, 34, 41, 48, -1, -1, -1, -1},
    {28, 35, 42, 49, 56, -1, -1, -1},
    {29, 36, 43, 50, 57, -1, -1, -1},
    {30, 37, 44, 51, 58, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {32, -1, -1, -1, -1, -1, -1, -1},
    {33, 40, -1, -1, -1, -1, -1, -1},
    {34, 41, 48, -1, -1, -1, -1, -1},
    {35, 42, 49, 56, -1, -1, -1, -1},
    {36, 43, 50, 57, -1, -1, -1, -1},
    {37, 44, 51, 58, -1, -1, -1, -1},
    {38, 45, 52, 59, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {40, -1, -1, -1, -1, -1, -1, -1},
    {41, 48, -1, -1, -1, -1, -1, -1},
    {42, 49, 56, -1, -1, -1, -1, -1},
    {43, 50, 57, -1, -1, -1, -1, -1},
    {44, 51, 58, -1, -1, -1, -1, -1},
    {45, 52, 59, -1, -1, -1, -1, -1},
    {46, 53, 60, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {48, -1, -1, -1, -1, -1, -1, -1},
    {49, 56, -1, -1, -1, -1, -1, -1},
    {50, 57, -1, -1, -1, -1, -1, -1},
    {51, 58, -1, -1, -1, -1, -1, -1},
    {52, 59, -1, -1, -1, -1, -1, -1},
    {53, 60, -1, -1, -1, -1, -1, -1},
    {54, 61, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {56, -1, -1, -1, -1, -1, -1, -1},
    {57, -1, -1, -1, -1, -1, -1, -1},
    {58, -1, -1, -1, -1, -1, -1, -1},
    {59, -1, -1, -1, -1, -1, -1, -1},
    {60, -1, -1, -1, -1, -1, -1, -1},
    {61, -1, -1, -1, -1, -1, -1, -1},
    {62, -1, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},

};

const static int MOVES_KNIGHT[][8] = {
    {10, 17, -1, -1, -1, -1, -1, -1},
    {11, 16, 18, -1, -1, -1, -1, -1},
    {8, 12, 17, 19, -1, -1, -1, -1},
    {9, 13, 18, 20, -1, -1, -1, -1},
    {10, 14, 19, 21, -1, -1, -1, -1},
    {11, 15, 20, 22, -1, -1, -1, -1},
    {12, 21, 23, -1, -1, -1, -1, -1},
    {13, 22, -1, -1, -1, -1, -1, -1},
    {2, 18, 25, -1, -1, -1, -1, -1},
    {3, 19, 24, 26, -1, -1, -1, -1},
    {0, 4, 16, 20, 25, 27, -1, -1},
    {1, 5, 17, 21, 26, 28, -1, -1},
    {2, 6, 18, 22, 27, 29, -1, -1},
    {3, 7, 19, 23, 28, 30, -1, -1},
    {4, 20, 29, 31, -1, -1, -1, -1},
    {5, 21, 30, -1, -1, -1, -1, -1},
    {1, 10, 26, 33, -1, -1, -1, -1},
    {0, 2, 11, 27, 32, 34, -1, -1},
    {1, 3, 8, 12, 24, 28, 33, 35},
    {2, 4, 9, 13, 25, 29, 34, 36},
    {3, 5, 10, 14, 26, 30, 35, 37},
    {4, 6, 11, 15, 27, 31, 36, 38},
    {5, 7, 12, 28, 37, 39, -1, -1},
    {6, 13, 29, 38, -1, -1, -1, -1},
    {9, 18, 34, 41, -1, -1, -1, -1},
    {8, 10, 19, 35, 40, 42, -1, -1},
    {9, 11, 16, 20, 32, 36, 41, 43},
    {10, 12, 17, 21, 33, 37, 42, 44},
    {11, 13, 18, 22, 34, 38, 43, 45},
    {12, 14, 19, 23, 35, 39, 44, 46},
    {13, 15, 20, 36, 45, 47, -1, -1},
    {14, 21, 37, 46, -1, -1, -1, -1},
    {17, 26, 42, 49, -1, -1, -1, -1},
    {16, 18, 27, 43, 48, 50, -1, -1},
    {17, 19, 24, 28, 40, 44, 49, 51},
    {18, 20, 25, 29, 41, 45, 50, 52},
    {19, 21, 26, 30, 42, 46, 51, 53},
    {20, 22, 27, 31, 43, 47, 52, 54},
    {21, 23, 28, 44, 53, 55, -1, -1},
    {22, 29, 45, 54, -1, -1, -1, -1},
    {25, 34, 50, 57, -1, -1, -1, -1},
    {24, 26, 35, 51, 56, 58, -1, -1},
    {25, 27, 32, 36, 48, 52, 57, 59},
    {26, 28, 33, 37, 49, 53, 58, 60},
    {27, 29, 34, 38, 50, 54, 59, 61},
    {28, 30, 35, 39, 51, 55, 60, 62},
    {29, 31, 36, 52, 61, 63, -1, -1},
    {30, 37, 53, 62, -1, -1, -1, -1},
    {33, 42, 58, -1, -1, -1, -1, -1},
    {32, 34, 43, 59, -1, -1, -1, -1},
    {33, 35, 40, 44, 56, 60, -1, -1},
    {34, 36, 41, 45, 57, 61, -1, -1},
    {35, 37, 42, 46, 58, 62, -1, -1},
    {36, 38, 43, 47, 59, 63, -1, -1},
    {37, 39, 44, 60, -1, -1, -1, -1},
    {38, 45, 61, -1, -1, -1, -1, -1},
    {41, 50, -1, -1, -1, -1, -1, -1},
    {40, 42, 51, -1, -1, -1, -1, -1},
    {41, 43, 48, 52, -1, -1, -1, -1},
    {42, 44, 49, 53, -1, -1, -1, -1},
    {43, 45, 50, 54, -1, -1, -1, -1},
    {44, 46, 51, 55, -1, -1, -1, -1},
    {45, 47, 52, -1, -1, -1, -1, -1},
    {46, 53, -1, -1, -1, -1, -1, -1},

};


#define GET_SQUARES(MOVE_ARRAY) ({              \
    for(moveIndex=0; moveIndex<8; ++moveIndex, ++bufferIndex) {                        \
        temp = MOVE_ARRAY[square][moveIndex];   \
        if(NEGATIVE_INT(temp)) break;           \
        buffer[bufferIndex] = temp;             \
        if(game->squares[temp]) { ++bufferIndex; break; }  \
    }                                           \
})

int getControlledSquares_Pawn(void *gamePtr, int square, int *buffer)
{
    
    GameBoard *game = (GameBoard *)gamePtr;
    Color color = game->squares[square]->color;
    int curSquare;
    register int index = 0;

    if(color) { //black
        buffer[index] = MOVES_DOWN_LEFT[square][0];
        index += (NEGATIVE_INT(buffer[index]))? 0:1;
        buffer[index] = MOVES_DOWN_RIGHT[square][0];
    }
    else {
        buffer[index] = MOVES_UP_LEFT[square][0];
        index += (NEGATIVE_INT(buffer[index]))? 0:1;
        buffer[index] = MOVES_UP_RIGHT[square][0];
    }

    return 1;
}

int getControlledSquares_Rook(void *gamePtr, int square, int *buffer)
{
    //printf("Square %i\n", square);
    GameBoard *game = (GameBoard *)gamePtr;
    Color color = game->squares[square]->color;
    int curSquare;
    register int moveIndex, bufferIndex = 0, temp = 0;
    
    GET_SQUARES(MOVES_LEFT);
    GET_SQUARES(MOVES_RIGHT);
    GET_SQUARES(MOVES_UP);
    GET_SQUARES(MOVES_DOWN);
    

    return 1;
}

int getControlledSquares_Bishop(void *gamePtr, int square, int *buffer)
{
    
    GameBoard *game = (GameBoard *)gamePtr;
    Color color = game->squares[square]->color;
    int curSquare;
    register int moveIndex, bufferIndex = 0, temp = 0;
    
    GET_SQUARES(MOVES_UP_LEFT);
    GET_SQUARES(MOVES_DOWN_RIGHT);
    GET_SQUARES(MOVES_UP_RIGHT);
    GET_SQUARES(MOVES_DOWN_LEFT);
    

    return 1;
}

int getControlledSquares_Knight(void *gamePtr, int square, int *buffer)
{
    
    GameBoard *game = (GameBoard *)gamePtr;
    Color color = game->squares[square]->color;
    int curSquare;
    register int moveIndex, bufferIndex = 0, temp = 0;
    
    GET_SQUARES(MOVES_KNIGHT);

    
    return 1;
}

int getControlledSquares_King(void *gamePtr, int square, int *buffer)
{
    
    GameBoard *game = (GameBoard *)gamePtr;
    Color color = game->squares[square]->color;
    int curSquare;
    register int index = 0;

    buffer[index] = MOVES_DOWN_LEFT[square][0];
    index += (NEGATIVE_INT(buffer[index]))? 0:1;

    buffer[index] = MOVES_DOWN_RIGHT[square][0];
    index += (NEGATIVE_INT(buffer[index]))? 0:1;

    buffer[index] = MOVES_UP_RIGHT[square][0];
    index += (NEGATIVE_INT(buffer[index]))? 0:1;

    buffer[index] = MOVES_UP_LEFT[square][0];
    index += (NEGATIVE_INT(buffer[index]))? 0:1;

    buffer[index] = MOVES_DOWN[square][0];
    index += (NEGATIVE_INT(buffer[index]))? 0:1;

    buffer[index] = MOVES_UP[square][0];
    index += (NEGATIVE_INT(buffer[index]))? 0:1;

    buffer[index] = MOVES_RIGHT[square][0];
    index += (NEGATIVE_INT(buffer[index]))? 0:1;

    buffer[index] = MOVES_LEFT[square][0];

    
    return 1;
}

int getControlledSquares_Queen(void *gamePtr, int square, int *buffer)
{
    
    GameBoard *game = (GameBoard *)gamePtr;
    Color color = game->squares[square]->color;
    int curSquare;
    register int moveIndex, bufferIndex = 0, temp = 0;

    GET_SQUARES(MOVES_LEFT);
    GET_SQUARES(MOVES_RIGHT);
    GET_SQUARES(MOVES_UP);
    GET_SQUARES(MOVES_DOWN);
    GET_SQUARES(MOVES_UP_LEFT);
    GET_SQUARES(MOVES_DOWN_RIGHT);
    GET_SQUARES(MOVES_UP_RIGHT);
    GET_SQUARES(MOVES_DOWN_LEFT);
    

    return 1;
}