#include<stdio.h>
#include"SquareArrSum.h"
#include"structures.h"
#include<stdlib.h>
matrix SquareArrSum(matrix square_1, matrix square_2)
{
    if(square_1.size_X != square_2.size_X || square_1.size_Y != square_2.size_Y)
    {
        printf("�� ����� �����-�� �����!!! �.�. ������� ������ �� ���������\n");
        return(square_1);
    }

    size_t size_X = square_1.size_X;
    size_t size_Y = square_1.size_Y;

    int* start = (int*)calloc(size_X * size_Y, sizeof(int));

    for(size_t Y = 0; Y < size_Y; Y++)
    {
         for(size_t X = 0; X < size_X; X++)
         {
            *(start + Y*size_X + X) = *(square_1.start + Y*size_X + X) + *(square_2.start + Y*size_X + X);
         }
    }
    return {start, size_X, size_Y};
}
