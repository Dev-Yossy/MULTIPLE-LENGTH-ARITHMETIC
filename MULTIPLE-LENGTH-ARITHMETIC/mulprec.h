///////////////////////////////////////////////////////////////////////////////////////////
// 
//                               多倍長演算を行う変数と関数
//
// * コンパイル時オプション (-D [option], -D[option], -D [option=data], -D[option=data]):
//       KETA : コンパイル時に桁数(KETA)の値を変更することができる.
//       RADIX : コンパイル時に進数(RADIX)の値を変更することができる.
//       USE_RANDOM : コンパイル時に乱数生成関数設定(USE_RANDOM)の値を変更することができる.
// * 型 :
//       struct NUMBER : 多倍長整数型
//       struct BUNSU  : 多倍長分数型
//
// * 定義済マクロ
//       KETA : 多倍長整数型, 多倍長分数型(分母, 分子) の桁数
//           - 範囲 : 1 以上(デフォルト:20)
//           - 補足 : 桁数が小さすぎると動作が不安定になる可能性あり. 
//                    PIを求める際はRADIX=10000では4以上推奨, RADIX=10では16以上推奨.
//	     RADIX : 進数変更
//           - 範囲 : 10, 10000(デフォルト)
//           - 補足 : PIを求める際は 10進数では KETA >= 16, 10000進数では KETA >= 4 である必要がある.
//       USE_RANDOM : 乱数生成関数選択
//           - 範囲 : 0, 非0
//           - 補足 : 0のときはどの環境においても「rand関数」「srand関数」を使用する.
//                    1のときは「 _DEBUG 」「 __WIN32__ 」が定義されていない環境(主にLinux
//                    (仮想)環境)においては「random関数」「srandom関数」を使用する.
//                    「 _DEBUG 」「 __WIN32__ 」が定義されている環境では0のときと同様.
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////
//      Define      (定義)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------


// 小数点以下必要な桁数 * 2 = KETA ... きれいな値の方が良い
//RADIX = 10000 ... KETA = ROOP * 4 が望ましい(というかそれに最適化している)
//RADIX = 10    ... KETA = ROOP * 16 が望ましい(というかそれに最適化している)
//コンパイル時に「 -D _KETA_=[桁数] 」または 「 -D_KETA_=[桁数] 」を指定すればコンパイル時に桁を変更できる.
#ifndef KETA
#define KETA 20		//桁数
#endif

//コンパイル時に「 -D _RADIX_=[進数] 」または 「 -D_RADIX_=[進数] 」を指定すればコンパイル時に桁を変更できる.(10, 1000のみに対応. デフォルトは10000)
#ifndef RADIX
#define RADIX 10000	//進数
#endif

#define SIGN_MINUS -1
#define SIGN_PLUS 1

//乱数生成関数処理
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
