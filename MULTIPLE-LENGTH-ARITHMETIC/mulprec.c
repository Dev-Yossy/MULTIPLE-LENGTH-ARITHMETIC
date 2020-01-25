#include "mulprec.h"



//*****************************************************************
//�T�v�F���{�����Z�ɂ����鏉���ݒ���s��, struct NUMBER �^ �萔 SN_0...0, SN_1...1, SN_2...2
//�����F�Ȃ�
//�ߒl�F�Ȃ�
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
//�T�v�F���{���ϐ���0�ɏ���������
//�����Fstruct NUMBER* a : ���������鑽�{���ϐ�
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void clearByZero(struct NUMBER* a)
{
	copyNumber(&SN_0, a);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ���\������
//�����Fstruct NUMBER* a : �\�����鑽�{���ϐ�
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void dispNumber(struct NUMBER* a)
{
	int i;
	if (getSign(a) == SIGN_PLUS)	putchar('+');
	else							putchar('-');

	if (KETA == 1000) {
		for (i = KETA - 1; i >= 0; i--)
			printf("%04d", a->n[i]);        //�����m�F�p
	}
	else if (KETA == 10) {
		for (i = KETA - 1; i >= 0; i--)
			printf("%1d", a->n[i]);        //�����m�F�p
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
		a->n[i] = random() % RADIX;
	//����
	setSign(a, (random() % 2 == 1) ? SIGN_PLUS : SIGN_MINUS);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ����R�s�[����
//�����Fstruct NUMBER* a : �R�s�[���̑��{���ϐ�, struct NUMBER* b : �R�s�[��̑��{���ϐ�
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void copyNumber(struct NUMBER* a, struct NUMBER* b)
{
	*b = *a;
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ��̐�Βl�����߂Ċi�[����
//�����Fstruct NUMBER* a : ��Βl�����߂鑽�{���ϐ�, struct NUMBER* b : ��Βl���i�[���鑽�{���ϐ�
//�ߒl�F�Ȃ�
///////////////////////////////////////////////////////////////////
void getAbs(struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	setSign(b, SIGN_PLUS);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ���0���ǂ����𔻕ʂ���
//�����Fstruct NUMBER* a : ���ʂ��鑽�{���ϐ�
//�ߒl�F0�̂Ƃ� : 0, ����ȊO�̂Ƃ� : -1
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
//�T�v�F���{���ϐ���10�{���Ċi�[����
//�����Fstruct NUMBER* a : 10�{���������{���ϐ�, struct NUMBER* b : �v�Z�����l���i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s(�����ӂ�) : -1(b�̒l�͕ω����Ȃ�), ���s(���̑�) : -1(b�̒l�͕ω����Ȃ�), 
//�⑫�FRADIX�i���ɕύX��������10�{�ł͂Ȃ�RADIX�{�ɂȂ�B
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
//�T�v�F���{���ϐ���10�Ŋ����������i�[����
//�����Fstruct NUMBER* a : 1/10�ɂ��������{���ϐ�, struct NUMBER* b : �v�Z�����l���i�[���鑽�{���ϐ�
//�ߒl�F���� : �]��
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
//�T�v�F���{���ϐ���int�^�̐������i�[����
//�����Fstruct NUMBER* a : �i�[����鑽�{���ϐ�, int x : �i�[���������{���ϐ�
//�ߒl�F���� : 0, ���s : -1(a�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int setInt(struct NUMBER* a, int x)
{
	int i = 0;
	struct NUMBER ans;
	clearByZero(&ans);

	if (x < 0) {	//a�͂��łɁ{�Ȃ̂�x��-�̂Ƃ��̂�setSign����
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
//�T�v�F���{���ϐ��̕�����ݒ肷��
//�����Fstruct NUMBER* a : �ݒ肳��鑽�{���ϐ�, int x : �ݒ肷�镄��(+ : 1, - : -1)
//�ߒl�F���� : 0, ���s : -1(a�̕����͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int setSign(struct NUMBER* a, int s)
{
	if (s != SIGN_PLUS && s != SIGN_MINUS)
		return -1;
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
	//-0�����ꍞ�񂾎��̑΍�
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
//�T�v�F���{���ϐ�a, b�̌�������
//�����Fstruct NUMBER* a : �������鑽�{���ϐ�(1), struct NUMBER* b : �������鑽�{���ϐ�(2)
//�ߒl�F�Ȃ�
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
//�T�v�F���{���ϐ�a, b�̘a�����߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �a���i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
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

	//���Z
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
//�T�v�F���{���ϐ�a���C���N�������g����c�Ɋi�[����
//�����Fstruct NUMBER* a : �C���N�������g���鑽�{���ϐ�, struct NUMBER* b : ���ʂ��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int increment(struct NUMBER* a, struct NUMBER* b)
{
	return add(a, &SN_1, b);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ�a, b�̍������߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
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

	//���Z
	int i, d, flg = 0;

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (numComp(&abs_a, &abs_b) < 0) {			//a < b
		swap(&abs_a, &abs_b);
		if (setSign(&ans, getSign(&ans) * SIGN_MINUS)) // a < 0, b < 0 �̂Ƃ��Ƀ}�C�i�X�ɂȂ��Ă���\��������̂Ŕ��]
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
//�T�v�F���{���ϐ�a���f�N�������g����c�Ɋi�[����
//�����Fstruct NUMBER* a : �f�N�������g���鑽�{���ϐ�, struct NUMBER* b : ���ʂ��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int decrement(struct NUMBER* a, struct NUMBER* b)
{
	return sub(a, &SN_1, b);
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ�a, b�̐ς����߂�c�Ɋi�[����
//�����Fstruct NUMBER* a : ��Z���鑽�{���ϐ�(1), struct NUMBER* b : ��Z���鑽�{���ϐ�(2), struct NUMBER* c : �ς��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0) {		//�����Ȃ��Ƃ��ǂ��炩�����0�̂Ƃ�
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
	//�ǂ��炩����̂ݕ��̂Ƃ�
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))
			return -1;

	copyNumber(&ans, c);

	return 0;
}


//*****************************************************************
//�T�v�F���{���ϐ�a, b�̐ς����߂�c�Ɋi�[����(�J����)
//�����Fstruct NUMBER* a : ��Z���鑽�{���ϐ�(1), struct NUMBER* b : ��Z���鑽�{���ϐ�(2), struct NUMBER* c : �ς��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
//�⑫�Fmultiple�֐��̖�3�{(KETA=10), ��16.7�{(KETA=100)�̑��x. (KETA / 2)
//*****************************************************************
int Dev_multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans, tmp;
	int i, j, flag = 0;

	if (isZero(a) == 0 || isZero(b) == 0) {		//�ǂ��炩�����0�̂Ƃ�
		clearByZero(c);
		return 0;
	}

	clearByZero(&ans);
	clearByZero(&tmp);

	for (i = KETA - 1; i >= 0; i--) {		//b�̏�̌�����s��
		if (b->n[i]) {
			if (b->n[i] == 1) {
				copyNumber(a, &tmp);
			}
			else {
				for (j = 0; j < KETA; j++) {		//��i���̓������o��
					int e = a->n[j] * b->n[i] + flag;
					tmp.n[j] = e % RADIX;
					flag = e / RADIX;
				}
				if (flag)
					return -1;
			}

			if (add(&ans, &tmp, &ans))			//���Z
				return -1;
		}
		if (i > 0 && mulBy10(&ans, &ans))	//�Ō��1��ȊO��10�{ * RADIX�{
			return -1;
	}
	//�ǂ��炩����̂ݕ��̂Ƃ�
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))
			return -1;

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

	//1�����ʗp
	int flg;
	if ((flg = divide_U10(a, b, c, d)) != -2)	//b��1���łȂ��ꍇ�ȊO�̎��̏��Z
		return flg;

	//��������++�̏��Z
	copyNumber(&abs_a, &rem);

	while (numComp(&rem, &abs_b) >= 0) {
		if (sub(&rem, &abs_b, &rem))
			return -2;
		if (increment(&ans, &ans))
			return -2;
	}

	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
		if (setSign(&ans, SIGN_MINUS))	//�ǂ��炩����̂ݕ��̂Ƃ�
			return -2;
	if (setSign(&rem, getSign(a)))		//�]��̕���
		return -2;

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
	struct NUMBER ans, rem;
	int h = 0, i = KETA - 1;

	clearByZero(&ans);

	//�]�� : rem
	int r = divBy10(b, &ans);

	if (isZero(b) == 0)		//0���Z
		return -1;
	if (isZero(&ans))		//b��1���łȂ��Ȃ�
		return -2;
	if (isZero(a) == 0) {	//���q��0
		clearByZero(c);
		clearByZero(d);
		return 0;
	}

	//b��1���Ȃ�
	//b �� rem �Ɠ�����(struct NUMBER -> int)

	for (i = KETA - 1; i >= 0; i--) {
		int t = h * RADIX + a->n[i];
		h = t % r;
		ans.n[i] = t / r;
	}

	//�ǂ��炩����̂ݕ��̂Ƃ�
	if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS) {
		if (setSign(&ans, SIGN_MINUS))
			return -3;
	}
	else {
		setSign(&ans, SIGN_PLUS);		//1���̔��ʂ̍ۂ�c�Ƀ}�C�i�X�̕����������Ă���\�������邽�ߐݒ肷��
	}

	if (setInt(&rem, h))		//�]��
		return -3;
	if (setSign(&rem, getSign(a)))		//�]��̕���
		return -3;

	copyNumber(&ans, c);
	copyNumber(&rem, d);

	return 0;
}


//*****************************************************************
//�T�v�F���{���ϐ�a, b�̏������߂�c�Ɋi�[���A�]���d�Ɋi�[����B(�J���ŁF����)
//�����Fstruct NUMBER* a : ���Z���鑽�{���ϐ�(1), struct NUMBER* b : ���Z���鑽�{���ϐ�(2), struct NUMBER* c : �����i�[���鑽�{���ϐ�, struct NUMBER* d : �]����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s(0���Z) : -1(c, d�̒l�͕ω����Ȃ�), ���s(���̑��G���[)�F-2(c, d�̒l�͕ω����Ȃ�)
//*****************************************************************
int Dev_divide(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c, struct NUMBER* d)
{
	struct NUMBER ans, tmp_a, tmp_b, tmp_d, tmp_e, tmp_check;

	if (isZero(b) == 0)		//0���Z
		return -1;
	if (isZero(a) == 0) {	//���q��0�̂Ƃ�
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

	//��������++�̏��Z

	getAbs(a, &tmp_a);
	getAbs(b, &tmp_b);

	while (numComp(&tmp_a, &tmp_b) >= 0) {	//a < b �łȂ��Ȃ�
		copyNumber(&tmp_b, &tmp_d);

		copyNumber(&SN_1, &tmp_e);

		int rem = divBy10(&tmp_a, &tmp_check);
		while (1) {
			int flg = numComp(&tmp_check, &tmp_d);
			if (flg == -1)						//tmp_d��mulBy10�����tmp_a�𒴂���
				break;
			if (flg == 0 && rem < tmp_d.n[0])	//�������Ƃ��͗]��rem�ɂ���Č��܂�. rem>0�Ȃ�tmp_a > tmp_d*10    * RADIX
				break;							//d.n[0]�Ƃ̔�r��1��ڂ̂���, 2��ڈȍ~��d.n[0]��0�Ȃ̂ŏ��false
			//tmp_a >= tmp_d * 10�̂Ƃ� * RADIX
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
		if (setSign(&ans, -1))	//�ǂ��炩����̂ݕ��̂Ƃ�
			return -2;
	if (setSign(&tmp_a, getSign(a)))		//�]��̕���
		return -2;

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
	struct NUMBER ans, tmp_a, tmp_b, tmp_d, tmp_e;
	//�菇1
	clearByZero(&ans);
	clearByZero(&tmp_a);
	clearByZero(&tmp_b);
	clearByZero(&tmp_d);
	clearByZero(&tmp_e);
	//0���Z
	if (isZero(b) == 0)
		return -1;
	//���q��0�̂Ƃ�
	if (isZero(a) == 0) {
		clearByZero(c);
		clearByZero(d);
		return 0;
	}
	//�}�C�i�X����
	//���Ȃ��Ƃ��ǂ��炩��������̂Ƃ�
	if (getSign(a) == SIGN_MINUS || getSign(b) == SIGN_MINUS) {
		getAbs(a, &tmp_a);
		getAbs(b, &tmp_b);

		int num = Dev_divide_X(&tmp_a, &tmp_b, &ans, &tmp_d);
		if (num < 0)
			return num;
		//�ǂ��炩����̂ݕ��̂Ƃ�
		if (getSign(a) + getSign(b) == SIGN_PLUS + SIGN_MINUS)
			if (setSign(&ans, SIGN_MINUS))
				return -2;
		//�]��̕��� (�]��̕����͏�Ɋ����鐔�̕����Ɉˑ�����)
		if (setSign(&tmp_d, getSign(a)))
			return -2;

		copyNumber(&ans, c);
		copyNumber(&tmp_d, d);

		return 0;
	}

	copyNumber(a, &tmp_a);
	copyNumber(b, &tmp_b);

	//�菇2
	while (numComp(&tmp_a, &tmp_b) != -1) {
		//�菇3
		copyNumber(&tmp_b, &tmp_d);
		//�菇4
		copyNumber(&SN_1, &tmp_e);
		//�菇5

		//d��10�{���Ă����ƍŏ��bit����0�ɂȂ��Ă��Ȃ�a>d�ƂȂ邱�Ƃ����邽��, �����10�{�����overflow * RADIX
		//������1...��ɗ]�T�̂��錅����p�ӂ��Ă���
		//������2...�ŏ��bit�̒l����0�ɂȂ����Ƃ��ɓ��ʂȏ�����`��
		while (1) {
			if (mulBy10(&tmp_d, &tmp_d))
				return -2;
			if (numComp(&tmp_a, &tmp_d) != 1) {
				divBy10(&tmp_d, &tmp_d);	//���ꂾ��KETA-1�܂Ŗ��܂�悤�Ȑ����̎��ɕs����N����\��������
				break;
			}
			//�菇6
			if (mulBy10(&tmp_e, &tmp_e))
				return -2;
		}

		//�菇7
		if (sub(&tmp_a, &tmp_d, &tmp_a))
			return -2;

		if (add(&ans, &tmp_e, &ans))
			return -2;
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
	struct NUMBER ans, tmp;

	clearByZero(&ans);
	clearByZero(&tmp);

	if (getSign(b) == SIGN_MINUS)	//b�����̂Ƃ�
		return -2;
	if (isZero(b) == 0) {	//b = 0�̂Ƃ�
		copyNumber(&SN_1, &ans);
		copyNumber(&ans, c);
		return 0;
	}

	//�ݏ�
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
//�T�v�F���{���ϐ�a, b�ɂ�����a��b���c�Ɋi�[����(�J����)
//�����Fstruct NUMBER* a : �ݏ悳��鑽�{���ϐ�, struct NUMBER* b :	�ݏ�̏�̂Ƃ��̑��{���ϐ�, struct NUMBER* c : �ݏ悵���l���i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s (�I�[�o�[�t���[/�A���_�[�t���[): -1(c�̒l�͕ω����Ȃ�), ���s(b<0)�F-2(c�̒l�͕ω����Ȃ�)
//*****************************************************************
int Dev_power(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;

	clearByZero(&ans);
	//b�����̂Ƃ�
	if (getSign(b) == SIGN_MINUS)
		return -2;
	//b = 0�̂Ƃ�
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

	if (Dev_divide(b, &SN_2, &div, &tmp))//tmp = 2 -> ��], div = b / 2
		return -1;
	if (isZero(&tmp) == 0) {		//�����̎�
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
//�T�v�F���{���ϐ�a, b�ɂ�����a��b�̍ő���񐔂�c�Ɋi�[����
//�����Fstruct NUMBER* a : �ő���񐔂����߂鑽�{���ϐ�, struct NUMBER* b : �ő���񐔂����߂鑽�{���ϐ�, struct NUMBER* c : �ő���񐔂��i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int gcd(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER abs_a, abs_b, rem;

	clearByZero(&abs_a);
	clearByZero(&abs_b);
	clearByZero(&rem);

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (numComp(&abs_a, &abs_b) == -1)	//a < b �Ȃ�
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

	//�����ɂ����Ƃ�������num1�ɂȂ�
	copyNumber(&abs_a, c);

	return 0;
}


///////////////////////////////////////////////////////////////////
//�T�v�F���{���ϐ�a, b�ɂ�����a��b�̍ŏ����{����c�Ɋi�[����
//�����Fstruct NUMBER* a : �ŏ����{�������߂鑽�{���ϐ�, struct NUMBER* b : �ŏ����{�������߂鑽�{���ϐ�, struct NUMBER* c : �ŏ����{�����i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�)
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
	if (gcd(a, b, &abs_a))		//gcd�͕����ɉe�����Ȃ�����a,b�����̂܂ܗp���Ă���
		return -1;
	//num1 = gcd(a,b)
	if (Dev_divide(&ans, &abs_a, &ans, &SN_trush))
		return -1;

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
	struct NUMBER ans, abs_a, abs_b;

	clearByZero(&ans);
	clearByZero(&abs_a);
	clearByZero(&abs_b);

	getAbs(a, &abs_a);
	getAbs(b, &abs_b);

	if (gcd(a, b, &ans))		//gcd�͕����ɉe�����Ȃ�����a,b�����̂܂ܗp���Ă���
		return -1;
	if (Dev_divide(&abs_a, &ans, &ans, &SN_trush))
		return -1;
	if (Dev_multiple(&ans, &abs_b, &ans))
		return -1;

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
	struct NUMBER num, rem, tmp;

	clearByZero(&num);
	clearByZero(&rem);
	clearByZero(&tmp);

	if (numComp(a, &SN_1) <= 0)	//a <= 1
		return 0;
	if (Dev_divide(a, &SN_2, &tmp, &rem))	//2�Ŋ���  tmp = a/2 ... ����͈͓̔��Ń��[�v����
		return 0;
	if (numComp(&tmp, &SN_1) == 0)	//a=2 (a/2=1)�̎��̏���	... 2�͑f��
		return 1;

	if (setInt(&num, 3))
		return 0;

	while (1) {
		if (Dev_divide(a, &num, &SN_trush, &rem))
			break;
		if (isZero(&rem) == 0)	//����؂ꂽ�Ƃ�
			break;
		if (add(&num, &SN_2, &num))
			break;
		if (numComp(&num, &tmp) > 0)
			return 1;
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
//�T�v�F���{���ϐ�a�ɂ�����a�̕�������Newton-Raphson�@��p���ċ��߂�b�Ɋi�[����(�����ɂ�sqrt(a)�𒴂��Ȃ��ő�̐�����b�Ɋi�[����)
//�����Fstruct NUMBER* a : �����������߂鑽�{���ϐ�, struct NUMBER* b : ���������i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(b�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int sqrt_newton(struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER x;		//���݂̕������̋ߎ��l
	struct NUMBER x_b;		//1�O��x
	struct NUMBER x_c;		//2�O��x

	clearByZero(&x);
	clearByZero(&x_b);
	clearByZero(&x_c);

	if (numComp(a, &SN_0) < 0)		//a < 0
		return -11;
	if (numComp(a, &SN_0) == 0 || numComp(a, &SN_1) == 0) {	// a = 0 or 1 �Ȃ� sqrt(a) = a
		copyNumber(a, b);
		return 0;
	}
	//�����lx�̐ݒ�
	//if (Dev_divide(a, &SN_2, &x, &SN_trush))		//X = a / 2
	//	return -1;
	copyNumber(a, &x);
	int i = 0, cnt;
	while (x.n[KETA - 1 - i] == 0)
		i++;
	cnt = (KETA - (i / 2)) / 4 + KETA / 20;	//�ŏ��bit�܂Œl�������Ă����ԂɍœK��
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

		if (numComp(&x, &x_b) == 0)		// ����
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
//�T�v�F���{���ϐ�a�ɂ�����a�̕�������񕪖@��p���ċ��߂�b�Ɋi�[����(�����ɂ�sqrt(a)�𒴂��Ȃ��ő�̐�����b�Ɋi�[����)
//�����Fstruct NUMBER* a : �����������߂鑽�{���ϐ�, struct NUMBER* b : ���������i�[���鑽�{���ϐ�
//�ߒl�F���� : 0, ���s : -1(c�̒l�͕ω����Ȃ�), ���������� : -2(c�̒l�͕ω����Ȃ�)
///////////////////////////////////////////////////////////////////
int bisection(struct NUMBER* a, struct NUMBER* b, struct NUMBER* need_sqrt, struct NUMBER* c)
{
	struct NUMBER e;	//��������p�̕ϐ�
	struct NUMBER d;	//���݂�x�̒l
	struct NUMBER fx, fa, fb;	//f(x), f(a), f(b)�̒l
	struct NUMBER num_plus, num_minus, num2, trush;
	int as, bs, cs;		//f(a), f(b), f(c)�̕���

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
//                          �ȉ������p                           //
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

	//���q
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
	if (B_setSign(&ans, getSign(&tmp)))		//����
		return -16;
	getAbs(&tmp, &tmp);
	copyNumber(&tmp, &ans.bunshi);

	//����
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

	//���q
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
	if (B_setSign(&ans, getSign(&tmp)))		//����
		return -16;
	getAbs(&tmp, &tmp);
	copyNumber(&tmp, &ans.bunshi);

	//����
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
	copyNumber(a, &c->bunshi);		//���q
	copyNumber(b, &c->bunbo);		//����
}
//������b�ɂ�
void BtoN_copyNumber(struct BUNSU* a, struct NUMBER* b, struct NUMBER* c)
{
	struct NUMBER ans;
	clearByZero(&ans);
	copyNumber(&a->bunshi, &ans);	//���q�ɂ͕��������邽�߈�xans�ɓ���Ă���
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
	//����
	if (B_setSign(&ans, getSign(a)))
		return -1;
	//���q
	getAbs(a, &ans.bunshi);
	//����
	copyNumber(&SN_1, &ans.bunbo);

	B_copyNumber(&ans, b);
	return 0;
}


///////////////////////////////////////////////////////////////////
//                        �ȉ����Ԍv���p                         //
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
