#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "typedefs.h"
#include "asciiHelper.h"

/* ---------------------------------------------------*/
/* ------------------ Aux Functions ------------------*/
/* ---------------------------------------------------*/
uint8_t isUpper(char c) {
    return ((c >= 0x41) && (c <= 0x5A));
}

uint8_t isLower(char c) {
    return ((c >= 0x61) && (c <= 0x7A));
}

char toLower(char c) {
    return isUpper(c) ? c + 0x20 : isLower(c) ? c : c + 0x61;
}

char toUpper(char c) {
    return isLower(c) ? c - 0x20 : isUpper(c) ? c : c + 0x61;
}

uint8_t isNumber(char c) {
    return ((c >= 0x30) && (c <= 0x39));
}
uint8_t toNumber(char c) {
    return c - 0x30;
}

char toASCII(uint8_t val) {
    return val + 0x30;
}
/* ---------------------------------------------------*/


int alg2int(char *alg) {
    return 8*(8-(alg[1]-'0'))+(alg[0]-'a');
}

String int2alg(int pos) {
    String alg = malloc(sizeof(char)*3);
    alg[0] = (pos % 8)+'a';
    alg[1] = (8-(pos / 8))+'0';
    alg[2] = '\0';
    return alg;
}
