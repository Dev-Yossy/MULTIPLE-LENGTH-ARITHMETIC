#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"

void check_setInt(struct NUMBER* a, int roop);

int main(void)
{
	srand((unsigned)time(NULL));

	struct NUMBER a, b;

	clearByZero(&a);
	clearByZero(&b);

	/*
	
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

	*/

	check_setInt(&a, 10000000);

	return 0;
}


void check_setInt(struct NUMBER *a, int roop)
{
	int i, roopDiv100 = roop / 100;

	printf("\r%4d %%\r", 0);

	for (i = 0; i < roop; i++)
	{
		int x = rand();
		setInt(a, x);

		if (check(a, x+1))
		{
			printf("a = ");
			dispNumber(a);
			putchar('\n');
			printf("x = %d\n", x);
		}

		if ((i + 1) % roopDiv100 == 0)
		{
			printf("\r%4d %%\r", (i + 1) / roopDiv100);
		}
	}
	printf("\r%4d %% --- Done !\n", 100);
}
