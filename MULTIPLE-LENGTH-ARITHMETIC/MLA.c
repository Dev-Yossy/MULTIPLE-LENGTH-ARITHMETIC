#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"

int main(void)
{
	srand((unsigned)time(NULL));

	struct NUMBER a, b;

	clearByZero(&a);
	clearByZero(&b);

	setRnd(&a, 3);

	printf("a = ");
	dispNumber(&a);
	putchar('\n');

	mulBy10(&a, &b);

	printf("b = ");
	dispNumber(&b);
	putchar('\n');

	divBy10(&a, &b);

	printf("b = ");
	dispNumber(&b);
	putchar('\n');

	setInt(&a, 123);
	printf("a = ");
	dispNumber(&a);
	putchar('\n');

	return 0;
}

