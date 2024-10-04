#include<stdio.h>
#include"comp_oper.h"


int main(void)
{
    struct complex a = {2, 7};
    struct complex b = {3, 8};

    printf("a + b = "); CompPrintf(CompSum(a,b));
    printf("a - b = "); CompPrintf(CompDif(a,b));
    printf("a * b = "); CompPrintf(CompMult(a,b));
    printf("a / b = "); CompPrintf(CompRat(a,b));
    
    return 0;
}

