#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define KETA 30

struct NUMBER
{
	int n[KETA];    //ŠeŒ…‚Ì’l [ã‚ÌŒ…]---[‰º‚ÌŒ…] [KETA - 1]---[0]
	int sign;       //•„†•Ï” 1:³ 0, -1:•‰
};

void clearByZero(struct NUMBER* a);
void dispNumber(struct NUMBER* a);
void setRnd(struct NUMBER* a, int k);
void copyNumber(struct NUMBER* a, struct NUMBER* b);
void getAbs(struct NUMBER* a, struct NUMBER* b);
int isZero(struct NUMBER* a);
int mulBy10(struct NUMBER* a, struct NUMBER* b);
int divBy10(struct NUMBER* a, struct NUMBER* b);
