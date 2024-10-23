#include"processor.h"

int main(void)
{
    printf("HELLO WORLD!\n");
    SPU_t SPU = MakeNullSPU();
    MakeSPU("compiler/new_program.txt", &SPU);
    Run(&SPU);
    return 0;
}