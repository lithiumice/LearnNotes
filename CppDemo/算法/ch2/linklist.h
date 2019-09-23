/*
   ������Ļ�������
*/
#include "malloc.h"
#include "stdio.h"

/*������Ĵ洢�ṹ*/
typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node *next;
}LNode,*PNode,*LinkList;

/*�㷨2-9��ʼ��������*/
int InitList(LinkList *h)
{
	*h=(LinkList)malloc(sizeof(LNode));
	if(!h)
	{
		printf("��ʼ���������\n");
		return 0;
	}
	(*h)->next=NULL;
	return 1;
}

/*�㷨2-10�������*/
int ListLength(LinkList h)
{
	int total=0;
	PNode p=h->next;
	while(p)
	{
		total++;
		p=p->next;
	}
	return total;
}

/*�㷨2-11�жϵ������Ƿ�Ϊ��*/
int ListEmpty(LinkList h)
{
	if(h->next)
		return 0;
	else
		return 1;
}

/*�㷨2-12����*/
int ListInsert(LinkList h,int pos,DataType x)
{
	PNode p=h,q;
	int i=0;
	while(p && i<pos-1)
	{
		p=p->next;
		i++;
	}
	if(!p || i>pos-1)
	{
		printf("����λ�ò��Ϸ���\n");
		return 0;
	}
	q=(PNode)malloc(sizeof(LNode));
	if(!q)
	{
		printf("���������½��\n");
		return 0;
	}
	q->data=x;
	q->next=p->next;
	p->next=q;
	return 1;
}

/*�㷨2-13ɾ��*/
int ListDelete(LinkList h,int pos,DataType *item)
{
	PNode p=h,q;
	int i=0;
	while(p->next  && i<pos-1)
	{
		p=p->next;
		i++;
	}
	if(!p->next  || i>pos-1)
	{
		printf("ɾ��λ�ò��Ϸ���\n");
		return 0;
	}	
	
	q=p->next;
	p->next=q->next;
	*item=q->data;
	free(q);
	return 1;
}

/*�㷨2-14����ָ��Ԫ���ڵ������е�λ��*/
PNode Find(LinkList h,DataType item)
{
	PNode p=h->next;
	while(p  && p->data!=item)
		p=p->next;
	return p;
}

/*�㷨2-15��ȡ��������ָ��λ���ϵ�����Ԫ��*/
int GetElem(LinkList h,int pos,DataType *item)
{
	int i=0;
	PNode p=h->next;
	while(p  && i<pos-1)
	{
		i++;
		p=p->next;
	}
	if(!p || i>pos-1)
	{
		printf("λ�ò������Ϸ���\n");
		return 0;
	}
	*item=p->data;
	return 1;
}

/*�㷨2-16���ٵ�����*/
void DestroyList(LinkList h)
{
	PNode p=h->next;
	while(h)
	{
		p=h;
		h=h->next;
		free(p);
	}
}

/*�㷨2-17����������*/
void TraverseList(LinkList h)
{
	PNode p=h->next;
	while(p)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
	printf("\n");
}

