#include<stdio.h>

struct point
{
    int x;
    int y;
};

int main(void)
{
    struct point my_point = {-7, 6};
    if (my_point.y < ((-my_point.x + 8)/2) && my_point.y > (-my_point.x/2) && my_point.x > (-8) && my_point.x < (-4))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}