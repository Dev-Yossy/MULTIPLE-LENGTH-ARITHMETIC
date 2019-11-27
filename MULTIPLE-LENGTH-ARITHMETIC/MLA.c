#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"



int main(void)
{
	srand((unsigned)time(NULL));

	struct NUMBER a, b, c, d, e;

	int roop_add = 100000;
	printf("roop function \'add\' %d times.\n", roop_add);
	printf("--- Start ---\n");
	RoopFunction_for_Cul(add, roop_add, 10, None);
	printf("--- Done ! ---\n");

	int roop_mul = 10;
	printf("roop function \'mul\' %d times.\n", roop_mul);
	printf("--- Start ---\n");
	RoopFunction_for_Cul(multiple, roop_mul, 11, All);
	printf("--- Done ! ---\n");

	return 0;
}