#include"MultTest.h"
#include"structures.h"
#include"SquareArrMult.h"
#include"SquareArr.h"

void RunAllMultTests(const char *Testfile)
{
    matrix rect_1 = {},
           rect_2 = {},
           rect_sum = {};

    FILE *tests_data = fopen(Testfile, "r");

    if(tests_data == NULL)
    {
        fprintf(stderr, "ERROR: could not open the file\n");
        return;
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
                return;
            }

            if(ferror(tests_data))
            {
                fprintf(stderr, "ERROR reading file.\n");
                return;
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
                        return;
                    }

                    if(ferror(tests_data))
                    {
                        fprintf(stderr,"ERROR reading file.\n");
                        return;
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
                fprintf(stderr, "File format incorrect.\n");
                return;
            }

            if(ferror(tests_data))
            {
                fprintf(stderr, "ERROR reading file.\n");
                return;
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
                        fprintf(stderr, "File format incorrect.\n");
                        return;
                    }

                    if(ferror(tests_data))
                    {
                        fprintf(stderr, "ERROR reading file.\n");
                        return;
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
                fprintf(stderr, "File format incorrect.\n");
                return;
            }

            if(ferror(tests_data))
            {
                fprintf(stderr, "ERROR reading file.\n");
                return;
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
                        fprintf(stderr, "File format incorrect.\n");
                        return;
                    }

                    if(ferror(tests_data))
                    {
                        fprintf(stderr, "ERROR reading file.\n");
                        return;
                    }

                }
            }

            fscanf(tests_data, "\n\n");

            RunMultTest(rect_1, rect_2, rect_sum, test_number);
            test_number++;
        } while (!feof(tests_data));

        fclose(tests_data);
    }
}

void RunMultTest(matrix matrix_1, matrix matrix_2, matrix matrix_mult, unsigned int test_number)
{
    matrix pred_sum = SquareArrMult(matrix_1, matrix_2);

    if (pred_sum.size_X != matrix_mult.size_X || pred_sum.size_Y != matrix_mult.size_Y)
    {
        fprintf(stderr, "\nERROR  Test %d\n matrix_mult.size_X = %d   matrix_mult.size_Y = %d\n\t"
                "EXPECTED:\n matrix_mult.size_X = %d   matrix_mult.size_Y = %d\n", test_number, 
                pred_sum.size_X, pred_sum.size_Y, matrix_mult.size_X, matrix_mult.size_Y);
        
        return;
    }
    
    for (size_t y = 0; y < matrix_mult.size_Y; y++)
    {
        for (size_t x = 0; x < matrix_mult.size_X; x++)
        {
            if (*(pred_sum.start + y*pred_sum.size_X + x) != *(matrix_mult.start + y*matrix_mult.size_X + x))
            {
                fprintf(stderr, "\nERROR Test %d\n", test_number);
                
                fprintf(stderr, "Received matrix_mult:\n");
                RectPrint(pred_sum);

                fprintf(stderr, "Expected matrix_mult:\n");
                RectPrint(matrix_mult);
                return;
            }
        }
    }
    fprintf(stderr, "Test %d Passed\n", test_number);
    return;
}