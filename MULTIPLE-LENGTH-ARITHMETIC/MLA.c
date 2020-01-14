#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"



int main(void)
{
#ifdef _DEBUG
	printf("Visual Studio Debug Mode ---\n");
#else
	printf("Standard Mode ---\n");
#endif


	srandom((unsigned)time(NULL));

	int errorCode;
	struct NUMBER a, b, c, d, e;
	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	clearByZero(&e);

	int RoopSetting_Roop = 10000;
	int RoopSetting_RndLen = 3;

	//���Z���[�v**************************************************
	if (0)
	{
		int roop_add = RoopSetting_Roop;
		printf("roop function \'add\' %d times.\n", roop_add);
		printf("--- Start ---\n");
		clockStart();
		RoopFunction_ASM(add, roop_add, RoopSetting_RndLen, None);
		double tmp = clockStop();
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//��Z���[�v**************************************************
	if (0)
	{
		int roop_mul = RoopSetting_Roop;
		printf("roop function \'mul\' %d times.\n", roop_mul);
		printf("--- Start ---\n");
		clockStart();
		RoopFunction_ASM(multiple, roop_mul, RoopSetting_RndLen, None);
		double tmp = clockStop();
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//��ZDev���[�v***********************************************
	if (0)
	{
		int roop_dev_mul = RoopSetting_Roop;
		printf("roop function \'Dev_mul\' %d times.\n", roop_dev_mul);
		printf("--- Start ---\n");
		clockStart();
		RoopFunction_ASM(Dev_multiple, roop_dev_mul, RoopSetting_RndLen, None);
		double tmp = clockStop();
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//���Z���[�v**************************************************
	if (0)
	{
		int roop_div = RoopSetting_Roop;
		printf("roop function \'div\' %d times.\n", roop_div);
		printf("--- Start ---\n");
		/*
		clockStart();
		RoopFunction_D(divide, roop_div, RoopSetting_RndLen, None);
		unsigned int tmp = clockStop();
		*/
		double tmp = FastRoopFunction_D(divide, roop_div, RoopSetting_RndLen);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//���ZDev���[�v***********************************************
	if (1)
	{
		int roop_dev_div = RoopSetting_Roop;
		printf("roop function \'Dev_div\' %d times.\n", roop_dev_div);
		printf("--- Start ---\n");
		/*
		clockStart();
		RoopFunction_D(Dev_divide, roop_dev_div, RoopSetting_RndLen, None);
		unsigned int tmp = clockStop();
		*/
		double tmp = FastRoopFunction_D(Dev_divide, roop_dev_div, RoopSetting_RndLen);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//���ZDevX���[�v**********************************************
	if (0)
	{
		int roop_devX_div = RoopSetting_Roop;
		printf("roop function \'DevX_div\' %d times.\n", roop_devX_div);
		printf("--- Start ---\n");
		/*
		clockStart();
		RoopFunction_D(Dev_divide_X, roop_devX_div, RoopSetting_RndLen, None);
		unsigned int tmp = clockStop();
		*/
		double tmp = FastRoopFunction_D(Dev_divide_X, roop_devX_div, RoopSetting_RndLen);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
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
		errorCode = multiple(&a, &b, &c);
		if (errorCode)
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
		errorCode = multiple(&a, &b, &c);
		if (errorCode)
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
		setInt(&a, 999999999);
		setInt(&b, 999999998);
		a.n[9] = 9;
		b.n[9] = 9;
		errorCode = Dev_divide(&a, &b, &c, &d);
		if (errorCode)
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
		errorCode = divide(&a, &b, &c, &d);
		if (errorCode)
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
		errorCode = power(&a, &b, &c);
		if (errorCode)
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
		errorCode = power(&a, &b, &c);
		if (errorCode)
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
		errorCode = power(&a, &b, &c);
		if (errorCode)
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
		errorCode = factorial(&a, &b);
		if (errorCode)
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
		errorCode = factorial(&a, &b);
		if (errorCode)
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
		errorCode = factorial(&a, &b);
		if (errorCode)
		{
			printf("func > factorial - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a      = ");	dispNumber(&a);	putchar('\n');
			printf("b = a! = ");	dispNumber(&b);	putchar('\n');
		}
	}

	//�ő����***************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//���퓮��
		printf("\n�ő����-���퓮��----------\n");
		setInt(&a, 1357911);
		setInt(&b, 246810);
		errorCode = gcd(&a, &b, &c);
		if (errorCode)
		{
			printf("func > gcd - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a            = ");	dispNumber(&a);	putchar('\n');
			printf("b            = ");	dispNumber(&b);	putchar('\n');
			printf("c = gcd(a,b) = ");	dispNumber(&c);	putchar('\n');
		}
	}

	//�ŏ����{��***************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//���퓮��
		printf("\n�ŏ����{��-���퓮��----------\n");
		setInt(&a, 98765);
		setInt(&b, 43210);
		errorCode = lcm(&a, &b, &c);
		if (errorCode)
		{
			printf("func > lcm - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a            = ");	dispNumber(&a);	putchar('\n');
			printf("b            = ");	dispNumber(&b);	putchar('\n');
			printf("c = lcm(a,b) = ");	dispNumber(&c);	putchar('\n');
		}
	}

	return 0;
}