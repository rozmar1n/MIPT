#include"Stack.h"

int StackPush(Stack_t* stk, StackElem_t elem)
{
    int err = 0;//проверка на ошибки в будущем

    if ((stk->stk_size) >= (stk->stk_capacity))
    {
        if (stk->stk_capacity)
        {
            (stk->stk_capacity) = 2*(stk->stk_capacity);
            (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), (stk->stk_capacity)*sizeof(StackElem_t));
        }
        else
        {
            (stk->stk_capacity) = (stk->stk_size) + 1;
        
            StackElem_t* new_array = (StackElem_t*)realloc((stk->stk_array), (stk->stk_capacity)*sizeof(StackElem_t));
            free(stk->stk_array);
            (stk->stk_array) = new_array;    
        }
    }
    
    (stk->stk_array)[stk->stk_size] = elem;
    (stk->stk_size)++;
    return err;//сделать проверку на ошибки
}
int StackPop(Stack_t* stk, StackElem_t* elem)
{
    int err = 0;//сделать проверки на ошибки
    
    (stk->stk_size)--;
    if ((stk->stk_size) && (stk->stk_capacity))
    {
        if ((stk->stk_capacity)/(stk->stk_size) >= 4)
        {
            (stk->stk_capacity) = (stk->stk_capacity)/4;

           (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), ((stk->stk_capacity))*sizeof(StackElem_t));
        }
    }
    *elem = (stk->stk_array)[stk->stk_size];
    (stk->stk_array)[stk->stk_size] = 0;
    return err;
}
int StackCtor(Stack_t* stk, StackElem_t fst_elem)
{
    int err = 0;//сделать как-нибудь
    (stk->stk_array) = (StackElem_t*)calloc(1, sizeof(StackElem_t));
    (stk->stk_size) = 0;
    (stk->stk_capacity) = 0;
    if (StackError(stk))
    {
        StackDump(stk);
        assert(0);
    }
    StackPush(stk, fst_elem);
    
    
    return err;
}
int StackDtor(Stack_t* stk)
{
    int err = 0;

    free(stk->stk_array);
    stk->stk_size = 0;
    stk -> stk_capacity = 0;

    return err;
}
int StackDump(Stack_t* stk)
{
    int err = 0;

    printf("Stack capacity: %zu\n", (stk->stk_capacity));
    printf("Stack size: %zu\n", (stk->stk_size));
    printf("Stack:\n");
    
    for (size_t elem = 0; elem < (stk->stk_capacity); elem++)
    {
        printf("%lg ", (stk->stk_array)[elem]);
    }
    printf("\n");
    return err;
}

int StackError(Stack_t* stk)
{
    int err = 0;
    return err;
}