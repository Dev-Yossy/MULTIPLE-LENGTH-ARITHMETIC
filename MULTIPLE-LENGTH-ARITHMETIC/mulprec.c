#include "mulprec.h"


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚ğ0‚É‰Šú‰»‚·‚é
//ˆø”Fstruct NUMBER* a : ‰Šú‰»‚·‚é‘½”{’·•Ï”
//–ß’lF‚È‚µ
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
//ŠT—vF‘½”{’·•Ï”‚ğ•\¦‚·‚é
//ˆø”Fstruct NUMBER* a : •\¦‚·‚é‘½”{’·•Ï”
//–ß’lF‚È‚µ
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
		printf(" %2d", a->n[i]);        //”šŠm”F—p
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
	{
		a->n[i] = random() % 10;
	}
	//•„†
	setSign(a, (random() % 2 == 1) ? 1 : -1);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚ğƒRƒs[‚·‚é
//ˆø”Fstruct NUMBER* a : ƒRƒs[Œ³‚Ì‘½”{’·•Ï”, struct NUMBER* b : ƒRƒs[æ‚Ì‘½”{’·•Ï”
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	//”š
	for (i = 0; i < KETA; i++)
	{
		b->n[i] = a->n[i];
	}
	//•„†
	setSign(b, getSign(a));
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚Ìâ‘Î’l‚ğ‹‚ß‚ÄŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : â‘Î’l‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : â‘Î’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	setSign(b, 1);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚ª0‚©‚Ç‚¤‚©‚ğ”»•Ê‚·‚é
//ˆø”Fstruct NUMBER* a : ”»•Ê‚·‚é‘½”{’·•Ï”
//–ß’lF0‚Ì‚Æ‚« : 0, ‚»‚êˆÈŠO‚Ì‚Æ‚« : -1
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
//ŠT—vF‘½”{’·•Ï”‚ğ10”{‚µ‚ÄŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : 10”{‚µ‚½‚¢‘½”{’·•Ï”, struct NUMBER* b : ŒvZ‚µ‚½’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, Œ…‚ ‚Ó‚ê : -1(b‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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
//ŠT—vF‘½”{’·•Ï”‚ğ10‚ÅŠ„‚Á‚½¤‚ğŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : 1/10‚É‚µ‚½‚¢‘½”{’·•Ï”, struct NUMBER* b : ŒvZ‚µ‚½’l‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : —]‚è
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
//ŠT—vF‘½”{’·•Ï”‚ÉintŒ^‚Ì”š‚ğŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Ši”[‚³‚ê‚é‘½”{’·•Ï”, int x : Ši”[‚µ‚½‚¢‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(a‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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
		x = ~x + 1/*‚í‚ñ‚¿‚á‚ñ*-1‚Å‚àƒRƒ“ƒpƒCƒ‰‚Åˆ—‚³‚ê‚é*/;
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
//ŠT—vF‘½”{’·•Ï”‚Ì•„†‚ğİ’è‚·‚é
//ˆø”Fstruct NUMBER* a : İ’è‚³‚ê‚é‘½”{’·•Ï”, int x : İ’è‚·‚é•„†(+ : 1, - : -1)
//–ß’lF¬Œ÷ : 0, ¸”s : -1(a‚Ì•„†‚Í•Ï‰»‚µ‚È‚¢)
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
//ŠT—vF‘½”{’·•Ï”a, b‚ÌŒğŠ·‚·‚é
//ˆø”Fstruct NUMBER* a : ŒğŠ·‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : ŒğŠ·‚·‚é‘½”{’·•Ï”(2)
//–ß’lF‚È‚µ
///////////////////////////////////////////////////////////////////
void swap(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER tmp = *a;
	*a = *b;
	*b = tmp;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚Ì˜a‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : ‰ÁZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : ‰ÁZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ˜a‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int add(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	int d, i = 0, flag = 0;//min...0, max...1
	struct NUMBER tmp;		//tmp‚ğg‚¤‚±‚Æ‚Å¸”s‚Éc‚Ìƒf[ƒ^‚ª‰ó‚ê‚È‚¢‚æ‚¤‚É‚¢‚Ä‚¢‚é

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
		//‰ÁZ
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
//ŠT—vF‘½”{’·•Ï”a‚ğƒCƒ“ƒNƒŠƒƒ“ƒg‚µ‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : ƒCƒ“ƒNƒŠƒƒ“ƒg‚·‚é‘½”{’·•Ï”, struct NUMBER* b : Œ‹‰Ê‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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
//ŠT—vF‘½”{’·•Ï”a, b‚Ì·‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Œ¸Z‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : Œ¸Z‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ·‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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
	//‚±‚±‚©‚çŒ¸Z
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
		//Œ¸Z
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
//ŠT—vF‘½”{’·•Ï”a‚ğƒfƒNƒŠƒƒ“ƒg‚µ‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : ƒfƒNƒŠƒƒ“ƒg‚·‚é‘½”{’·•Ï”, struct NUMBER* b : Œ‹‰Ê‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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
//ŠT—vF‘½”{’·•Ï”a, b‚ÌÏ‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : æZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : æZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : Ï‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, k, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0)		//‚·‚­‚È‚­‚Æ‚à‚Ç‚¿‚ç‚©ˆê•û‚ª0‚Ì‚Æ‚«
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

	if (getSign(a) + getSign(b) == 0)			//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
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
//ŠT—vF‘½”{’·•Ï”a, b‚ÌÏ‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é(ŠJ”­”Å)
//ˆø”Fstruct NUMBER* a : æZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : æZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : Ï‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//•â‘«FmultipleŠÖ”‚Ì–ñ3”{(KETA=10), –ñ16.7”{(KETA=100)‚Ì‘¬“x
//*****************************************************************
int Dev_multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0)		//‚Ç‚¿‚ç‚©ˆê•û‚ª0‚Ì‚Æ‚«
	{
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);

	for (i = KETA - 1; i >= 0; i--)		//b‚Ìã‚ÌŒ…‚©‚çs‚¤
	{
		clearByZero(&tmp);
		for (j = 0; j < KETA; j++)		//ˆê’i•ª‚Ì“š‚¦‚ğo‚·
		{
			int e = a->n[j] * b->n[i] + flag;
			tmp.n[j] = e % 10;
			flag = e / 10;
		}

		if (flag)
		{
			return -1;
		}

		if (add(&ans, &tmp, &ans))			//‰ÁZ
		{
			return -1;
		}

		if (i > 0 && mulBy10(&ans, &ans))	//ÅŒã‚Ì1‰ñˆÈŠO‚Å10”{
		{
			return -1;
		}
	}

	if (getSign(a) + getSign(b) == 0)			//‚Ç‚¿‚ç‚©ˆê•û‚ª•‰‚Ì‚Æ‚«
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
//ŠT—vF‘½”{’·•Ï”a, b‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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

	if (getSign(a) == -1 || getSign(b) == -1)			//‚Ç‚¿‚ç‚©ˆê•û‚ª•‰‚Ì‚Æ‚«
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

		if (getSign(a) + getSign(b) == 0)	//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}

		if (setSign(&rem, getSign(a)))		//—]‚è‚Ì•„†
		{
			return -2;
		}

		copyNumber(&ans, c);
		copyNumber(&rem, d);

		return 0;
	}

	//1Œ…”»•Ê—p
	int flg;
	if ((flg = divide_U10(a, b, c, d)) != -2)	//b‚ª1Œ…‚Å‚È‚¢ê‡ˆÈŠO‚Ì‚ÌœZ
	{
		return flg;
	}

	//‚±‚±‚©‚ç++‚ÌœZ
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
//ŠT—vF‘½”{’·•Ï”a, b(b‚Í1Œ…)‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(b‚ª1Œ…‚Å‚È‚¢)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-3(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//*****************************************************************
int divide_U10(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	int h = 0;
	int i = KETA - 1;

	//—]‚è : rem
	int rem = divBy10(b, &ans);

	if (b == 0)				//0œZ
	{
		return -1;
	}

	if (isZero(&ans))		//b‚ª1Œ…‚Å‚È‚¢‚È‚ç
	{
		return -2;
	}

	clearByZero(&ans);

	//b‚ª1Œ…‚È‚ç
	//b ‚Í rem ‚Æ“™‚µ‚¢(struct NUMBER -> int)

	for (i = KETA - 1; i >= 0; i--)
	{
		int t = h * 10 + a->n[i];
		h = t % rem;
		ans.n[i] = (t - h) / rem;
	}

	copyNumber(&ans, c);
	if (setInt(d, h))		//—]‚è
	{
		return -3;
	}

	return 0;
}


//*****************************************************************
//ŠT—vF‘½”{’·•Ï”a, b‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚é(ŠJ”­”ÅF•sˆÀ’è)
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//*****************************************************************
int Dev_divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	struct NUMBER tmp_a, tmp_b, tmp_d, tmp_e;
	struct NUMBER tmp_check;		//Šm”F—p•Ï”

	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);
	clearByZero(&tmp_check);

	//0œZ
	if (isZero(b) == 0)
	{
		return -1;
	}
	//•ªq‚ª0‚Ì‚Æ‚«
	if (isZero(a) == 0)
	{
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//ƒ}ƒCƒiƒXˆ—
	//­‚È‚­‚Æ‚à‚Ç‚¿‚ç‚©ˆê•û‚ª•‰‚Ì‚Æ‚«
	if (getSign(a) == -1 || getSign(b) == -1)
	{
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
		{
			return num;
		}
		//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
		if (getSign(a) + getSign(b) == 0)
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}
		//—]‚è‚Ì•„† (—]‚è‚Ì•„†‚Íí‚ÉŠ„‚ç‚ê‚é”‚Ì•„†‚ÉˆË‘¶‚·‚é)
		if (setSign(&tmp_d, getSign(a)))
		{
			return -2;
		}

		copyNumber(&ans, c);
		copyNumber(&tmp_d, d);

		return 0;
	}

	//‚±‚±‚©‚ç++‚ÌœZ

	copyNumber(a, &tmp_a);
	copyNumber(b, &tmp_b);

	while (numComp(&tmp_a, &tmp_b) != -1)	//a < b ‚Å‚È‚¢‚È‚ç
	{
		copyNumber(&tmp_b, &tmp_d);

		setInt(&tmp_e, 1);

		while (1)
		{
			int rem = divBy10(&tmp_a, &tmp_check);

			int flg = numComp(&tmp_check, &tmp_d);
			if (flg == -1)	//tmp_d‚ğmulBy10‚·‚é‚Ætmp_a‚ğ’´‚¦‚é
			{
				break;
			}
			else if (flg == 0 && rem < tmp_d.n[0])	//“™‚µ‚¢‚Æ‚«‚Í—]‚èrem‚É‚æ‚Á‚ÄŒˆ‚Ü‚é. rem>0‚È‚çtmp_a > tmp_d*10
			{										//d.n[0]‚Æ‚Ì”äŠr‚Í1‰ñ–Ú‚Ì‚½‚ß, 2‰ñ–ÚˆÈ~‚Íd.n[0]‚Í0‚È‚Ì‚Åí‚Éfalse
				break;
			}

			//tmp_a >= tmp_d * 10‚Ì‚Æ‚«

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
//ŠT—vF‘½”{’·•Ï”a, b‚Ì¤‚ğ‹‚ß‚Äc‚ÉŠi”[‚µA—]‚è‚ğd‚ÉŠi”[‚·‚é(ŠJ”­”ÅF•sˆÀ’è)
//ˆø”Fstruct NUMBER* a : œZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : œZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F-2(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//•â‘«FÅãˆÊbit‚Ü‚Å’l‚ª“ü‚Á‚Ä‚¢‚éó‘Ô‚¾‚Æoverflow‚·‚éê‡‚ª‚ ‚é(—áFKETA=5,a=99999,b=99998)
//*****************************************************************
int Dev_divide_X(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	struct NUMBER tmp_a, tmp_b, tmp_d, tmp_e;
	//è‡1
	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);

	//0œZ
	if (isZero(b) == 0)
	{
		return -1;
	}
	//•ªq‚ª0‚Ì‚Æ‚«
	if (isZero(a) == 0)
	{
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//ƒ}ƒCƒiƒXˆ—
	//­‚È‚­‚Æ‚à‚Ç‚¿‚ç‚©ˆê•û‚ª•‰‚Ì‚Æ‚«
	if (getSign(a) == -1 || getSign(b) == -1)
	{
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide_X(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
		{
			return num;
		}
		//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
		if (getSign(a) + getSign(b) == 0)
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}
		//—]‚è‚Ì•„† (—]‚è‚Ì•„†‚Íí‚ÉŠ„‚ç‚ê‚é”‚Ì•„†‚ÉˆË‘¶‚·‚é)
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

	//è‡2
	while (numComp(&tmp_a, &tmp_b) != -1)
	{
		//è‡3
		copyNumber(&tmp_b, &tmp_d);
		//è‡4
		setInt(&tmp_e, 1);
		//è‡5

		//d‚ğ10”{‚µ‚Ä‚¢‚­‚ÆÅãˆÊbit‚ª”ñ0‚É‚È‚Á‚Ä‚à‚È‚¨a>d‚Æ‚È‚é‚±‚Æ‚ª‚ ‚é‚½‚ß, ‚³‚ç‚É10”{‚³‚ê‚Äoverflow‚µ‚Ä‚µ‚Ü‚¤
		//‰ğŒˆô1...í‚É—]—T‚Ì‚ ‚éŒ…”‚ğ—pˆÓ‚µ‚Ä‚¨‚­
		//‰ğŒˆô2...ÅãˆÊbit‚Ì’l‚ª”ñ0‚É‚È‚Á‚½‚Æ‚«‚É“Á•Ê‚Èˆ—‚ğ•`‚­
		while (1)
		{
			if (mulBy10(&tmp_d, &tmp_d))
			{
				return -2;
			}

			if (numComp(&tmp_a, &tmp_d) != 1)
			{
				divBy10(&tmp_d, &tmp_d);	//‚±‚ê‚¾‚ÆKETA-1‚Ü‚Å–„‚Ü‚é‚æ‚¤‚È”š‚Ì‚É•s‹ï‡‚ª‹N‚«‚é‰Â”\«‚ª‚ ‚é
				break;
			}

			//è‡6
			if (mulBy10(&tmp_e, &tmp_e))
			{
				return -2;
			}
		}

		//è‡7
		sub(&tmp_a, &tmp_d, &tmp_a);

		if (add(&ans, &tmp_e, &ans))
		{
			return -2;
		}
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
	struct NUMBER ans;
	struct NUMBER tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	//b‚ª•‰‚Ì‚Æ‚«
	if (getSign(b) == -1)
	{
		return -2;
	}

	//b = 0‚Ì‚Æ‚«
	if (isZero(b) == 0)
	{
		//c = 1
		if (increment(&ans, &ans))
		{
			return -1;
		}
		copyNumber(&ans, c);
	}

	//—İæ
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

		//ˆ—
		if (multiple(&ans, a, &ans))
		{
			return -1;
		}
	}
	copyNumber(&ans, c);

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
//ŠT—vF‘½”{’·•Ï”a, b‚É‚¨‚¢‚Äa‚Æb‚ÌÅ‘åŒö–ñ”‚ğc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Å‘åŒö–ñ”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : Å‘åŒö–ñ”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* c : Å‘åŒö–ñ”‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int gcd(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER num1, num2, rem;

	clearByZero(&num1);
	clearByZero(&num2);
	clearByZero(&rem);

	getAbs(a, &num1);
	getAbs(b, &num2);

	if (numComp(&num1, &num2) == -1)	//a < b ‚È‚ç
	{
		getAbs(b, &num1);
		getAbs(a, &num2);
	}

	if (isZero(&num2) == 0)
	{
		copyNumber(&num1, c);
		return 0;
	}

	while (1)
	{
		if (divide(&num1, &num2, &num1/*•s—v*/, &rem))
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

	//‚±‚±‚É‚«‚½‚Æ‚«œ”‚Ínum1‚É‚È‚é
	copyNumber(&num1, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”a, b‚É‚¨‚¢‚Äa‚Æb‚ÌÅ¬Œö”{”‚ğc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : Å¬Œö”{”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* b : Å¬Œö”{”‚ğ‹‚ß‚é‘½”{’·•Ï”, struct NUMBER* c : Å¬Œö”{”‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
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

	if (gcd(a, b, &num1))		//gcd‚Í•„†‚É‰e‹¿‚µ‚È‚¢‚½‚ßa,b‚ğ‚»‚Ì‚Ü‚Ü—p‚¢‚Ä‚¢‚é
	{
		return -1;
	}

	//num1 = gcd(a,b)

	if (divide(&ans, &num1, &ans, &num1/*•s—v*/))
	{
		return -1;
	}

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
	struct NUMBER ans, num1, num2;
	clearByZero(&ans);
	clearByZero(&num1);
	clearByZero(&num2);

	getAbs(a, &num1);
	getAbs(b, &num2);

	if (gcd(a, b, &ans))		//gcd‚Í•„†‚É‰e‹¿‚µ‚È‚¢‚½‚ßa,b‚ğ‚»‚Ì‚Ü‚Ü—p‚¢‚Ä‚¢‚é
	{
		return -1;
	}

	//ans = gcd(a,b)

	if (divide(&num1, &ans, &ans, &num1/*•s—v*/))
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
//                        ˆÈ‰ºŠÔŒv‘ª—p                          //
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

		//Šm”F
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

	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_c);

	while (i++ < roop)
	{
		setRnd(&tmp_a, KETA);
		setRnd(&tmp_b, (random() % KETA) + 1);
		clockStart();
		tmp += (func(&tmp_a, &tmp_b, &tmp_c) ? 1 : 0);
		flag += clockStop();
	}
	printf("ErrorNumber: %d\n", tmp);

	return flag;
}


double FastRoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size)
{
	unsigned int i = 0, tmp = 0;
	double flag = 0;
	struct NUMBER tmp_a, tmp_b, tmp_c, tmp_d;

	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_c);
	clearByZero(&tmp_d);

	while(i++ < roop)
	{
		setRnd(&tmp_a, KETA);
		setRnd(&tmp_b, (random() % KETA) + 1);
		clockStart();
		tmp += (Dev_divide(&tmp_a, &tmp_b, &tmp_c, &tmp_d) ? 1 : 0);
		flag += clockStop();
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

//a, x‚ª“™‚µ‚¯‚ê‚Î0, ˆá‚¤‚È‚ç-1
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

