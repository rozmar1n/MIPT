#ifndef processor_h
#define processor_h

#include "instructions.h"
#include <stdio.h>
#include "Stack/Stack.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

const int nRegisters = 8;
const int procVersion = 2;

// enum instruction //TODO:  command || instruction
// {
//     push  = 1,
//     add   = 2,
//     sub   = 3,
//     mul   = 4,
//     divs  = 5,//TODO: префиксы!!!
//     out   = 6,
//     in    = 7,
//     sqr   = 8,
//     sins  = 9,
//     coss  = 10,
//     dump  = 11,
//     pop   = 12,
//     jmp   = 13,
//     ja    = 14,
//     jae   = 15,
//     jb    = 16,
//     jbe   = 17,
//     je    = 18,
//     jne   = 19,
//     pushr = 20,
//     hlt   = -1

// };

struct SPU_t
{
    double* cmds;
    int     ip;
    Stack_t stk;
    double*    registers;
};

void  MakeSPU    (const char *cmdFile, SPU_t *SPU);
void  MakeBinSPU (const char *binFile, SPU_t *SPU);
void  Run        (SPU_t *SPU);
SPU_t MakeNullSPU();
#endif //processor