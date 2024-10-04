#ifndef  COMP_OPER
#define  COMP_OPER

#include"complex.h"
#include"stdio.h"

struct complex CompMult  (struct complex num1, struct complex num2);
struct complex CompSum   (struct complex num1, struct complex num2);
struct complex CompRat   (struct complex num1, struct complex num2);
struct complex CompDif   (struct complex num1, struct complex num2);
void           CompPrintf(struct complex num);

#endif /*COMP_OPER*/