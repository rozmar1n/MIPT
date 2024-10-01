/**@file*/

#ifndef FILE_H
#define FILE_H
/*!
\file
    \brief Header file for structures, constants and including headers from standard library

    This file contains different headers, that we use in different other files of project,
    structures for reference solution, solutions that we get from our function that solve equation, equation coefficients and all elements of square equation including its solutions
*/
#include "TXLib.h"
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
///\brief Structure for reference solutions
struct Ref
{
    double x1Ref;///<Higher right coefficient
    double x2Ref;///<Lower right coefficient
    int nRootsRef;///<Right number of roots
};
///\brief Structure for solutions that predicted our program
struct pred_sol
{
    double x1Pred;///<Higher predicted coefficient
    double x2Pred;///<Lower predicted coefficient
    int nRootsPred;///<Predicted number of roots
};
///\brief Structure for coefficients of quadratic equation
struct square_eq_coef
{
    double a;///<First coefficient
    double b;///<Second coefficient
    double c;///<Third coefficient
};
///\brief Structure for all elements of equation including right solutions
struct square_equation
{
    square_eq_coef coefficients;///< coefficients from equation
    Ref solutions;///<Right solutions which are a reference during testing
};
///\brief The maximum fault we consider acceptable when working with the "double" data type
const double MaxDifference = 0.001;

#endif
