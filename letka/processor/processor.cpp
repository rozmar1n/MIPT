#include"processor.h"
const int BufferSize = 25;
const int InfoSize = 16;

double* MakeAlgorithm(const char *cmdFile)
{
    FILE* commandFile = fopen(cmdFile, "r");
    if (commandFile == NULL)
    {
        fprintf(stderr, "We cannot open this file!\n");
        fprintf(stderr, "fileptr: %p", commandFile);
        return NULL;
    }    
    
    char buffer[BufferSize];
    double* algorithm = NULL;

    char info[InfoSize] = {};
    fscanf(commandFile, "%s", info);
    if (strcmp(info, "ROST"))
    {
        fprintf(stderr, "We cannot read this type of code!\n");
        return NULL;
    }
    else
    {
        fscanf(commandFile, "%s", info);
        if (strcmp(info, "1"))
        {
            fprintf(stderr, "Version of compiler and processor are not similar");
            fprintf(stderr, "version: %s", info);
            return NULL;
        }
        else
        {
            fscanf(commandFile, "%s", info);
            char* temp = NULL;
            u_int32_t ncmds = strtoul(info, &temp, 16);
            //fprintf(stderr, "size: %d\n", ncmds);
            double* cmdarray = (double*)calloc(ncmds, sizeof(double));
            //fprintf(stderr, "заколлочено\n");
            char string_elem[25] = {'\0'};
            double elem = 0;
            for (u_int32_t i = 0; i < ncmds; i++)
            {
                fscanf(commandFile, "%s", string_elem);
                //fprintf(stderr, "%s ", string_elem);
                elem = strtod(string_elem, &temp);
                *(cmdarray + i) = elem;
                //fprintf(stderr, "%lg ", cmdarray[i]);
            }
            fprintf(stderr, "\n");
            return cmdarray;
        }
    }
}
void Run(double code[], size_t size)
{
    Stack_t stk = {};
    StackCtor(&stk, 0);


    int ip = 0;
    int runCond = 0;
    while(runCond == 0)
    {
        //fprintf(stderr, "cmd: %d\n", (int)code[ip]);
        switch ((int)code[ip])
        {
        case push: {
            StackPush(&stk, code[ip+1]);
            ip += 2;
            break;
        }
        case add: {
            double a = NAN;
            StackPop(&stk, &a);
            double b = NAN;
            StackPop(&stk, &b);
            assert(a != NAN && b != NAN);
            StackPush(&stk, a + b);
            ip += 1;
            break;
        }
        case sub: {
            double a = NAN;
            StackPop(&stk, &a);
            double b = NAN;
            StackPop(&stk, &b);
            assert(a != NAN && b != NAN);
            StackPush(&stk, b - a);
            ip += 1;
            break;
        }
        case divs: {
            double a = NAN;
            StackPop(&stk, &a);
            double b = NAN;
            StackPop(&stk, &b);
            assert(a != NAN && b != NAN);
            StackPush(&stk, b/a);
            ip += 1;
            break;
        }    
        case mul: {
            double a = NAN;
            StackPop(&stk, &a);
            double b = NAN;
            StackPop(&stk, &b);
            assert(a != NAN && b != NAN);
            StackPush(&stk, b*a);
            ip += 1;
            break;
        }
        case sqr: {
            double a = NAN;
            StackPop(&stk, &a);
            assert(a != NAN);
            StackPush(&stk, sqrt(a));
            ip += 1;
            break;
        }
        case sins: {
            double a = NAN;
            StackPop(&stk, &a);
            assert(a != NAN);
            StackPush(&stk, sin(a));
            ip += 1;
            break;
        }
        case coss: {
            double a = NAN;
            StackPop(&stk, &a);
            assert(a != NAN);
            //fprintf(stderr, "%lg ", a);
            a = cos(a);
            //fprintf(stderr, "%lg \n", a);
            StackPush(&stk, cos(a));
            ip += 1; 
            break;
        }
        case hlt: {
            StackDtor(&stk);
            runCond = 1;
            break;
        }
        case dump: {
            StackDump(&stk);
            ip += 1;
            break;
        }
        case in: {
            double a = NAN;
            scanf("%lg", &a);
            StackPush(&stk, a);
            ip += 1;
            break;
        }
        case out: {
            double a = NAN;
            StackPop(&stk, &a);
            //assert(a != NAN);
            printf("%lg\n", a);
            ip += 1;
            break;
        }
        
        default: 
            fprintf(stk.logfile, 
            "\n------------------Invalid command"
            "--------------\n");
            break;
        }
        
    }
}