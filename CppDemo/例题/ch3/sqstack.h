/*
	˳��ջ�Ļ�������
 */
#include<stdio.h>

/*˳��ջ�洢�ṹ*/
#define STACKSIZE 100
typedef int DataType;

typedef struct
{
	DataType items[STACKSIZE];
	int top;
}SqStack;


/*�㷨3-1��ʼ��˳��ջ*/
int InitStack(SqStack *S)
{
	S->top=-1;
	return 1;
}


/*�㷨3-2�п�ջ*/
int StackEmpty(SqStack S)
{
	if(S.top==-1)
		return 1;
	else
		return 0;
}


/*�㷨3-3��ջ*/
int Push(SqStack *S,DataType e)
{	
	if(S->top>=STACKSIZE-1)
	{
		printf("��ջ���������������ջ������\n");
		return 0;
	}
	S->top++;
	S->items[S->top]=e;
	return 1;
}


/*�㷨3-4��ջ*/
int Pop(SqStack *S,DataType *e)
{	
	if(S->top<=-1)
	{
		printf("��ջ�ѿգ�������ɳ�ջ������\n");
		return 0;
	}	
	*e=S->items[S->top];
	S->top--;
	return 1;
}


/*�㷨3-5 ȡջ��Ԫ��*/
int GetTop(SqStack S,DataType *e)
{	
	if(S.top<=-1)
	{
		printf("��ջ�ѿգ��������ȡջ��Ԫ�ز�����\n");
		return 0;
	}	
	*e=S.items[S.top];
	return 1;
}


/*�㷨3-18 ��������
int TraverseQueue(SqQueue Q)
{	
	int pos;
	pos=Q.front;
	while((pos+1)%QUEUESIZE<Q.rear)
	{
		printf("%d\t",Q.items[pos]);
		pos++;
	}	
	printf("\n");
	return 1;
}*/
