#include "mulprec.h"


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
		printf("%2d", a->n[i]);        //数字確認用
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
		a->n[i] = random() % 10;
	}
	//符号
	setSign(a, (random() % 2 == 1) ? 1 : -1);
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
	/* if (getSign(a) == -1)
	{
		return -1;
	}
 */			//-0が紛れ込んだ時の対策
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
	else //if (sign_a == -1 && sign_b == -1)
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

	if (isZero(a) == 0 || isZero(b) == 0)		//すくなくともどちらか一方が0のとき
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

	if (getSign(a) + getSign(b) == 0)			//どちらか一方のみ負のとき
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
//補足：multiple関数の約3倍(KETA=10), 約16.7倍(KETA=100)の速度
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
//概要：多倍長変数a, bの商を求めてcに格納し、余りをdに格納する。
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
	if (getSign(a) == -1 || getSign(b) == -1)			//少なくともどちらか一方が負のとき
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
		if (numComp(&rem, b) < 0)//x < y
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
//概要：多倍長変数a, b(bは1桁)の商を求めてcに格納し、余りをdに格納する。(開発版：安定)
//引数：struct NUMBER* a : 除算する多倍長変数(1), struct NUMBER* b : 除算する多倍長変数(2), struct NUMBER* c : 商を格納する多倍長変数, struct NUMBER* d : 余りを格納する多倍長変数
//戻値：成功 : 0, 失敗(0除算) : -1(c, dの値は変化しない), 失敗(bが1桁でない)：-2(c, dの値は変化しない), 失敗(その他エラー)：-3(c, dの値は変化しない)
//*****************************************************************
int divide_U10(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	int h = 0;
	int i = KETA - 1;

	clearByZero(&ans);

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
		return -3;
	}

	return 0;
}


//*****************************************************************
//概要：多倍長変数a, bの商を求めてcに格納し、余りをdに格納する。(開発版：安定)
//引数：struct NUMBER* a : 除算する多倍長変数(1), struct NUMBER* b : 除算する多倍長変数(2), struct NUMBER* c : 商を格納する多倍長変数, struct NUMBER* d : 余りを格納する多倍長変数
//戻値：成功 : 0, 失敗(0除算) : -1(c, dの値は変化しない), 失敗(その他エラー)：-2(c, dの値は変化しない)
//*****************************************************************
int Dev_divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	struct NUMBER tmp_a, tmp_b, tmp_d, tmp_e;
	struct NUMBER tmp_check;		//確認用変数

	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);
	clearByZero(&tmp_check);

	//0除算
	if (isZero(b) == 0)
	{
		return -1;
	}
	//分子が0のとき
	if (isZero(a) == 0)
	{
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//マイナス処理
	//少なくともどちらか一方が負のとき
	if (getSign(a) == -1 || getSign(b) == -1)
	{
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
		{
			return num;
		}
		//どちらか一方のみ負のとき
		if (getSign(a) + getSign(b) == 0)
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}
		//余りの符号 (余りの符号は常に割られる数の符号に依存する)
		if (setSign(&tmp_d, getSign(a)))
		{
			return -2;
		}

		copyNumber(&ans, c);
		copyNumber(&tmp_d, d);

		return 0;
	}

	//ここから++の除算

	copyNumber(a, &tmp_a);
	copyNumber(b, &tmp_b);

	while (numComp(&tmp_a, &tmp_b) != -1)	//a < b でないなら
	{
		copyNumber(&tmp_b, &tmp_d);

		if (setInt(&tmp_e, 1))
		{
			return -2;
		}

		while (1)
		{
			int rem = divBy10(&tmp_a, &tmp_check);

			int flg = numComp(&tmp_check, &tmp_d);
			if (flg == -1)	//tmp_dをmulBy10するとtmp_aを超える
			{
				break;
			}
			else if (flg == 0 && rem < tmp_d.n[0])	//等しいときは余りremによって決まる. rem>0ならtmp_a > tmp_d*10
			{										//d.n[0]との比較は1回目のため, 2回目以降はd.n[0]は0なので常にfalse
				break;
			}

			//tmp_a >= tmp_d * 10のとき

			if (mulBy10(&tmp_d, &tmp_d))
			{
				return -2;
			}

			if (mulBy10(&tmp_e, &tmp_e))
			{
				return -2;
			}
		}

		sub(&tmp_a, &tmp_d, &tmp_a);

		if (add(&ans, &tmp_e, &ans))
		{
			return -2;
		}
	}

	copyNumber(&tmp_a, d);
	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//概要：多倍長変数a, bの商を求めてcに格納し、余りをdに格納する。(開発版：不安定)
//引数：struct NUMBER* a : 除算する多倍長変数(1), struct NUMBER* b : 除算する多倍長変数(2), struct NUMBER* c : 商を格納する多倍長変数, struct NUMBER* d : 余りを格納する多倍長変数
//戻値：成功 : 0, 失敗(0除算) : -1(c, dの値は変化しない), 失敗(その他エラー)：-2(c, dの値は変化しない)
//補足：最上位bitまで値が入っている状態だとoverflowする場合がある(例：KETA=5,a=99999,b=99998)
//*****************************************************************
int Dev_divide_X(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	struct NUMBER tmp_a, tmp_b, tmp_d, tmp_e;
	//手順1
	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);

	//0除算
	if (isZero(b) == 0)
	{
		return -1;
	}
	//分子が0のとき
	if (isZero(a) == 0)
	{
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//マイナス処理
	//少なくともどちらか一方が負のとき
	if (getSign(a) == -1 || getSign(b) == -1)
	{
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide_X(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
		{
			return num;
		}
		//どちらか一方のみ負のとき
		if (getSign(a) + getSign(b) == 0)
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}
		//余りの符号 (余りの符号は常に割られる数の符号に依存する)
		if (setSign(&tmp_d, getSign(a)))
		{
			return -2;
		}

		copyNumber(&ans, c);
		copyNumber(&tmp_d, d);

		return 0;
	}

	copyNumber(a, &tmp_a);
	copyNumber(b, &tmp_b);

	//手順2
	while (numComp(&tmp_a, &tmp_b) != -1)
	{
		//手順3
		copyNumber(&tmp_b, &tmp_d);
		//手順4
		if (setInt(&tmp_e, 1))
		{
			return -2;
		}
		//手順5

		//dを10倍していくと最上位bitが非0になってもなおa>dとなることがあるため, さらに10倍されてoverflowしてしまう
		//解決策1...常に余裕のある桁数を用意しておく
		//解決策2...最上位bitの値が非0になったときに特別な処理を描く
		while (1)
		{
			if (mulBy10(&tmp_d, &tmp_d))
			{
				return -2;
			}

			if (numComp(&tmp_a, &tmp_d) != 1)
			{
				divBy10(&tmp_d, &tmp_d);	//これだとKETA-1まで埋まるような数字の時に不具合が起きる可能性がある
				break;
			}

			//手順6
			if (mulBy10(&tmp_e, &tmp_e))
			{
				return -2;
			}
		}

		//手順7
		sub(&tmp_a, &tmp_d, &tmp_a);

		if (add(&ans, &tmp_e, &ans))
		{
			return -2;
		}
	}

	//手順10
	copyNumber(&tmp_a, d);
	copyNumber(&ans, c);

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

		return 0;
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


//*****************************************************************
//概要：多倍長変数a, bにおいてaのb乗をcに格納する(開発版)
//引数：struct NUMBER* a : 累乗される多倍長変数, struct NUMBER* b :	累乗の上のとこの多倍長変数, struct NUMBER* c : 累乗した値を格納する多倍長変数
//戻値：成功 : 0, 失敗 (オーバーフロー/アンダーフロー): -1(cの値は変化しない), 失敗(b<0)：-2(cの値は変化しない)
//*****************************************************************
int Dev_power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
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
	}
	else
	{
		if (Cul_power(a, b, &ans))
		{
			return -1;
		}
	}

	copyNumber(&ans, c);

	return 0;
}

int Cul_power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER tmp, div;
	if (setInt(&tmp, 1))
		//tmp = 1
	{
		return -1;
	}

	if (isZero(b) == 0)			// b = 0 ?
	{
		copyNumber(&tmp, c);
		return 0;
	}

	if (numComp(b, &tmp) == 0)	//b = 1 ?
	{
		copyNumber(a, c);
		return 0;
	}

	if (increment(&tmp, &tmp))	// tmp = 1 -> 2
	{
		return -1;
	}

	if (divide(b, &tmp, &div, &tmp))	//tmp = 2 -> 剰余, div = b / 2
	{
		return -1;
	}

	if (isZero(&tmp) == 0)	//偶数の時
	{
		if (multiple(a, a, &tmp))	//a^2
		{
			return -1;
		}

		if (Cul_power(&tmp, &div, &tmp))
		{
			return -1;
		}
	}
	else
	{
		if (decrement(b, &tmp))
		{
			return -1;
		}

		if (Cul_power(a, &tmp, &tmp))
		{
			return -1;
		}

		if (multiple(a, &tmp, &tmp))
		{
			return -1;
		}
	}

	copyNumber(&tmp, c);

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
//概要：多倍長変数a, bにおいてaとbの最大公約数をcに格納する
//引数：struct NUMBER* a : 最大公約数を求める多倍長変数, struct NUMBER* b : 最大公約数を求める多倍長変数, struct NUMBER* c : 最大公約数を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int gcd(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER num1, num2, rem;

	clearByZero(&num1);
	clearByZero(&num2);
	clearByZero(&rem);


	if (numComp(&num1, &num2) == -1)	//a < b なら
	{
		getAbs(b, &num1);
		getAbs(a, &num2);
	}
	else
	{
		getAbs(a, &num1);
		getAbs(b, &num2);
	}


	if (isZero(&num2) == 0)
	{
		copyNumber(&num1, c);
		return 0;
	}

	while (1)
	{
		if (divide(&num1, &num2, &num1/*不要*/, &rem))
		{
			return -1;
		}
		copyNumber(&num2, &num1);
		copyNumber(&rem, &num2);

		if (isZero(&rem) == 0)
		{
			break;
		}
	}

	//ここにきたとき除数はnum1になる
	copyNumber(&num1, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bにおいてaとbの最小公倍数をcに格納する
//引数：struct NUMBER* a : 最小公倍数を求める多倍長変数, struct NUMBER* b : 最小公倍数を求める多倍長変数, struct NUMBER* c : 最小公倍数を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int lcm(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, num1, num2;
	clearByZero(&ans);
	clearByZero(&num1);
	clearByZero(&num2);

	getAbs(a, &num1);
	getAbs(b, &num2);

	if (multiple(&num1, &num2, &ans))
	{
		return -1;
	}

	//ans = |a|*|b|

	if (gcd(a, b, &num1))		//gcdは符号に影響しないためa,bをそのまま用いている
	{
		return -1;
	}

	//num1 = gcd(a,b)

	if (divide(&ans, &num1, &ans, &num1/*不要*/))
	{
		return -1;
	}

	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//概要：多倍長変数a, bにおいてaとbの最小公倍数をcに格納する(開発版)
//引数：struct NUMBER* a : 最小公倍数を求める多倍長変数, struct NUMBER* b : 最小公倍数を求める多倍長変数, struct NUMBER* c : 最小公倍数を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
//補足：|a|*|b|/gcd(a,b) -> |a|/gcd(a,b)*|b| に変更
//*****************************************************************
int Dev_lcm(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, num1, num2;
	clearByZero(&ans);
	clearByZero(&num1);
	clearByZero(&num2);

	getAbs(a, &num1);
	getAbs(b, &num2);

	if (gcd(a, b, &ans))		//gcdは符号に影響しないためa,bをそのまま用いている
	{
		return -1;
	}

	//ans = gcd(a,b)

	if (divide(&num1, &ans, &ans, &num1/*不要*/))
	{
		return -1;
	}

	//ans = |a| / gcd(a,b)
	//num2 = |b|

	if (multiple(&ans, &num2, &ans))
	{
		return -1;
	}

	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aにおいてaが素数か判別する
//引数：struct NUMBER* a : 素数か判別する多倍長変数
//戻値：素数である : 1, 素数でないまたは失敗 : 0
///////////////////////////////////////////////////////////////////
int isPrime(struct NUMBER* a)
{
	struct NUMBER num, rem, tmp, two, tmp2;
	clearByZero(&num);
	clearByZero(&rem);
	clearByZero(&tmp);
	clearByZero(&two);
	clearByZero(&tmp2);

	if (setInt(&two, 2))
	{
		return 0;
	}

	if (setInt(&num, 1))
	{
		return 0;
	}
	copyNumber(&num, &tmp);		//setInt(&tmp, 1);

	if (numComp(a, &tmp) <= 0)	//a <= 1
	{
		return 0;
	}

	if (Dev_divide(a, &two, &tmp, &rem))	//2で割る  tmp = a/2 ... これの範囲内でループする
	{
		return 0;
	}

	if (numComp(&tmp, &num/*1*/) == 0)	//a=2の時の処理
	{
		return 1;
	}


	while (1)
	{
		if (isZero(&rem) == 0)	//割り切れたとき
		{
			break;
		}

		if (add(&num, &two, &num))
		{
			break;
		}

		if (numComp(&num, &tmp) > 0)
		{
			return 1;
		}

		if (Dev_divide(a, &num, &tmp2, &rem))
		{
			break;
		}
	}

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aにおいてaの平方根をbに格納する(正式にはsqrt(a)を超えない最大の整数をbに格納する)
//引数：struct NUMBER* a : 平方根を求める多倍長変数, struct NUMBER* b : 平方根を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(bの値は変化しない)
///////////////////////////////////////////////////////////////////
int squareroot(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER tmp_a, tmp_b, two, cnt;
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&two);
	clearByZero(&cnt);

	if (numComp(a, &tmp_a) < 0)	//a < 0 ?
	{
		return -1;
	}

	copyNumber(a, &tmp_a);	//tmp_a ... N

	if (increment(&tmp_b, &tmp_b))	//tmp = 1
	{
		return -1;
	}

	setInt(&two, 2);

	while (1)
	{
		if (numComp(&tmp_a, &tmp_b) < 0)	//tmp_a < tmp ?
		{
			break;
		}

		if (sub(&tmp_a, &tmp_b, &tmp_a))
		{
			return -1;
		}

		if (increment(&cnt, &cnt))
		{
			return -1;
		}

		if (add(&tmp_b, &two, &tmp_b))
		{
			return -1;
		}
	}

	copyNumber(&cnt, b);

	return 0;
}





///////////////////////////////////////////////////////////////////
//                        以下時間計測用                          //
///////////////////////////////////////////////////////////////////

#ifndef _DEBUG

static struct timeval tv;
static double tstart, tend;

void timeStart(void)
{
	clockStart();
}
double timeStop(void)
{
	return clockStop();
}

void clockStart(void)
{
	gettimeofday(&tv, NULL);
	tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
}

double clockStop(void)
{
	gettimeofday(&tv, NULL);
	tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
	return (tend - tstart) * 1000;
}

#else

void timeStart(void)
{
	timeCount = time(NULL);
}

//s
double timeStop(void)
{
	time_t stop = time(NULL);
	time_t diff = stop - timeCount;
	timeCount = 0;
	return (unsigned int)diff;
}


void clockStart(void)
{
	clockCount = clock();
}

//ms
double clockStop(void)
{
	clock_t stop = clock();
	clock_t diff = stop - clockCount;
	clockCount = 0;
	return ((double)diff * 1000 / CLOCKS_PER_SEC);
}

#endif


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

		//確認
		if (1)
		{
			struct NUMBER check;
			clearByZero(&check);
			multiple(&tmp_b, &tmp_c, &check);
			add(&check, &tmp_d, &check);
			flag = (numComp(&check, &tmp_a) == 0 && flag == 0) ? 0 : -1;
		}

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
			printf("Surplus = ");	dispNumber(&tmp_d);	putchar('\n');
			break;
		}
	}
}


double FastRoopFunction_ASM(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size)
{
	unsigned int i = 0, tmp = 0;
	double flag = 0;
	struct NUMBER tmp_a, tmp_b, tmp_c;



	while (i++ < roop)
	{
		int i;
		clearByZero(&tmp_a);
		clearByZero(&tmp_b);
		clearByZero(&tmp_c);
		setRnd(&tmp_a, size);
		setRnd(&tmp_b, 1);//(random() % size) + 1);
		setSign(&tmp_b, 1);
		clockStart();
		i = func(&tmp_a, &tmp_b, &tmp_c);
		flag += clockStop();
		tmp += ((i != 0 && i != -1) ? 1 : 0);
		if (i)
		{
			printf("-----------------------------------------------------------------------------\n");
			printf("a = ");	dispNumber(&tmp_a);	putchar('\n');
			printf("b = ");	dispNumber(&tmp_b);	putchar('\n');
			printf("c = ");	dispNumber(&tmp_c);	putchar('\n');
		}
	}
	printf("ErrorNumber: %d\n", tmp);

	return flag;
}


double FastRoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size)
{
	unsigned int i = 0, tmp = 0;
	double flag = 0;
	struct NUMBER tmp_a, tmp_b, tmp_c, tmp_d;

	while (i++ < roop)
	{
		int i;
		clearByZero(&tmp_a);
		clearByZero(&tmp_b);
		clearByZero(&tmp_c);
		clearByZero(&tmp_d);
		setRnd(&tmp_a, KETA);
		setRnd(&tmp_b, (random() % KETA) + 1);
		clockStart();
		i = Dev_divide(&tmp_a, &tmp_b, &tmp_c, &tmp_d);
		flag += clockStop();
		tmp += ((i != 0 && i != -1) ? 1 : 0);
		if (i)
		{
			printf("-----------------------------------------------------------------------------\n");
			printf("a = ");	dispNumber(&tmp_a);	putchar('\n');
			printf("b = ");	dispNumber(&tmp_b);	putchar('\n');
			printf("c = ");	dispNumber(&tmp_c);	putchar('\n');
			printf("d = ");	dispNumber(&tmp_d);	putchar('\n');
		}
	}
	printf("ErrorNumber: %d\n", tmp);

	return flag;
}


void check_setInt(struct NUMBER* a)
{
	int x = random();
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
