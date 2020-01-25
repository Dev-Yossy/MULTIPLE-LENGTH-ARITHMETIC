/////////////////////////////////////////////////////////////////////////////////////
// * �R���p�C�����I�v�V���� (-D [option], -D[option], -D [option=data], -D[option=data]):
//       _DO_PRINT_ : �R���p�C�����ɉ~�����v�ZLOG(DO_PRINT)�̒l��ύX���邱�Ƃ��ł���.
//           - �͈� : 0, ��0
/////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"
#include "culPI.h"

#define ROOP_ADD		0
#define ROOP_SUB		0
#define ROOP_MUL		0
#define ROOP_D_MUL		0
#define ROOP_DIV		0
#define ROOP_D_DIV		0
#define ROOP_DX_DIV		0
#define ROOP_POW		0
#define ROOP_D_POW		0

#define ADD				0
#define SUB				0
#define MUL				0
#define DIV				0
#define POW				0
#define D_POW			0
#define FAC				0
#define GCD				0
#define LCM				0
#define PRI				0
#define SQRT			0
#define SQRT_NT 		0

#define BUNSU_ADD		0
#define BUNSU_SUB		0
#define BUNSU_MUL		0
#define BUNSU_DIV		0

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

	/*	*/
	//�����ݒ�
	MLAsetup();

	if (culPI())
		printf("\nFailed...\n");
	else
		printf("\nSuccessfully Completed !\n");

	return 0;


	/*
		//�����ݒ�
		MLAsetup();

		// NUMBER �`�F�b�N
		int errorCode;
		struct NUMBER a, b, c, d, e;
		struct BUNSU B_a, B_b, B_c;
		clearByZero(&a);
		clearByZero(&b);
		clearByZero(&c);
		clearByZero(&d);
		clearByZero(&e);

		int RoopSetting_Roop = 10000;
		int RoopSetting_RndLen = 15;

		//���Z���[�v**************************************************
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

		//���Z���[�v**************************************************
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

		//��Z���[�v**************************************************
		if (ROOP_MUL)
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

		//���Z���[�v**************************************************
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

		//���ZDev���[�v***********************************************
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

		//���ZDevX���[�v**********************************************
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

		//�ݏ惋�[�v**************************************************
		if (ROOP_POW)
		{
			int roop_power = RoopSetting_Roop;
			printf("roop function \'power\' %d times.\n", roop_power);
			printf("--- Start ---\n");
			double tmp = FastRoopFunction_ASM(power, roop_power, 3);
			printf("--- Done ! ---\n");
			printf("--- time = %f [ms]\n", tmp);
		}

		//�ݏ�Dev���[�v***********************************************
		if (ROOP_D_POW)
		{
			int roop_Dev_power = RoopSetting_Roop;
			printf("roop function \'Dev_power\' %d times.\n", roop_Dev_power);
			printf("--- Start ---\n");
			double tmp = FastRoopFunction_ASM(Dev_power, roop_Dev_power, 3);
			printf("--- Done ! ---\n");
			printf("--- time = %f [ms]\n", tmp);
		}

		//���Z********************************************************
		if (SUB)
		{
			clearByZero(&a);
			clearByZero(&b);
			clearByZero(&c);

			//���퓮��
			printf("\n���Z-���퓮��----------\n");
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
			printf("\n���Z-�G���[(overflow)----------\n");
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

		//��Z********************************************************
		if (MUL)
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
		if (DIV)
		{
			clearByZero(&a);
			clearByZero(&b);
			clearByZero(&c);
			clearByZero(&d);

			//���퓮��
			printf("\n���Z-���퓮��----------\n");
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
			printf("\n���Z-�G���[(b=0)----------\n");
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

		//�ݏ�********************************************************
		if (POW)
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

		//Dev�ݏ�*****************************************************
		if (D_POW)
		{
			clearByZero(&a);
			clearByZero(&b);
			clearByZero(&c);

			//���퓮��
			printf("\n�ݏ�-���퓮��----------\n");
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
			printf("\n�ݏ�-�G���[(b < 0)----------\n");
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
			printf("\n�ݏ�-�G���[(overflow)----------\n");
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

		//�K��********************************************************
		if (FAC)
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
			printf("\n�K��-�G���[(overflow)----------\n");
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
			printf("\n�K��-�G���[(a<0)----------\n");
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

		//�ő����**************************************************
		if (GCD)
		{
			clearByZero(&a);
			clearByZero(&b);
			clearByZero(&c);

			//���퓮��
			printf("\n�ő����-���퓮��----------\n");
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

		//�ŏ����{��**************************************************
		if (LCM)
		{
			clearByZero(&a);
			clearByZero(&b);
			clearByZero(&c);

			//���퓮��
			printf("\n�ŏ����{��-���퓮��----------\n");
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

		//�f��********************************************************
		if (PRI)
		{
			clearByZero(&a);

			//���퓮��
			printf("\n�f��-���퓮��----------\n");

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
				printf("�f������ --> %s\n", errorCode ? "�f��" : "�f���łȂ�");
				break;
			}
		}

		//������******************************************************
		if (SQRT)
		{
			clearByZero(&a);
			clearByZero(&b);

			//���퓮��
			printf("\n������-���퓮��----------\n");
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
			printf("\n������-error----------\n");
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

		//Newton������************************************************
		if (SQRT_NT)
		{
			clearByZero(&a);
			clearByZero(&b);

			//���퓮��
			printf("\nNewton������-���퓮��----------\n");
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
			printf("\nNewton������-error----------\n");
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

		//�������Z****************************************************
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

		//�������Z****************************************************
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

		//������Z****************************************************
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

		//�������Z****************************************************
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

			//������****************************************************
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
	*/
}
