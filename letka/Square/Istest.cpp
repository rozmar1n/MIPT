#include"TXLib.h"
#include"stdlib.h"
#include"Istest.h"
#include"stdio.h"

int Istest()
{
    printf("������� 1 ���� ������ ������ ���� ���������� ��������� ��� ������� 0, ���� ������ ��������� �����:  ");
    int a = NAN;
    scanf("%d", &a);
    switch(a)
    {
        case 1:
            return 1;
        case 0:
            return 0;
        default:
            printf("����, ��� �� ������ �� ������...");
            exit(0);
    }
}
