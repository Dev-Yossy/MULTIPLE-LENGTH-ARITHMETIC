#include "mulprec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
		a->n[i] = rand() % 10;
	}
	//•„†
	setSign(a, (rand() % 2 == 1) ? 1 : -1);
}


///////////////////////////////////////////////////////////////////
//ŠT—vF‘½”{’·•Ï”‚ğƒRƒs[‚·‚é
//ˆø”Fstruct NUMBER* a : ƒRƒs[‚·‚é‘½”{’·•Ï”, struct NUMBER* b : ƒRƒs[‚³‚ê‚é‘½”{’·•Ï”
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
	setSign(&tmp, getSign(a));

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
	setSign(&tmp, getSign(a));

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
		x = ~x + 1/*‚í‚ñ‚¿‚á‚ñ*-1‚Å‚àƒRƒ“ƒpƒCƒ‰‚Åˆ—‚³‚ê‚é*/, setSign(a, -1);
	}
	else
	{
		setSign(a, 1);
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
		setSign(&tmp, -1);
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
		setSign(&tmp, -1);
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
		setSign(&tmp, -1);
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
//ŠT—vF‘½”{’·•Ï”a, b‚ÌÏ‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é
//ˆø”Fstruct NUMBER* a : æZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : æZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : Ï‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, k, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0)		//‚Ç‚¿‚ç‚©ˆê•û‚ª0‚Ì‚Æ‚«
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

//*****************************************************************
//ŠT—vF‘½”{’·•Ï”a, b‚ÌÏ‚ğ‹‚ß‚Äc‚ÉŠi”[‚·‚é(ŠJ”­”Å)
//ˆø”Fstruct NUMBER* a : æZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : æZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : Ï‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s : -1(c‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
//•â‘«FmultipleŠÖ”‚Ì–ñ3”{‚Ì‘¬“x
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
//ˆø”Fstruct NUMBER* a : æZ‚·‚é‘½”{’·•Ï”(1), struct NUMBER* b : æZ‚·‚é‘½”{’·•Ï”(2), struct NUMBER* c : ¤‚ğŠi”[‚·‚é‘½”{’·•Ï”, struct NUMBER* d : —]‚è‚ğŠi”[‚·‚é‘½”{’·•Ï”
//–ß’lF¬Œ÷ : 0, ¸”s(0œZ) : -1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢), ¸”s(‚»‚Ì‘¼ƒGƒ‰[)F1(c, d‚Ì’l‚Í•Ï‰»‚µ‚È‚¢)
///////////////////////////////////////////////////////////////////
int divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans, rem, one;

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
		struct NUMBER tmp_a, tmp_b;

		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		if (divide(&tmp_a, &tmp_b, &ans, &rem))
		{
			return -1;
		}

		if (getSign(a) + getSign(b) == 0)	//‚Ç‚¿‚ç‚©ˆê•û‚Ì‚İ•‰‚Ì‚Æ‚«
		{
			if (setSign(&ans, -1))
			{
				return -1;
			}
		}

		if (setSign(&rem, getSign(a)))		//—]‚è‚Ì•„†
		{
			return -1;
		}

		copyNumber(&ans, c);
		copyNumber(&rem, d);

		return 0;
	}

	clearByZero(&ans);
	copyNumber(a, &rem);
	setInt(&one, 1);

	while (1)
	{
		if (numComp(&rem, b) == -1)//x < y)
		{
			break;
		}
		if (sub(&rem, b, &rem))
		{
			return 1;
		}
		add(&ans, &one, &ans);
	}

	copyNumber(&ans, c);
	copyNumber(&rem, d);

	return 0;
}

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

