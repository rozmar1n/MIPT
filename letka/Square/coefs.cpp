#include"coefs.h"
#include"file.h"

void ElemInput(int number_of_coefficient, double *coefficient, int* counter)
{

    while(*counter < number_of_coefficient)
    {
        char ch;

        *counter +=scanf("%lg", coefficient);
        if(*counter < number_of_coefficient)
        {
            ch = char(getchar());
        }
        if(ch == EOF)
        {
            printf("The file is finished\n");
            exit(0);
        }

    }
    return;
}


void ClearBuffer()
{
    char ch = '\0';
    while(ch != '\n' && ch != EOF)
    {
        ch = char(getchar());
    }
}


void InputCoef(square_eq_coef* coefficients)
{
    printf("Entering the coefficients:  ");

    int counter = 0;

    printf("\nEnter the first coefficient:  ");
    ElemInput(1, &coefficients->a, &counter);
    printf("Enter the second coefficient:  ");
    ElemInput(2, &coefficients->b, &counter);
    printf("Enter the third coefficient:  ");
    ElemInput(3, &coefficients->c, &counter);

    ClearBuffer();
}


void  OutputResults(pred_sol results)
{
    switch(results.nRootsPred)
    {
        case 0:
            printf("Your equation has no roots\n");
            break;
        case 1:
            printf("Your equation has one root:  %lg\n", results.x1Pred);
            break;
        case 2:
            printf("First root:  %lg\n"
                   "Second root:  %lg\n", results.x1Pred, results.x2Pred);
            break;
        case -1:
            printf("Your equation has Infinity roots!\n");
            break;
        default:
            printf("Something went wrong...");
            exit(0);
    }
}


void CoefExam(square_eq_coef* coefficients)
{
    if(int(coefficients->a) != int(coefficients->a) || int(coefficients->b) != int(coefficients->b) || int(coefficients->c) != int(coefficients->c))
    {
        printf("\nTHE INPUT WAS INCORRECT AAAAAAA!!!\n");
        char ch = '\0';
        while(ch != '\n')
        {
            ch = char(getchar());
        }
        if(ch == EOF)
        {
            exit(0);
        }
        ClearBuffer();
        InputCoef(coefficients);
        CoefExam(coefficients);
    }
    else
    {
            printf("Your coefficients:\n"
            "The first coef:  %lg \n"
            "The second coef:  %lg \n"
            "The third coef:  %lg \n\n"
            "If everything is correct, enter 1 and press Enter, otherwise enter 0:   ", coefficients->a, coefficients->b, coefficients->c);

        int result = 2;


        int temp = scanf("%d", &result);
        switch(result)
        {
            case 1:
                printf("Great!\n\n");
                break;
            case 0:
                printf("Too bad, let's try again\n");
                InputCoef(coefficients);
                CoefExam(coefficients);
                break;
            case 2:
                printf("THE INPUT WAS INCORRECT AAAAAAA!!!!!");
                exit(0);
                break;
            default:
                printf("You entered the wrong character, let's try again\n");
                if(temp)
                {
                    CoefExam(coefficients);
                }
                break;
        }
    }
}
