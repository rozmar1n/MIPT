#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"ForIndexes.h"
#include"struct.h"

Strings* MakeIndex(char* textik, int* AmountOfLines, long TextSize)
{
    int nstrings          = 0;

    Strings *strings_in_func = (Strings*)calloc(TextSize, sizeof(Strings));
fprintf(stderr, "\nзаколлочено!\n");
    ((strings_in_func + 0) -> string_start) = textik;

    int ThisStringLength = 0;
    int inCmd            = 0;

    for (size_t i = 0; i < TextSize; i++)
    {
        if (textik[i] == '\n' || textik[i] == '\r' || isspace(textik[i]) || textik[i] == '\0')
        {
            textik[i] = '\0';
            if (inCmd)
            {
                strings_in_func[nstrings].string_size = ThisStringLength;
                ThisStringLength = 0;
                nstrings++;
                textik[i] = '\0';
            }
            inCmd = 0;
        }
        else
        {
            if (inCmd)
            {
                ThisStringLength++;
            }
            else
            {
                strings_in_func[nstrings].string_start = &(textik[i]);
            }
            inCmd = 1;
        }
    }

    //strings_in_func = (Strings*)realloc(strings_in_func, nstrings*sizeof(Strings));
    *AmountOfLines = nstrings;
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