#include"../headers/assembler.h"

int main(int argc, const char *argv[])
{
    char InputFile[20];
    char OutputFile[20];
    
    if (argc > 1)
    {
        strcpy(InputFile, argv[1]);
        if (argc > 2)
            strcpy(OutputFile, argv[2]);
        else
            strcpy(OutputFile, "new_program.bin");
    }
    else
    {
        strcpy(InputFile, "default.txt");
        strcpy(OutputFile, "new_program.bin");
    }
    fprintf(stderr, "InputFile: %s\n OutputFile: %s\n", InputFile, OutputFile);

    labelArray_t labels;
    LabelCtor(&labels, amount_of_labels);
    
    MakeMachCode(InputFile, OutputFile, "logfile.txt", 1, &labels);
    MakeMachCode(InputFile, OutputFile, "logfile.txt", 2, &labels);
}