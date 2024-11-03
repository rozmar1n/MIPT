#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE* write_binfile = fopen("test_binfile.bin", "wb");
    
    char signa[] = {82, 79, 83, 84};
    fwrite(signa, sizeof(char), 4, write_binfile);
    
    double b = 0;
    for (int i = 0; i < 10; i++)
    {
        b = i + 1.5555;
        fwrite(&b, sizeof(b), 1, write_binfile);
    }
    fclose(write_binfile);

    printf("%d", '\n');











    // while(n >= -1 * R)
    // {
    //     array[(int)round(R - sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter)] = 1;
    //     fprintf(logfile, "push 64 \npop[%d] \n", (int)round(R - sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter));
    //     array[(int)round(R + sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter) + 1] = 1;
    //     fprintf(logfile, "push 64 \npop[%d] \n", (int)round(R + sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter));
    //     fprintf(logfile, "push 10 \npop[%d] \n", int(2*R*(counter+1)));
    //     counter++;
    //     n -= 1;
    // }
}