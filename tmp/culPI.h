#pragma once

#include "mulprec.h"

//定義済みマクロ
#define DO_PRINT	1

#ifdef _DO_PRINT_
#undef DO_PRINT
#define DO_PRINT _DO_PRINT_
#endif

#if RADIX == 10000
#define ROOP		(KETA / 4)		// ... KETA / 4
#else
#define ROOP		(KETA / 16)		// ... KETA / 4
#endif

//円周率計算用変数
struct NUMBER A, B, C, D, E, F, G, H, I, J, K, L, M, N, P, ans, trush;
struct BUNSU R, S, T, U, V, W, X, Y, Z;
struct NUMBER num_6;

//円周率計算用関数
int culPI();

//円周率表示用関数
void dispResult(struct NUMBER* a);

