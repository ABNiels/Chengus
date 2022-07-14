#ifndef ASCIIHELPER_H
#define ASCIIHELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "typedefs.h"

uint8_t isUpper(char);
uint8_t isLower(char);
char toLower(char);
uint8_t isNumber(char);
uint8_t toNumber(char c);
char toASCII(uint8_t val);
int alg2int(char *alg);
String int2alg(int pos);
#endif