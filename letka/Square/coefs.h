/**@file*/
#ifndef CoefFunctions
#define CoefFunctions
#include "file.h"
void ElemInput(int number_of_coefficient, double *coefficient, int* counters);
///\brief Function that moves the caret to the end of the input
void ClearBuffer();
/*!
    Function that inputs coefficients from the command line or file
    \param coefficients  coefficients of user's quadratic equation
*/
void InputCoef(square_eq_coef* coefficients);
/*!
    Function that outputs the results of the function SquareSolver
    \param results roots and
*/
void OutputResults(pred_sol results);
///\brief Function that allows the user to check whether the program correctly understood the coefficients entered by him
void CoefExam(square_eq_coef* coefficients);


#endif //CoefFunctions


