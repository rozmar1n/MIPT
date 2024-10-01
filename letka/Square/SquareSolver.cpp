#include"SquareSolver.h"
#include "file.h"

pred_sol SquareSolver(square_eq_coef coefficients)
{
    double a = coefficients.a, b = coefficients.b, c = coefficients.c;
    double x1 = NAN, x2 = NAN;

    if(int(a) != int(a) or int(b) != int(b) || int(c) != int(c))
    {
        return {x1, x2, 0};
    }

    if(fabs(a - 0) < 0.00001 || int(a) != int(a))
    {
        if(fabs(b - 0) < 0.00001)
        {
            if(fabs(c - 0) < 0.00001)
            {
                return {x1, x2, -1};
            }
            return {x1, x2, 0};
        }
        else
        {
            x1 = -(coefficients.c)/(coefficients.a);
            x2 = NAN;
            return {x1, x2, 1};
        }
    }

    double D;
    D = b*b - 4*a*c;
    if(D < 0.0)
    {
        return {NAN, NAN, 0};
    }

    x1 = (-b + sqrt(D))/(2*a);
    x2 = (-b - sqrt(D))/(2*a);

    if (fabs(x1 - x2) < 0.0001)
    {
        return {x1, x2, 1};
    }
    return {x1, x2, 2};
}


