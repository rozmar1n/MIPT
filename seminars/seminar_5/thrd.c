#include"stdio.h"
#include"math.h"

struct point 
{
    int x;
    int y;
};
struct circle
{
    struct point cx;
    int r;
};

void init_circle(struct circle* my_ccrl1, struct circle* my_ccrl2);
void init_point(struct point *my_pt);
void pt_exam(struct circle cc1, struct circle cc2, struct point pt);

int main()
{
    struct circle circle_1 = {{0, 0}, 0};
    struct circle circle_2 = {{0, 0}, 0};
    struct point pt = {0, 0};

    init_circle(&circle_1, &circle_2);

    init_point(&pt);
    printf("point: %d, %d", pt.x, pt.y);
    pt_exam(circle_1, circle_2, pt);

}

void init_circle(struct circle* my_ccrl1, struct circle* my_ccrl2)
{
    my_ccrl1 ->cx.x = 4;
    my_ccrl1 ->cx.y = 2;
    my_ccrl1 ->r = 4;

    my_ccrl2 ->cx.x = 10;
    my_ccrl2 ->cx.y = 4;
    my_ccrl2 ->r = 6;
}

void init_point(struct point *my_pt)
{
    printf("Enter the coordinates of the point: ");
    scanf("%d %d", &my_pt->x, &my_pt->y);
}

void pt_exam(struct circle cc1, struct circle cc2, struct point pt)
{
    char result = 0;
    
    if ((pt.x - cc1.cx.x)*(pt.x - cc1.cx.x) + (pt.y - cc1.cx.y)*(pt.y - cc1.cx.y) < cc1.r*cc1.r)
    {
        result += 1;
        printf("in the first\n");
    }

    if ((pt.x - cc2.cx.x)*(pt.x - cc2.cx.x) + (pt.y - cc2.cx.y)*(pt.y - cc2.cx.y) < cc2.r*cc2.r)
    {
        result += 2;
        printf("in the second\n");
    }

    switch (result)
    {
    case 0:
        printf("the point is outside the circles\n");
        break;

    case 1:
        printf("the point is inside 1 circle\n");
        break;
    
    case 2:
        printf("the point is inside 2 circle\n");
        break;
    
    case 3:
        printf("the point is at the intersection of the circles\n");
        break;

    default:
        printf("ZALUPA");
        break;
    }
}