#include <stdio.h>

#define true 1
#define false 0


typedef struct
{
    int (*print)(int a);
} Object;

int printer(int a);



int printer(int a)
{
    printf("%d", a + 1);
}


int main(void)
{
    Object.print(3);

    return 0;
}