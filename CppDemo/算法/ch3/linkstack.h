/*
	��ջ�Ļ�������
 */
#include "stdio.h"
#include "malloc.h"

/*��ջ�洢�ṹ*/
typedef int DataType;
typedef struct SNode{
	DataType data;
	struct SNode* next;
}SNode, *LinkStack;



/*�㷨3-6��ʼ����ջ*/
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



/*�㷨3-7�п�ջ*/
int StackEmpty(LinkStack top)
{
	if(top->next==NULL)
		return 1;
	else
		return 0;
}



/*�㷨3-8��ջ*/
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



/*�㷨3-9��ջ*/
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



/*�㷨3-10 ȡջ��Ԫ��*/
int GetTop(LinkStack top,DataType* e)
{
	SNode *p;
	if(!top->next)
	{
		printf("ջ�ѿգ��޷����ȡջ��Ԫ�ز�����\n");
		return 0;
	}
	p=top->next;	
	*e=p->data;	
	return 1;
}



/*�㷨3-11������ջ*/
int Destroy(LinkStack top)
{
	SNode *p;
	while(top)
	{
		p=top;
		top=top->next;
		free(p);		
	}
	return 1;
}
