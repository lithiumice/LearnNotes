// app1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "malloc.h"
#include "stdio.h"
#define MAXSIZE 100
typedef int ElemType ;
typedef struct{
	ElemType items[MAXSIZE];
	int top;
}SqStack;

int InitStack(SqStack *S)
{
	S->top=-1;
	return 1;
}

int IsEmpty(SqStack S)
{
	if(S.top==-1)
		return 1;
	else
		return 0;
}

int Push(SqStack *S,ElemType e)
{	
	if(S->top>=MAXSIZE-1)
	{
		printf("堆栈已满，不能完成入栈操作！\n");
		return 0;
	}
	S->top++;
	S->items[S->top]=e;
	return 1;
}

int Pop(SqStack *S,ElemType *e)
{	
	if(S->top<=-1)
	{
		printf("堆栈已空，不能完成出栈操作！\n");
		return 0;
	}	
	*e=S->items[S->top];
	S->top--;
	return 1;
}

void Convert(int num,int d)
{
	SqStack s;
	char ch[]="0123456789ABCDEF";
	int tmp;
	InitStack(&s);
	do
	{
		Push(&s,ch[num%d]);
		num=num/d;
	}while(num!=0);
	while(!IsEmpty(s))
	{
		Pop(&s,&tmp);
		printf("%c",tmp);
	}
}


int main(int argc, char* argv[])
{
	SqStack sta;
	int num,d;
	InitStack(&sta);
	printf("请输入非负十进制数：\n");
	scanf("%d",&num);
	printf("请输入转换进制：\n");
	scanf("%d",&d);
	Convert(num,d);	
	return 1;
}

