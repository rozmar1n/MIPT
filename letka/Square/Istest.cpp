#include"TXLib.h"
#include"stdlib.h"
#include"Istest.h"
#include"stdio.h"

int Istest()
{
    printf("¬ведите 1 если хотите ввести свое квадратное уравнение или введите 0, если хотите запустить тесты:  ");
    int a = NAN;
    scanf("%d", &a);
    switch(a)
    {
        case 1:
            return 1;
        case 0:
            return 0;
        default:
            printf("∆аль, что вы ничего не хотите...");
            exit(0);
    }
}
