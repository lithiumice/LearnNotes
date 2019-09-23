#include <stdio.h>
#define STACKSIZE 100
typedef DataType int

typedef struct 
{
	DataType items[STACKSIZE];
	int top;
}SqStack;


int InitStack(SqStack *S)
{
	S -> top = -1;
	return 1;
}


int StackEmpty(SqStack S)
{
	if (S.top == -1)
	{
		return 1;
	}
	else 
		return 0;
}


int Push(SqStack *S, DataType e)
{
	if (S -> top >= STACKSIZE -1)
	{
		printf("the stack is full!\n");
		return 0;
	}
	S -> top ++;
	S -> items[S -> top] = e;
	return 1;
}


int Pop(SqStack *S, DataType e)
{
	if (S ->top <= -1)
	{
		printf("the stack is empty!\n");
		return 0;
	}
	*e = S -> items[S ->top];
	S -> top --;
	return 1;
}


int GetTop(SqStack S, DataType *e)
{
	if(S.top <= -1)
	{
		printf("the stack is empty!\n");
		return 0;
	}
	*e = S.items[S.top];
	return 1;
}