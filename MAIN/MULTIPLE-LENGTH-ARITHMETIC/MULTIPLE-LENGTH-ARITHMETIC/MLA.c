#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define KETA 30

struct NUMBER
{
	int n[KETA];    //�e���̒l [��̌�]---[���̌�] [KETA - 1]---[0]
	int sign;       //�����ϐ� 1:�� 0, -1:��
};

void clearByZero(struct NUMBER* a);
void dispNumber(struct NUMBER* a);
void setRnd(struct NUMBER* a, int k);
void copyNumber(struct NUMBER* a, struct NUMBER* b);
void getAbs(struct NUMBER* a, struct NUMBER* b);
int isZero(struct NUMBER* a);
int mulBy10(struct NUMBER* a, struct NUMBER* b);
int divBy10(struct NUMBER* a, struct NUMBER* b);

int main(void)
{
	srand(time(NULL));

	struct NUMBER a, b;

	clearByZero(&a);
	clearByZero(&b);

	setRnd(&a, 15);

	printf("a = ");
	dispNumber(&a);
	putchar('\n');

	mulBy10(&a, &b);

	printf("b = ");
	dispNumber(&b);
	putchar('\n');

	divBy10(&a, &b);

	printf("b = ");
	dispNumber(&b);
	putchar('\n');

	return 0;
}

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
		printf(" %2d", a->n[i]);        //�����m�F�p
}

/**
 * struct NUMBER *a         ����������\����
 * int k                    ��k���𗐐��Ŗ��߂�
*/
void setRnd(struct NUMBER* a, int k)
{
	int i;
	//����
	for (i = 0; i < k; i++)
		a->n[i] = rand() % 10;
	//����
	a->sign = (rand() % 2 == 1) ? 1 : -1;
}

void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	//����
	for (i = 0; i < KETA; i++)
		b->n[i] = a->n[i];
	//����
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