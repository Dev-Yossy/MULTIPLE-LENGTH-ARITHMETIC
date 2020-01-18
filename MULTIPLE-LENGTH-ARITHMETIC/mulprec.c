#include "mulprec.h"


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
		printf("%2d", a->n[i]);        //�����m�F�p
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
		a->n[i] = random() % 10;
	}
	//����
	setSign(a, (random() % 2 == 1) ? 1 : -1);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ����R�s�[����
//�����Fstruct NUMBER* a : �R�s�[���̑��{���ϐ�, struct NUMBER* b : �R�s�[��̑��{���ϐ�
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
	/* if (getSign(a) == -1)
	{
		return -1;
	}
 */			//-0�����ꍞ�񂾎��̑΍�
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
//�T�v�F���{���ϐ���10�Ŋ����������i�[����
//�����Fstruct NUMBER* a : 1/10�ɂ��������{���ϐ�, struct NUMBER* b : �v�Z�����l���i�[���鑽�{���ϐ�
//�ߒl�F���� : �]��
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
		x = ~x + 1/*��񂿂��*-1�ł��R���p�C���ŏ��������*/;
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
//�����Fstruct NUMBER* a : ��r���鑽�{���ϐ�(1), struct NUMBER* b : ��r���鑽�{���ϐ�(2)
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
//�T�v�F���{���ϐ�a, b�̌�������
//�����Fstruct NUMBER* a : �������鑽�{���ϐ�(1), struct NUMBER* b : �������鑽�{���ϐ�(2)
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void swap(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER tmp = *a;
	*a = *b;
	*b = tmp;
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ�a, b�̘a�����߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �a���i�[���鑽�{���ϐ�
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
//�T�v�F���{���ϐ�a���C���N�������g����c�Ɋi�[����
//�����Fstruct NUMBER* a : �C���N�������g���鑽�{���ϐ�, struct NUMBER* b : ���ʂ��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
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
//�T�v�F���{���ϐ�a, b�̍������߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �����i�[���鑽�{���ϐ�
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
	//�������猸�Z
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
//�T�v�F���{���ϐ�a���f�N�������g����c�Ɋi�[����
//�����Fstruct NUMBER* a : �f�N�������g���鑽�{���ϐ�, struct NUMBER* b : ���ʂ��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
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
//�T�v�F���{���ϐ�a, b�̐ς����߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ��Z���鑽�{���ϐ�(1), struct NUMBER* b : ��Z���鑽�{���ϐ�(2), struct NUMBER* c : �ς��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, k, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0)		//�����Ȃ��Ƃ��ǂ��炩�����0�̂Ƃ�
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

	if (getSign(a) + getSign(b) == 0)			//�ǂ��炩����̂ݕ��̂Ƃ�
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
//�T�v�F���{���ϐ�a, b�̐ς����߂�c�Ɋi�[����(�J����)
//�����Fstruct NUMBER* a : ��Z���鑽�{���ϐ�(1), struct NUMBER* b : ��Z���鑽�{���ϐ�(2), struct NUMBER* c : �ς��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
//�⑫�Fmultiple�֐��̖�3�{(KETA=10), ��16.7�{(KETA=100)�̑��x
//*****************************************************************
int Dev_multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0)		//�ǂ��炩�����0�̂Ƃ�
	{
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);

	for (i = KETA - 1; i >= 0; i--)		//b�̏�̌�����s��
	{
		clearByZero(&tmp);
		for (j = 0; j < KETA; j++)		//��i���̓������o��
		{
			int e = a->n[j] * b->n[i] + flag;
			tmp.n[j] = e % 10;
			flag = e / 10;
		}

		if (flag)
		{
			return -1;
		}

		if (add(&ans, &tmp, &ans))			//���Z
		{
			return -1;
		}

		if (i > 0 && mulBy10(&ans, &ans))	//�Ō��1��ȊO��10�{
		{
			return -1;
		}
	}

	if (getSign(a) + getSign(b) == 0)			//�ǂ��炩��������̂Ƃ�
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
//�T�v�F���{���ϐ�a, b�̏������߂�c�Ɋi�[���A�]���d�Ɋi�[����B
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �����i�[���鑽�{���ϐ�, struct NUMBER* d : �]����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s(0���Z) : -1(c, d�̒l�͕ω����Ȃ�), ���s(���̑��G���[)�F-2(c, d�̒l�͕ω����Ȃ�)
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
	if (getSign(a) == -1 || getSign(b) == -1)			//���Ȃ��Ƃ��ǂ��炩��������̂Ƃ�
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
		if (getSign(a) + getSign(b) == 0)	//�ǂ��炩����̂ݕ��̂Ƃ�
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}
		if (setSign(&rem, getSign(a)))		//�]��̕���
		{
			return -2;
		}

		copyNumber(&ans, c);
		copyNumber(&rem, d);

		return 0;
	}
	//1�����ʗp
	int flg;
	if ((flg = divide_U10(a, b, c, d)) != -2)	//b��1���łȂ��ꍇ�ȊO�̎��̏��Z
	{
		return flg;
	}
	//��������++�̏��Z
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
//�T�v�F���{���ϐ�a, b(b��1��)�̏������߂�c�Ɋi�[���A�]���d�Ɋi�[����B(�J���ŁF����)
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �����i�[���鑽�{���ϐ�, struct NUMBER* d : �]����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s(0���Z) : -1(c, d�̒l�͕ω����Ȃ�), ���s(b��1���łȂ�)�F-2(c, d�̒l�͕ω����Ȃ�), ���s(���̑��G���[)�F-3(c, d�̒l�͕ω����Ȃ�)
//*****************************************************************
int divide_U10(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	int h = 0;
	int i = KETA - 1;

	clearByZero(&ans);

	//�]�� : rem
	int rem = divBy10(b, &ans);

	if (b == 0)				//0���Z
	{
		return -1;
	}

	if (isZero(&ans))		//b��1���łȂ��Ȃ�
	{
		return -2;
	}

	clearByZero(&ans);

	//b��1���Ȃ�
	//b �� rem �Ɠ�����(struct NUMBER -> int)

	for (i = KETA - 1; i >= 0; i--)
	{
		int t = h * 10 + a->n[i];
		h = t % rem;
		ans.n[i] = (t - h) / rem;
	}

	copyNumber(&ans, c);
	if (setInt(d, h))		//�]��
	{
		return -3;
	}

	return 0;
}


//*****************************************************************
//�T�v�F���{���ϐ�a, b�̏������߂�c�Ɋi�[���A�]���d�Ɋi�[����B(�J���ŁF����)
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �����i�[���鑽�{���ϐ�, struct NUMBER* d : �]����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s(0���Z) : -1(c, d�̒l�͕ω����Ȃ�), ���s(���̑��G���[)�F-2(c, d�̒l�͕ω����Ȃ�)
//*****************************************************************
int Dev_divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	struct NUMBER tmp_a, tmp_b, tmp_d, tmp_e;
	struct NUMBER tmp_check;		//�m�F�p�ϐ�

	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);
	clearByZero(&tmp_check);

	//0���Z
	if (isZero(b) == 0)
	{
		return -1;
	}
	//���q��0�̂Ƃ�
	if (isZero(a) == 0)
	{
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//�}�C�i�X����
	//���Ȃ��Ƃ��ǂ��炩��������̂Ƃ�
	if (getSign(a) == -1 || getSign(b) == -1)
	{
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
		{
			return num;
		}
		//�ǂ��炩����̂ݕ��̂Ƃ�
		if (getSign(a) + getSign(b) == 0)
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}
		//�]��̕��� (�]��̕����͏�Ɋ����鐔�̕����Ɉˑ�����)
		if (setSign(&tmp_d, getSign(a)))
		{
			return -2;
		}

		copyNumber(&ans, c);
		copyNumber(&tmp_d, d);

		return 0;
	}

	//��������++�̏��Z

	copyNumber(a, &tmp_a);
	copyNumber(b, &tmp_b);

	while (numComp(&tmp_a, &tmp_b) != -1)	//a < b �łȂ��Ȃ�
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
			if (flg == -1)	//tmp_d��mulBy10�����tmp_a�𒴂���
			{
				break;
			}
			else if (flg == 0 && rem < tmp_d.n[0])	//�������Ƃ��͗]��rem�ɂ���Č��܂�. rem>0�Ȃ�tmp_a > tmp_d*10
			{										//d.n[0]�Ƃ̔�r��1��ڂ̂���, 2��ڈȍ~��d.n[0]��0�Ȃ̂ŏ��false
				break;
			}

			//tmp_a >= tmp_d * 10�̂Ƃ�

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
//�T�v�F���{���ϐ�a, b�̏������߂�c�Ɋi�[���A�]���d�Ɋi�[����B(�J���ŁF�s����)
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �����i�[���鑽�{���ϐ�, struct NUMBER* d : �]����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s(0���Z) : -1(c, d�̒l�͕ω����Ȃ�), ���s(���̑��G���[)�F-2(c, d�̒l�͕ω����Ȃ�)
//�⑫�F�ŏ��bit�܂Œl�������Ă����Ԃ���overflow����ꍇ������(��FKETA=5,a=99999,b=99998)
//*****************************************************************
int Dev_divide_X(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans;
	struct NUMBER tmp_a, tmp_b, tmp_d, tmp_e;
	//�菇1
	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);

	//0���Z
	if (isZero(b) == 0)
	{
		return -1;
	}
	//���q��0�̂Ƃ�
	if (isZero(a) == 0)
	{
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//�}�C�i�X����
	//���Ȃ��Ƃ��ǂ��炩��������̂Ƃ�
	if (getSign(a) == -1 || getSign(b) == -1)
	{
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide_X(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
		{
			return num;
		}
		//�ǂ��炩����̂ݕ��̂Ƃ�
		if (getSign(a) + getSign(b) == 0)
		{
			if (setSign(&ans, -1))
			{
				return -2;
			}
		}
		//�]��̕��� (�]��̕����͏�Ɋ����鐔�̕����Ɉˑ�����)
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

	//�菇2
	while (numComp(&tmp_a, &tmp_b) != -1)
	{
		//�菇3
		copyNumber(&tmp_b, &tmp_d);
		//�菇4
		if (setInt(&tmp_e, 1))
		{
			return -2;
		}
		//�菇5

		//d��10�{���Ă����ƍŏ��bit����0�ɂȂ��Ă��Ȃ�a>d�ƂȂ邱�Ƃ����邽��, �����10�{�����overflow���Ă��܂�
		//������1...��ɗ]�T�̂��錅����p�ӂ��Ă���
		//������2...�ŏ��bit�̒l����0�ɂȂ����Ƃ��ɓ��ʂȏ�����`��
		while (1)
		{
			if (mulBy10(&tmp_d, &tmp_d))
			{
				return -2;
			}

			if (numComp(&tmp_a, &tmp_d) != 1)
			{
				divBy10(&tmp_d, &tmp_d);	//���ꂾ��KETA-1�܂Ŗ��܂�悤�Ȑ����̎��ɕs����N����\��������
				break;
			}

			//�菇6
			if (mulBy10(&tmp_e, &tmp_e))
			{
				return -2;
			}
		}

		//�菇7
		sub(&tmp_a, &tmp_d, &tmp_a);

		if (add(&ans, &tmp_e, &ans))
		{
			return -2;
		}
	}

	//�菇10
	copyNumber(&tmp_a, d);
	copyNumber(&ans, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ�a, b�ɂ�����a��b���c�Ɋi�[����
//�����Fstruct NUMBER* a : �ݏ悳��鑽�{���ϐ�, struct NUMBER* b :	�ݏ�̏�̂Ƃ��̑��{���ϐ�, struct NUMBER* c : �ݏ悵���l���i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s (�I�[�o�[�t���[/�A���_�[�t���[): -1(c�̒l�͕ω����Ȃ�), ���s(b<0)�F-2(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;
	struct NUMBER tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	//b�����̂Ƃ�
	if (getSign(b) == -1)
	{
		return -2;
	}

	//b = 0�̂Ƃ�
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

	//�ݏ�
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

		//����
		if (multiple(&ans, a, &ans))
		{
			return -1;
		}
	}
	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//�T�v�F���{���ϐ�a, b�ɂ�����a��b���c�Ɋi�[����(�J����)
//�����Fstruct NUMBER* a : �ݏ悳��鑽�{���ϐ�, struct NUMBER* b :	�ݏ�̏�̂Ƃ��̑��{���ϐ�, struct NUMBER* c : �ݏ悵���l���i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s (�I�[�o�[�t���[/�A���_�[�t���[): -1(c�̒l�͕ω����Ȃ�), ���s(b<0)�F-2(c�̒l�͕ω����Ȃ�)
//*****************************************************************
int Dev_power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;
	struct NUMBER tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	//b�����̂Ƃ�
	if (getSign(b) == -1)
	{
		return -2;
	}

	//b = 0�̂Ƃ�
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

	if (divide(b, &tmp, &div, &tmp))	//tmp = 2 -> ��], div = b / 2
	{
		return -1;
	}

	if (isZero(&tmp) == 0)	//�����̎�
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
//�T�v�F���{���ϐ�a�ɂ�����a�̊K��(a!)��b�Ɋi�[����
//�����Fstruct NUMBER* a : �K�悷�鑽�{���ϐ�, struct NUMBER* b : �K�悵���l���i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s(�I�[�o�[�t���[/�A���_�[�t���[) : -1(b�̒l�͕ω����Ȃ�), ���s(a<0) : -2(b�̒l�͕ω����Ȃ�)
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
//�T�v�F���{���ϐ�a, b�ɂ�����a��b�̍ő���񐔂�c�Ɋi�[����
//�����Fstruct NUMBER* a : �ő���񐔂����߂鑽�{���ϐ�, struct NUMBER* b : �ő���񐔂����߂鑽�{���ϐ�, struct NUMBER* c : �ő���񐔂��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int gcd(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER num1, num2, rem;

	clearByZero(&num1);
	clearByZero(&num2);
	clearByZero(&rem);


	if (numComp(&num1, &num2) == -1)	//a < b �Ȃ�
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
		if (divide(&num1, &num2, &num1/*�s�v*/, &rem))
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

	//�����ɂ����Ƃ�������num1�ɂȂ�
	copyNumber(&num1, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ�a, b�ɂ�����a��b�̍ŏ����{����c�Ɋi�[����
//�����Fstruct NUMBER* a : �ŏ����{�������߂鑽�{���ϐ�, struct NUMBER* b : �ŏ����{�������߂鑽�{���ϐ�, struct NUMBER* c : �ŏ����{�����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
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

	if (gcd(a, b, &num1))		//gcd�͕����ɉe�����Ȃ�����a,b�����̂܂ܗp���Ă���
	{
		return -1;
	}

	//num1 = gcd(a,b)

	if (divide(&ans, &num1, &ans, &num1/*�s�v*/))
	{
		return -1;
	}

	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//�T�v�F���{���ϐ�a, b�ɂ�����a��b�̍ŏ����{����c�Ɋi�[����(�J����)
//�����Fstruct NUMBER* a : �ŏ����{�������߂鑽�{���ϐ�, struct NUMBER* b : �ŏ����{�������߂鑽�{���ϐ�, struct NUMBER* c : �ŏ����{�����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
//�⑫�F|a|*|b|/gcd(a,b) -> |a|/gcd(a,b)*|b| �ɕύX
//*****************************************************************
int Dev_lcm(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, num1, num2;
	clearByZero(&ans);
	clearByZero(&num1);
	clearByZero(&num2);

	getAbs(a, &num1);
	getAbs(b, &num2);

	if (gcd(a, b, &ans))		//gcd�͕����ɉe�����Ȃ�����a,b�����̂܂ܗp���Ă���
	{
		return -1;
	}

	//ans = gcd(a,b)

	if (divide(&num1, &ans, &ans, &num1/*�s�v*/))
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
//�T�v�F���{���ϐ�a�ɂ�����a���f�������ʂ���
//�����Fstruct NUMBER* a : �f�������ʂ��鑽�{���ϐ�
//�ߒl�F�f���ł��� : 1, �f���łȂ��܂��͎��s : 0
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

	if (Dev_divide(a, &two, &tmp, &rem))	//2�Ŋ���  tmp = a/2 ... ����͈͓̔��Ń��[�v����
	{
		return 0;
	}

	if (numComp(&tmp, &num/*1*/) == 0)	//a=2�̎��̏���
	{
		return 1;
	}


	while (1)
	{
		if (isZero(&rem) == 0)	//����؂ꂽ�Ƃ�
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
//�T�v�F���{���ϐ�a�ɂ�����a�̕�������b�Ɋi�[����(�����ɂ�sqrt(a)�𒴂��Ȃ��ő�̐�����b�Ɋi�[����)
//�����Fstruct NUMBER* a : �����������߂鑽�{���ϐ�, struct NUMBER* b : ���������i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(b�̒l�͕ω����Ȃ�)
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
//                        �ȉ����Ԍv���p                          //
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
//                       �ȉ��`�F�b�N�p                          //
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

		//�m�F
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

//a, x�����������0, �Ⴄ�Ȃ�-1
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
