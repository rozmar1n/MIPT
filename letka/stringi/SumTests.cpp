#include"SumTests.h"
#include"structures.h"
#include"SquareArrSum.h"
#include"SquareArr.h"

void RunAllSumTests(const char *Testfile)
{
    matrix rect_1 = {},
           rect_2 = {},
           rect_sum = {};

    FILE *tests_data = fopen(Testfile, "r");

    if(tests_data == NULL)
    {
        printf("ERROR: could not open the file\n");
        exit(0);
    }
    else
    {
        unsigned int test_number = 1;
        do
        {
            int read_1 = 0;
            read_1 = fscanf(tests_data,
                          "%d;%d\n",

                          &rect_1.size_X,
                          &rect_1.size_Y);


            if(read_1 != 2 && !feof(tests_data))
            {
                fprintf(stderr, "File format incorrect.\n");
                exit(0);
            }

            if(ferror(tests_data))
            {
                fprintf(stderr, "ERROR reading file.\n");
                exit(0);
            }

            rect_1.start = (int*)calloc(rect_1.size_X*rect_1.size_Y, sizeof(int));

            for (size_t y = 0; y < rect_1.size_Y; y++)
            {
                for (size_t x = 0; x < rect_1.size_X; x++)
                {
                    int read_elem = 0;

                    read_elem = fscanf(tests_data,
                            "%d;", rect_1.start + y*rect_1.size_X + x);
                    
                    if(read_elem != 1 && !feof(tests_data))
                    {
                        fprintf(stderr,"File format incorrect.\n");
                        exit(0);
                    }

                    if(ferror(tests_data))
                    {
                        fprintf(stderr,"ERROR reading file.\n");
                        exit(0);
                    }
                }
            }
            fscanf(tests_data, "\n");
            /////////////////////////////////////////////////////////////////////////
            int read_2 = 0;

            read_2 = fscanf(tests_data,
                          "%d;%d\n",
                          &rect_2.size_X,
                          &rect_2.size_Y);
            
            if(read_2 != 2 && !feof(tests_data))
            {
                printf("File format incorrect.\n");
                exit(0);
            }

            if(ferror(tests_data))
            {
                printf("ERROR reading file.\n");
                exit(0);
            }

            rect_2.start = (int*)calloc(rect_2.size_X*rect_2.size_Y, sizeof(int));

            for (size_t y = 0; y < rect_2.size_Y; y++)
            {
                for (size_t x = 0; x < rect_2.size_X; x++)
                {
                    int read_elem = 0;

                    read_elem = fscanf(tests_data,
                            "%d;", rect_2.start + y*rect_2.size_X + x);
                    
                    if(read_elem != 1 && !feof(tests_data))
                    {
                        printf("File format incorrect.\n");
                        exit(0);
                    }

                    if(ferror(tests_data))
                    {
                        printf("ERROR reading file.\n");
                        exit(0);
                    }

                }
            }

            fscanf(tests_data, "\n");
            ///////////////////////////////////////////////////////////////////////////////    
            
            int read_sum = 0;

            read_sum = fscanf(tests_data,
                          "%d;%d\n",
                          &rect_sum.size_X,
                          &rect_sum.size_Y);

            
            if(read_sum != 2 && !feof(tests_data))
            {
                printf("File format incorrect.\n");
                exit(0);
            }

            if(ferror(tests_data))
            {
                printf("ERROR reading file.\n");
                exit(0);
            }

            rect_sum.start = (int*)calloc(rect_sum.size_X*rect_sum.size_Y, sizeof(int));
            
            for (size_t y = 0; y < rect_sum.size_Y; y++)
            {
                for (size_t x = 0; x < rect_sum.size_X; x++)
                {
                    int read_elem = 0;

                    read_elem = fscanf(tests_data,
                            "%d;", rect_sum.start + y*rect_sum.size_X + x);
                    
                    if(read_elem != 1 && !feof(tests_data))
                    {
                        printf("File format incorrect.\n");
                        return;
                    }

                    if(ferror(tests_data))
                    {
                        printf("ERROR reading file.\n");
                        return;
                    }

                }
            }

            fscanf(tests_data, "\n\n");

            RunTest(rect_1, rect_2, rect_sum, test_number);
            test_number++;
        } while (!feof(tests_data));

        fclose(tests_data);
    }
}

void RunTest(matrix matrix_1, matrix matrix_2, matrix matrix_sum, unsigned int test_number)
{
    matrix pred_sum = SquareArrSum(matrix_1, matrix_2);

    if (pred_sum.size_X != matrix_sum.size_X || pred_sum.size_Y != matrix_sum.size_Y)
    {
        printf("\nERROR  Test %d\n matrix_sum.size_X = %d   matrix_sum.size_Y = %d\n\t"
                "EXPECTED:\n matrix_sum.size_X = %d   matrix_sum.size_Y = %d\n", test_number, 
                pred_sum.size_X, pred_sum.size_Y, matrix_sum.size_X, matrix_sum.size_Y);
        
        return;
    }
    
    for (size_t y = 0; y < matrix_sum.size_Y; y++)
    {
        for (size_t x = 0; x < matrix_sum.size_X; x++)
        {
            if (*(pred_sum.start + y*pred_sum.size_X + x) != *(matrix_sum.start + y*matrix_sum.size_X + x))
            {
                fprintf(stderr,"\nERROR Test %d\n", test_number);
                
                fprintf(stderr, "Received matrix_sum:\n");
                RectPrint(pred_sum);

                printf("Expected matrix_sum:\n");
                RectPrint(matrix_sum);
                return;
            }
        }
    }
    printf("Test %dPassed\n", test_number);
    return;
}