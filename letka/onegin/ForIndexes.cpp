#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"ForIndexes.h"
#include"struct.h"

Strings* MakeIndex(char* textik, int* AmountOfLines, int TextSize, int* MaxLine)
{
    char symbol              = '\0';
    int nstrings             = 0;

    Strings *strings_in_func = (Strings*)calloc(1, sizeof(Strings));

    ((strings_in_func + 0) -> string_start) = textik;

    int ThatString = 0;
    int MaxString = 0;
    
    for (size_t i = 0; i < TextSize; i++)
    {
        symbol = textik[i];
        ThatString += 1;
        if (symbol != '\r')
        {
            if (symbol == '\n' || symbol == '\0')
            {
                strings_in_func[nstrings].string_size = ThatString - 1;
                nstrings++;
                
                textik[i] = '\0';
                strings_in_func[nstrings].string_start = &(textik[i + 1]);
                
                if (MaxString < ThatString)
                {
                    MaxString = ThatString; 
                }
                ThatString = 0;
            }
        }
        else
        {
            textik[i] = '\0';
        }

        if (i != TextSize)
        {
            strings_in_func = (Strings*)realloc(strings_in_func, (nstrings + 2)*sizeof(Strings)); 
        }

    }

    *AmountOfLines = nstrings;
    *MaxLine = MaxString;
    return strings_in_func;
}

char* PutText(const char *TextFile, long* TextSize)
{
    FILE *OneginText = fopen(TextFile, "r");
    char* buffer = NULL;
    
    if(!OneginText)
    {
        fprintf(stderr, "We cannot open your file!\n");
        return buffer;
    }
    else
    {
        fseek(OneginText, 0, SEEK_END);
        long OneginSize = ftell(OneginText);

        buffer = (char*)calloc(OneginSize + 1, sizeof(char));

        rewind(OneginText);
        fread(buffer, sizeof(char), OneginSize, OneginText);
        fclose(OneginText);
        buffer[OneginSize + 1] = '\0';
        
        *TextSize = OneginSize + 1;
        return buffer;
    }
}

void OutputStrings(Strings** strings, int AmountOfLines)
{
    for (int string_number = 0; string_number < AmountOfLines; string_number++)
    {
        if ((*(strings) + string_number)->string_size)
        {
            printf("%s\n", (*(strings) + string_number)->string_start);
        }
    }
    printf("\n\n\n");
}