#include"processor.h"

int main(void)
{
    SPU_t SPU = MakeNullSPU();
    //MakeSPU("compiler/new_program.bin", &SPU);
    MakeBinSPU("compiler/txtfiles/new_program.bin", &SPU);
    Run(&SPU);
    return 0;
}