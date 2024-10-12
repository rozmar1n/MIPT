#include"assembler.h"

void MakeAsm(const char* ProgramFile, const char* OutFile)
{
    FILE* asmFile = fopen(OutFile, "w");
    if (asmFile == 0)
    {
        fprintf(stderr, "We couldn't open you asmfile!!!\n");
    }
    
    FILE* ProgFile = fopen(ProgramFile, "r");

    if (ProgFile == 0)
    {
        fprintf(stderr, "We couldn't open you Progfile!!!\n");
    }

    fprintf(asmFile, "ROST\n");
    fprintf(asmFile, "1\n");
    fprintf(asmFile, "0x");
    long int sizeptr = ftell(asmFile);

    for (int i = 0; i < 2*sizeof(u_int32_t); i++)
    {
        fprintf(asmFile, "0");
    }
    fprintf(asmFile, "\n");

    char cmd[10];
    char temp = 'q';
    int err = 1;
    unsigned int nComands = 0;

    while (err)
    {
        err = fscanf(ProgFile, "%s", cmd);

        if (strcmp(cmd, "push") == 0)
        {
            if(err) err = fprintf(asmFile, "1 ");
            if(err) err = fscanf(ProgFile, "%s", cmd);
            if(err) err = fprintf(asmFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "add") == 0)
        {
            if(err) err = fprintf(asmFile, "2 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sub") == 0)
        {
            if(err) err = fprintf(asmFile, "3 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "mul") == 0)
        {
            if(err) err = fprintf(asmFile, "4 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "div") == 0)
        {
            if(err) err = fprintf(asmFile, "5 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "out") == 0)
        {
            if(err) err = fprintf(asmFile, "6 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "in") == 0)
        {
            if(err) err = fprintf(asmFile, "7 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sqrt") == 0)
        {
            if(err) err = fprintf(asmFile, "8 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sin") == 0)
        {
            if(err) err = fprintf(asmFile, "9 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "cos") == 0)
        {
            if(err) err = fprintf(asmFile, "10 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "dump") == 0)
        {
            if(err) err = fprintf(asmFile, "11 ");
            nComands++;
            continue;
        }
        if (strcmp(cmd, "hlt") == 0)
        {
            if(err) err = fprintf(asmFile, "-1 ");
            nComands++;
            err = 0;
        }
        err = 0;
    }
    fprintf(asmFile, "-1 ");
    fseek(asmFile, sizeptr, SEEK_SET);
    fprintf(asmFile, "%0*x\n", 8, nComands);
    
    fclose(asmFile);
    fclose(ProgFile);

    
    return;
}