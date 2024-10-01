#ifndef _Stack_H
#define _Stack_H

//#include"TXLib.h"
#include<cassert>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//enum for ERRORS

typedef double StackElem_t;

struct Stack_t
{
    StackElem_t* stk_array;
    size_t stk_size;
    size_t stk_capacity;
};

int StackPush(Stack_t* stk, StackElem_t elem);
int StackPop(Stack_t* stk, StackElem_t* elem);
int StackCtor(Stack_t* stk, StackElem_t fst_elem);
int StackDtor(Stack_t* stk);
int StackDump(Stack_t* stk);
int StackError(Stack_t* stk);




#endif 