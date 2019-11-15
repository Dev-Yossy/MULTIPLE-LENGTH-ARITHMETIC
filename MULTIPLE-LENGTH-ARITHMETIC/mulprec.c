#include "mulprec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



void clearByZero(struct NUMBER* a)
{
	int i;
	for (i = 0; i < KETA; i++)
		a->n[i] = 0;
	a->sign = 1;
}

void dispNumber(struct NUMBER* a)
{
	int i;
	if (a->sign >= 0)
		putchar('+');
	else
		putchar('-');

	for (i = KETA - 1; i >= 0; i--)
		printf(" %2d", a->n[i]);        //数字確認用
}

/**
 * struct NUMBER *a         数字を入れる構造体
 * int k                    下k桁を乱数で埋める
*/
void setRnd(struct NUMBER* a, int k)
{
	int i;
	//数字
	for (i = 0; i < k; i++)
		a->n[i] = rand() % 10;
	//符号
	a->sign = (rand() % 2 == 1) ? 1 : -1;
}

void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	//数字
	for (i = 0; i < KETA; i++)
		b->n[i] = a->n[i];
	//符号
	b->sign = a->sign;
}

void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	b->sign = 1;
}

int isZero(struct NUMBER* a)
{
	if (a->sign == -1)
		return -1;

	int i;
	for (i = 0; i < KETA; i++)
		if (a->n[i] != 0)
			return -1;

	return 0;
}

int mulBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	for (i = 0; i < KETA - 1; i++)
		b->n[i + 1] = a->n[i];

	b->n[0] = 0;
	b->sign = a->sign;

	if (a->n[KETA - 1] != 0)
		return -1;
	return 0;
}

int divBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	for (i = 1; i < KETA; i++)
		b->n[i - 1] = a->n[i];

	b->n[KETA - 1] = 0;
	b->sign = a->sign;

	return a->n[0];
}