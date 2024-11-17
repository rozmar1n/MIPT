#include"Stack.h"

int main(void)
{
    Stack_t my_stk;
    StackElem_t my_stk_elem;

    StackCtor(&my_stk, 10);
    printf("fst_elem: %lg\n", (my_stk.stk_array)[1]);

    for (int i = 1; i < 100; i++)
    {
        StackPush(&my_stk, i);
    }
    while(my_stk.stk_size)
    {
        StackPop(&my_stk, &my_stk_elem);
        //printf("elem: %lg \n", my_stk_elem);
    }
    printf("\n");
    for (int i = 1; i < 100; i++)
    {
        StackPush(&my_stk, i);
    }
    while((my_stk.stk_size) - 9)
    {
        StackPop(&my_stk, &my_stk_elem);
        printf("elem: %lg \n", my_stk_elem);
    }
    printf("\n");
    StackDump(&my_stk);
    StackDtor(&my_stk);

}
