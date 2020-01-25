///////////////////////////////////////////////////////////////////////////////////////////
// 
//                               ���{�����Z���s���ϐ��Ɗ֐�
//
// * �R���p�C�����I�v�V���� (-D [option], -D[option], -D [option=data], -D[option=data]):
//       KETA : �R���p�C�����Ɍ���(KETA)�̒l��ύX���邱�Ƃ��ł���.
//       RADIX : �R���p�C�����ɐi��(RADIX)�̒l��ύX���邱�Ƃ��ł���.
//       USE_RANDOM : �R���p�C�����ɗ��������֐��ݒ�(USE_RANDOM)�̒l��ύX���邱�Ƃ��ł���.
// * �^ :
//       struct NUMBER : ���{�������^
//       struct BUNSU  : ���{�������^
//
// * ��`�σ}�N��
//       KETA : ���{�������^, ���{�������^(����, ���q) �̌���
//           - �͈� : 1 �ȏ�(�f�t�H���g:20)
//           - �⑫ : ����������������Ɠ��삪�s����ɂȂ�\������. 
//                    PI�����߂�ۂ�RADIX=10000�ł�4�ȏ㐄��, RADIX=10�ł�16�ȏ㐄��.
//	     RADIX : �i���ύX
//           - �͈� : 10, 10000(�f�t�H���g)
//           - �⑫ : PI�����߂�ۂ� 10�i���ł� KETA >= 16, 10000�i���ł� KETA >= 4 �ł���K�v������.
//       USE_RANDOM : ���������֐��I��
//           - �͈� : 0, ��0
//           - �⑫ : 0�̂Ƃ��͂ǂ̊��ɂ����Ă��urand�֐��v�usrand�֐��v���g�p����.
//                    1�̂Ƃ��́u _DEBUG �v�u __WIN32__ �v����`����Ă��Ȃ���(���Linux
//                    (���z)��)�ɂ����Ắurandom�֐��v�usrandom�֐��v���g�p����.
//                    �u _DEBUG �v�u __WIN32__ �v����`����Ă�����ł�0�̂Ƃ��Ɠ��l.
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////
//      Define      (��`)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------


// �����_�ȉ��K�v�Ȍ��� * 2 = KETA ... ���ꂢ�Ȓl�̕����ǂ�
//RADIX = 10000 ... KETA = ROOP * 4 ���]�܂���(�Ƃ���������ɍœK�����Ă���)
//RADIX = 10    ... KETA = ROOP * 16 ���]�܂���(�Ƃ���������ɍœK�����Ă���)
//�R���p�C�����Ɂu -D _KETA_=[����] �v�܂��� �u -D_KETA_=[����] �v���w�肷��΃R���p�C�����Ɍ���ύX�ł���.
#ifndef KETA
#define KETA 20		//����
#endif

//�R���p�C�����Ɂu -D _RADIX_=[�i��] �v�܂��� �u -D_RADIX_=[�i��] �v���w�肷��΃R���p�C�����Ɍ���ύX�ł���.(10, 1000�݂̂ɑΉ�. �f�t�H���g��10000)
#ifndef RADIX
#define RADIX 10000	//�i��
#endif

#define SIGN_MINUS -1
#define SIGN_PLUS 1

//���������֐�����
#ifndef USE_RANDOM
#define USE_RANDOM 1
#endif

#if !USE_RANDOM || (defined _DEBUG) || (defined __WIN32__)
#define USE_TIME
#define srandom(m) srand(m)
#define random() rand()
#endif

//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//      Type of Variable      (�ϐ��̌^)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

struct NUMBER
{
	int n[KETA];    //�e���̒l [��̌�]---[���̌�] [KETA - 1]---[0]
	int sign;       //�����ϐ� 1:�� 0, -1:��
};


struct BUNSU
{
	struct NUMBER bunshi;	//���q�̒l(>=0)
	struct NUMBER bunbo;	//����̒l(>=0)
	int sign;				//�����S�̂̕��� 1:�� 0, -1:��
};


//�`�F�b�N�p
enum ViewStyle
{
	None,
	OnlyAnswer,
	All,
};

//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//      Prototype Declaration - NUMBER -     (�v���g�^�C�v�錾)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

void clearByZero(struct NUMBER*);
void dispNumber(struct NUMBER*);
void setRnd(struct NUMBER*, int);
void copyNumber(struct NUMBER*, struct NUMBER*);
void getAbs(struct NUMBER*, struct NUMBER*);
int isZero(struct NUMBER*);
int mulBy10(struct NUMBER*, struct NUMBER*);
int divBy10(struct NUMBER*, struct NUMBER*);
int setInt(struct NUMBER*, int);
int setSign(struct NUMBER*, int);
int getSign(struct NUMBER*);
int numComp(struct NUMBER*, struct NUMBER*);
void swap(struct NUMBER*, struct NUMBER*);
int add(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int increment(struct NUMBER*, struct NUMBER*);
int sub(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int decrement(struct NUMBER*, struct NUMBER*);
int multiple(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int Dev_multiple(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int divide(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*);
int divide_U10(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*);
int Dev_divide(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*);
int Dev_divide_X(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*);
int power(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int Dev_power(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int Cul_power(struct NUMBER*, struct NUMBER*, struct NUMBER*);	//Dev_power�p
int factorial(struct NUMBER*, struct NUMBER*);
int gcd(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int lcm(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int Dev_lcm(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int isPrime(struct NUMBER*);
int squareroot(struct NUMBER*, struct NUMBER*);
int sqrt_newton(struct NUMBER*, struct NUMBER*);

//------------------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////////////
//      Prototype Declaration - BUNSU -     (�v���g�^�C�v�錾)
//////////////////////////////////////////////////////////////////////////////////////

void B_clearByZero(struct BUNSU*);
void B_dispNumber(struct BUNSU*);
int B_getSign(struct BUNSU*);
int B_setSign(struct BUNSU*, int);
void B_copyNumber(struct BUNSU*, struct BUNSU*);
void B_setRnd(struct BUNSU*, int);
int B_setInt(struct BUNSU*, int, int);
void B_getAbs(struct BUNSU*, struct BUNSU*);
int B_yakubun(struct BUNSU*, struct BUNSU*);
int B_multiple(struct BUNSU*, struct BUNSU*, struct BUNSU*);
int B_divide(struct BUNSU*, struct BUNSU*, struct BUNSU*);
int B_add(struct BUNSU*, struct BUNSU*, struct BUNSU*);
int B_sub(struct BUNSU*, struct BUNSU*, struct BUNSU*);
void NtoB_copyNumber(struct NUMBER*, struct NUMBER*, struct BUNSU*);
void BtoN_copyNumber(struct BUNSU*, struct NUMBER*, struct NUMBER*);
int B_FractionToReal(struct BUNSU*, struct NUMBER*);
int B_RealToFraction(struct NUMBER*, struct BUNSU*);


//------------------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////////////
//                                �ȉ������ݒ�p
//////////////////////////////////////////////////////////////////////////////////////

//�ϐ�
// struct NUMBER �^ �萔
struct NUMBER SN_0;		// 0
struct NUMBER SN_1;		// 1
struct NUMBER SN_2;		// 2
// struct NUMBER �^ �ϐ�
struct NUMBER SN_trush;	// �g�p���Ȃ������ɓ����֐�. �l�͕s��
//�֐�
void MLAsetup(void);

//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//                                �ȉ����Ԍv���p                                     //
//////////////////////////////////////////////////////////////////////////////////////



#ifndef _DEBUG 

#include <sys/time.h>
time_t timeCount;
void timeStart(void);
unsigned int timeStop(void);
void clockStart(void);
double clockStop(void);


#else

#include <time.h>
time_t timeCount;
clock_t clockCount;
void timeStart(void);
unsigned int timeStop(void);
void clockStart(void);
double clockStop(void);

#endif


//////////////////////////////////////////////////////////////////////////////////////
//                                �ȉ��`�F�b�N�p                                     //
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

void RoopFunction_ASM(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int, unsigned int, enum ViewStyle);
void RoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int, unsigned int, enum ViewStyle);
double FastRoopFunction_ASM(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size);
double FastRoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size);
void check_setInt(struct NUMBER* a);
int checkNumber(struct NUMBER* a, int x);

//------------------------------------------------------------------------------------
