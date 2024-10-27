#include"TextSort.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"ForSort.h"
#include"strings.h"
// TODO: void*
void TextSort(Strings** strings, int LineAmount, int MaxLine, compar_func_t Comparator)
{
    for (int index_elem = 0; index_elem < LineAmount - 1; index_elem++)
    {
        for (int compar_elem = 0; compar_elem < LineAmount - 1; compar_elem++)
        {
            if(Comparator(*(*(strings) + compar_elem), *(*(strings) + compar_elem + 1), MaxLine))
            {
               SwapStrings(strings, compar_elem, compar_elem + 1);
            }
        }
    }
}