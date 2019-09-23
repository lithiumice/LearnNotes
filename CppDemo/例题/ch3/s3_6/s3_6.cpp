// s3_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "malloc.h"
typedef int DataType;

typedef struct SNode{
	DataType data;
	struct SNode* next;
}SNode, *LinkStack;

int InitStack(LinkStack *top)
{
	*top=(LinkStack)malloc(sizeof(SNode));
	if(*top==NULL)
	{
		printf("初始化链栈出错！\n");
		return 0;
	}
	(*top)->next=NULL;
	return 1;
}

int Push(LinkStack *top,DataType e)
{
	SNode *p;
	p=(SNode*)malloc(sizeof(SNode));
	if(!p)
	{
		printf("入栈操作出错！\n");
		return 0;
	}
	p->data=e;
	p->next=*top;
	*top=p;
	return 1;
}

int Pop(LinkStack top,DataType* e)
{
	SNode *p;
	if(!top)
	{
		printf("栈已空，无法完成出栈操作！\n");
		return 0;
	}
	p=top;
	top=top->next;
	*e=p->data;
	free(p);
	return 1;
}




int main(int argc, char* argv[])
{
	LinkStack top;
	int x;
	InitStack(&top);
	Push(&top,10);
	Pop(top,&x);
	printf("%d\n",x);
	return 0;
}