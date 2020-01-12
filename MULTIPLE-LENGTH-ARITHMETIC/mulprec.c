#include "mulprec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////
//概要：多倍長変数を0に初期化する
//引数：struct NUMBER* a : 初期化する多倍長変数
//戻値：なし
///////////////////////////////////////////////////////////////////
void clearByZero(struct NUMBER* a)
{
	int i;
	for (i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}
	setSign(a, 1);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を表示する
//引数：struct NUMBER* a : 表示する多倍長変数
//戻値：なし
///////////////////////////////////////////////////////////////////
void dispNumber(struct NUMBER* a)
{
	int i;
	if (getSign(a) >= 0)
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
//引数：struct NUMBER* a : 乱数を格納する多倍長変数, int k : 生成する乱数の桁数
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
	setSign(a, (rand() % 2 == 1) ? 1 : -1);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数をコピーする
//引数：struct NUMBER* a : コピー元の多倍長変数, struct NUMBER* b : コピー先の多倍長変数
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
	setSign(b, getSign(a));
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数の絶対値を求めて格納する
//引数：struct NUMBER* a : 絶対値を求める多倍長変数, struct NUMBER* b : 絶対値を格納する多倍長変数
//戻値：なし
///////////////////////////////////////////////////////////////////
void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	setSign(b, 1);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数が0かどうかを判別する
//引数：struct NUMBER* a : 判別する多倍長変数
//戻値：0のとき : 0, それ以外のとき : -1
///////////////////////////////////////////////////////////////////
int isZero(struct NUMBER* a)
{
	if (getSign(a) == -1)
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
//引数：struct NUMBER* a : 10倍したい多倍長変数, struct NUMBER* b : 計算した値を格納する多倍長変数
//戻値：成功 : 0, 桁あふれ : -1(bの値は変化しない)
///////////////////////////////////////////////////////////////////
int mulBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	struct NUMBER tmp;

	clearByZero(&tmp);

	if (a->n[KETA - 1] != 0)
	{
		return -1;
	}

	for (i = 0; i < KETA - 1; i++)
	{
		tmp.n[i + 1] = a->n[i];
	}

	tmp.n[0] = 0;
	if (setSign(&tmp, getSign(a)))
	{
		return -1;
	}

	copyNumber(&tmp, b);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を10で割った商を格納する
//引数：struct NUMBER* a : 1/10にしたい多倍長変数, struct NUMBER* b : 計算した値を格納する多倍長変数
//戻値：成功 : 余り
///////////////////////////////////////////////////////////////////
int divBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;

	struct NUMBER tmp;

	clearByZero(&tmp);

	for (i = 1; i < KETA; i++)
	{
		tmp.n[i - 1] = a->n[i];
	}

	tmp.n[KETA - 1] = 0;
	if (setSign(&tmp, getSign(a)))
	{
		return -1;
	}

	copyNumber(&tmp, b);

	return a->n[0];
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数にint型の数字を格納する
//引数：struct NUMBER* a : 格納される多倍長変数, int x : 格納したい多倍長変数
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
		x = ~x + 1/*わんちゃん*-1でもコンパイラで処理される*/;
		if (setSign(a, -1))
		{
			return -1;
		}
	}
	else
	{
		if (setSign(a, 1))
		{
			return -1;
		}
	}

	while (x > 0)
	{
		x = (x - (a->n[i++] = x % 10)) / 10;
	}

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数の符号を設定する
//引数：struct NUMBER* a : 設定される多倍長変数, int x : 設定する符号(+ : 1, - : -1)
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
//引数：struct NUMBER* a : 符号を取得する多倍長変数
//戻値：正 : 1, 負 : -1
///////////////////////////////////////////////////////////////////
int getSign(struct NUMBER* a)
{
	return a->sign;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bを比較する
//引数：struct NUMBER* a : 比較する多倍長変数(1), struct NUMBER* b : 比較する多倍長変数(2)
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
//概要：多倍長変数a, bの交換する
//引数：struct NUMBER* a : 交換する多倍長変数(1), struct NUMBER* b : 交換する多倍長変数(2)
//戻値：なし
///////////////////////////////////////////////////////////////////
void swap(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER tmp = *a;
	*a = *b;
	*b = tmp;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの和を求めてcに格納する
//引数：struct NUMBER* a : 加算する多倍長変数(1), struct NUMBER* b : 加算する多倍長変数(2), struct NUMBER* c : 和を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int add(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	int d, i = 0, flag = 0;//min...0, max...1
	struct NUMBER tmp;		//tmpを使うことで失敗時にcのデータが壊れないようにいている

	clearByZero(&tmp);

	if (getSign(a) < 0 && getSign(b) < 0)		//a < 0, b < 0 --- a + b = -(|a| + |b|)
	{
		struct NUMBER tmp_a, tmp_b;
		getAbs(a, &tmp_a), getAbs(b, &tmp_b);
		flag = add(&tmp_a, &tmp_b, &tmp);
		if (setSign(&tmp, -1))
		{
			return -1;
		}
	}
	else if (getSign(a) < 0 && getSign(b) > 0)	//a < 0, b > 0 --- a + b = b - |a| 
	{
		struct NUMBER tmp_a;
		getAbs(a, &tmp_a);
		flag = sub(b, &tmp_a, &tmp);
	}
	else if (getSign(a) > 0 && getSign(b) < 0)	//a > 0, b < 0 --- a + b = a - |b|
	{
		struct NUMBER tmp_b;
		getAbs(b, &tmp_b);
		flag = sub(a, &tmp_b, &tmp);
	}
	else
	{
		//加算
		for (i = 0; i < KETA; i++)
		{
			d = a->n[i] + b->n[i] + flag;
			tmp.n[i] = d % 10;
			flag = d / 10;
		}
	}

	if (flag)
	{
		return -1;
	}

	copyNumber(&tmp, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aをインクリメントしてcに格納する
//引数：struct NUMBER* a : インクリメントする多倍長変数, struct NUMBER* b : 結果を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int increment(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER one;

	if (setInt(&one, 1))
	{
		return -1;
	}

	return add(a, &one, b);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの差を求めてcに格納する
//引数：struct NUMBER* a : 減算する多倍長変数(1), struct NUMBER* b : 減算する多倍長変数(2), struct NUMBER* c : 差を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int sub(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER tmp;
	int flag = 0;
	int i = 0;

	clearByZero(&tmp);


	if (getSign(a) < 0 && getSign(b) < 0)		//a < 0, b < 0 --- a - b = |b| - |a|
	{
		struct NUMBER tmp_a, tmp_b;
		getAbs(a, &tmp_a), getAbs(b, &tmp_b);
		flag = sub(&tmp_b, &tmp_a, &tmp);
	}
	else if (getSign(a) < 0 && getSign(b) > 0)	//a < 0, b > 0 --- a - b = -(|a| + b)
	{
		struct NUMBER tmp_a;
		getAbs(a, &tmp_a);
		flag = add(&tmp_a, b, &tmp);
		if (setSign(&tmp, -1))
		{
			return -1;
		}
	}
	else if (getSign(a) > 0 && getSign(b) < 0)	//a > 0, b < 0 --- a - b = a + |b|
	{
		struct NUMBER tmp_b;
		getAbs(b, &tmp_b);
		flag = add(a, &tmp_b, &tmp);
	}
	//ここから減算
	else if (numComp(a, b) < 0)			//a < b
	{
		flag = sub(b, a, &tmp);
		if (setSign(&tmp, -1))
		{
			return -1;
		}
	}
	else
	{
		//減算
		for (i = 0; i < KETA; i++)
		{
			if (a->n[i] - flag >= b->n[i])
			{
				tmp.n[i] = a->n[i] - flag - b->n[i];
				flag = 0;
			}
			else
			{
				tmp.n[i] = 10 + a->n[i] - flag - b->n[i];
				flag = 1;
			}
		}
	}

	if (flag != 0)
	{
		return -1;
	}

	copyNumber(&tmp, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aをデクリメントしてcに格納する
//引数：struct NUMBER* a : デクリメントする多倍長変数, struct NUMBER* b : 結果を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int decrement(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER one;
	if (setInt(&one, 1))
	{
		return -1;
	}
	return sub(a, &one, b);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの積を求めてcに格納する
//引数：struct NUMBER* a : 乗算する多倍長変数(1), struct NUMBER* b : 乗算する多倍長変数(2), struct NUMBER* c : 積を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, k, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0)		//どちらか一方が0のとき
	{
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);

	for (i = 0; i < KETA; i++)
	{
		clearByZero(&tmp);
		for (j = 0; j < KETA; j++)
		{
			int e = a->n[j] * b->n[i] + flag;
			tmp.n[j] = e % 10;
			flag = e / 10;
		}

		if (flag)
		{
			return -1;
		}

		for (k = 0; k < i; k++)
		{
			if (mulBy10(&tmp, &tmp))
			{
				return -1;
			}
		}

		if (add(&ans, &tmp, &ans))
		{
			return -1;
		}
	}

	if (getSign(a) + getSign(b) == 0)			//どちらか一方が負のとき
	{
		if (setSign(&ans, -1))
		{
			return -1;
		}
	}

	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//概要：多倍長変数a, bの積を求めてcに格納する(開発版)
//引数：struct NUMBER* a : 乗算する多倍長変数(1), struct NUMBER* b : 乗算する多倍長変数(2), struct NUMBER* c : 積を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
//補足：multiple関数の約3倍の速度
//*****************************************************************
int Dev_multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0)		//どちらか一方が0のとき
	{
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);

	for (i = KETA - 1; i >= 0; i--)		//bの上の桁から行う
	{
		clearByZero(&tmp);
		for (j = 0; j < KETA; j++)		//一段分の答えを出す
		{
			int e = a->n[j] * b->n[i] + flag;
			tmp.n[j] = e % 10;
			flag = e / 10;
		}

		if (flag)
		{
			return -1;
		}

		if (add(&ans, &tmp, &ans))			//加算
		{
			return -1;
		}

		if (i > 0 && mulBy10(&ans, &ans))	//最後の1回以外で10倍
		{
			return -1;
		}
	}

	if (getSign(a) + getSign(b) == 0)			//どちらか一方が負のとき
	{
		if (setSign(&ans, -1))
		{
			return -1;
		}
	}

	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの商を求めてcに格納し、余りをdに格納する
//引数：struct NUMBER* a : 除算する多倍長変数(1), struct NUMBER* b : 除算する多倍長変数(2), struct NUMBER* c : 商を格納する多倍長変数, struct NUMBER* d : 余りを格納する多倍長変数
//戻値：成功 : 0, 失敗(0除算) : -1(c, dの値は変化しない), 失敗(その他エラー)：-2(c, dの値は変化しない)
///////////////////////////////////////////////////////////////////
int divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans, rem;

	if (isZero(b) == 0)
	{
		return -1;
	}

	if (isZero(a) == 0)
	{
		clearByZero(c);
		clearByZero(d);
		return 0;
	}

	if (getSign(a) == -1 || getSign(b) == -1)			//どちらか一方が負のとき
	{
		int num;
		struct NUMBER tmp_a, tmp_b;

		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		num = divide(&tmp_a, &tmp_b, &ans, &rem);
		if (num < 0)
		{
			return num;
		}

		if (getSign(a) + getSign(b) == 0)	//どちらか一方のみ負のとき
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}

		if (setSign(&rem, getSign(a)))		//余りの符号
		{
			return -2;
		}

		copyNumber(&ans, c);
		copyNumber(&rem, d);

		return 0;
	}

	//1桁判別用
	int flg;
	if ((flg = divide_U10(a, b, c, d)) != -2)	//bが1桁でない場合以外の時の除算
	{
		return flg;
	}
	
	//ここから++の除算
	clearByZero(&ans);
	copyNumber(a, &rem);

	while (1)
	{
		if (numComp(&rem, b) == -1)//x < y)
		{
			break;
		}
		if (sub(&rem, b, &rem))
		{
			return -2;
		}
		if (increment(&ans, &ans))
		{
			return -2;
		}
	}

	copyNumber(&ans, c);
	copyNumber(&rem, d);

	return 0;
}


//*****************************************************************
//概要：多倍長変数a, b(bは1桁)の商を求めてcに格納し、余りをdに格納する
//引数：struct NUMBER* a : 除算する多倍長変数(1), struct NUMBER* b : 除算する多倍長変数(2), struct NUMBER* c : 商を格納する多倍長変数, struct NUMBER* d : 余りを格納する多倍長変数
//戻値：成功 : 0, 失敗(0除算) : -1(c, dの値は変化しない), 失敗(bが1桁でない)：-2(c, dの値は変化しない), 失敗(その他エラー)：-3(c, dの値は変化しない)
//*****************************************************************
int divide_U10(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	printf("divide_U10-----------------------------------------------\n");
	struct NUMBER ans;
	int h = 0;
	int i = KETA - 1;

	//余り : rem
	int rem = divBy10(b, &ans);

	if (b == 0)				//0除算
	{
		return -1;
	}

	if (isZero(&ans))		//bが1桁でないなら
	{
		return -2;
	}

	clearByZero(&ans);

	//bが1桁なら
	//b は rem と等しい(struct NUMBER -> int)

	for (i = KETA - 1; i >= 0; i--)
	{
		int t = h * 10 + a->n[i];
		h = t % rem;
		ans.n[i] = (t - h) / rem;
	}

	copyNumber(&ans, c);
	if (setInt(d, h))		//余り
	{
		return -1;
	}

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bにおいてaのb乗をcに格納する
//引数：struct NUMBER* a : 累乗される多倍長変数, struct NUMBER* b :	累乗の上のとこの多倍長変数, struct NUMBER* c : 累乗した値を格納する多倍長変数
//戻値：成功 : 0, 失敗 (オーバーフロー/アンダーフロー): -1(cの値は変化しない), 失敗(b<0)：-2(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;
	struct NUMBER tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	//bが負のとき
	if (getSign(b) == -1)
	{
		return -2;
	}

	//b = 0のとき
	if (isZero(b) == 0)
	{
		//c = 1
		if (increment(&ans, &ans))
		{
			return -1;
		}
		copyNumber(&ans, c);
	}

	//累乗
	copyNumber(a, &ans);
	copyNumber(b, &tmp);
	while (1)
	{
		if (decrement(&tmp, &tmp))
		{
			return -1;
		}

		if (isZero(&tmp) == 0)
		{
			break;
		}

		//処理
		if (multiple(&ans, a, &ans))
		{
			return -1;
		}
	}
	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aにおいてaの階乗(a!)をbに格納する
//引数：struct NUMBER* a : 階乗する多倍長変数, struct NUMBER* b : 階乗した値を格納する多倍長変数
//戻値：成功 : 0, 失敗(オーバーフロー/アンダーフロー) : -1(bの値は変化しない), 失敗(a<0) : -2(bの値は変化しない)
///////////////////////////////////////////////////////////////////
int factorial(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER ans;
	struct NUMBER tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	//a<0
	if (getSign(a) < 0)
	{
		return -2;
	}

	//a=0
	if (isZero(a) == 0)
	{
		increment(&ans, &ans);
		copyNumber(&ans, b);
		return 0;
	}

	copyNumber(a, &tmp);
	copyNumber(a, &ans);

	while (1)
	{
		if (decrement(&tmp, &tmp))
		{
			return -1;
		}

		if (isZero(&tmp) == 0)
		{
			break;
		}

		if (multiple(&ans, &tmp, &ans))
		{
			return -1;
		}
	}

	copyNumber(&ans, b);

	return 0;
}


///////////////////////////////////////////////////////////////////
//                       以下時間計測用                          //
///////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////
//                       以下チェック用                          //
///////////////////////////////////////////////////////////////////

void RoopFunction_ASM(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size, enum ViewStyle style)
{
	unsigned int i;

	struct NUMBER tmp_a, tmp_b, tmp_c;

	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_c);

	for (i = 0; i < roop; i++)
	{
		setRnd(&tmp_a, size);
		setRnd(&tmp_b, size);

		int flag = func(&tmp_a, &tmp_b, &tmp_c);

		switch (style)
		{
		case None:
			if (!flag)
				break;
		case All:
			printf("Input1 = ");	dispNumber(&tmp_a);	putchar('\n');
			printf("Input2 = ");	dispNumber(&tmp_b);	putchar('\n');
		case OnlyAnswer:
			printf("Answer = ");	dispNumber(&tmp_c);	putchar('\n');
			break;
		}
	}
}

void RoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size, enum ViewStyle style)
{
	unsigned int i;

	struct NUMBER tmp_a, tmp_b, tmp_c, tmp_d;

	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_c);
	clearByZero(&tmp_d);

	for (i = 0; i < roop; i++)
	{
		setRnd(&tmp_a, size);
		setRnd(&tmp_b, size);

		int flag = func(&tmp_a, &tmp_b, &tmp_c, &tmp_d);

		switch (style)
		{
		case None:
			if (!flag)
				break;
		case All:
			printf("Input1 = ");	dispNumber(&tmp_a);	putchar('\n');
			printf("Input2 = ");	dispNumber(&tmp_b);	putchar('\n');
		case OnlyAnswer:
			printf("Answer = ");	dispNumber(&tmp_c);	putchar('\n');
			break;
		}
	}
}

void check_setInt(struct NUMBER* a, int roop)
{
	int x = rand();
	setInt(a, x);

	if (checkNumber(a, x))
	{
		printf("a = ");
		dispNumber(a);
		putchar('\n');
		printf("x = %d\n", x);
	}
}

//a, xが等しければ0, 違うなら-1
int checkNumber(struct NUMBER* a, int x)
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

