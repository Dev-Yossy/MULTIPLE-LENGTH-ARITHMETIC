#include "mulprec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ���0�ɏ���������
//�����Fstruct NUMBER* a : ���������鑽�{���ϐ�
//�ߒl�F�Ȃ�
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
//�T�v�F���{���ϐ���\������
//�����Fstruct NUMBER* a : �\�����鑽�{���ϐ�
//�ߒl�F�Ȃ�
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
		printf(" %2d", a->n[i]);        //�����m�F�p
	}
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ��ɗ������i�[����
//�����Fstruct NUMBER* a : �������i�[���鑽�{���ϐ�, int k : �������闐���̌���
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void setRnd(struct NUMBER* a, int k)
{
	int i;
	//����
	for (i = 0; i < k; i++)
	{
		a->n[i] = rand() % 10;
	}
	//����
	setSign(a, (rand() % 2 == 1) ? 1 : -1);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ����R�s�[����
//�����Fstruct NUMBER* a : �R�s�[���鑽�{���ϐ�, struct NUMBER* b : �R�s�[����鑽�{���ϐ�
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	//����
	for (i = 0; i < KETA; i++)
	{
		b->n[i] = a->n[i];
	}
	//����
	setSign(b, getSign(a));
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ��̐�Βl�����߂Ċi�[����
//�����Fstruct NUMBER* a : ��Βl�����߂鑽�{���ϐ�, struct NUMBER* b : ��Βl���i�[���鑽�{���ϐ�
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	setSign(b, 1);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ���0���ǂ����𔻕ʂ���
//�����Fstruct NUMBER* a : ���ʂ��鑽�{���ϐ�
//�ߒl�F0�̂Ƃ� : 0, ����ȊO�̂Ƃ� : -1
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
//�T�v�F���{���ϐ���10�{���Ċi�[����
//�����Fstruct NUMBER* a : 10�{���������{���ϐ�, struct NUMBER* b : �v�Z�����l���i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, �����ӂ� : -1(b�̒l�͕ω����Ȃ�)
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
	setSign(b, getSign(a));

	return 0;
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ���10�Ŋ����������i�[����
//�����Fstruct NUMBER* a : 1/10�ɂ��������{���ϐ�, struct NUMBER* b : �v�Z�����l���i�[���鑽�{���ϐ�
//�ߒl�F���� : �]��
///////////////////////////////////////////////////////////////////
int divBy10(struct NUMBER* a, struct NUMBER* b)
{
	int i;
	for (i = 1; i < KETA; i++)
	{
		b->n[i - 1] = a->n[i];
	}

	b->n[KETA - 1] = 0;
	setSign(b, getSign(a));

	return a->n[0];
}

///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ���int�^�̐������i�[����
//�����Fstruct NUMBER* a : �i�[����鑽�{���ϐ�, int x : �i�[���������{���ϐ�
//�ߒl�F���� : 0, ���s : -1(a�̒l�͕ω����Ȃ�)
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
		x = ~x + 1/*��񂿂��*-1�ł��R���p�C���ŏ��������*/, setSign(a, -1);
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
//�T�v�F���{���ϐ��̕�����ݒ肷��
//�����Fstruct NUMBER* a : �ݒ肳��鑽�{���ϐ�, int x : �ݒ肷�镄��(+ : 1, - : -1)
//�ߒl�F���� : 0, ���s : -1(a�̕����͕ω����Ȃ�)
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
//�T�v�F���{���ϐ��̕������擾����
//�����Fstruct NUMBER* a : �������擾���鑽�{���ϐ�
//�ߒl�F�� : 1, �� : -1
///////////////////////////////////////////////////////////////////
int getSign(struct NUMBER* a)
{
	return a->sign;
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ�a, b���r����
//�����Fstruct NUMBER* a : ��r���鑽�{���ϐ�(1), struct NUMBER* a : ��r���鑽�{���ϐ�(2)
//�ߒl�Fa == b : 0, a > b : 1, a < b : -1
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
//�T�v�F���{���ϐ�a, b�̘a�����߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* a : ���Z���鑽�{���ϐ�(2)
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int add(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	int d, i = 0, flag = 0;//min...0, max...1
	struct NUMBER tmp;		//tmp���g�����ƂŎ��s����c�̃f�[�^�����Ȃ��悤�ɂ��Ă���

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
		//���Z
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
//�T�v�F���{���ϐ�a, b�̍������߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* a : ���Z���鑽�{���ϐ�(2)
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
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
	//�������猸�Z
	else if (numComp(a, b) < 0)			//a < b
	{
		flag = sub(b, a, &tmp);
		setSign(&tmp, -1);
	}
	else
	{
		//���Z
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
//                       �ȉ��`�F�b�N�p                          //
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