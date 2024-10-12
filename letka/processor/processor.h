#ifndef processor_h
#define processor_h

#include<stdio.h>
#include"Stack/Stack.h"
#include<math.h>
#include<assert.h>
#include<stdlib.h>

enum actions
{
    push = 1,
    add,
    sub,
    mul,
    divs,
    out,
    in,
    sqr,
    sins,
    coss,
    dump,
    hlt = -1
};

double* MakeAlgorithm(const char *cmdFile);
void Run(double code[], size_t size);

#endif //processor