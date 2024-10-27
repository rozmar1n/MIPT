#ifndef _ForString_H
#define _ForString_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"struct.h"

char* MakeGoodText(char* text, int TextSize);

void SwapStrings(Strings** strings, int string_1, int string_2);

int Forward_Comp(Strings string_1, Strings string_2, int MaxLine);
int Backward_Comp(Strings string_1, Strings string_2, int MaxLine);

#endif