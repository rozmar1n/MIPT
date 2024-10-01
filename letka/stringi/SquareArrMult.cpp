#include"structures.h"
#include<stdio.h>
#include"SquareArrMult.h"
#include<stdlib.h>
int min(size_t a, size_t b)
{
    size_t c = (a < b) ? a : b;
    return c;
}
matrix SquareArrMult(matrix rect_1, matrix rect_2)
{
    if(rect_1.size_X != rect_2.size_Y)
    {
        printf("You entered some shit!!! The number of columns of the first matrix does not match the number of rows of the second matrix\n");
        return(rect_1);
    }
    
    size_t vert = rect_1.size_Y;
    size_t hor = rect_2.size_X;
    int* start = (int*)calloc(hor * vert, sizeof(int));

    int line = rect_1.size_X;

    for(size_t x = 0; x < hor; x++)
    {
        for(size_t y = 0; y < vert; y++)
        {
            int sum = 0;
            for(int t = 0; t < line; t++)
            {
                sum += *(rect_1.start + y*rect_1.size_X + t) * (*(rect_2.start + t*rect_2.size_X + x));
            }
            *(start + y*hor + x) = sum;
        }
    }
    return {start, hor, vert};
}
