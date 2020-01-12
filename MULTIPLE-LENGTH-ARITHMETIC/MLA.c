#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"

int main(void)
{
	srand((unsigned)time(NULL));

	int errorCode;
	struct NUMBER a, b, c, d, e;
	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	clearByZero(&e);


	//���Z���[�v**************************************************
	if (0)
	{
		int roop_add = 100000;
		printf("roop function \'add\' %d times.\n", roop_add);
		printf("--- Start ---\n");
		RoopFunction_ASM(add, roop_add, 10, None);
		printf("--- Done ! ---\n");
	}

	//��Z���[�v**************************************************
	if (0)
	{
		int roop_mul = 100000;
		printf("roop function \'mul\' %d times.\n", roop_mul);
		printf("--- Start ---\n");
		RoopFunction_ASM(multiple, roop_mul, 10, None);
		printf("--- Done ! ---\n");
	}

	//��ZDev���[�v***********************************************
	if (0)
	{
		int roop_dev_mul = 100000;
		printf("roop function \'Dev_mul\' %d times.\n", roop_dev_mul);
		printf("--- Start ---\n");
		RoopFunction_ASM(Dev_multiple, roop_dev_mul, 10, None);
		printf("--- Done ! ---\n");
	}

	//���Z���[�v**************************************************
	if (0)
	{
		int roop_div = 100000;
		printf("roop function \'div\' %d times.\n", roop_div);
		printf("--- Start ---\n");
		RoopFunction_D(divide, roop_div, 10, All);
		printf("--- Done ! ---\n");
	}

	//��Z********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//���퓮��
		printf("\n��Z-���퓮��----------\n");
		setInt(&a, 250);
		setInt(&b, 33);
		if (errorCode = multiple(&a, &b, &c))
		{
			printf("func > multiple - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a         = ");		dispNumber(&a);	putchar('\n');
			printf("b         = ");		dispNumber(&b);	putchar('\n');
			printf("c = a * b = ");		dispNumber(&c);	putchar('\n');
		}

		//overflow
		printf("\n��Z-�G���[(overflow)----------\n");
		setRnd(&a, 18);
		setInt(&b, 999999999);
		if (errorCode = multiple(&a, &b, &c))
		{
			printf("func > multiple - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a =         ");		dispNumber(&a);	putchar('\n');
			printf("b =         ");		dispNumber(&b);	putchar('\n');
			printf("c = a * b = ");		dispNumber(&c);	putchar('\n');
		}
	}

	//���Z********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);
		clearByZero(&d);

		//���퓮��
		printf("\n���Z-���퓮��----------\n");
		setInt(&a, -1000);
		setInt(&b, 3);
		if (errorCode = divide(&a, &b, &c, &d))
		{
			printf("func > divide - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a         = ");		dispNumber(&a);	putchar('\n');
			printf("b         = ");		dispNumber(&b);	putchar('\n');
			printf("c = a / b = ");		dispNumber(&c);	putchar('\n');
			printf("d = a %% b = ");	dispNumber(&d);	putchar('\n');
		}

		//b = 0
		printf("\n���Z-�G���[(b=0)----------\n");
		setInt(&a, 1000);
		setInt(&b, 0);
		if (errorCode = divide(&a, &b, &c, &d))
		{
			printf("func > divide - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a =         ");		dispNumber(&a);	putchar('\n');
			printf("b =         ");		dispNumber(&b);	putchar('\n');
			printf("c = a / b = ");		dispNumber(&c);	putchar('\n');
			printf("d = a %% b = ");	dispNumber(&d);	putchar('\n');
		}
	}

	//�ݏ�********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//���퓮��
		printf("\n�ݏ�-���퓮��----------\n");
		setInt(&a, 3);
		setInt(&b, 5);
		if (errorCode = power(&a, &b, &c))
		{
			printf("func > power - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a       = ");	dispNumber(&a);	putchar('\n');
			printf("b       = ");	dispNumber(&b);	putchar('\n');
			printf("c = a^b = ");	dispNumber(&c);	putchar('\n');
		}

		//b < 0
		printf("\n�ݏ�-�G���[(b < 0)----------\n");
		setInt(&b, -3);
		if (errorCode = power(&a, &b, &c))
		{
			printf("func > power - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a       = ");	dispNumber(&a);	putchar('\n');
			printf("b       = ");	dispNumber(&b);	putchar('\n');
			printf("c = a^b = ");	dispNumber(&c);	putchar('\n');
		}

		//overflow
		printf("\n�ݏ�-�G���[(overflow)----------\n");
		setInt(&a, 1000);
		setInt(&b, 10);
		if (errorCode = power(&a, &b, &c))
		{
			printf("func > power - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a       = ");	dispNumber(&a);	putchar('\n');
			printf("b       = ");	dispNumber(&b);	putchar('\n');
			printf("c = a^b = ");	dispNumber(&c);	putchar('\n');
		}
	}

	//�K��********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);

		//���퓮��
		printf("\n�K��-���퓮��----------\n");
		setInt(&a, 5);
		if (errorCode = factorial(&a, &b))
		{
			printf("func > factorial - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a      = ");	dispNumber(&a);	putchar('\n');
			printf("b = a! = ");	dispNumber(&b);	putchar('\n');
		}

		//overflow
		printf("\n�ݏ� - �G���[(overflow)----------\n");
		setInt(&a, 1000);
		if (errorCode = factorial(&a, &b))
		{
			printf("func > factorial - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a      = ");	dispNumber(&a);	putchar('\n');
			printf("b = a! = ");	dispNumber(&b);	putchar('\n');
		}

		//a<0
		printf("\n�ݏ� - �G���[(a<0)----------\n");
		setInt(&a, -3);
		if (errorCode = factorial(&a, &b))
		{
			printf("func > factorial - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a      = ");	dispNumber(&a);	putchar('\n');
			printf("b = a! = ");	dispNumber(&b);	putchar('\n');
		}
	}



	return 0;
}