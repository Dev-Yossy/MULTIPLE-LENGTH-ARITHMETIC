#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"



int main(void)
{
	srand((unsigned)time(NULL));

	struct NUMBER a, b, c, d, e;
	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	clearByZero(&e);


	//加算***********************************************************
	int roop_add = 0;//100000;
	printf("roop function \'add\' %d times.\n", roop_add);
	printf("--- Start ---\n");
	RoopFunction_ASM(add, roop_add, 10, None);
	printf("--- Done ! ---\n");

	//乗算***********************************************************
	int roop_mul = 0;//100000;
	printf("roop function \'mul\' %d times.\n", roop_mul);
	printf("--- Start ---\n");
	RoopFunction_ASM(multiple, roop_mul, 10, None);
	printf("--- Done ! ---\n");

	//乗算***********************************************************
	int roop_dev_mul = 0;//100000;
	printf("roop function \'Dev_mul\' %d times.\n", roop_dev_mul);
	printf("--- Start ---\n");
	RoopFunction_ASM(Dev_multiple, roop_dev_mul, 10, None);
	printf("--- Done ! ---\n");

	//除算***********************************************************
	int roop_div = 0;//100000;
	printf("roop function \'div\' %d times.\n", roop_div);
	printf("--- Start ---\n");
	RoopFunction_D(divide, roop_div, 10, All);
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

	//階乗********************************************************
	setInt(&a, 5);
	if(factorial(&a, &b))
		printf("Failed ...\n");
	else
		printf("Success !\n");
	
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("a! = ");	dispNumber(&b);	putchar('\n');

	return 0;
}