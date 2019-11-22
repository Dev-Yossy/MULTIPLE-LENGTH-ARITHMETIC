#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mulprec.h"



int main(void)
{
	srand((unsigned)time(NULL));

	struct NUMBER a, b;

	clearByZero(&a);
	clearByZero(&b);

	/*
	
	setRnd(&a, 3);

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

	setInt(&a, 123);
	printf("a = ");
	dispNumber(&a);
	putchar('\n');

	*/

	//check_setInt(&a, 10000000);

	/*
	struct NUMBER c;
	clearByZero(&c);

	int x = 123456;
	int y = 999999;

	setInt(&a, x);
	setInt(&b, y);

	for (int i = 0; i < KETA; i++)
	{
		b.n[i] = 9;
	}

	printf("a = ");
	dispNumber(&a);
	putchar('\n');

	printf("b = ");
	dispNumber(&b);
	putchar('\n');

	printf("%s\n", sub(&a, &b, &c) ? "¸”s" : "¬Œ÷");

	printf("c = ");
	dispNumber(&c);
	putchar('\n');

	printf(">>> %d\n", check(&c, x - y));
	*/

	struct NUMBER d;
	clearByZero(&d);
	
	printf("----------‰ÁZ--------------------------------------------------------------------");

	setInt(&a, 12345);
	setInt(&b, 12345);
	printf("%s\n", add(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	setInt(&a, -12345);
	setInt(&b, 12345);
	printf("%s\n", add(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	setInt(&a, 12345);
	setInt(&b, -12345);
	printf("%s\n", add(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	setInt(&a, -12345);
	setInt(&b, -12345);
	printf("%s\n", add(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	printf("----------Œ¸Z--------------------------------------------------------------------");

	setInt(&a, 12345);
	setInt(&b, 12345);
	printf("%s\n", sub(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	setInt(&a, -12345);
	setInt(&b, 12345);
	printf("%s\n", sub(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	setInt(&a, 12345);
	setInt(&b, -12345);
	printf("%s\n", sub(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	setInt(&a, -12345);
	setInt(&b, -12345);
	printf("%s\n", sub(&a, &b, &d) ? "¸”s" : "¬Œ÷");
	printf("a = ");	dispNumber(&a);	putchar('\n');
	printf("b = ");	dispNumber(&b);	putchar('\n');
	printf("d = ");	dispNumber(&d);	putchar('\n');

	putchar('\n');

	return 0;
}
