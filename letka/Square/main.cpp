/**@file*/

#include "file.h"
#include"coefs.h"
#include"SquareSolver.h"
#include "SquareSolverTester.h"

int main()
{
    /*!
        \brief Conditional compilation

        In the first case, we want to enter our own coefficients
        but in the second one, the code will perform the check itself without requiring us to enter anything.
    */

    #if 1

    square_eq_coef coefficients {.a = NAN, .b = NAN, .c = NAN};
    InputCoef(&coefficients);
    CoefExam(&coefficients);

    pred_sol prog_res = SquareSolver(coefficients);
    OutputResults(prog_res);

    #else

    SquareSolverTester("TestData.csv");

    #endif
}








