#include "mulprec.h"



//*****************************************************************
//概要：多倍長演算における初期設定を行い, struct NUMBER 型 定数 SN_0...0, SN_1...1, SN_2...2
//引数：なし
//戻値：なし
//*****************************************************************
void MLAsetup(void)
{
	int i;
	// 0
	for (i = 0; i < KETA; i++)
		SN_0.n[i] = 0;
	SN_0.sign = SIGN_PLUS;
	// 1
	copyNumber(&SN_0, &SN_1);
	SN_1.n[0] = 1;
	// 2
	copyNumber(&SN_0, &SN_2);
	SN_2.n[0] = 2;
	// trush
	copyNumber(&SN_0, &SN_trush);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を0に初期化する
//引数：struct NUMBER* a : 初期化する多倍長変数
//戻値：なし
///////////////////////////////////////////////////////////////////
void clearByZero(struct NUMBER* a)
{
	copyNumber(&SN_0, a);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を表示する
//引数：struct NUMBER* a : 表示する多倍長変数
//戻値：なし
///////////////////////////////////////////////////////////////////
void dispNumber(struct NUMBER* a)
{
	int i;
	if (getSign(a)  ==  SIGN_PLUS)	putchar('+');
	else							putchar('-');

#if RADIX == 10000
		for (i = KETA - 1; i >= 0; i--)
			printf("%04d", a->n[i]);        //数字確認用
#else
		for (i = KETA - 1; i >= 0; i--)
			printf("%1d", a->n[i]);        //数字確認用
#endif
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
		a->n[i] = random() % RADIX;
	//符号
	setSign(a, (random() % 2 == 1) ? SIGN_PLUS : SIGN_MINUS);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数をコピーする
//引数：struct NUMBER* a : コピー元の多倍長変数, struct NUMBER* b : コピー先の多倍長変数
//戻値：なし
///////////////////////////////////////////////////////////////////
void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	*b = *a;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数の絶対値を求めて格納する
//引数：struct NUMBER* a : 絶対値を求める多倍長変数, struct NUMBER* b : 絶対値を格納する多倍長変数
//戻値：なし
///////////////////////////////////////////////////////////////////
void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	setSign(b, SIGN_PLUS);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数が0かどうかを判別する
//引数：struct NUMBER* a : 判別する多倍長変数
//戻値：0のとき : 0, それ以外のとき : -1
///////////////////////////////////////////////////////////////////
int isZero(struct NUMBER* a)
{
	int i;
	for (i = 0; i < KETA; i++)
		if (a->n[i] != 0)
			return -1;
	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を10倍して格納する
//引数：struct NUMBER* a : 10倍したい多倍長変数, struct NUMBER* b : 計算した値を格納する多倍長変数
//戻値：成功 : 0, 失敗(桁あふれ) : -1(bの値は変化しない), 失敗(その他) : -1(bの値は変化しない), 
//補足：RADIX進数に変更したため10倍ではなくRADIX倍になる。
///////////////////////////////////////////////////////////////////
int mulBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	struct NUMBER ans;

	clearByZero(&ans);

	if (a->n[KETA - 1] != 0)
		return -1;
	for (i = 0; i < KETA - 1; i++)
		ans.n[i + 1] = a->n[i];
	ans.n[0] = 0;
	if (setSign(&ans, getSign(a)))
		return -1;
	
	copyNumber(&ans, b);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数を10で割った商を格納する
//引数：struct NUMBER* a : 1/10にしたい多倍長変数, struct NUMBER* b : 計算した値を格納する多倍長変数
//戻値：成功 : 余り
///////////////////////////////////////////////////////////////////
int divBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i, rem = a->n[0];
	struct NUMBER ans;

	clearByZero(&ans);

	for (i = 1; i < KETA; i++)
		ans.n[i - 1] = a->n[i];
	ans.n[KETA - 1] = 0;
	if (setSign(&ans, getSign(a)))
		return -1;
	copyNumber(&ans, b);

	return rem;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数にint型の数字を格納する
//引数：struct NUMBER* a : 格納される多倍長変数, int x : 格納したい多倍長変数
//戻値：成功 : 0, 失敗 : -1(aの値は変化しない)
///////////////////////////////////////////////////////////////////
int setInt(struct NUMBER* a, int x)
{
	int i = 0;
	struct NUMBER ans;
	clearByZero(&ans);

	if (x < 0) {	//aはすでに＋なのでxが-のときのみsetSignする
		x *= -1;
		if (setSign(&ans, SIGN_MINUS))
			return -1;
	}

	while (x > 0) {
		if (i >= KETA)
			return -1;
		ans.n[i++] = x % RADIX;
		x /= RADIX;
	}

	clearByZero(a);
	copyNumber(&ans, a);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数の符号を設定する
//引数：struct NUMBER* a : 設定される多倍長変数, int x : 設定する符号(+ : 1, - : -1)
//戻値：成功 : 0, 失敗 : -1(aの符号は変化しない)
///////////////////////////////////////////////////////////////////
int setSign(struct NUMBER* a, int s)
{
	if (s != SIGN_PLUS && s != SIGN_MINUS)
		return -1;
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
	//-0が紛れ込んだ時の対策
	if (isZero(a) == 0 && isZero(b) == 0)
		return 0;
	if (sign_a == SIGN_PLUS && sign_b == SIGN_MINUS)
		return 1;
	if (sign_a == SIGN_MINUS && sign_b == SIGN_PLUS)
		return -1;
	if (sign_a == SIGN_PLUS && sign_b == SIGN_PLUS) {
		int i = KETA;
		while (--i >= 0) {
			if (a->n[i] == b->n[i])
				continue;
			if (a->n[i] > b->n[i])
				return 1;
			return -1;	//a < b
		}
	}
	else { //if (sign_a == SIGN_MINUS && sign_b == SIGN_MINUS)
		int i = KETA;
		while (--i >= 0) {
			if (a->n[i] == b->n[i])
				continue;
			if (a->n[i] > b->n[i])
				return -1;
			return 1;	// a < b
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
	struct NUMBER tmp;
	clearByZero(&tmp);
	copyNumber(a, &tmp);
	copyNumber(b, a);
	copyNumber(&tmp, b);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの和を求めてcに格納する
//引数：struct NUMBER* a : 加算する多倍長変数(1), struct NUMBER* b : 加算する多倍長変数(2), struct NUMBER* c : 和を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int add(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	int sign_a = getSign(a), sign_b = getSign(b);
	struct NUMBER ans;

	clearByZero(&ans);

	if (sign_a == SIGN_MINUS && sign_b == SIGN_PLUS) {	//a < 0, b > 0 --- a + b = b - |a|
		struct NUMBER abs_a;
		clearByZero(&abs_a);
		getAbs(a, &abs_a);
		return sub(b, &abs_a, c);
	}

	if (sign_a == SIGN_PLUS && sign_b == SIGN_MINUS) {	//a > 0, b < 0 --- a + b = a - |b|
		struct NUMBER abs_b;
		clearByZero(&abs_b);
		getAbs(b, &abs_b);
		return sub(a, &abs_b, c);
	}

	if (sign_a == SIGN_MINUS && sign_b == SIGN_MINUS)	//a < 0, b < 0 --- a - b = -(|a| + |b|)
		setSign(&ans, SIGN_MINUS);

	//加算
	int i, d, flg = 0;
	for (i = 0; i < KETA; i++) {
		d = a->n[i] + b->n[i] + flg;
		ans.n[i] = d % RADIX;
		flg = d / RADIX;
	}

	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aをインクリメントしてcに格納する
//引数：struct NUMBER* a : インクリメントする多倍長変数, struct NUMBER* b : 結果を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int increment(struct NUMBER* a, struct NUMBER* b)
{
	return add(a, &SN_1, b);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの差を求めてcに格納する
//引数：struct NUMBER* a : 減算する多倍長変数(1), struct NUMBER* b : 減算する多倍長変数(2), struct NUMBER* c : 差を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int sub(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	int sign_a = getSign(a), sign_b = getSign(b);
	struct NUMBER ans, abs_a, abs_b;

	clearByZero(&ans);
	clearByZero(&abs_a);
	clearByZero(&abs_b);

	if (sign_a == SIGN_MINUS && sign_b == SIGN_PLUS) {	//a < 0, b > 0 --- a - b = -(|a| + b)
		getAbs(a, &abs_a);
		if (add(&abs_a, b, c))			return -1;
		if (setSign(c, SIGN_MINUS))		return -1;
		return 0;
	}

	if (sign_a == SIGN_PLUS && sign_b == SIGN_MINUS) {	//a > 0, b < 0 --- a - b = a + |b|
		getAbs(b, &abs_b);
		return add(a, &abs_b, c);
	}

	if (sign_a == SIGN_MINUS && sign_b == SIGN_MINUS)	//a < 0, b < 0 --- a - b = |b| - |a| = -(|a| - |b|)
		setSign(&ans, SIGN_MINUS);

	//減算
	int i, d, flg = 0;

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (numComp(&abs_a, &abs_b) < 0) {			//a < b
		swap(&abs_a, &abs_b);
		if (setSign(&ans, getSign(&ans) * SIGN_MINUS)) // a < 0, b < 0 のときにマイナスになっている可能性があるので反転
			return -1;
	}

	for (i = 0; i < KETA; i++) {
		d = abs_a.n[i] - abs_b.n[i] - flg;

		if (d < 0)
			d += RADIX, flg = 1;
		else
			flg = 0;

		ans.n[i] = d;
	}

	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aをデクリメントしてcに格納する
//引数：struct NUMBER* a : デクリメントする多倍長変数, struct NUMBER* b : 結果を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int decrement(struct NUMBER* a, struct NUMBER* b)
{
	return sub(a, &SN_1, b);
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bの積を求めてcに格納する
//引数：struct NUMBER* a : 乗算する多倍長変数(1), struct NUMBER* b : 乗算する多倍長変数(2), struct NUMBER* c : 積を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0) {		//すくなくともどちらか一方が0のとき
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);
	clearByZero(&tmp);

	for (i = 0; i < KETA; i++) {
		clearByZero(&tmp);
		for (j = 0; j < KETA; j++) {
			int e = a->n[j] * b->n[i] + flag;
			tmp.n[j] = e % RADIX;
			flag = e / RADIX;
		}

		if (flag)
			return -1;
		for (j = 0; j < i; j++)
			if (mulBy10(&tmp, &tmp))
				return -1;
		if (add(&ans, &tmp, &ans))
			return -1;
	}
	//どちらか一方のみ負のとき
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))
			return -1;

	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//概要：多倍長変数a, bの積を求めてcに格納する(開発版)
//引数：struct NUMBER* a : 乗算する多倍長変数(1), struct NUMBER* b : 乗算する多倍長変数(2), struct NUMBER* c : 積を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
//補足：multiple関数の約3倍(KETA=10), 約16.7倍(KETA=100)の速度. (KETA / 2)
//*****************************************************************
int Dev_multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0){		//どちらか一方が0のとき
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);
	clearByZero(&tmp);

	for (i = KETA - 1; i >= 0; i--) {		//bの上の桁から行う
		if(b->n[i]) {
			if (b->n[i] == 1){
				copyNumber(a, &tmp);
			}
			else {
				for (j = 0; j < KETA; j++) {		//一段分の答えを出す
					int e = a->n[j] * b->n[i] + flag;
					tmp.n[j] = e % RADIX;
					flag = e / RADIX;
				}
				if (flag)
					return -1;
			}
			
			if (add(&ans, &tmp, &ans))			//加算
				return -1;
		}
		if (i > 0 && mulBy10(&ans, &ans))	//最後の1回以外で10倍 * RADIX倍
			return -1;
	}
	//どちらか一方のみ負のとき
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))
			return -1;

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
	struct NUMBER ans, rem, abs_a, abs_b;

	if (isZero(b) == 0)
		return -1;
	if (isZero(a) == 0) {
		clearByZero(c);
		clearByZero(d);
		return 0;
	}

	clearByZero(&ans);
	clearByZero(&rem);
	clearByZero(&abs_a);
	clearByZero(&abs_b);
	
	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	//1桁判別用
	int flg;
	if ((flg = divide_U10(a, b, c, d)) != -2)	//bが1桁でない場合以外の時の除算
		return flg;

	//ここから++の除算
	copyNumber(&abs_a, &rem);

	while (numComp(&rem, &abs_b) >= 0){
		if (sub(&rem, &abs_b, &rem))
			return -2;
		if (increment(&ans, &ans))
			return -2;
	}

	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
	if (setSign(&ans, SIGN_MINUS))	//どちらか一方のみ負のとき
		return -2;
	if (setSign(&rem, getSign(a)))		//余りの符号
		return -2;

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
	struct NUMBER ans, rem;
	int h = 0, i = KETA - 1;

	clearByZero(&ans);

	//余り : rem
	int r = divBy10(b, &ans);

	if (isZero(b) == 0)		//0除算
		return -1;
	if (isZero(&ans))		//bが1桁でないなら
		return -2;
	if (isZero(a) == 0) {	//分子が0
		clearByZero(c);
		clearByZero(d);
		return 0;
	}

	//bが1桁なら
	//b は rem と等しい(struct NUMBER -> int)

	for (i = KETA - 1; i >= 0; i--){
		int t = h * RADIX + a->n[i];
		h = t % r;
		ans.n[i] = t / r;
	}

	//どちらか一方のみ負のとき
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS) {
		if (setSign(&ans, SIGN_MINUS))
			return -3;
	}
	else {
		setSign(&ans, SIGN_PLUS);		//1桁の判別の際にcにマイナスの符号が入っている可能性があるため設定する
	}

	if (setInt(&rem, h))		//余り
		return -3;
	if (setSign(&rem, getSign(a)))		//余りの符号
		return -3;

	copyNumber(&ans, c);
	copyNumber(&rem, d);

	return 0;
}


//*****************************************************************
//概要：多倍長変数a, bの商を求めてcに格納し、余りをdに格納する。(開発版：安定)
//引数：struct NUMBER* a : 除算する多倍長変数(1), struct NUMBER* b : 除算する多倍長変数(2), struct NUMBER* c : 商を格納する多倍長変数, struct NUMBER* d : 余りを格納する多倍長変数
//戻値：成功 : 0, 失敗(0除算) : -1(c, dの値は変化しない), 失敗(その他エラー)：-2(c, dの値は変化しない)
//*****************************************************************
int Dev_divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans, tmp_a, tmp_b, tmp_d, tmp_e, tmp_check;

	if (isZero(b) == 0)		//0除算
		return -1;
	if (isZero(a) == 0) {	//分子が0のとき
		clearByZero(c);
		clearByZero(d);
		return 0;
	}

	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);
	clearByZero(&tmp_check);

	//ここから++の除算

	getAbs(a, &tmp_a);
	getAbs(b, &tmp_b);

	while (numComp(&tmp_a, &tmp_b) >= 0) {	//a < b でないなら
		copyNumber(&tmp_b, &tmp_d);

		copyNumber(&SN_1, &tmp_e);

		int rem = divBy10(&tmp_a, &tmp_check);
		while (1) {
			int flg = numComp(&tmp_check, &tmp_d);
			if (flg == -1)						//tmp_dをmulBy10するとtmp_aを超える
				break;
			if (flg == 0 && rem < tmp_d.n[0])	//等しいときは余りremによって決まる. rem>0ならtmp_a > tmp_d*10    * RADIX
				break;							//d.n[0]との比較は1回目のため, 2回目以降はd.n[0]は0なので常にfalse
			//tmp_a >= tmp_d * 10のとき * RADIX
			if (mulBy10(&tmp_d, &tmp_d))
				return -2;
			if (mulBy10(&tmp_e, &tmp_e))
				return -2;
		}

		if (sub(&tmp_a, &tmp_d, &tmp_a))
			return -2;
		if (add(&ans, &tmp_e, &ans))
			return -2;
	}

	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, -1))	//どちらか一方のみ負のとき
			return -2;
	if (setSign(&tmp_a, getSign(a)))		//余りの符号
		return -2;

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
	struct NUMBER ans, tmp_a, tmp_b, tmp_d, tmp_e;
	//手順1
	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);
	//0除算
	if (isZero(b) == 0)
		return -1;
	//分子が0のとき
	if (isZero(a) == 0){
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//マイナス処理
	//少なくともどちらか一方が負のとき
	if (getSign(a) == SIGN_MINUS || getSign(b) == SIGN_MINUS) {
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide_X(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
			return num;
		//どちらか一方のみ負のとき
		if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
			if (setSign(&ans, SIGN_MINUS))
				return -2;
		//余りの符号 (余りの符号は常に割られる数の符号に依存する)
		if (setSign(&tmp_d, getSign(a)))
			return -2;

		copyNumber(&ans, c);
		copyNumber(&tmp_d, d);

		return 0;
	}

	copyNumber(a, &tmp_a);
	copyNumber(b, &tmp_b);

	//手順2
	while (numComp(&tmp_a, &tmp_b) != -1) {
		//手順3
		copyNumber(&tmp_b, &tmp_d);
		//手順4
		copyNumber(&SN_1, &tmp_e);
		//手順5

		//dを10倍していくと最上位bitが非0になってもなおa>dとなることがあるため, さらに10倍されてoverflow * RADIX
		//解決策1...常に余裕のある桁数を用意しておく
		//解決策2...最上位bitの値が非0になったときに特別な処理を描く
		while (1) {
			if (mulBy10(&tmp_d, &tmp_d))
				return -2;
			if (numComp(&tmp_a, &tmp_d) != 1) {
				divBy10(&tmp_d, &tmp_d);	//これだとKETA-1まで埋まるような数字の時に不具合が起きる可能性がある
				break;
			}
			//手順6
			if (mulBy10(&tmp_e, &tmp_e))
				return -2;
		}

		//手順7
		if (sub(&tmp_a, &tmp_d, &tmp_a))
			return -2;

		if (add(&ans, &tmp_e, &ans))
			return -2;
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
	struct NUMBER ans, tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	if (getSign(b) == SIGN_MINUS)	//bが負のとき
		return -2;
	if (isZero(b) == 0) {	//b = 0のとき
		copyNumber(&SN_1, &ans);
		copyNumber(&ans, c);
		return 0;
	}

	//累乗
	copyNumber(a, &ans);
	copyNumber(b, &tmp);
	while (1) {
		if (decrement(&tmp, &tmp))
			return -1;
		if (isZero(&tmp) == 0)
			break;
		if (Dev_multiple(&ans, a, &ans))
			return -1;
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
	
	clearByZero(&ans);
	//bが負のとき
	if (getSign(b) == SIGN_MINUS)
		return -2;
	//b = 0のとき
	if (isZero(b) == 0)	//c = 1	
		copyNumber(&SN_1, &ans);
	else
		if (Cul_power(a, b, &ans))
			return -1;

	copyNumber(&ans, c);

	return 0;
}

int Cul_power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER tmp, div;
	
	clearByZero(&div);
	clearByZero(&tmp);

	if (isZero(b) == 0) {			// b = 0 ?
		copyNumber(&SN_1, c);
		return 0;
	}
	if (numComp(b, &SN_1) == 0) {	//b = 1 ?
		copyNumber(a, c);
		return 0;
	}

	if (Dev_divide(b, &SN_2, &div, &tmp))//tmp = 2 -> 剰余, div = b / 2
		return -1;
	if (isZero(&tmp) == 0) {		//偶数の時
		if (Dev_multiple(a, a, &tmp))	//a^2
			return -1;
		if (Cul_power(&tmp, &div, &tmp))
			return -1;
	}
	else {
		if (decrement(b, &tmp))
			return -1;
		if (Cul_power(a, &tmp, &tmp))
			return -1;
		if (Dev_multiple(a, &tmp, &tmp))
			return -1;
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

	if (getSign(a) < 0)	//a<0
		return -2;
	if (isZero(a) == 0){	//a=0
		copyNumber(&SN_1, b);
		return 0;
	}

	copyNumber(a, &tmp);
	copyNumber(a, &ans);

	while (1) {
		if (decrement(&tmp, &tmp))
			return -1;
		if (isZero(&tmp) == 0)
			break;
		if (Dev_multiple(&ans, &tmp, &ans))
			return -1;
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
	struct NUMBER abs_a, abs_b, rem;

	clearByZero(&abs_a);
	clearByZero(&abs_b);
	clearByZero(&rem);
	
	getAbs(a, &abs_a);
	getAbs(b, &abs_b);
	
	if (numComp(&abs_a, &abs_b) == -1)	//a < b なら
		swap(&abs_a, &abs_b);
	if (isZero(&abs_b) == 0) {
		copyNumber(&abs_a, c);
		return 0;
	}
	while (1) {
		if (Dev_divide(&abs_a, &abs_b, &SN_trush, &rem))
			return -1;
		copyNumber(&abs_b, &abs_a);
		copyNumber(&rem, &abs_b);
		if (isZero(&rem) == 0)
			break;
	}

	//ここにきたとき除数はnum1になる
	copyNumber(&abs_a, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数a, bにおいてaとbの最小公倍数をcに格納する
//引数：struct NUMBER* a : 最小公倍数を求める多倍長変数, struct NUMBER* b : 最小公倍数を求める多倍長変数, struct NUMBER* c : 最小公倍数を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(cの値は変化しない)
///////////////////////////////////////////////////////////////////
int lcm(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, abs_a, abs_b;
	
	clearByZero(&ans);
	clearByZero(&abs_a);
	clearByZero(&abs_b);

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (Dev_multiple(&abs_a, &abs_b, &ans))
		return -1;
	//ans = |a|*|b|
	if (gcd(a, b, &abs_a))		//gcdは符号に影響しないためa,bをそのまま用いている
		return -1;
	//num1 = gcd(a,b)
	if (Dev_divide(&ans, &abs_a, &ans, &SN_trush))
		return -1;

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
	struct NUMBER ans, abs_a, abs_b;

	clearByZero(&ans);
	clearByZero(&abs_a);
	clearByZero(&abs_b);

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (gcd(a, b, &ans))		//gcdは符号に影響しないためa,bをそのまま用いている
		return -1;
	if (Dev_divide(&abs_a, &ans, &ans, &SN_trush))
		return -1;
	if (Dev_multiple(&ans, &abs_b, &ans))
		return -1;

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
	struct NUMBER num, rem, tmp;
	
	clearByZero(&num);
	clearByZero(&rem);
	clearByZero(&tmp);

	if (numComp(a, &SN_1) <= 0)	//a <= 1
		return 0;
	if (Dev_divide(a, &SN_2, &tmp, &rem))	//2で割る  tmp = a/2 ... これの範囲内でループする
		return 0;
	if (numComp(&tmp, &SN_1) == 0)	//a=2 (a/2=1)の時の処理	... 2は素数
		return 1;

	if (setInt(&num, 3))
		return 0;

	while (1) {
		if (Dev_divide(a, &num, &SN_trush, &rem))
			break;
		if (isZero(&rem) == 0)	//割り切れたとき
			break;
		if (add(&num, &SN_2, &num))
			break;
		if (numComp(&num, &tmp) > 0)
			return 1;
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
	struct NUMBER tmp_a, tmp_b, cnt;
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&cnt);
	
	if (numComp(a, &SN_0) < 0)	//a < 0 ?
		return -1;

	copyNumber(a, &tmp_a);	//tmp_a ... N
	copyNumber(&SN_1, &tmp_b);

	while (1) {
		if (numComp(&tmp_a, &tmp_b) < 0)	//tmp_a < tmp ?
			break;
		if (sub(&tmp_a, &tmp_b, &tmp_a))
			return -1;
		if (increment(&cnt, &cnt))
			return -1;
		if (add(&tmp_b, &SN_2, &tmp_b))
			return -1;
	}

	copyNumber(&cnt, b);

	return 0;
}


///////////////////////////////////////////////////////////////////
//概要：多倍長変数aにおいてaの平方根をNewton-Raphson法を用いて求めてbに格納する(正式にはsqrt(a)を超えない最大の整数をbに格納する)
//引数：struct NUMBER* a : 平方根を求める多倍長変数, struct NUMBER* b : 平方根を格納する多倍長変数
//戻値：成功 : 0, 失敗 : -1(bの値は変化しない)
///////////////////////////////////////////////////////////////////
int sqrt_newton(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER x;		//現在の平方根の近似値
	struct NUMBER x_b;		//1つ前のx
	struct NUMBER x_c;		//2つ前のx

	clearByZero(&x);
	clearByZero(&x_b);
	clearByZero(&x_c);

	if (numComp(a, &SN_0) < 0)		//a < 0
		return -11;
	if (numComp(a, &SN_0) == 0 || numComp(a, &SN_1) == 0) {	// a = 0 or 1 なら sqrt(a) = a
		copyNumber(a, b);
		return 0;
	}
	//初期値xの設定
	//if (Dev_divide(a, &SN_2, &x, &SN_trush))		//X = a / 2
	//	return -1;
	copyNumber(a, &x);
	int i = 0, cnt;
	while (x.n[KETA - 1 - i] == 0)
		i++;
	cnt = (KETA - (i / 2)) / 4 + KETA / 20;	//最上位bitまで値が入っている状態に最適化
	for (i = 0; i < cnt; i++)  //KETA/4+ROOP/5 , ROOP = KETA / 4
		divBy10(&x, &x);
	Dev_divide(&x, &SN_2, &x, &SN_trush);	// x = (a*10^(-(KETA/4+ROOP/5)))/2

	copyNumber(&x, &x_b);
	//copyNumber(&x, &x_c);
	while (1) {
		copyNumber(&x_b, &x_c);
		copyNumber(&x, &x_b);

		// x = (b + (N / b)) / 2
		if (Dev_divide(a, &x_b, &x, &SN_trush))
			return -12;
		if (add(&x, &x_b, &x))
			return -13;

		if (Dev_divide(&x, &SN_2, &x, &SN_trush))
			return -14;

		if (numComp(&x, &x_b) == 0)		// 収束
			break;
		if (numComp(&x, &x_c) == 0) {
			if (numComp(&x_b, &x) < 0)
				copyNumber(&x_b, &x);
			break;
		}
	}
	copyNumber(&x, b);
	return 0;
}


///////////////////////////////////////////////////////////////////
//                          以下分数用                           //
///////////////////////////////////////////////////////////////////

void B_clearByZero(struct BUNSU* a)
{
	clearByZero(&a->bunbo);
	clearByZero(&a->bunshi);
	B_setSign(a, SIGN_PLUS);
}

void B_dispNumber(struct BUNSU* a)
{
	int i;

	if (B_getSign(a) == SIGN_PLUS)	putchar('+');
	else							putchar('-');

#if RADIX == 10000
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunshi.n[i]);
		putchar('/');
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunbo.n[i]);
#else
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunshi.n[i]);
		putchar('/');
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunbo.n[i]);
#endif
}

int B_getSign(struct BUNSU* a)
{
	return a->sign;
}

int B_setSign(struct BUNSU* a, int sign)
{
	if (sign != SIGN_PLUS && sign != SIGN_MINUS)
		return -1;
	a->sign = sign;
	return 0;
}

void B_copyNumber(struct BUNSU* a, struct BUNSU* b)
{
	copyNumber(&a->bunshi, &b->bunshi);
	copyNumber(&a->bunbo, &b->bunbo);
	b->sign = a->sign;
}

void B_setRnd(struct BUNSU* a, int keta)
{
	setRnd(&a->bunshi, keta);
	setRnd(&a->bunbo, keta);
	setSign(&a->bunshi, SIGN_PLUS);
	setSign(&a->bunbo, SIGN_PLUS);
	B_setSign(a, (random() % 2) ? SIGN_PLUS : SIGN_MINUS);
}

int B_setInt(struct BUNSU* a, int bunshi, int bunbo)
{
	struct BUNSU ans;
	int sign = SIGN_PLUS;

	B_clearByZero(&ans);

	if (bunbo == 0)
		return -1;
	if (bunshi < 0) {
		sign = SIGN_MINUS;
		bunshi *= -1;
	}
	if (bunbo < 0) {
		sign *= -1;
		bunbo *= -1;
	}
	// bunshi >= 0, bunbo >= 0, sign = 1 or -1

	if (setInt(&ans.bunshi, bunshi))
		return -1;
	if (setInt(&ans.bunbo, bunbo))
		return -1;
	if (B_setSign(&ans, sign))
		return -1;


	B_clearByZero(a);
	B_copyNumber(&ans, a);

	return 0;
}

void B_getAbs(struct BUNSU* a, struct BUNSU* b)
{
	B_copyNumber(a, b);
	B_setSign(b, SIGN_PLUS);
}

int B_yakubun(struct BUNSU* a, struct BUNSU* b)
{
	struct NUMBER gcd_a;
	struct BUNSU ans;

	clearByZero(&gcd_a);
	B_clearByZero(&ans);

	if (gcd(&a->bunshi, &a->bunbo, &gcd_a))
		return -1;
	if (Dev_divide(&a->bunshi, &gcd_a, &ans.bunshi, &SN_trush))
		return -1;
	if (Dev_divide(&a->bunbo, &gcd_a, &ans.bunbo, &SN_trush))
		return -1;
	if (B_setSign(&ans, B_getSign(a)))
		return -1;
	B_copyNumber(&ans, b);
	return 0;
}

int B_multiple(struct BUNSU* a, struct BUNSU* b, struct BUNSU* c)
{
	struct BUNSU ans, bst_a, bst_b;
	struct NUMBER gcd_ab, gcd_ba;

	B_clearByZero(&ans);
	B_clearByZero(&bst_a);
	B_clearByZero(&bst_b);
	clearByZero(&gcd_ab);
	clearByZero(&gcd_ba);

	if (B_yakubun(a, &bst_a))
		return -1;
	if (B_yakubun(b, &bst_b))
		return -1;
	gcd(&bst_a.bunshi, &bst_b.bunbo, &gcd_ab);
	gcd(&bst_b.bunshi, &bst_a.bunbo, &gcd_ba);
	
	Dev_divide(&bst_a.bunshi, &gcd_ab, &bst_a.bunshi, &SN_trush);
	Dev_divide(&bst_b.bunbo, &gcd_ab, &bst_b.bunbo, &SN_trush);
	Dev_divide(&bst_b.bunshi, &gcd_ba, &bst_b.bunshi, &SN_trush);
	Dev_divide(&bst_a.bunbo, &gcd_ba, &bst_a.bunbo, &SN_trush);

	if (Dev_multiple(&a->bunshi, &b->bunshi, &ans.bunshi))
		return -1;
	if (Dev_multiple(&a->bunbo, &b->bunbo, &ans.bunbo))
		return -1;
	if (B_setSign(&ans, B_getSign(a) * B_getSign(b)))
		return -1;
	if (B_yakubun(&ans, &ans))
		return -1;
	B_copyNumber(&ans, c);
	return 0;
}

int B_divide(struct BUNSU* a, struct BUNSU* b, struct BUNSU* c)
{
	struct BUNSU ans, rev;

	B_clearByZero(&ans);
	B_clearByZero(&rev);

	copyNumber(&b->bunshi, &rev.bunbo);
	copyNumber(&b->bunbo, &rev.bunshi);
	if (B_setSign(&rev, B_getSign(b)))
		return -1;
	if (B_multiple(a, &rev, &ans))
		return -1;
	B_copyNumber(&ans, c);
	return 0;
}

int B_add(struct BUNSU* a, struct BUNSU* b, struct BUNSU* c) // (a/b)+(c/d) = (ad+bc)/(bd)
{
	struct BUNSU ans;
	struct NUMBER mul_ad, mul_bc, tmp;

	clearByZero(&mul_ad);
	clearByZero(&mul_bc);
	clearByZero(&tmp);
	B_clearByZero(&ans);
	
	//分子
	if (Dev_multiple(&a->bunshi, &b->bunbo, &mul_ad))	//ad
		return -11;
	if (Dev_multiple(&a->bunbo, &b->bunshi, &mul_bc))	//bc
		return -12;
	if (setSign(&mul_ad, B_getSign(a)))
		return -13;
	if (setSign(&mul_bc, B_getSign(b)))
		return -14;
	if (add(&mul_ad, &mul_bc, &tmp))	//ad+bc -> tmp
		return -15;
	if (B_setSign(&ans, getSign(&tmp)))		//符号
		return -16;
	getAbs(&tmp, &tmp);
	copyNumber(&tmp, &ans.bunshi);

	//分母
	clearByZero(&tmp);
	if (Dev_multiple(&a->bunbo, &b->bunbo, &tmp))
		return -17;
	copyNumber(&tmp, &ans.bunbo);
	
	if (B_yakubun(&ans, &ans))
		return -18;
	B_copyNumber(&ans, c);
	return 0;
}

int B_sub(struct BUNSU* a, struct BUNSU* b, struct BUNSU* c)
{
	struct BUNSU ans;
	struct NUMBER mul_ad, mul_bc, tmp;

	clearByZero(&mul_ad);
	clearByZero(&mul_bc);
	clearByZero(&tmp);
	B_clearByZero(&ans);

	//分子
	if (Dev_multiple(&a->bunshi, &b->bunbo, &mul_ad))	//ad
		return -11;
	if (Dev_multiple(&a->bunbo, &b->bunshi, &mul_bc))	//bc
		return -12;
	if (setSign(&mul_ad, B_getSign(a)))
		return -13;
	if (setSign(&mul_bc, B_getSign(b)))
		return -14;
	if (sub(&mul_ad, &mul_bc, &tmp))	//ad-bc -> tmp
		return -15;
	if (B_setSign(&ans, getSign(&tmp)))		//符号
		return -16;
	getAbs(&tmp, &tmp);
	copyNumber(&tmp, &ans.bunshi);

	//分母
	clearByZero(&tmp);
	if (Dev_multiple(&a->bunbo, &b->bunbo, &tmp))
		return -17;
	copyNumber(&tmp, &ans.bunbo);

	if (B_yakubun(&ans, &ans))
		return -18;
	B_copyNumber(&ans, c);
	return 0;
}

void NtoB_copyNumber(struct NUMBER* a, struct NUMBER* b, struct BUNSU* c)
{
	copyNumber(a, &c->bunshi);		//分子
	copyNumber(b, &c->bunbo);		//分母
}
//符号はbにつく
void BtoN_copyNumber(struct BUNSU* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;
	clearByZero(&ans);
	copyNumber(&a->bunshi, &ans);	//分子には符号をつけるため一度ansに入れている
	setSign(&ans, B_getSign(a));
	copyNumber(&ans, b);
	copyNumber(&a->bunbo, c);
}

int B_FractionToReal(struct BUNSU* a, struct NUMBER* b)
{
	struct NUMBER ans;
	clearByZero(&ans);
	clearByZero(&SN_trush);

	if (Dev_divide(&a->bunshi, &a->bunbo, &ans, &SN_trush))
		return -1;
	if (setSign(&ans, B_getSign(a)))
		return -1;
	copyNumber(&ans, b);
	return 0;
}

int B_RealToFraction(struct NUMBER* a, struct BUNSU* b)
{
	struct BUNSU ans;
	B_clearByZero(&ans);
	//符号
	if (B_setSign(&ans, getSign(a)))
		return -1;
	//分子
	getAbs(a, &ans.bunshi);
	//分母
	copyNumber(&SN_1, &ans.bunbo);
	
	B_copyNumber(&ans, b);
	return 0;
}


///////////////////////////////////////////////////////////////////
//                        以下時間計測用                         //
///////////////////////////////////////////////////////////////////

#ifndef _DEBUG

static struct timeval tv;
static double tstart, tend;

void timeStart(void)
{
	timeCount = time(NULL);
}
unsigned int timeStop(void)
{
	time_t stop = time(NULL);
	time_t diff = stop - timeCount;
	timeCount = 0;
	return (unsigned int)diff;
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
unsigned int timeStop(void)
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
		setRnd(&tmp_a, KETA-1);
		setRnd(&tmp_b, (random() % KETA) + 1);
		clockStart();
		i = func(&tmp_a, &tmp_b, &tmp_c, &tmp_d);
		flag += clockStop();
		tmp += ((i != 0 && i != -1) ? 1 : 0);
		if (i != 0 && i != -1)
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
