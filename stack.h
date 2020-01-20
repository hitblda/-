#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

#define MaxSize 128 //Ԥ�ȷ���ռ䣬�����ֵ����ʵ����ҪԤ��ȷ��
typedef struct _SqStack {
	Bnode* base; //ջ��ָ��
	Bnode* top; //ջ��ָ��
}SqStack;

bool InitStack(SqStack& S) //����һ����ջ S
{
	S.base = new Bnode[MaxSize];//Ϊ˳��ջ����һ���������Ϊ Maxsize �Ŀռ�
	if (!S.base) //�ռ����ʧ��
			return false;
	S.top = S.base; //top ��ʼΪ base����ջ
	return true;
}

bool PushStack(SqStack& S, Bnode e) // ����Ԫ�� e Ϊ�µ�ջ��Ԫ��
{
	if (S.top - S.base == MaxSize) //ջ��
		return false;
	*(S.top++) = e; //Ԫ�� e ѹ��ջ����Ȼ��ջ��ָ��� 1���ȼ���*S.top=e;
	S.top++;
	return true;
}

bool PopStack(SqStack& S, Bnode& e) //ɾ�� S ��ջ��Ԫ�أ��ݴ��ڱ���e��
{
	if (S.base == S.top) { //ջ��
		return false;
	}
	e = *(--S.top); //ջ��ָ��� 1����ջ��Ԫ�ظ��� e
	return true;
}

Bnode* GetTop(SqStack& S) //���� S ��ջ��Ԫ�أ�ջ��ָ�벻��
{
	if (S.top != S.base) { //ջ�ǿ�
		return S.top - 1; //����ջ��Ԫ�ص�ֵ��ջ��ָ�벻��
	}
	else {
		return NULL;
	}
}

int GetSize(SqStack& S) {//����ջ��Ԫ�ظ���
	return (S.top - S.base);
}

bool IsEmpty(SqStack& S) {//�ж�ջ�Ƿ�Ϊ��
	if (S.top == S.base) {
		return true;
	}
	else {
		return false;
	}
}

void DestroyStack(SqStack& S) {//����ջ
	if (S.base) {
		free(S.base);
		S.base = NULL;
		S.top = NULL;
	}
}