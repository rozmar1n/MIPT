#include"TXLib.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"ForIndexes.h"
#include"ForSort.h"
#include"TextSort.h"

#include"struct.h"

int main(int argc, char *argv[])
{
    char* text = NULL;
    long TextSize = 0;
    
    if (argc > 1)
    {
        text = PutText(argv[1], &TextSize);
    }
    else
    {
        text = PutText("onegin.txt", &TextSize);
    }

    Strings *strings_in_text;
    int AmountOfLines = 0;
    int MaxLine = 0;
     
    strings_in_text = MakeIndex(text, &AmountOfLines, TextSize, &MaxLine);
    
    // forward-sorted text
    // backward-sorted
    // original
    TextSort(&strings_in_text, AmountOfLines, MaxLine, Forward_Comp);//Comp_2 - плохо 
    OutputStrings(&strings_in_text, AmountOfLines);

    TextSort(&strings_in_text, AmountOfLines, MaxLine, Backward_Comp);//Comp_2 - плохо 
    OutputStrings(&strings_in_text, AmountOfLines);

    text = PutText("onegin.txt", &TextSize);
    strings_in_text = MakeIndex(text, &AmountOfLines, TextSize, &MaxLine);
    OutputStrings(&strings_in_text, AmountOfLines);

    return 0;
}