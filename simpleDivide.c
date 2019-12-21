#include <stdio.h>

int simpleDivide(int x, int y, int *z, int *w);

int main(void)
{
    int a, b, c, d;
    int r;

    a = 37;
    b = 6;

    r = simpleDivide(a, b, &c, &d);

    if(r == -1)
    {
        printf("divide by zero error.\n");
    }
    else
    {
        printf("%d / %d = %d ... %d\n", a, b, c, d);
    }

    return 0;
}

int simpleDivide(int x, int y, int *z, int *w)
{
    int k;

    if (y == 0)
    {
        return -1;
    }

    k = 0;

    while (1)
    {
        if (x < y)
        {
            break;
        }
        x -= y;
        k++;
    }

    *z = k;
    *w = x;

    return 0;
}