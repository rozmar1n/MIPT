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

    FILE* read_binfile = fopen("test_binfile.bin", "rb");
    double array[10];
    char signat[5] = {'\0'};
    fread(signat, sizeof(char), 4, read_binfile);
    //fprintf(stderr,"%s\n", signat);
    fread(array, sizeof(double), 10, read_binfile);
    //for (int i = 0; i < 10; i++)
    //{
      //  fprintf(stderr, "%lg ", array[i]);
    //}
    long long int test_lli = 28; 
    fprintf(stderr, "%llx", test_lli);
  
    
}