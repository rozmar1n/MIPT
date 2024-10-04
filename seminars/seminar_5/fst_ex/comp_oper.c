#include"complex.h"
#include"comp_oper.h"
#include"stdio.h"

struct complex CompMult(struct complex num1, struct complex num2)
{
    struct complex result = {0};
    result.Re = num1.Re*num2.Re - num1.Im*num2.Im; 
    result.Im = num1.Re*num2.Im + num1.Im*num2.Re;
    return result;
}
struct complex CompSum(struct complex num1, struct complex num2)
{
    struct complex result = {0};
    result.Im = num1.Im + num2.Im;
    result.Re = num1.Re + num2.Re;
    return result;
}
struct complex CompRat(struct complex num1, struct complex num2)
{
    struct complex result = {0};
    result.Re = (num1.Re*num2.Re + num1.Im*num2.Im)/(num2.Re * num2.Re + num2.Im * num2.Im); 
    result.Im = (num2.Re*num1.Im - num1.Re*num2.Im)/(num2.Re * num2.Re + num2.Im * num2.Im);
    return result;
}
struct complex CompDif(struct complex num1, struct complex num2)
{
    struct complex result = {0};
    result.Im = num1.Im - num2.Im;
    result.Re = num1.Re - num2.Re;
    return result;
}
void CompPrintf(struct complex num)
{
    printf("%lg + %lgi\n", num.Re, num.Im);
    return;
}
