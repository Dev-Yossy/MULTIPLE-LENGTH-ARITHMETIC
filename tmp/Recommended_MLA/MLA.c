#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"

//円周率計算用変数
struct NUMBER A, B, C, D, E, F, G, H, I, J, K, L, M, N, P, ans, trush;
struct BUNSU R, S, T, U, V, W, X, Y, Z;
struct NUMBER num_1, num_2, num_6;
//円周率計算用関数
int culPI();

#define ROOP_ADD		0
#define ROOP_SUB		0
#define ROOP_MUL		0
#define ROOP_D_MUL		0
#define ROOP_DIV		0
#define ROOP_D_DIV		0
#define ROOP_DX_DIV		0
#define ROOP_POW		0
#define ROOP_D_POW		0

#define ADD		0
#define SUB		0
#define MUL		0
#define DIV		0
#define POW		0
#define D_POW	0
#define FAC		0
#define GCD		0
#define LCM		0
#define PRI		0
#define SQRT	0
#define SQRT_NT 0

#define BUNSU_ADD	0
#define BUNSU_SUB	0
#define BUNSU_MUL	0
#define BUNSU_DIV	0


#define DO_PRINT	1
#define ROOP		6		//ROOP * 3 < KETAでないと不安定(RADIX=10000) 4倍がおすすめ
//#define RESULT_KETA	20		//KETA - (ROOP*6*2) > RESULT_KETA かな？ 平方根をとると有効桁は半分弱になる *4される


/*
RADIX			10000
KETA			40
ROOP			10
RESULT ...		20
*/
int main(void)
{
#ifdef _DEBUG
	printf("Visual Studio Debug Mode --- ");
#else
	printf("Standard Mode --- ");
#endif

#ifdef USE_TIME
	printf("Timer: time.h\n");
#else
	printf("Timer: sys/time.h\n");
#endif

	srandom((unsigned)time(NULL));

	/*

	if (culPI())
		printf("\n失敗...\n");
	else
		printf("\n成功 !\n");

	return 0;
	*/

	//初期設定
	MLAsetup();

	// NUMBER チェック
	int errorCode;
	struct NUMBER a, b, c, d, e;
	struct BUNSU B_a, B_b, B_c;
	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	clearByZero(&e);

	int RoopSetting_Roop = 1000;
	int RoopSetting_RndLen = 5;

	//加算ループ**************************************************
	if (ROOP_ADD)
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
	
	//減算ループ**************************************************
	if (ROOP_SUB)
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
	
	//乗算ループ**************************************************
	if (ROOP_MUL)
	{
		int roop_mul = RoopSetting_Roop;
		printf("roop function \'mul\' %d times.\n", roop_mul);
		printf("--- Start ---\n");
		clockStart();
		RoopFunction_ASM(Dev2_multiple, roop_mul, RoopSetting_RndLen, None);
		double tmp = clockStop();
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//乗算Devループ***********************************************
	if (ROOP_D_MUL)
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

	//除算ループ**************************************************
	if (ROOP_DIV)
	{
		int roop_div = RoopSetting_Roop;
		printf("roop function \'div\' %d times.\n", roop_div);
		printf("--- Start ---\n");
		
		//clockStart();
		//RoopFunction_D(divide, roop_div, RoopSetting_RndLen, None);
		//unsigned int tmp = clockStop();
		
		double tmp = FastRoopFunction_D(divide, roop_div, RoopSetting_RndLen);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//除算Devループ***********************************************
	if (ROOP_D_DIV)
	{
		int roop_dev_div = RoopSetting_Roop;
		printf("roop function \'Dev_div\' %d times.\n", roop_dev_div);
		printf("--- Start ---\n");
		
		//clockStart();
		//RoopFunction_D(Dev_divide, roop_dev_div, RoopSetting_RndLen, None);
		//unsigned int tmp = clockStop();
		
		double tmp = FastRoopFunction_D(Dev_divide, roop_dev_div, RoopSetting_RndLen);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//除算DevXループ**********************************************
	if (ROOP_DX_DIV)
	{
		int roop_devX_div = RoopSetting_Roop;
		printf("roop function \'DevX_div\' %d times.\n", roop_devX_div);
		printf("--- Start ---\n");
		
		//clockStart();
		//RoopFunction_D(Dev_divide_X, roop_devX_div, RoopSetting_RndLen, None);
		//unsigned int tmp = clockStop();
		
		double tmp = FastRoopFunction_D(Dev_divide_X, roop_devX_div, RoopSetting_RndLen);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//累乗ループ**************************************************
	if (ROOP_POW)
	{
		int roop_power = RoopSetting_Roop;
		printf("roop function \'power\' %d times.\n", roop_power);
		printf("--- Start ---\n");
		double tmp = FastRoopFunction_ASM(power, roop_power, 3);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//累乗Devループ***********************************************
	if (ROOP_D_POW)
	{
		int roop_Dev_power = RoopSetting_Roop;
		printf("roop function \'Dev_power\' %d times.\n", roop_Dev_power);
		printf("--- Start ---\n");
		double tmp = FastRoopFunction_ASM(Dev_power, roop_Dev_power, 3);
		printf("--- Done ! ---\n");
		printf("--- time = %f [ms]\n", tmp);
	}

	//減算********************************************************
	if (SUB)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//正常動作
		printf("\n減算-正常動作----------\n");
		setInt(&a, 250);
		setInt(&b, 33);
		errorCode = sub(&a, &b, &c);
		if (errorCode){
			printf("func > sub - failed.  code > %d\n", errorCode);
		}
		else{
			printf("a         = ");		dispNumber(&a);	putchar('\n');
			printf("b         = ");		dispNumber(&b);	putchar('\n');
			printf("c = a - b = ");		dispNumber(&c);	putchar('\n');
		}

		//overflow
		printf("\n減算-エラー(overflow)----------\n");
		setInt(&a, 3);
		setInt(&b, 5);
		errorCode = sub(&a, &b, &c);
		if (errorCode){
			printf("func > sub - failed.  code > %d\n", errorCode);
		}
		else{
			printf("a =         ");		dispNumber(&a);	putchar('\n');
			printf("b =         ");		dispNumber(&b);	putchar('\n');
			printf("c = a - b = ");		dispNumber(&c);	putchar('\n');
		}
	}

	//乗算********************************************************
	if (MUL)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//正常動作
		printf("\n乗算-正常動作----------\n");
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
		printf("\n乗算-エラー(overflow)----------\n");
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

	//徐算********************************************************
	if (DIV)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);
		clearByZero(&d);

		//正常動作
		printf("\n除算-正常動作----------\n");
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
		printf("\n除算-エラー(b=0)----------\n");
		setInt(&a, -1000);
		setInt(&b, 3);
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

	//累乗********************************************************
	if (POW)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//正常動作
		printf("\n累乗-正常動作----------\n");
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
		printf("\n累乗-エラー(b < 0)----------\n");
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
		printf("\n累乗-エラー(overflow)----------\n");
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
	
	//Dev累乗*****************************************************
	if (D_POW)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//正常動作
		printf("\n累乗-正常動作----------\n");
		setInt(&a, 83365332);
		setInt(&b, 13);
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
		printf("\n累乗-エラー(b < 0)----------\n");
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
		printf("\n累乗-エラー(overflow)----------\n");
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

	//階乗********************************************************
	if (FAC)
	{
		clearByZero(&a);
		clearByZero(&b);

		//正常動作
		printf("\n階乗-正常動作----------\n");
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
		printf("\n階乗-エラー(overflow)----------\n");
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
		printf("\n階乗-エラー(a<0)----------\n");
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

	//最大公約数**************************************************
	if (GCD)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//正常動作
		printf("\n最大公約数-正常動作----------\n");
		setInt(&a, -1357911);
		setInt(&b, -246810);
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

	//最小公倍数**************************************************
	if (LCM)
	{
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);

		//正常動作
		printf("\n最小公倍数-正常動作----------\n");
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

	//素数********************************************************
	if (PRI)
	{
		clearByZero(&a);

		//正常動作
		printf("\n素数-正常動作----------\n");

		int tmp = 192837437;
		while (1)
		{
			//setInt(&a, tmp);
			//if (isPrime(&a))				printf("%d,", tmp);
			//if (tmp % 100 == 0)				putchar('\n');
			//if (tmp >= 10000)				break;
			//tmp++;

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
			printf("素数判定 --> %s\n", errorCode ? "素数" : "素数でない");
			break;
		}
	}

	//平方根******************************************************
	if (SQRT)
	{
		clearByZero(&a);
		clearByZero(&b);

		//正常動作
		printf("\n平方根-正常動作----------\n");
		setRnd(&a, 10);
		setSign(&a, SIGN_PLUS);
		//setInt(&a, 333);

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
		printf("\n平方根-error----------\n");
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

	//Newton平方根************************************************
	if (SQRT_NT)
	{
		clearByZero(&a);
		clearByZero(&b);

		//正常動作
		printf("\nNewton平方根-正常動作----------\n");
		setRnd(&a, 10);
		setSign(&a, SIGN_PLUS);
		//setInt(&a, 333);
		printf("a                  = ");	dispNumber(&a);	putchar('\n');

		errorCode = sqrt_newton(&a, &b);

		if (errorCode)
		{
			printf("func > sqrt_newton - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a                  = ");	dispNumber(&a);	putchar('\n');
			printf("b = sqrt_newton(a) = ");	dispNumber(&b);	putchar('\n');
		}



		//error
		printf("\nNewton平方根-error----------\n");
		setInt(&a, -10);
		errorCode = sqrt_newton(&a, &b);

		if (errorCode)
		{
			printf("func > sqrt_newton - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("a                  = ");	dispNumber(&a);	putchar('\n');
			printf("b = sqrt_newton(a) = ");	dispNumber(&b);	putchar('\n');
		}
	}

	//分数加算****************************************************
	if (BUNSU_ADD)
	{
		B_clearByZero(&B_a);
		B_clearByZero(&B_b);
		B_clearByZero(&B_c);

		B_setInt(&B_a, -123, 456);
		B_setInt(&B_b, 987, -654);
		
		errorCode = B_add(&B_a, &B_b, &B_c);

		if (errorCode)
		{
			printf("func > B_add - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("B_a             = ");	B_dispNumber(&B_a);	putchar('\n');
			printf("B_b             = ");	B_dispNumber(&B_b);	putchar('\n');
			printf("B_c = B_a + B_b = ");	B_dispNumber(&B_c);	putchar('\n');
		}
	}

	//分数減算****************************************************
	if (BUNSU_SUB)
	{
		B_clearByZero(&B_a);
		B_clearByZero(&B_b);
		B_clearByZero(&B_c);

		B_setInt(&B_a, 123, 456);
		B_setInt(&B_b, -987, 654);

		errorCode = B_sub(&B_a, &B_b, &B_c);

		if (errorCode)
		{
			printf("func > B_sub - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("B_a             = ");	B_dispNumber(&B_a);	putchar('\n');
			printf("B_b             = ");	B_dispNumber(&B_b);	putchar('\n');
			printf("B_c = B_a - B_b = ");	B_dispNumber(&B_c);	putchar('\n');
		}
	}

	//分数乗算****************************************************
	if (BUNSU_MUL)
	{
		B_clearByZero(&B_a);
		B_clearByZero(&B_b);
		B_clearByZero(&B_c);

		B_setInt(&B_a, 123, 456);
		B_setInt(&B_b, 9871, 6542);

		errorCode = B_multiple(&B_a, &B_b, &B_c);

		if (errorCode)
		{
			printf("func > B_multiple - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("B_a             = ");	B_dispNumber(&B_a);	putchar('\n');
			printf("B_b             = ");	B_dispNumber(&B_b);	putchar('\n');
			printf("B_c = B_a * B_b = ");	B_dispNumber(&B_c);	putchar('\n');
		}
	}

	//分数除算****************************************************
	if (BUNSU_DIV)
	{
		B_clearByZero(&B_a);
		B_clearByZero(&B_b);
		B_clearByZero(&B_c);

		B_setInt(&B_a, 123, 456);
		B_setInt(&B_b, 987, 654);

		errorCode = B_divide(&B_a, &B_b, &B_c);

		if (errorCode)
		{
			printf("func > B_divide - failed.  code > %d\n", errorCode);
		}
		else
		{
			printf("B_a             = ");	B_dispNumber(&B_a);	putchar('\n');
			printf("B_b             = ");	B_dispNumber(&B_b);	putchar('\n');
			printf("B_c = B_a / B_b = ");	B_dispNumber(&B_c);	putchar('\n');
		}

		//分数約分****************************************************
		if (BUNSU_DIV)
		{
			B_clearByZero(&B_a);
			B_clearByZero(&B_b);

			B_setInt(&B_a, 7568, -7568 * 7568);

			errorCode = B_yakubun(&B_a, &B_b);

			if (errorCode)
			{
				printf("func > B_yakubun - failed.  code > %d\n", errorCode);
			}
			else
			{
				printf("B_a        = ");	B_dispNumber(&B_a);	putchar('\n');
				printf("B_b <- B_a = ");	B_dispNumber(&B_b);	putchar('\n');
			}
		}
	}

	return 0;

}


/*
  2   Ａ    Ｐ  １   Ｃ   Ｄ   Ｅ   Ｆ   Ｇ
PI  = ― × Σ  ― ( ― - ― - ― - ― + ― )  =  Ｒ × Σ  Ｓ ( Ｔ - Ｕ - Ｖ - Ｗ + Ｘ )  =  Ｒ × Σ  Ｓ × Ｔ  =  Ｒ × Σ  Ｓ  =  Ｒ × Ｙ
      Ｂ   Ｎ=0 Ｈ   Ｉ   Ｊ   Ｋ   Ｌ   Ｍ
*/
int culPI(void)
{
#if DO_PRINT
	printf("Setting Up ... ");
#endif // DO_PRINT

	timeStart();

	MLAsetup();

	int i = 0, flg = 0;

	clearByZero(&ans);
	clearByZero(&trush);

	clearByZero(&A);
	clearByZero(&B);
	clearByZero(&C);
	clearByZero(&D);
	clearByZero(&E);
	clearByZero(&F);
	clearByZero(&G);
	clearByZero(&H);
	clearByZero(&I);
	clearByZero(&J);
	clearByZero(&K);
	clearByZero(&L);
	clearByZero(&M);

	clearByZero(&N);
	clearByZero(&P);
	
	B_clearByZero(&R);
	B_clearByZero(&S);
	B_clearByZero(&T);
	B_clearByZero(&U);
	B_clearByZero(&V);
	B_clearByZero(&W);
	B_clearByZero(&X);
	B_clearByZero(&Y);
	B_setInt(&Y, 0, 1);		// 0 / 0 だと不具合が起きる(そもそも0/0のまま計算をしてはならない)
	B_clearByZero(&Z);


	//num_1
	flg += setInt(&num_1, 1);
	//num_2
	flg += setInt(&num_2, 2);
	//num_6
	flg += setInt(&num_6, 6);

	// A
	flg += setInt(&A, 9);
	// B
	flg += setInt(&B, 8);
	// C
	flg += setInt(&C, 16);
	// D
	flg += setInt(&D, 24);
	// E
	flg += setInt(&E, 8);
	// F
	flg += setInt(&F, 6);
	// G
	flg += setInt(&G, 1);
	// N ループ回数
	flg += setInt(&N, 0);
	// P ループ最大回数
	flg += setInt(&P, ROOP);
	// R = A / B
	NtoB_copyNumber(&A, &B, &R);

	if (flg){
		printf(" Error: where.CulPI.Setup\n");
		printf("flg = %d\n", flg);
		return -1;
	}

#if DO_PRINT
	printf("Done !\n\rRoop \'%d\' times ... %d / %d", ROOP, i, ROOP);
#endif // DO_PRINT
	
	while (numComp(&N, &P) < 0){

		clearByZero(&H);
		clearByZero(&I);
		clearByZero(&J);
		clearByZero(&K);
		clearByZero(&L);
		clearByZero(&M);
		B_clearByZero(&S);
		B_clearByZero(&T);
		B_clearByZero(&U);
		B_clearByZero(&V);
		B_clearByZero(&W);
		B_clearByZero(&X);

		//処理---ここから---
		// H
		flg += setInt(&H, 64);					// 64 ... H
		flg += Dev_power(&H, &N, &H);			// 64^n ... H
		// 6 n + #
		flg += Dev_multiple(&num_6, &N, &I);	// 6n
		flg += increment(&I, &I);				// 6n+1 ... I
		flg += increment(&I, &J);				// 6n+2 ... J
		flg += increment(&J, &K);				// 6n+3 ... K
		flg += increment(&K, &L);				// 6n+4 ... L
		flg += increment(&L, &M);				// 6n+5 ... M

		// I
		flg += Dev_power(&I, &num_2, &I);		// (6n+1)^2 ... I
		// J
		flg += Dev_power(&J, &num_2, &J);		// (6n+2)^2 ... J
		// K
		flg += Dev_power(&K, &num_2, &K);		// (6n+3)^2 ... K
		// L
		flg += Dev_power(&L, &num_2, &L);		// (6n+4)^2 ... L
		// M
		flg += Dev_power(&M, &num_2, &M);		// (6n+5)^2 ... M

		//1/H -> S
		NtoB_copyNumber(&num_1, &H, &S);
		//C/I -> T
		NtoB_copyNumber(&C, &I, &T);
		//D/J -> U
		NtoB_copyNumber(&D, &J, &U);
		//E/K -> V
		NtoB_copyNumber(&E, &K, &V);
		//F/L -> W
		NtoB_copyNumber(&F, &L, &W);
		//G/M -> X
		NtoB_copyNumber(&G, &M, &X);

		// T - U - V - W + X -> T
		flg += B_sub(&T, &U, &T);
		flg += B_sub(&T, &V, &T);
		flg += B_sub(&T, &W, &T);
		flg += B_add(&T, &X, &T);

		//S * T -> S
		flg += B_multiple(&S, &T, &S);

		//処理---ここまで---

		//ΣS -> Y
		flg += B_add(&Y, &S, &Y);
		//N++
		flg += increment(&N, &N);
		if (flg)
		{
			printf(" ... Error: where.CulPI.Roop\n");
			printf("\nflg = %d\n", flg);
			return -1;
		}

#if DO_PRINT
		printf("\rRoop \'%d\' times ... %d / %d", ROOP, ++i, ROOP);
#endif // DO_PRINT
	}

#if DO_PRINT
	printf(" ... Done !\nStart \'Last Calculation\' ... 0 / 4");
#endif // DO_PRINT




	// R * Y -> Z ... PI^2
	flg = B_multiple(&R, &Y, &Z);

	if (flg) {
		printf("Error: where.CulPI.LastCalculation.B_multiple )\n");
		printf("flg = %d\n", flg);
		return -1;
	}
#if DO_PRINT
	printf("\b\b\b\b\b1 / 4");
#endif // DO_PRINT




	//有効桁設定
	/*
	for (i = 0; i < RESULT_KETA; i++)		//平方根をとると有効桁は半分になる
		if (flg += mulBy10(&Z.bunshi, &Z.bunshi))
			break;
	*/
	while (1){
		i = mulBy10(&Z.bunshi, &Z.bunshi);
		if (i == -1)
			break;
		if (i == -2)
			flg = i;
	}

	if (flg) {
		printf("Error: where.CulPI.LastCalculation.mulBy10 )\n");
		printf("flg = %d\n", flg);
		return -1;
	}

#if DO_PRINT
	printf("\b\b\b\b\b2 / 4");
#endif // DO_PRINT




	//分数から実数への変換
	flg = B_FractionToReal(&Z, &ans);

	if (flg) {
		printf("Error: where.CulPI.LastCalculation.B_FractionToReal )\n");
		printf("flg = %d\n", flg);
		return -1;
	}

#if DO_PRINT
	printf("\b\b\b\b\b3 / 4");
#endif // DO_PRINT



	//ans / (2 * 10^(KETA/2)) ... h
	// h > sqrt(ans) なたよい
	struct NUMBER ans_To_h, two;
	clearByZero(&ans_To_h);
	clearByZero(&two);
	setInt(&two, 2);
	copyNumber(&ans, &ans_To_h);
	for (i = 0; i < KETA/4+ROOP/5; i++)
		divBy10(&ans_To_h, &ans_To_h);
	Dev_divide(&ans_To_h, &two, &ans_To_h, &trush);

	//平方根
	flg += sqrt_newton(&ans, &ans);

	if (flg){
		printf("Error: where.CulPI.LastCalculation )\n");
		printf("flg = %d\n", flg);
		return -1;
	}

#if DO_PRINT
	printf("\b\b\b\b\b4 / 4 ... Done !\n");
#endif // DO_PRINT

	printf("PI = ");	dispNumber(&ans);
	printf("\n\ntime: %d [s]\n", timeStop());

	return 0;
}
