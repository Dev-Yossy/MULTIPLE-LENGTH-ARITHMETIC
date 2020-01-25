#include "culPI.h"

/*
  2   A   P  1   C   D   E   F   G
PI  = ― × Σ  ― ( ― - ― - ― - ― + ― )  =  R × Σ  S ( T - U - V - W + X )  =  R × Σ  S × T  =  R × Σ  S  =  R × Y
	  B  N=0 H   I   J   K   L   M
*/
int culPI(void)
{
#if DO_PRINT
	printf("Setting Up ... ");
#endif // DO_PRINT

	if (ROOP == 0) {
		printf("Error: ROOP : %d\n", ROOP);
#if RADIX == 10000
		printf("KETA needs 4 ~\n");
#elif RADIX == 10
		printf("KETA needs 16 ~\n");
#endif
		return -1;
	}

	timeStart();

	MLAsetup();

	int i = 0, flg = 0;

	clearByZero(&ans);
	clearByZero(&trush);

	//clearByZero(&A);
	//clearByZero(&B);
	clearByZero(&C);
	clearByZero(&D);
	clearByZero(&E);
	clearByZero(&F);
	clearByZero(&G);
	clearByZero(&H);
	clearByZero(&I);
	clearByZero(&J);
	clearByZero(&K);
	clearByZero(&L);
	clearByZero(&M);

	clearByZero(&N);
	clearByZero(&P);

	B_clearByZero(&R);
	B_clearByZero(&S);
	B_clearByZero(&T);
	B_clearByZero(&U);
	B_clearByZero(&V);
	B_clearByZero(&W);
	B_clearByZero(&X);
	B_clearByZero(&Y);
	B_setInt(&Y, 0, 1);		// 0 / 0 だと不具合が起きる(そもそも0/0のまま計算をしてはならない)
	B_clearByZero(&Z);

	//num_6
	flg += setInt(&num_6, 6);

	// A
	//flg += setInt(&A, 9);
	// B
	//flg += setInt(&B, 8);
	// C
	flg += setInt(&C, 16);
	// D
	flg += setInt(&D, 24);
	// E
	flg += setInt(&E, 8);
	// F
	flg += setInt(&F, 6);
	// G
	//flg += setInt(&G, 1);
	copyNumber(&SN_1, &G);
	// N ループ回数
	//flg += setInt(&N, 0);
	copyNumber(&SN_0, &N);
	// P ループ最大回数
	flg += setInt(&P, ROOP);
	// R = A / B
	//NtoB_copyNumber(&A, &B, &R);
	B_setInt(&R, 9, 8);

	if (flg) {
		printf(" Error: where.CulPI.Setup\n");
		printf("flg = %d\n", flg);
		return -1;
	}

#if DO_PRINT
	printf("Done !\n\rRoop \'%d\' times ... %d / %d", ROOP, i, ROOP);
#endif // DO_PRINT

	while (numComp(&N, &P) < 0) {

		clearByZero(&H);
		clearByZero(&I);
		clearByZero(&J);
		clearByZero(&K);
		clearByZero(&L);
		clearByZero(&M);
		B_clearByZero(&S);
		B_clearByZero(&T);
		B_clearByZero(&U);
		B_clearByZero(&V);
		B_clearByZero(&W);
		B_clearByZero(&X);

		//処理---ここから---
		// H
		flg += setInt(&H, 64);					// 64 ... H
		flg += Dev_power(&H, &N, &H);			// 64^n ... H
		// 6 n + #
		flg += Dev_multiple(&num_6, &N, &I);	// 6n
		flg += increment(&I, &I);				// 6n+1 ... I
		flg += increment(&I, &J);				// 6n+2 ... J
		flg += increment(&J, &K);				// 6n+3 ... K
		flg += increment(&K, &L);				// 6n+4 ... L
		flg += increment(&L, &M);				// 6n+5 ... M

		// I
		flg += Dev_multiple(&I, &I, &I);		// (6n+1)^2 ... I
		// J
		flg += Dev_multiple(&J, &J, &J);		// (6n+2)^2 ... J
		// K
		flg += Dev_multiple(&K, &K, &K);		// (6n+3)^2 ... K
		// L
		flg += Dev_multiple(&L, &L, &L);		// (6n+4)^2 ... L
		// M
		flg += Dev_multiple(&M, &M, &M);		// (6n+5)^2 ... M

		//1/H -> S
		NtoB_copyNumber(&SN_1, &H, &S);
		//C/I -> T
		NtoB_copyNumber(&C, &I, &T);
		//D/J -> U
		NtoB_copyNumber(&D, &J, &U);
		//E/K -> V
		NtoB_copyNumber(&E, &K, &V);
		//F/L -> W
		NtoB_copyNumber(&F, &L, &W);
		//G/M -> X
		NtoB_copyNumber(&G, &M, &X);
		// T - U - V - W + X -> T
		flg += B_sub(&T, &U, &T);
		flg += B_sub(&T, &V, &T);
		flg += B_sub(&T, &W, &T);
		flg += B_add(&T, &X, &T);
		//S * T -> S
		flg += B_multiple(&S, &T, &S);

		//処理---ここまで---

		//ΣS -> Y
		flg += B_add(&Y, &S, &Y);
		//N++
		flg += increment(&N, &N);
		if (flg) {
			printf(" ... Error: where.CulPI.Roop\n");
			printf("\nflg = %d\n", flg);
			return -1;
		}

#if DO_PRINT
		printf("\rRoop \'%d\' times ... %d / %d", ROOP, ++i, ROOP);
#endif // DO_PRINT
	}

#if DO_PRINT
	printf(" ... Done !\nStart \'Last Calculation\' ... 0 / 4");
#endif // DO_PRINT



	// R * Y -> Z ... PI^2
	flg = B_multiple(&R, &Y, &Z);

	if (flg) {
		printf(" ... Error: where.CulPI.LastCalculation.B_multiple\n");
		printf("flg = %d\n", flg);
		return -1;
	}
#if DO_PRINT
	printf("\b\b\b\b\b1 / 4");
#endif // DO_PRINT



	while (1) {
		i = mulBy10(&Z.bunshi, &Z.bunshi);
		if (i == -1)
			break;
		if (i == -2)
			flg = i;
	}

	if (flg) {
		printf(" ... Error: where.CulPI.LastCalculation.mulBy10\n");
		printf("flg = %d\n", flg);
		return -1;
	}

#if DO_PRINT
	printf("\b\b\b\b\b2 / 4");
#endif // DO_PRINT



	//分数から実数への変換
	flg = B_FractionToReal(&Z, &ans);

	if (flg) {
		printf(" ... Error: where.CulPI.LastCalculation.B_FractionToReal\n");
		printf("flg = %d\n", flg);
		return -1;
	}

#if DO_PRINT
	printf("\b\b\b\b\b3 / 4");
#endif // DO_PRINT

	//平方根
	flg += sqrt_newton(&ans, &ans);

	if (flg) {
		printf(" ... Error: where.CulPI.LastCalculation\n");
		printf("flg = %d\n", flg);
		return -1;
	}

	int time = timeStop();

#if DO_PRINT
	printf("\b\b\b\b\b4 / 4 ... Done !\n");
#endif // DO_PRINT

	//printf("PI = ");	dispNumber(&ans);
	printf("PI (Default)      = ");    dispNumber(&ans);   putchar('\n');
	//次行で表示している値はRADIX=10000に最適化し、予測した有効桁の表示を行っています。表示されている有効桁は正しくない場合があります。
	printf("PI (Optimization) = ");	dispResult(&ans);   putchar('\n');
	printf("time: %d [s]\n", time);

	return 0;
}

void dispResult(struct NUMBER* a)
{
	int i, cnt = -1;
	if (getSign(a) == SIGN_PLUS)	putchar('+');
	else							putchar('-');

#if RADIX == 10000

	for (i = KETA - 1; i >= 0; i--) {
		if (cnt == -1 && a->n[i] == 0) {
			continue;
		}
		if (cnt == -1 && (a->n[i] > 0 || i == 0)) {

			//0以外が来た最初の桁
			if (a->n[i] / 1000) {		//a->n[i]が4桁
				printf("%1d.", a->n[i] / 1000);
				printf("%3d", a->n[i] % 1000);
				cnt += 4;
			}
			else if (a->n[i] / 100) {	//a->n[i]が3桁
				printf("%1d.", a->n[i] / 100);
				printf("%2d", a->n[i] % 100);
				cnt += 3;
			}
			else if (a->n[i] / 10) {		//a->n[i]が2桁
				printf("%1d.", a->n[i] / 10);
				printf("%1d", a->n[i] % 10);
				cnt += 2;
			}
			else {						//a->n[i]が1桁
				printf("%1d.", a->n[i]);
				cnt++;
			}
		}
		else {
			if (cnt + 4 <= KETA / 2) {
				printf("%04d", a->n[i]);
				cnt += 4;
				continue;
			}
			else if (cnt + 3 == KETA / 2) {
				printf("%03d", a->n[i] / 10);
			}
			else if (cnt + 2 == KETA / 2) {
				printf("%02d", a->n[i] / 100);
			}
			else if (cnt + 1 == KETA / 2) {
				printf("%01d", a->n[i] / 1000);
			}
			break;
		}
	}
#else

	for (i = KETA - 1; i >= 0; i--) {
		if (cnt == -1 && a->n[i] == 0) {
			continue;
		}
		else if (cnt && (a->n[i] > 0 || i == 0)) {
			//0以外が来た最初の桁
			printf("%1d.", a->n[i]);
			cnt++;
		}
		else {
			printf("%1d", a->n[i]);
		}
	}

#endif
}