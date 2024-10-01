#include"SquareArr.h"
#include<stdio.h>
#include<stdlib.h>
void ClearBuffer()
{
    char ch = char(getchar());
    while(ch != '\n' && ch != EOF)
    {
        ch = char(getchar());
    }
    if(ch == EOF)
    {
        printf("File input terminated unexpectedly!!!\n");
        exit(0);
    }
}

void RectPrint(matrix int_rect)
{
    int max_elem = 0;
    for(size_t i = 0; i < int_rect.size_Y*int_rect.size_X; i++)
    {
        if(*(int_rect.start + i) > max_elem)
            max_elem = *(int_rect.start + i);
    }
    int disch = 0;
    while(max_elem > 0)
    {
        disch++;
        max_elem /= 10;
    }
    for(size_t Y = 0; Y < int_rect.size_Y; Y++)
    {
        for(size_t X = 0; X < int_rect.size_X; X++)
        {
            printf("%0*d ", disch, *(int_rect.start + Y * int_rect.size_X + X));
        }
        printf("\n");
    }
    printf("\n");
}
matrix RectInput()
{
    size_t size_y = 0;
    size_t size_x = 0;

    printf("Enter the number of lines:   ");
    scanf("%u", &size_y);
    ClearBuffer();

    printf("Enter the number of columns:   ");
    scanf("%u", &size_x);
    ClearBuffer();

    int* start = (int*)calloc(size_x*size_y, sizeof(int));
    int temp = 1;
    char ch = '\0';
    printf("Enter the elements of matrix in 1 line:   ");
    
    for(size_t Y = 0; Y < size_y; Y++)
    {
        for(size_t X = 0; X < size_x; X++)
        {
            temp = scanf("%d%c", start + Y * size_x + X, &ch);
        }
        if(ch == '\n')
        {
            //ClearBuffer();
            return{start, size_x, size_y};
        }
    }
    ClearBuffer();
    return{start, size_x, size_y};
}
