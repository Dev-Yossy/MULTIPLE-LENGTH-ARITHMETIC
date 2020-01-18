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
	int RoopSetting_RndLen = 10;

	//‰ÁZƒ‹[ƒv**************************************************
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
	
	//Œ¸Zƒ‹[ƒv**************************************************
	if (0)
	{
		int roop_sub = RoopSetting_Roop;
		printf("roop function \'sub\' %d times.\n", roop_sub);
		printf("--- Start ---\n");
		clockStart();
		RoopFunction_ASM(sub, roop_sub, RoopSetting_RndLen, None);
		double tmp = clockStop();
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}
	
	//æZƒ‹[ƒv**************************************************
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

	//æZDevƒ‹[ƒv***********************************************
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

	//œZƒ‹[ƒv**************************************************
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

	//œZDevƒ‹[ƒv***********************************************
	if (0)
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

	//œZDevXƒ‹[ƒv**********************************************
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

	//—İæƒ‹[ƒv**************************************************
	if (0)
	{
		int roop_power = RoopSetting_Roop;
		printf("roop function \'power\' %d times.\n", roop_power);
		printf("--- Start ---\n");
		double tmp = FastRoopFunction_ASM(power, roop_power, 3);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//—İæDevƒ‹[ƒv***********************************************
	if (0)
	{
		int roop_Dev_power = RoopSetting_Roop;
		printf("roop function \'Dev_power\' %d times.\n", roop_Dev_power);
		printf("--- Start ---\n");
		double tmp = FastRoopFunction_ASM(Dev_power, roop_Dev_power, 3);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//æZ********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\næZ-³í“®ì----------\n");
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
		printf("\næZ-ƒGƒ‰[(overflow)----------\n");
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

	//™Z********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);
		clearByZero(&d);

		//³í“®ì
		printf("\nœZ-³í“®ì----------\n");
		//setInt(&a, 999999999);
		//141421356173205082236067931417
		int tmp;
		setInt(&a, 141421356);
		for (tmp = 0; tmp < 9; tmp++)
			mulBy10(&a, &a);
		setInt(&c, 173205082);
		add(&a, &c, &a);
		for (tmp = 0; tmp < 9; tmp++)
			mulBy10(&a, &a);
		setInt(&c, 236067931);
		add(&a, &c, &a);
		for (tmp = 0; tmp < 3; tmp++)
			mulBy10(&a, &a);
		setInt(&c, 419);
		add(&a, &c, &a);


		setInt(&b, 7);
		//a.n[9] = 9;
		//b.n[9] = 9;
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
		printf("\nœZ-ƒGƒ‰[(b=0)----------\n");
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

	//—İæ********************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\n—İæ-³í“®ì----------\n");
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
		printf("\n—İæ-ƒGƒ‰[(b < 0)----------\n");
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
		printf("\n—İæ-ƒGƒ‰[(overflow)----------\n");
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
	
	//Dev—İæ*****************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\n—İæ-³í“®ì----------\n");
		setInt(&a, 3);
		setInt(&b, 5);
		errorCode = Dev_power(&a, &b, &c);
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
		printf("\n—İæ-ƒGƒ‰[(b < 0)----------\n");
		setInt(&b, -3);
		errorCode = Dev_power(&a, &b, &c);
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
		printf("\n—İæ-ƒGƒ‰[(overflow)----------\n");
		setInt(&a, 1000);
		setInt(&b, 10);
		errorCode = Dev_power(&a, &b, &c);
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
		printf("\nŠKæ-ƒGƒ‰[(overflow)----------\n");
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
		printf("\nŠKæ-ƒGƒ‰[(a<0)----------\n");
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

	//Å‘åŒö–ñ”**************************************************
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

	//Å¬Œö”{”**************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//³í“®ì
		printf("\nÅ¬Œö”{”-³í“®ì----------\n");
		//setInt(&a, 98765);
		//setInt(&b, 43210);
		setInt(&a, -987654321);
		setInt(&b, 0);
		errorCode = lcm(&a, &b, &c);
		//errorCode = Dev_lcm(&a, &b, &c);

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

	//‘f”********************************************************
	if (0)
	{
		clearByZero(&a);

		//³í“®ì
		printf("\n‘f”-³í“®ì----------\n");

		int tmp = 192837437;
		while (1)
		{
			/*
			setInt(&a, tmp);
			if (isPrime(&a))				printf("%d,", tmp);
			if (tmp % 100 == 0)				putchar('\n');
			if (tmp >= 10000)				break;
			tmp++;
			*/

			//141421356173205082236067931419
			setInt(&a, 141421356);
			for (tmp = 0; tmp < 9; tmp++)
				mulBy10(&a, &a);
			setInt(&c, 173205082);
			add(&a, &c, &a);
			for (tmp = 0; tmp < 9; tmp++)
				mulBy10(&a, &a);
			setInt(&c, 236067931);
			add(&a, &c, &a);
			for (tmp = 0; tmp < 3; tmp++)
				mulBy10(&a, &a);
			setInt(&c, 419);
			add(&a, &c, &a);


			printf("a = ");	dispNumber(&a);	putchar('\n');

			errorCode = isPrime(&a);
			printf("‘f””»’è --> %s\n", errorCode ? "‘f”" : "‘f”‚Å‚È‚¢");
			break;
		}
	}

	//•½•ûª******************************************************
	if (0)
	{
		clearByZero(&a);
		clearByZero(&b);

		//³í“®ì
		printf("\n•½•ûª-³í“®ì----------\n");
		setInt(&a, 264196);

		errorCode = squareroot(&a, &b);

		if (errorCode)
		{
			printf("func > squareroot - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a           = ");	dispNumber(&a);	putchar('\n');
			printf("b = sqrt(a) = ");	dispNumber(&b);	putchar('\n');
		}
		


		//error
		printf("\n•½•ûª-error----------\n");
		setInt(&a, -10);
		errorCode = squareroot(&a, &b);

		if (errorCode)
		{
			printf("func > squareroot - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a           = ");	dispNumber(&a);	putchar('\n');
			printf("b = sqrt(a) = ");	dispNumber(&b);	putchar('\n');
		}
	}

	return 0;
}