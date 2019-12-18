#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"



int main(void)
{
	srand((unsigned)time(NULL));

	struct NUMBER a, b, c, d, e;

	int roop_add = 100000;
	printf("roop function \'add\' %d times.\n", roop_add);
	printf("--- Start ---\n");
	RoopFunction_Cul(add, roop_add, 10, None);
	printf("--- Done ! ---\n");

	int roop_mul = 100000;
	printf("roop function \'mul\' %d times.\n", roop_mul);
	printf("--- Start ---\n");
	RoopFunction_Cul(multiple, roop_mul, 10, None);
	printf("--- Done ! ---\n");

	int roop_dev_mul = 100000;
	printf("roop function \'Dev_mul\' %d times.\n", roop_dev_mul);
	printf("--- Start ---\n");
	RoopFunction_Cul(Dev_multiple, roop_dev_mul, 10, None);
	printf("--- Done ! ---\n");

	int roop_div = 100000;
	printf("roop function \'div\' %d times.\n", roop_div);
	printf("--- Start ---\n");
	RoopFunction_Cul(divide, roop_div, 10, All);
	printf("--- Done ! ---\n");



	/*
	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	setInt(&a, 12345);
	setInt(&b, -2);
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	multiple(&a, &b, &c);
	printf("c(Nor) = ");	dispNumber(&c);	putchar('\n');
	Dev_multiple(&a, &b, &c);
	printf("c(Dev) = ");	dispNumber(&c);	putchar('\n');
	*/

	/*
	setInt(&a, -37);
	setInt(&b, -6);
	clearByZero(&c);
	clearByZero(&d);
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	switch (divide(&a, &b, &c, &d))
	{
	case 0:
		break;
	case -1:
		printf("divide by zero error.\n");
		break;
	case 1:
		printf("uncollectable error.\n");
		break;
	}
	printf("c = ");	dispNumber(&c);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');
	*/

	return 0;
}