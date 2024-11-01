#include <stdio.h>
#include <math.h>

int main()
{    
    double R = 0;
    printf("Enter R:\t");
    scanf("%lg", &R);
    double n = R;
    double size = 4*(R * R);
    int  array[(int)size] = {'\0'};
    int counter = 0;
    while(n >= -1 * R)
    {
        array[(int)round(R - sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter)] = 1;
        array[(int)round(R + sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter) + 1] = 1;
        counter++;
        n -= 1;
    }

    for (int i = 0; i <= 4*R*R; i++)
    {
        if (array[i] == 1)
        {
            fprintf(stderr, "%c  ", 64);
        }
        else
        {
            fprintf(stderr, "  ");
        }
        if (i % (int)(2*R) == 0)
        {
            fprintf(stderr, "\n");
        }
    }
}