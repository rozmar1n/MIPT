#ifndef _Stack_H
#define _Stack_H

//#include"TXLib.h"
#include<cassert>

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
//enum #ifndef _Stack_H
#define _Stack_H

//#include"TXLib.h"
#include<cassert>

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
//enum for ERRORS

typedef double StackElem_t;
typedef unsigned long long hash_t;

struct Stack_t
{
    StackElem_t* stk_array;
    size_t stk_size;
    size_t stk_capacity;
    hash_t stk_hash;
};

enum errors_t
{
    USE_HOROSHO,
    STACK_SIZE_ZALUPA,
    LEFT_KANAREIKA_ZALUPA,
    RIGHT_KANAREIKA_ZALUPA,
    HASH_ZALUPA
};

int StackPush(Stack_t* stk, StackElem_t elem);
int StackPop(Stack_t* stk, StackElem_t* elem);
int StackCtor(Stack_t* stk, StackElem_t fst_elem);
int StackDtor(Stack_t* stk);
int StackDump(Stack_t* stk);
enum errors_t StackError(Stack_t* stk);
void StackAssert(Stack_t* stk, const char *file_name, const int line);
hash_t StackHaschFunc(Stack_t* stk);




#endif 