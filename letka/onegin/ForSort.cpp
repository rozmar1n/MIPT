#include"ForSort.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* MakeGoodText(char* text, int TextSize)
{
    char* GoodText = NULL;
    GoodText = (char*)calloc(TextSize, sizeof(char));

    int j = 0;
    for (int symbol = 0; symbol < TextSize; symbol++)
    {
        if (isalpha(text[symbol]) || text[symbol] == '\n')
        {
            GoodText[j] = text[symbol];
            tolower(*(GoodText + j));
            j++; 
        }
    }
    return GoodText;
}


void SwapStrings(Strings** strings, int string_1, int string_2)
{
    Strings temp_string;
    temp_string = *(*(strings) + string_1);
    *(*(strings) + string_1) = *(*(strings) + string_2);
    *(*(strings) + string_2) = temp_string;
}

int Forward_Comp(Strings string_1, Strings string_2, int MaxLine)
{
    int i = 0, j = 0;
    for (int symbol = 0; symbol < MaxLine; symbol++)
    {
        if((isalpha(string_1.string_start[i]) || string_1.string_start[i] == '\0' || string_1.string_start[i] == '\n') && (isalpha(string_2.string_start[j])|| string_2.string_start[j] == '\0' || string_2.string_start[j] == '\n'))
        {
            if(tolower(string_1.string_start[i])  > tolower(string_2.string_start[j]))
            {
                return 1; 
            }
            if(tolower(string_1.string_start[i])  < tolower(string_2.string_start[j]))
            {
                return 0;
            }
            i++;
            j++;
        }
        else
        {
            if (!isalpha(string_1.string_start[i]))
            {
                i++;
            }
            if (!isalpha(string_2.string_start[j]))
            {
                j++;
            } 
        }
    }
}

int Backward_Comp(Strings string_1, Strings string_2, int MaxLine)
{
    int i = string_1.string_size;
    int j = string_2.string_size;
    for (int symbol = 0; symbol < MaxLine; symbol++)
    {
        if((isalpha(string_1.string_start[i]) || string_1.string_start[i] == '\0' || string_1.string_start[i] == '\n') && (isalpha(string_2.string_start[j])|| string_2.string_start[j] == '\0' || string_2.string_start[j] == '\n'))
        {
            if(tolower(string_1.string_start[i])  > tolower(string_2.string_start[j]))
            {
                return 1; 
            }
            if(tolower(string_1.string_start[i])  < tolower(string_2.string_start[j]))
            {
                return 0; 
            }
                i--;
                j--;
        }
        else
        {
            if (!isalpha(string_1.string_start[i]))
            {
                i--;
            }
            if (!isalpha(string_2.string_start[j]))
            {
                j--;
            } 
        }

    }
}