#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif



//////////////////////////////////////////////////////////////////////////////////////
//      Define      (��`)
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

#define KETA 20

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

enum ViewStyle
{
	None,
	OnlyAnswer,
	All,
};

//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//      Prototype Declaration      (�v���g�^�C�v�錾)
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
int power(struct NUMBER*, struct NUMBER*, struct NUMBER*);
int factorial(struct NUMBER*, struct NUMBER*);
//------------------------------------------------------------------------------------




//////////////////////////////////////////////////////////////////////////////////////
//                                �ȉ��`�F�b�N�p                                    //
//////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------

void RoopFunction_ASM(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int, unsigned int, enum ViewStyle);
void RoopFunction_D(int (*func)(struct NUMBER*, struct NUMBER*, struct NUMBER*, struct NUMBER*), unsigned int, unsigned int, enum ViewStyle);

void check_setInt(struct NUMBER* a, int roop);
int checkNumber(struct NUMBER* a, int x);

//------------------------------------------------------------------------------------
