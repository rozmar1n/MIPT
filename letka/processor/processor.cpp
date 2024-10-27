#include"processor.h"
const int BufferSize = 25;
const int InfoSize = 16;

void MakeSPU(const char *cmdFile, SPU_t *SPU)
{
    
    FILE* machCode = fopen(cmdFile, "r");
    if (machCode == NULL)
    {
        fprintf(stderr, "We cannot open this file!\n");
        fprintf(stderr, "fileptr: %p", machCode);
        return;
    }    
    
    char buffer[BufferSize];
    double* algorithm = NULL;

    char info[InfoSize] = {};
    fscanf(machCode, "%s", info);
    if (strcmp(info, "ROST"))
    {
        fprintf(stderr, "We cannot read this type of code!\n");
        return;
    }
    else
    {
        fscanf(machCode, "%s", info);
        if (strcmp(info, "1"))
        {
            fprintf(stderr, "Version of compiler and processor are not similar");
            fprintf(stderr, "version: %s", info);
            return;
        }
        else
        {
            fscanf(machCode, "%s", info);
            char* temp = NULL;
            u_int32_t ncmds = strtoul(info, &temp, 16);

            //fprintf(stderr, "size: %d\n", ncmds);
            SPU->cmds = (double*)calloc(ncmds, sizeof(double));
            //fprintf(stderr, "SPU->cmds callocated correctly\n");

            char string_elem[25] = {'\0'};
            double elem = 0;
            for (u_int32_t i = 0; i < ncmds; i++)
            {
                fscanf(machCode, "%s", string_elem);
                //fprintf(stderr, "%s ", string_elem);
                elem = strtod(string_elem, &temp);
                *(SPU->cmds + i) = elem;
                //fprintf(stderr, "%lg ", SPU->cmds[i]);
            }
            //fprintf(stderr, "\n");
            return;
        }
    }
}

void  MakeBinSPU (const char *binFile, SPU_t *SPU)
{
    FILE* machCode = fopen(binFile, "rb"); assert(machCode);
    
    u_int32_t signature = 0;
    fread(&signature, sizeof(u_int32_t), 1, machCode);
    //fprintf(stderr, "signature: %u\n", signature);
    if (signature != signatura)
    {
        fprintf(stderr, "THIS SPU CANNOT WORK WITH THIS FILES\n");
        assert(signature != signatura);
    }
    
    int ass_version = 0;
    fread(&ass_version, sizeof(int), 1, machCode);
    if (ass_version != procVersion)
    {
        fprintf(stderr, "THIS SPU CANNOT WORK WITH "
                        "THIS VERSION OF ASSEMBLY\n");
        assert(ass_version != procVersion);
    }
    //fprintf(stderr, "ass_version: %d\n", ass_version);

    u_int32_t nComands = 0;
    fread(&nComands, sizeof(u_int32_t), 1, machCode);
    //fprintf(stderr, "nCommands: %u\n", nComands);

    SPU->cmds = (double*)calloc(nComands, sizeof(double));

    fread(SPU->cmds, sizeof(double), nComands, machCode);
    // for (size_t i = 0; i < nComands; i++)
    // {
    //     fprintf(stderr, "%2lu. command:   %lg\n", i, SPU->cmds[i]);
    // }
}

void add_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), a + b);
    SPU->ip += 1;
}

void sub_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), b - a);
    SPU->ip += 1;
}

void jmp_f(SPU_t *SPU)
{
    int temp_ip = SPU->cmds[SPU->ip+1];
    SPU->ip = temp_ip; 
}

void ja_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b > a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip++;
}

void jae_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b >= a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip++;
}

void jb_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b < a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip++;
}

void jbe_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b <= a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip++;
}

void je_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b == a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip++;
}

void jne_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b != a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip++;
}

void div_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), b/a);
    SPU->ip += 1;
}

void mul_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), b*a);
    SPU->ip += 1;
}

void sqrt_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    StackPush(&(SPU->stk), sqrt(a));
    SPU->ip += 1;
}

void sin_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    StackPush(&(SPU->stk), sin(a));
    SPU->ip += 1;
}

void cos_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    //fprintf(stderr, "%lg ", a);
    a = cos(a);
    //fprintf(stderr, "%lg \n", a);
    StackPush(&(SPU->stk), cos(a));
    SPU->ip += 1;
}

void in_f(SPU_t *SPU)
{
    double a = NAN;
    scanf("%lg", &a);
    StackPush(&(SPU->stk), a);
    SPU->ip += 1;
}

void out_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    fprintf(stderr, "%lg\n", a);
    SPU->ip += 1;
}

void pushr_f(SPU_t *SPU)
{
    StackPush(&SPU->stk, SPU->registers[(long long int)(SPU->cmds[SPU->ip + 1])]);
    SPU->ip += 2;
}

void pop_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    SPU->registers[(long long int)(SPU->cmds[SPU->ip + 1])] = a;
    SPU->ip += 2;
}
void Run(SPU_t *SPU)
{
    int runCond = 0;
    while(runCond == 0)
    {
        //fprintf(stderr, "cmd: %d\n", (int)code[ip]);
        switch ((int)SPU->cmds[SPU->ip])
        {
        case cmd_push: {
            StackPush(&(SPU->stk), SPU->cmds[SPU->ip+1]);
            SPU->ip += 2;
            break;
        }
        case cmd_add: {
            add_f(SPU);
            break;
        }
        case cmd_sub: {
            sub_f(SPU);
            break;
        }
        case cmd_div: {
            div_f(SPU);
            break;
        }    
        case cmd_mul: {
            mul_f(SPU);
            break;
        }
        case cmd_sqrt: {
            sqrt_f(SPU);
            break;
        }
        case cmd_sin: {
            sin_f(SPU);
            break;
        }
        case cmd_cos: {
            cos_f(SPU);
            break;
        }
        case cmd_hlt: {
            StackDtor(&(SPU->stk));
            runCond = 1;
            break;
        }
        case cmd_dump: {
            StackDump(&(SPU->stk));//TODO: написать нормальный дамп
            SPU->ip += 1;
            break;
        }
        case cmd_in: {
            in_f(SPU);
            break;
        }
        case cmd_out: {
            out_f(SPU);
            break;
        }
        case cmd_pushr: {
            pushr_f(SPU);
            break;
        }
        case cmd_pop: {
            pop_f(SPU);
            break;
        }
        case cmd_jmp: {
            jmp_f(SPU);
            break;
        }
        case cmd_ja: {
            ja_f(SPU);
            break;
        }
        case cmd_jae: {
            jae_f(SPU);
            break;
        }
        case cmd_jb: {
            jb_f(SPU);
            break;
        }
        case cmd_jbe: {
            jbe_f(SPU);
            break;
        }
        case cmd_je: {
            je_f(SPU);
            break;
        }
        case cmd_jne: {
            jne_f(SPU);
            break;
        }
        default: 
            fprintf((SPU->stk).logfile, 
            "\n------------------Invalid command"
            "--------------\n");
            break;
        }
    }
}

SPU_t MakeNullSPU()
{
    SPU_t NullSPU;
    Stack_t null_stk;
    StackCtor(&null_stk, 0);

    NullSPU.cmds      = NULL;
    NullSPU.ip        = 0;
    NullSPU.stk       = null_stk;
    NullSPU.registers = (double*)calloc(nRegisters, sizeof(double));
    return NullSPU;
}
