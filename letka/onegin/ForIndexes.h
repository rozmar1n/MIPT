#ifndef _ForIndexes_H
#define _ForIndexes_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"struct.h"

Strings* MakeIndex(char* textik, int* AmountOfLines, int TextSize, int* MaxLine);
char* PutText(const char *TextFile, long* TextSize);
void OutputStrings(Strings** strings, int AmountOfLines);

#endif