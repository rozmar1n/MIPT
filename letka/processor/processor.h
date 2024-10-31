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
const int ram_volume = 2048;

struct SPU_t
{
    double*    cmds;
    int        ip;
    Stack_t    stk;
    Stack_t    proc_stk;
    double*    registers;
    double*    ram;
    FILE*      logfile;
};

void  MakeSPU    (const char *cmdFile, SPU_t *SPU);
void  MakeBinSPU (const char *binFile, SPU_t *SPU);
void  Run        (SPU_t *SPU);
SPU_t MakeNullSPU();
#endif //processor