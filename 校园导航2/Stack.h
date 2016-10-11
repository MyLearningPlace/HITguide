#pragma once
#ifndef Stack_h
#define Stack_h
#include "initall.h"
using namespace std;
typedef int ElemType;
typedef struct Stack
{
	int StackLine[Max];
	ElemType top;
	int sizeofstack;
} Stack;
/***********************³ÌÐòÇø********************/
void InitStack(Stack *S){
	S->StackLine[0] = 0;
	S->top =0;
	S->sizeofstack = 0;
}
bool IsEmpty(Stack S){
	if (S.top ==0)
		return true;
	else
		return false;
}
int StackLength(Stack S){
	return S.sizeofstack;
}
int Top(Stack S){
	ElemType e;
	if (S.top>0){
		e=S.StackLine[S.top-1];
		return e;
	}else return -1;
}
void Push(Stack *S, ElemType e){
		S->StackLine[S->top] = e;
		S->top++;
		S->sizeofstack += 1;
}
void Pop(Stack *S){
	if (S->top == 0)
		return;
	S->top--;
	S->sizeofstack--;
}
#endif;
