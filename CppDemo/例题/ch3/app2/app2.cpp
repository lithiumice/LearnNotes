// app2.cpp : Defines the entry point for the console application.
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
		printf("��ʼ����ջ����\n");
		return 0;
	}
	(*top)->next=NULL;
	return 1;
}

int IsEmpty(LinkStack top)
{
	if(top->next==NULL)
		return 1;
	else
		return 0;
}


int Push(LinkStack top,DataType e)
{
	SNode *p;
	p=(SNode*)malloc(sizeof(SNode));
	if(!p)
	{
		printf("��ջ��������\n");
		return 0;
	}
	p->data=e;
	p->next=top->next;
	top->next=p;
	return 1;
}

int Pop(LinkStack top,DataType* e)
{
	SNode *p;
	if(!top->next)
	{
		printf("ջ�ѿգ��޷���ɳ�ջ������\n");
		return 0;
	}
	p=top->next;
	top->next=p->next;
	*e=p->data;
	free(p);
	return 1;
}

void Convert(int num,int d)
{
	LinkStack s;
	char ch[]="0123456789ABCDEF";
	int tmp;
	InitStack(&s);
	do
	{
		Push(s,ch[num%d]);
		num=num/d;
	}while(num!=0);
	while(!IsEmpty(s))
	{
		Pop(s,&tmp);
		printf("%c",tmp);
	}
}

int main(int argc, char* argv[])
{
	LinkStack sta;
	int num,d;
	InitStack(&sta);
	printf("������Ǹ�ʮ��������\n");
	scanf("%d",&num);
	printf("������ת�����ƣ�\n");
	scanf("%d",&d);
	Convert(num,d);
	return 0;
}

