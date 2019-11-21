#include "mulprec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を0に初期化する
//引数：struct NUMBER* a : 初期化する数字
//戻値：なし
///////////////////////////////////////////////////////////////////
void clearByZero(struct NUMBER* a)
{
	int i;
	for (i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}
	a->sign = 1;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を表示する
//引数：struct NUMBER* a : 表示する数字
//戻値：なし
///////////////////////////////////////////////////////////////////
void dispNumber(struct NUMBER* a)
{
	int i;
	if (a->sign >= 0)
	{
		putchar('+');
	}
	else
	{
		putchar('-');
	}

	for (i = KETA - 1; i >= 0; i--)
	{
		printf(" %2d", a->n[i]);        //数字確認用
	}
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数に乱数を格納する
//引数：struct NUMBER* a : 乱数を格納する数字, int k : 生成する乱数の桁数
//戻値：なし
///////////////////////////////////////////////////////////////////
void setRnd(struct NUMBER* a, int k)
{
	int i;
	//数字
	for (i = 0; i < k; i++)
	{
		a->n[i] = rand() % 10;
	}
	//符号
	a->sign = (rand() % 2 == 1) ? 1 : -1;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数をコピーする
//引数：struct NUMBER* a : コピーする数字, struct NUMBER* b : コピーされる数字
//戻値：なし
///////////////////////////////////////////////////////////////////
void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	//数字
	for (i = 0; i < KETA; i++)
	{
		b->n[i] = a->n[i];
	}
	//符号
	b->sign = a->sign;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数の絶対値を求めて格納する
//引数：struct NUMBER* a : 絶対値を求める数字, int k : 絶対値を格納する数字
//戻値：なし
///////////////////////////////////////////////////////////////////
void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	b->sign = 1;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数が0かどうかを判別する
//引数：struct NUMBER* a : 判別する数字
//戻値：0のとき : 0, それ以外のとき : -1
///////////////////////////////////////////////////////////////////
int isZero(struct NUMBER* a)
{
	if (a->sign == -1)
	{
		return -1;
	}

	int i;
	for (i = 0; i < KETA; i++)
	{
		if (a->n[i] != 0)
		{
			return -1;
		}
	}

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を10倍して格納する
//引数：struct NUMBER* a : 10倍したい数字, struct NUMBER* b : 計算した値を格納する数字
//戻値：成功 : 0, 桁あふれ : -1(bの値は変化しない)
///////////////////////////////////////////////////////////////////
int mulBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;

	if (a->n[KETA - 1] != 0)
	{
		return -1;
	}

	for (i = 0; i < KETA - 1; i++)
	{
		b->n[i + 1] = a->n[i];
	}

	b->n[0] = 0;
	b->sign = a->sign;

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を10で割った商を格納する
//引数：struct NUMBER* a : 1/10にしたい数字, struct NUMBER* b : 計算した値を格納する数字
//戻値：成功 : 余り
///////////////////////////////////////////////////////////////////
int divBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	for (i = 1; i < KETA; i++)
	{
		b->n[i - 1] = a->n[i];
	}

	b->n[KETA - 1] = 0;
	b->sign = a->sign;

	return a->n[0];
}

///////////////////////////////////////////////////////////////////
//概要：多倍長変数にint型の数字を格納する
//引数：struct NUMBER* a : 格納される数字, int x : 格納したい数字
//戻値：成功 : 0, 失敗 : -1(aの値は変化しない)
///////////////////////////////////////////////////////////////////
int setInt(struct NUMBER* a, int x)
{
	int i = 1, tmp = x < 0 ? ~x + 1 : x;

	while ((tmp /= 10) > 0)
	{
		i++;
	}

	if (i > KETA)
	{
		return -1;
	}

	i = 0;
	clearByZero(a);

	if (x < 0)
	{
		x = ~x + 1/*わんちゃん*-1でもコンパイラで処理される*/, a->sign = -1;
	}
	else
	{
		a->sign = 1;
	}

	while (x > 0)
	{
		x = (x - (a->n[i++] = x % 10)) / 10;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////
//概要：多倍長変数の符号を設定する
//引数：struct NUMBER* a : 設定される数字, int x : 設定する符号(+ : 1, - : -1)
//戻値：成功 : 0, 失敗 : -1(aの符号は変化しない)
///////////////////////////////////////////////////////////////////
int setSign(struct NUMBER* a, int s)
{
	if (s != 1 && s != -1)
	{
		return -1;
	}
	a->sign = s;

	return 0;
}

///////////////////////////////////////////////////////////////////
//概要：多倍長変数の符号を取得する
//引数：struct NUMBER* a : 符号を取得する数字
//戻値：正 : 1, 負 : -1
///////////////////////////////////////////////////////////////////
int getSign(struct NUMBER* a)
{
	return a->sign;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの数字を比較する
//引数：struct NUMBER* a : 比較する多倍長変数(1), struct NUMBER* a : 比較する多倍長変数(2)
//戻値：a == b : 0, a > b : 1, a < b : -1
///////////////////////////////////////////////////////////////////
int numComp(struct NUMBER* a, struct NUMBER* b)
{
	int sign_a = getSign(a), sign_b = getSign(b);

	if (sign_a == 1 && sign_b == -1)
	{
		return 1;
	}

	if (sign_a == -1 && sign_b == 1)
	{
		return -1;
	}

	if (sign_a == 1 && sign_b == 1)
	{
		int i = KETA;
		while (--i >= 0)
		{
			if (a->n[i] == b->n[i])
			{
				continue;
			}

			if (a->n[i] > b->n[i])
			{
				return 1;
			}

			//if (a->n[i] < b->n[i])
			//{
			//	return 1;
			//}
			return -1;
		}
	}

	if (sign_a == -1 && sign_b == -1)
	{
		int i = KETA;
		while (--i >= 0)
		{
			if (a->n[i] == b->n[i])
			{
				continue;
			}

			if (a->n[i] > b->n[i])
			{
				return -1;
			}

			//if (a->n[i] < b->n[i])
			//{
			//	return 1;
			//}
			return 1;
		}
	}

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの和を求めてcに格納する
//引数：struct NUMBER* a : 比較する多倍長変数(1), struct NUMBER* a : 比較する多倍長変数(2)
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int add(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	int d, i = 0, carry = 0;//min...0, max...1
	struct NUMBER tmp;		//tmpを使うことで失敗時にcのデータが壊れないようにいている

	clearByZero(&tmp);

	for (i = 0; i < KETA; i++)
	{
		d = a->n[i] + b->n[i] + carry;
		tmp.n[i] = d % 10;
		carry = d / 10;
	}

	if (carry)
	{
		return -1;
	}

	copyNumber(&tmp, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//                       以下チェック用                          //
///////////////////////////////////////////////////////////////////

void check_setInt(struct NUMBER* a, int roop)
{
	int i, roopDiv100 = roop / 100;

	printf("\r%4d %%\r", 0);

	for (i = 0; i < roop; i++)
	{
		int x = rand();
		setInt(a, x);

		if (check(a, x))
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

int check(struct NUMBER* a, int x)
{
	int i;
	int a_int = 0;
	int max;
	if (KETA < 10)
	{
		max = KETA;
	}
	else
	{
		max = 10;
	}

	for (i = 0; i < max; i++)
	{
		a_int *= 10;
		a_int += a->n[max - 1 - i];
		
	}

	if (a->sign == -1)
	{
		a_int = ~a_int + 1;
	}

	//printf("a->n ---> (int) = %d, x = %d\n", a_int, x);

	if (a_int != x)
	{
		return -1;
	}
	return 0;
}