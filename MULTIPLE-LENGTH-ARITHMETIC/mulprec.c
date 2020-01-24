#include "mulprec.h"



//*****************************************************************
//ŠT—vF‘½”{’·‰‰Z‚É‚¨‚¯‚é‰Šúİ’è‚ğs‚¢, struct NUMBER Œ^ ’è” SN_0...0, SN_1...1, SN_2...2
//ˆø”F‚È‚µ
//–ß’lF‚È‚µ
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
//ŠT—vF‘½”{’·•Ï”‚ğ0‚É‰Šú‰»‚·‚é
//ˆø”Fstruct NUMBER* a : ‰Šú‰»‚·‚é‘½”{’·•Ï”
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void clearByZero(struct NUMBER* a)
{
	copyNumber(&SN_0, a);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚ğ•\¦‚·‚é
//ˆø”Fstruct NUMBER* a : •\¦‚·‚é‘½”{’·•Ï”
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void dispNumber(struct NUMBER* a)
{
	int i;
	if (getSign(a) == SIGN_PLUS)	putchar('+');
	else							putchar('-');

	if (KETA == 1000) {
		for (i = KETA - 1; i >= 0; i--)
			printf("%04d", a->n[i]);        //”šŠm”F—p
	}
	else if (KETA == 10) {
		for (i = KETA - 1; i >= 0; i--)
			printf("%1d", a->n[i]);        //”šŠm”F—p
	}

}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚É—”‚ğŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : —”‚ğŠi”[‚·‚é‘½”{’·•Ï”, int k : ¶¬‚·‚é—”‚ÌŒ…”
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void setRnd(struct NUMBER* a, int k)
{
	int i;
	//”š
	for (i = 0; i < k; i++)
		a->n[i] = random() % RADIX;
	//•„†
	setSign(a, (random() % 2 == 1) ? SIGN_PLUS : SIGN_MINUS);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚ğƒRƒs[‚·‚é
//ˆø”Fstruct NUMBER* a : ƒRƒs[Œ³‚Ì‘½”{’·•Ï”, struct NUMBER* b : ƒRƒs[æ‚Ì‘½”{’·•Ï”
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	*b = *a;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚Ìâ‘Î’l‚ğ‹‚ß‚ÄŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : â‘Î’l‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : â‘Î’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	setSign(b, SIGN_PLUS);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚ª0‚©‚Ç‚¤‚©‚ğ”»•Ê‚·‚é
//ˆø”Fstruct NUMBER* a : ”»•Ê‚·‚é‘½”{’·•Ï”
//–ß’lF0‚Ì‚Æ‚« : 0, ‚»‚êˆÈŠO‚Ì‚Æ‚« : -1
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
//ŠT—vF‘½”{’·•Ï”‚ğ10”{‚µ‚ÄŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : 10”{‚µ‚½‚¢‘½”{’·•Ï”, struct NUMBER* b : ŒvZ‚µ‚½’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(Œ…‚ ‚Ó‚ê) : -1(b‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼) : -1(b‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), 
//•â‘«FRADIXi”‚É•ÏX‚µ‚½‚½‚ß10”{‚Å‚Í‚È‚­RADIX”{‚É‚È‚éB
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
//ŠT—vF‘½”{’·•Ï”‚ğ10‚ÅŠ„‚Á‚½¤‚ğŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : 1/10‚É‚µ‚½‚¢‘½”{’·•Ï”, struct NUMBER* b : ŒvZ‚µ‚½’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : —]‚è
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
//ŠT—vF‘½”{’·•Ï”‚ÉintŒ^‚Ì”š‚ğŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Ši”[‚³‚ê‚é‘½”{’·•Ï”, int x : Ši”[‚µ‚½‚¢‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(a‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int setInt(struct NUMBER* a, int x)
{
	int i = 0;
	struct NUMBER ans;
	clearByZero(&ans);

	if (x < 0) {	//a‚Í‚·‚Å‚É{‚È‚Ì‚Åx‚ª-‚Ì‚Æ‚«‚Ì‚İsetSign‚·‚é
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
//ŠT—vF‘½”{’·•Ï”‚Ì•„†‚ğİ’è‚·‚é
//ˆø”Fstruct NUMBER* a : İ’è‚³‚ê‚é‘½”{’·•Ï”, int x : İ’è‚·‚é•„†(+ : 1, - : -1)
//–ß’lF¬Œ÷ : 0, ¸”s : -1(a‚Ì•„†‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int setSign(struct NUMBER* a, int s)
{
	if (s != SIGN_PLUS && s != SIGN_MINUS)
		return -1;
	a->sign = s;

	return 0;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚Ì•„†‚ğæ“¾‚·‚é
//ˆø”Fstruct NUMBER* a : •„†‚ğæ“¾‚·‚é‘½”{’·•Ï”
//–ß’lF³ : 1, •‰ : -1
///////////////////////////////////////////////////////////////////
int getSign(struct NUMBER* a)
{
	return a->sign;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚ğ”äŠr‚·‚é
//ˆø”Fstruct NUMBER* a : ”äŠr‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : ”äŠr‚·‚é‘½”{’·•Ï”(2)
//–ß’lFa == b : 0, a > b : 1, a < b : -1
///////////////////////////////////////////////////////////////////
int numComp(struct NUMBER* a, struct NUMBER* b)
{
	int sign_a = getSign(a), sign_b = getSign(b);
	//-0‚ª•´‚ê‚ñ‚¾‚Ì‘Îô
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
//ŠT—vF‘½”{’·•Ï”a, b‚ÌŒğŠ·‚·‚é
//ˆø”Fstruct NUMBER* a : ŒğŠ·‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : ŒğŠ·‚·‚é‘½”{’·•Ï”(2)
//–ß’lF‚È‚µ
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
//ŠT—vF‘½”{’·•Ï”a, b‚Ì˜a‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : ‰ÁZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : ‰ÁZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ˜a‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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

	//‰ÁZ
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
//ŠT—vF‘½”{’·•Ï”a‚ğƒCƒ“ƒNƒŠƒƒ“ƒg‚µ‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : ƒCƒ“ƒNƒŠƒƒ“ƒg‚·‚é‘½”{’·•Ï”, struct NUMBER* b : Œ‹‰Ê‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int increment(struct NUMBER* a, struct NUMBER* b)
{
	return add(a, &SN_1, b);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚Ì·‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Œ¸Z‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : Œ¸Z‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ·‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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

	//Œ¸Z
	int i, d, flg = 0;

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (numComp(&abs_a, &abs_b) < 0) {			//a < b
		swap(&abs_a, &abs_b);
		if (setSign(&ans, getSign(&ans) * SIGN_MINUS)) // a < 0, b < 0 ‚Ì‚Æ‚«‚Éƒ}ƒCƒiƒX‚É‚È‚Á‚Ä‚¢‚é‰Â”\«‚ª‚ ‚é‚Ì‚Å”½“]
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
//ŠT—vF‘½”{’·•Ï”a‚ğƒfƒNƒŠƒƒ“ƒg‚µ‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : ƒfƒNƒŠƒƒ“ƒg‚·‚é‘½”{’·•Ï”, struct NUMBER* b : Œ‹‰Ê‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int decrement(struct NUMBER* a, struct NUMBER* b)
{
	return sub(a, &SN_1, b);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚ÌÏ‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : æZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : æZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : Ï‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0) {		//‚·‚­‚È‚­‚Æ‚à‚Ç‚¿‚ç‚©ˆê•û‚ª0‚Ì‚Æ‚«
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
	//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))
			return -1;

	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//ŠT—vF‘½”{’·•Ï”a, b‚ÌÏ‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é(ŠJ”­”Å)
//ˆø”Fstruct NUMBER* a : æZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : æZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : Ï‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//•â‘«FmultipleŠÖ”‚Ì–ñ3”{(KETA=10), –ñ16.7”{(KETA=100)‚Ì‘¬“x. (KETA / 2)
//*****************************************************************
int Dev_multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0) {		//‚Ç‚¿‚ç‚©ˆê•û‚ª0‚Ì‚Æ‚«
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);
	clearByZero(&tmp);

	for (i = KETA - 1; i >= 0; i--) {		//b‚Ìã‚ÌŒ…‚©‚çs‚¤
		if (b->n[i]) {
			if (b->n[i] == 1) {
				copyNumber(a, &tmp);
			}
			else {
				for (j = 0; j < KETA; j++) {		//ˆê’i•ª‚Ì“š‚¦‚ğo‚·
					int e = a->n[j] * b->n[i] + flag;
					tmp.n[j] = e % RADIX;
					flag = e / RADIX;
				}
				if (flag)
					return -1;
			}

			if (add(&ans, &tmp, &ans))			//‰ÁZ
				return -1;
		}
		if (i > 0 && mulBy10(&ans, &ans))	//ÅŒã‚Ì1‰ñˆÈŠO‚Å10”{ * RADIX”{
			return -1;
	}
	//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))
			return -1;

	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚éB
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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

	//1Œ…”»•Ê—p
	int flg;
	if ((flg = divide_U10(a, b, c, d)) != -2)	//b‚ª1Œ…‚Å‚È‚¢ê‡ˆÈŠO‚Ì‚ÌœZ
		return flg;

	//‚±‚±‚©‚ç++‚ÌœZ
	copyNumber(&abs_a, &rem);

	while (numComp(&rem, &abs_b) >= 0) {
		if (sub(&rem, &abs_b, &rem))
			return -2;
		if (increment(&ans, &ans))
			return -2;
	}

	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))	//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
			return -2;
	if (setSign(&rem, getSign(a)))		//—]‚è‚Ì•„†
		return -2;

	copyNumber(&ans, c);
	copyNumber(&rem, d);

	return 0;
}


//*****************************************************************
//ŠT—vF‘½”{’·•Ï”a, b(b‚Í1Œ…)‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚éB(ŠJ”­”ÅFˆÀ’è)
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(b‚ª1Œ…‚Å‚È‚¢)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-3(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//*****************************************************************
int divide_U10(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans, rem;
	int h = 0, i = KETA - 1;

	clearByZero(&ans);

	//—]‚è : rem
	int r = divBy10(b, &ans);

	if (isZero(b) == 0)		//0œZ
		return -1;
	if (isZero(&ans))		//b‚ª1Œ…‚Å‚È‚¢‚È‚ç
		return -2;
	if (isZero(a) == 0) {	//•ªq‚ª0
		clearByZero(c);
		clearByZero(d);
		return 0;
	}

	//b‚ª1Œ…‚È‚ç
	//b ‚Í rem ‚Æ“™‚µ‚¢(struct NUMBER -> int)

	for (i = KETA - 1; i >= 0; i--) {
		int t = h * RADIX + a->n[i];
		h = t % r;
		ans.n[i] = t / r;
	}

	//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS) {
		if (setSign(&ans, SIGN_MINUS))
			return -3;
	}
	else {
		setSign(&ans, SIGN_PLUS);		//1Œ…‚Ì”»•Ê‚ÌÛ‚Éc‚Éƒ}ƒCƒiƒX‚Ì•„†‚ª“ü‚Á‚Ä‚¢‚é‰Â”\«‚ª‚ ‚é‚½‚ßİ’è‚·‚é
	}

	if (setInt(&rem, h))		//—]‚è
		return -3;
	if (setSign(&rem, getSign(a)))		//—]‚è‚Ì•„†
		return -3;

	copyNumber(&ans, c);
	copyNumber(&rem, d);

	return 0;
}


//*****************************************************************
//ŠT—vF‘½”{’·•Ï”a, b‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚éB(ŠJ”­”ÅFˆÀ’è)
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//*****************************************************************
int Dev_divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans, tmp_a, tmp_b, tmp_d, tmp_e, tmp_check;

	if (isZero(b) == 0)		//0œZ
		return -1;
	if (isZero(a) == 0) {	//•ªq‚ª0‚Ì‚Æ‚«
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

	//‚±‚±‚©‚ç++‚ÌœZ

	getAbs(a, &tmp_a);
	getAbs(b, &tmp_b);

	while (numComp(&tmp_a, &tmp_b) >= 0) {	//a < b ‚Å‚È‚¢‚È‚ç
		copyNumber(&tmp_b, &tmp_d);

		copyNumber(&SN_1, &tmp_e);

		int rem = divBy10(&tmp_a, &tmp_check);
		while (1) {
			int flg = numComp(&tmp_check, &tmp_d);
			if (flg == -1)						//tmp_d‚ğmulBy10‚·‚é‚Ætmp_a‚ğ’´‚¦‚é
				break;
			if (flg == 0 && rem < tmp_d.n[0])	//“™‚µ‚¢‚Æ‚«‚Í—]‚èrem‚É‚æ‚Á‚ÄŒˆ‚Ü‚é. rem>0‚È‚çtmp_a > tmp_d*10    * RADIX
				break;							//d.n[0]‚Æ‚Ì”äŠr‚Í1‰ñ–Ú‚Ì‚½‚ß, 2‰ñ–ÚˆÈ~‚Íd.n[0]‚Í0‚È‚Ì‚Åí‚Éfalse
			//tmp_a >= tmp_d * 10‚Ì‚Æ‚« * RADIX
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
		if (setSign(&ans, -1))	//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
			return -2;
	if (setSign(&tmp_a, getSign(a)))		//—]‚è‚Ì•„†
		return -2;

	copyNumber(&tmp_a, d);
	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//ŠT—vF‘½”{’·•Ï”a, b‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚éB(ŠJ”­”ÅF•sˆÀ’è)
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//•â‘«FÅãˆÊbit‚Ü‚Å’l‚ª“ü‚Á‚Ä‚¢‚éó‘Ô‚¾‚Æoverflow‚·‚éê‡‚ª‚ ‚é(—áFKETA=5,a=99999,b=99998)
//*****************************************************************
int Dev_divide_X(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans, tmp_a, tmp_b, tmp_d, tmp_e;
	//è‡1
	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);
	//0œZ
	if (isZero(b) == 0)
		return -1;
	//•ªq‚ª0‚Ì‚Æ‚«
	if (isZero(a) == 0) {
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//ƒ}ƒCƒiƒXˆ—
	//­‚È‚­‚Æ‚à‚Ç‚¿‚ç‚©ˆê•û‚ª•‰‚Ì‚Æ‚«
	if (getSign(a) == SIGN_MINUS || getSign(b) == SIGN_MINUS) {
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide_X(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
			return num;
		//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
		if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
			if (setSign(&ans, SIGN_MINUS))
				return -2;
		//—]‚è‚Ì•„† (—]‚è‚Ì•„†‚Íí‚ÉŠ„‚ç‚ê‚é”‚Ì•„†‚ÉˆË‘¶‚·‚é)
		if (setSign(&tmp_d, getSign(a)))
			return -2;

		copyNumber(&ans, c);
		copyNumber(&tmp_d, d);

		return 0;
	}

	copyNumber(a, &tmp_a);
	copyNumber(b, &tmp_b);

	//è‡2
	while (numComp(&tmp_a, &tmp_b) != -1) {
		//è‡3
		copyNumber(&tmp_b, &tmp_d);
		//è‡4
		copyNumber(&SN_1, &tmp_e);
		//è‡5

		//d‚ğ10”{‚µ‚Ä‚¢‚­‚ÆÅãˆÊbit‚ª”ñ0‚É‚È‚Á‚Ä‚à‚È‚¨a>d‚Æ‚È‚é‚±‚Æ‚ª‚ ‚é‚½‚ß, ‚³‚ç‚É10”{‚³‚ê‚Äoverflow * RADIX
		//‰ğŒˆô1...í‚É—]—T‚Ì‚ ‚éŒ…”‚ğ—pˆÓ‚µ‚Ä‚¨‚­
		//‰ğŒˆô2...ÅãˆÊbit‚Ì’l‚ª”ñ0‚É‚È‚Á‚½‚Æ‚«‚É“Á•Ê‚Èˆ—‚ğ•`‚­
		while (1) {
			if (mulBy10(&tmp_d, &tmp_d))
				return -2;
			if (numComp(&tmp_a, &tmp_d) != 1) {
				divBy10(&tmp_d, &tmp_d);	//‚±‚ê‚¾‚ÆKETA-1‚Ü‚Å–„‚Ü‚é‚æ‚¤‚È”š‚Ì‚É•s‹ï‡‚ª‹N‚«‚é‰Â”\«‚ª‚ ‚é
				break;
			}
			//è‡6
			if (mulBy10(&tmp_e, &tmp_e))
				return -2;
		}

		//è‡7
		if (sub(&tmp_a, &tmp_d, &tmp_a))
			return -2;

		if (add(&ans, &tmp_e, &ans))
			return -2;
	}

	//è‡10
	copyNumber(&tmp_a, d);
	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚É‚¨‚¢‚Äa‚Ìbæ‚ğc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : —İæ‚³‚ê‚é‘½”{’·•Ï”, struct NUMBER* b :	—İæ‚Ìã‚Ì‚Æ‚±‚Ì‘½”{’·•Ï”, struct NUMBER* c : —İæ‚µ‚½’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s (ƒI[ƒo[ƒtƒ[/ƒAƒ“ƒ_[ƒtƒ[): -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(b<0)F-2(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	if (getSign(b) == SIGN_MINUS)	//b‚ª•‰‚Ì‚Æ‚«
		return -2;
	if (isZero(b) == 0) {	//b = 0‚Ì‚Æ‚«
		copyNumber(&SN_1, &ans);
		copyNumber(&ans, c);
		return 0;
	}

	//—İæ
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
//ŠT—vF‘½”{’·•Ï”a, b‚É‚¨‚¢‚Äa‚Ìbæ‚ğc‚ÉŠi”[‚·‚é(ŠJ”­”Å)
//ˆø”Fstruct NUMBER* a : —İæ‚³‚ê‚é‘½”{’·•Ï”, struct NUMBER* b :	—İæ‚Ìã‚Ì‚Æ‚±‚Ì‘½”{’·•Ï”, struct NUMBER* c : —İæ‚µ‚½’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s (ƒI[ƒo[ƒtƒ[/ƒAƒ“ƒ_[ƒtƒ[): -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(b<0)F-2(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//*****************************************************************
int Dev_power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;

	clearByZero(&ans);
	//b‚ª•‰‚Ì‚Æ‚«
	if (getSign(b) == SIGN_MINUS)
		return -2;
	//b = 0‚Ì‚Æ‚«
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

	if (Dev_divide(b, &SN_2, &div, &tmp))//tmp = 2 -> è—], div = b / 2
		return -1;
	if (isZero(&tmp) == 0) {		//‹ô”‚Ì
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
//ŠT—vF‘½”{’·•Ï”a‚É‚¨‚¢‚Äa‚ÌŠKæ(a!)‚ğb‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : ŠKæ‚·‚é‘½”{’·•Ï”, struct NUMBER* b : ŠKæ‚µ‚½’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(ƒI[ƒo[ƒtƒ[/ƒAƒ“ƒ_[ƒtƒ[) : -1(b‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(a<0) : -2(b‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int factorial(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER ans;
	struct NUMBER tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	if (getSign(a) < 0)	//a<0
		return -2;
	if (isZero(a) == 0) {	//a=0
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
//ŠT—vF‘½”{’·•Ï”a, b‚É‚¨‚¢‚Äa‚Æb‚ÌÅ‘åŒö–ñ”‚ğc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Å‘åŒö–ñ”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : Å‘åŒö–ñ”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* c : Å‘åŒö–ñ”‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int gcd(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER abs_a, abs_b, rem;

	clearByZero(&abs_a);
	clearByZero(&abs_b);
	clearByZero(&rem);

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (numComp(&abs_a, &abs_b) == -1)	//a < b ‚È‚ç
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

	//‚±‚±‚É‚«‚½‚Æ‚«œ”‚Ínum1‚É‚È‚é
	copyNumber(&abs_a, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚É‚¨‚¢‚Äa‚Æb‚ÌÅ¬Œö”{”‚ğc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Å¬Œö”{”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : Å¬Œö”{”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* c : Å¬Œö”{”‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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
	if (gcd(a, b, &abs_a))		//gcd‚Í•„†‚É‰e‹¿‚µ‚È‚¢‚½‚ßa,b‚ğ‚»‚Ì‚Ü‚Ü—p‚¢‚Ä‚¢‚é
		return -1;
	//num1 = gcd(a,b)
	if (Dev_divide(&ans, &abs_a, &ans, &SN_trush))
		return -1;

	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//ŠT—vF‘½”{’·•Ï”a, b‚É‚¨‚¢‚Äa‚Æb‚ÌÅ¬Œö”{”‚ğc‚ÉŠi”[‚·‚é(ŠJ”­”Å)
//ˆø”Fstruct NUMBER* a : Å¬Œö”{”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : Å¬Œö”{”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* c : Å¬Œö”{”‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//•â‘«F|a|*|b|/gcd(a,b) -> |a|/gcd(a,b)*|b| ‚É•ÏX
//*****************************************************************
int Dev_lcm(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, abs_a, abs_b;

	clearByZero(&ans);
	clearByZero(&abs_a);
	clearByZero(&abs_b);

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (gcd(a, b, &ans))		//gcd‚Í•„†‚É‰e‹¿‚µ‚È‚¢‚½‚ßa,b‚ğ‚»‚Ì‚Ü‚Ü—p‚¢‚Ä‚¢‚é
		return -1;
	if (Dev_divide(&abs_a, &ans, &ans, &SN_trush))
		return -1;
	if (Dev_multiple(&ans, &abs_b, &ans))
		return -1;

	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a‚É‚¨‚¢‚Äa‚ª‘f”‚©”»•Ê‚·‚é
//ˆø”Fstruct NUMBER* a : ‘f”‚©”»•Ê‚·‚é‘½”{’·•Ï”
//–ß’lF‘f”‚Å‚ ‚é : 1, ‘f”‚Å‚È‚¢‚Ü‚½‚Í¸”s : 0
///////////////////////////////////////////////////////////////////
int isPrime(struct NUMBER* a)
{
	struct NUMBER num, rem, tmp;

	clearByZero(&num);
	clearByZero(&rem);
	clearByZero(&tmp);

	if (numComp(a, &SN_1) <= 0)	//a <= 1
		return 0;
	if (Dev_divide(a, &SN_2, &tmp, &rem))	//2‚ÅŠ„‚é  tmp = a/2 ... ‚±‚ê‚Ì”ÍˆÍ“à‚Åƒ‹[ƒv‚·‚é
		return 0;
	if (numComp(&tmp, &SN_1) == 0)	//a=2 (a/2=1)‚Ì‚Ìˆ—	... 2‚Í‘f”
		return 1;

	if (setInt(&num, 3))
		return 0;

	while (1) {
		if (Dev_divide(a, &num, &SN_trush, &rem))
			break;
		if (isZero(&rem) == 0)	//Š„‚èØ‚ê‚½‚Æ‚«
			break;
		if (add(&num, &SN_2, &num))
			break;
		if (numComp(&num, &tmp) > 0)
			return 1;
	}
	return 0;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a‚É‚¨‚¢‚Äa‚Ì•½•ûª‚ğb‚ÉŠi”[‚·‚é(³®‚É‚Ísqrt(a)‚ğ’´‚¦‚È‚¢Å‘å‚Ì®”‚ğb‚ÉŠi”[‚·‚é)
//ˆø”Fstruct NUMBER* a : •½•ûª‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : •½•ûª‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(b‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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
//ŠT—vF‘½”{’·•Ï”a‚É‚¨‚¢‚Äa‚Ì•½•ûª‚ğNewton-Raphson–@‚ğ—p‚¢‚Ä‹‚ß‚Äb‚ÉŠi”[‚·‚é(³®‚É‚Ísqrt(a)‚ğ’´‚¦‚È‚¢Å‘å‚Ì®”‚ğb‚ÉŠi”[‚·‚é)
//ˆø”Fstruct NUMBER* a : •½•ûª‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : •½•ûª‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(b‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int sqrt_newton(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER x;		//Œ»İ‚Ì•½•ûª‚Ì‹ß—’l
	struct NUMBER x_b;		//1‚Â‘O‚Ìx
	struct NUMBER x_c;		//2‚Â‘O‚Ìx

	clearByZero(&x);
	clearByZero(&x_b);
	clearByZero(&x_c);

	if (numComp(a, &SN_0) < 0)		//a < 0
		return -11;
	if (numComp(a, &SN_0) == 0 || numComp(a, &SN_1) == 0) {	// a = 0 or 1 ‚È‚ç sqrt(a) = a
		copyNumber(a, b);
		return 0;
	}
	//‰Šú’lx‚Ìİ’è
	//if (Dev_divide(a, &SN_2, &x, &SN_trush))		//X = a / 2
	//	return -1;
	copyNumber(a, &x);
	int i = 0, cnt;
	while (x.n[KETA - 1 - i] == 0)
		i++;
	cnt = (KETA - (i / 2)) / 4 + KETA / 20;	//ÅãˆÊbit‚Ü‚Å’l‚ª“ü‚Á‚Ä‚¢‚éó‘Ô‚ÉÅ“K‰»
	for (i = 0; i < cnt; i++)  //KETA/4+ROOP/5 , ROOP = KETA / 4
		divBy10(&x, &x);
	Dev_divide(&x, &SN_2, &x, &SN_trush);	// x = (a*10^(-(KETA/4+ROOP/5)))/2

	copyNumber(&x, &x_b);
	//copyNumber(&x, &x_c);
	putchar('\n');//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	while (1) {

		putchar('\r');	dispNumber(&x);//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::

		copyNumber(&x_b, &x_c);
		copyNumber(&x, &x_b);

		// x = (b + (N / b)) / 2
		if (Dev_divide(a, &x_b, &x, &SN_trush))
			return -12;
		if (add(&x, &x_b, &x))
			return -13;

		if (Dev_divide(&x, &SN_2, &x, &SN_trush))
			return -14;

		if (numComp(&x, &x_b) == 0)		// û‘©
			break;
		if (numComp(&x, &x_c) == 0) {
			if (numComp(&x_b, &x) < 0)
				copyNumber(&x_b, &x);
			break;
		}
	}
	putchar('\n');//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	copyNumber(&x, b);
	return 0;
}

/*
///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a‚É‚¨‚¢‚Äa‚Ì•½•ûª‚ğ“ñ•ª–@‚ğ—p‚¢‚Ä‹‚ß‚Äb‚ÉŠi”[‚·‚é(³®‚É‚Ísqrt(a)‚ğ’´‚¦‚È‚¢Å‘å‚Ì®”‚ğb‚ÉŠi”[‚·‚é)
//ˆø”Fstruct NUMBER* a : •½•ûª‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : •½•ûª‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), •„†‚ª“¯‚¶ : -2(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int bisection(struct NUMBER* a, struct NUMBER* b, struct NUMBER* need_sqrt, struct NUMBER* c)
{
	struct NUMBER e;	//û‘©”»’è—p‚Ì•Ï”
	struct NUMBER d;	//Œ»İ‚Ìx‚Ì’l
	struct NUMBER fx, fa, fb;	//f(x), f(a), f(b)‚Ì’l
	struct NUMBER num_plus, num_minus, num2, trush;
	int as, bs, cs;		//f(a), f(b), f(c)‚Ì•„†

	clearByZero(&e);
	clearByZero(&d);
	clearByZero(&fx);
	clearByZero(&fa);
	clearByZero(&fb);
	clearByZero(&num_plus);
	clearByZero(&num_minus);
	clearByZero(&num2);
	clearByZero(&trush);

	setInt(&num2, 2);

	if (f(a, need_sqrt, fa))
		return -1;
	as = getSign(fa);

	if (f(b, need_sqrt, fb))
		return -1;
	bs = getSign(&fb);

	if (as <= bs)
		return -2

	copyNumber(a, &num_plus);
	copyNumber(b, &num_minus);

	while (1){
		if (add(&num_plus, &num_minus, &d))
			return -1;
		if(Dev_divide(&d, &num2, &d, &trush))
			return -1;
		//d = (a + b) / 2
		if(f(&d, need_sqrt, &fx))
			return -1;
		if (getAbs(&fx, &fx))
			return -1;

		cs = numComp(&fx, e);

		if (cs <= 0)	//|f(x)| < e
			break;
		if(getSign(&fx) == as)
			copyNumber(&d, &num_plus);

		if (sub(&fa, &fb, &d))
			return -1;

	}

}

int f(struct NUMBER* a, struct NUMBER* pow_pi_2, struct NUMBER* b)
{
	struct NUMBER a2;
	clearByZero(&a2);

	//x*x - (pi^2)
	if (Dev_multiple(a, a, &a2))
		return -1;
	if (sub(&a2, pow_pi_2, &a2))
		return -1;
	copyNumber(&a2, b);
	return 0;
}
*/


///////////////////////////////////////////////////////////////////
//                          ˆÈ‰º•ª”—p                           //
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

	if (KETA == 1000) {
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunshi.n[i]);
		putchar('/');
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunbo.n[i]);
	}
	else if (KETA == 10) {
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunshi.n[i]);
		putchar('/');
		for (i = KETA - 1; i >= 0; i--)
			printf("%01d", a->bunbo.n[i]);
	}
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

	//•ªq
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
	if (B_setSign(&ans, getSign(&tmp)))		//•„†
		return -16;
	getAbs(&tmp, &tmp);
	copyNumber(&tmp, &ans.bunshi);

	//•ª•ê
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

	//•ªq
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
	if (B_setSign(&ans, getSign(&tmp)))		//•„†
		return -16;
	getAbs(&tmp, &tmp);
	copyNumber(&tmp, &ans.bunshi);

	//•ª•ê
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
	copyNumber(a, &c->bunshi);		//•ªq
	copyNumber(b, &c->bunbo);		//•ª•ê
}
//•„†‚Íb‚É‚Â‚­
void BtoN_copyNumber(struct BUNSU* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;
	clearByZero(&ans);
	copyNumber(&a->bunshi, &ans);	//•ªq‚É‚Í•„†‚ğ‚Â‚¯‚é‚½‚ßˆê“xans‚É“ü‚ê‚Ä‚¢‚é
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
	//•„†
	if (B_setSign(&ans, getSign(a)))
		return -1;
	//•ªq
	getAbs(a, &ans.bunshi);
	//•ª•ê
	copyNumber(&SN_1, &ans.bunbo);

	B_copyNumber(&ans, b);
	return 0;
}


///////////////////////////////////////////////////////////////////
//                        ˆÈ‰ºŠÔŒv‘ª—p                         //
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
//                       ˆÈ‰ºƒ`ƒFƒbƒN—p                          //
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
		setRnd(&tmp_a, KETA - 1);
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
