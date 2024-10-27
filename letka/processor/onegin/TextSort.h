#ifndef _TextSort_H
#define _TextSort_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"ForSort.h"
#include"struct.h"

typedef int(*compar_func_t)(Strings elem_1, Strings elem_2, int MaxLine);

void TextSort(Strings** strings, int LineAmount, int MaxLine, compar_func_t Comparator);

#endif