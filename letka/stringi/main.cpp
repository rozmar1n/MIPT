#include"TXLib.h"
#include<stdio.h>
#include"SquareArr.h"
#include"TriangleArr.h"
#include"structures.h"
#include"SquareArrSum.h"
#include"SquareArrMult.h"
#include"SumTests.h"
#include"MultTest.h"

const size_t MAXSIZE = 500;

int main(void)
{
    
    
    
    
    #if 1
    
        #if 0

        matrix int_rect_1 = RectInput();
        matrix int_rect_2 = RectInput();

        printf("Enter the first matrix\n");
        RectPrint(int_rect_1);
      printf("Enter the second matrix:\n");
        RectPrint(int_rect_2);
    
            #if 0
            printf("Their sum:\n");
            RectPrint(SquareArrSum(int_rect_1, int_rect_2));
            #else
            printf("Their multyplication:\n");
            RectPrint(SquareArrMult(int_rect_1, int_rect_2));
            #endif
        #else
        int line_arr[MAXSIZE] = {};
        size_t array_size = MAXSIZE;
        array_size = InputTriArr(line_arr, MAXSIZE);
        TriPrint(line_arr, array_size);
        #endif
    
    #else
    printf("Sum Tests:\n");
    RunAllSumTests("TestSumData.csv");
    printf("Mult Tests:\n");
    RunAllMultTests("TestMultData.csv"); 
    #endif
}

