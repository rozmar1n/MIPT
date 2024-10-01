#include"TriangleArr.h"
#include<stdio.h>
#include<math.h>

int InputTriArr(int *data, size_t max_size)
{
    int elem = 0;
    int temp = 1;
    char ch = '\0';

    for(elem; elem < max_size; elem++)
    {
        temp = scanf("%d", data + elem);

        if(temp != 1)
        {
            return elem;
        }
    }
    return max_size;
}

void TriPrint(int *data, size_t array_size)
{
    int max_elem = 0;
    for(size_t i = 0; i < array_size; i++)
    {
        if(*(data + i) > max_elem)
            max_elem = *(data + i);
    }
    int disch = 0;
    while(max_elem > 0)
    {
        disch++;
        max_elem /= 10;
    }

    unsigned int number_of_rows = 0;

    number_of_rows = int((sqrt(1 + 8*array_size)-1)/2);

    for(int row = 0; row < number_of_rows; row++)
    {
        for(int column = 0; column < row; column++)
            printf("%0*d ", disch, *(data + row*(row-1)/2 + column));

        printf("\n");
    }
}
