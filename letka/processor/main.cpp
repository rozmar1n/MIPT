#include"processor.h"

int main(void)
{
    printf("HELLO WORLD!\n");
    double* algoarray = MakeAlgorithm("compiler/new_program.txt");
    Run(algoarray, sizeof(algoarray)/sizeof(algoarray[0]));
    return 0;
}