#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define USE_RANDOM 1
#if !USE_RANDOM || (defined _DEBUG) || (defined __WIN32__)
#define USE_TIME
#define srandom(m) srand(m)
#define random() rand()
#endif


//////////////////////////////////////////////////////////////////////////////////////
//      Define      (定義)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

#define KETA 24	//roop *1.5  < KETA でないと不安定(RADIX=10000) ... roopの3倍以上あれば足りる 4倍推奨
#define RADIX 10000	//進数
#define SIGN_PLUS 1
#define SIGN_MINUS -1

//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//      Type of Variable      (変数の型)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

struct NUMBER
{
	int n[KETA];    //各桁の値 [上の桁]---[下の桁] [KETA - 1]---[0]
	int sign;       //符号変数 1:正 0, -1:負
};


struct BUNSU
{
	struct NUMBER bunshi;	//分子の値(>=0)
	struct NUMBER bunbo;	//分母の値(>=0)
	int sign;				//分数全体の符号 1:正 0, -1:負
};


//チェック用
enum ViewStyle
{
	None,
	OnlyAnswer,
	All,
};

//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//      Prototype Declaration - NUMBER -     (プロトタイプ宣言)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------
int Dev2_multiple(struct NUMBER* a, struct NUMBER* b, struct NUMBER* c);

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
int Cul_power(struct NUMBER*, struct NUMBER*, struct NUMBER*);	//Dev_power用
int factorial(struct NUMBER*, struct NUMBER*);
int gcd(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int lcm(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int Dev_lcm(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int isPrime(struct NUMBER*);
int squareroot(struct NUMBER*, struct NUMBER*);
int sqrt_newton(struct NUMBER*, struct NUMBER*);

//------------------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////////////
//      Prototype Declaration - BUNSU -     (プロトタイプ宣言)
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
//                                以下初期設定用
//////////////////////////////////////////////////////////////////////////////////////

//変数
// struct NUMBER 型 定数
struct NUMBER SN_0;		// 0
struct NUMBER SN_1;		// 1
struct NUMBER SN_2;		// 2
// struct NUMBER 型 変数
struct NUMBER SN_trush;	// 使用しない引数に入れる関数. 値は不定
//関数
void MLAsetup(void);

//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//                                以下時間計測用                                     //
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
//                                以下チェック用                                     //
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

void RoopFunction_ASM(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int, unsigned int, enum ViewStyle);
void RoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int, unsigned int, enum ViewStyle);
double FastRoopFunction_ASM(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size);
double FastRoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int roop, unsigned int size);
void check_setInt(struct NUMBER* a);
int checkNumber(struct NUMBER* a, int x);

//------------------------------------------------------------------------------------
