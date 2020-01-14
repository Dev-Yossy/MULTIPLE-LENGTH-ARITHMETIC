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

	//‰ÁŽZƒ‹[ƒv**************************************************
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

	//æŽZƒ‹[ƒv**************************************************
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

	//æŽZDevƒ‹[ƒv***********************************************
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

	//œŽZƒ‹[ƒv**************************************************
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

	//œŽZDevƒ‹[ƒv***********************************************
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

	//œŽZDevXƒ‹[ƒv**********************************************
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

	//æŽZ********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\næŽZ-³í“®ì----------\n");
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
		printf("\næŽZ-ƒGƒ‰[(overflow)----------\n");
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

	//™ŽZ********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);
		clearByZero(&d);

		//³í“®ì
		printf("\nœŽZ-³í“®ì----------\n");
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
		printf("\nœŽZ-ƒGƒ‰[(b=0)----------\n");
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

	//—Ýæ********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\n—Ýæ-³í“®ì----------\n");
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
		printf("\n—Ýæ-ƒGƒ‰[(b < 0)----------\n");
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
		printf("\n—Ýæ-ƒGƒ‰[(overflow)----------\n");
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

	//ŠKæ********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);

		//³í“®ì
		printf("\nŠKæ-³í“®ì----------\n");
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
		printf("\n—Ýæ - ƒGƒ‰[(overflow)----------\n");
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
		printf("\n—Ýæ - ƒGƒ‰[(a<0)----------\n");
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

	//Å‘åŒö–ñ”***************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\nÅ‘åŒö–ñ”-³í“®ì----------\n");
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

	//Å¬Œö”{”***************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\nÅ¬Œö”{”-³í“®ì----------\n");
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