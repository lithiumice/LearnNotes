/*
   ˫������Ļ�������
*/
#include "malloc.h"
#include "stdio.h"

/*˫������Ĵ洢�ṹ*/
typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node* prior;
	struct Node* next;
}DNode, *PDNode, *DLinkList;

/*�㷨2-18��ʼ��˫������*/
int InitList(DLinkList *h)
{
	*h=(DLinkList)malloc(sizeof(DNode));
	if(!h)
	{
		printf("��ʼ���������\n");
		return 0;
	}
	(*h)->next=*h;
	(*h)->prior=*h;
	return 1;
}



/*�㷨2-19����*/
int ListInsert(DLinkList h,int pos,DataType x)
{
	PDNode p=h->next ,q;
	int i=0;
	while(p!=h && i<pos-1)
	{
		p=p->next;
		i++;
	}
	if(p==h || i>pos-1)
	{
		printf("����λ�ò��Ϸ���\n");
		return 0;
	}
	q=(PDNode)malloc(sizeof(DNode));
	if(!q)
	{
		printf("�����������\n");
		return 0;
	}
	q->data=x;
	q->prior=p->prior;
	p->prior->next=q;
	q->next=p;
	p->prior=q;
	return 1;
}


/*�㷨2-20ɾ��*/
int ListDelete(DLinkList h,int pos,DataType *item)
{
	PDNode p=h->next ;
	int i=1;
	while(p->next!=h  && i<pos)
	{
		p=p->next;
		i++;
	}
	if(p->next==h  || i>pos)
	{
		printf("ɾ��λ�ò��Ϸ���\n");
		return 0;
	}	
	*item=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;	
	free(p);
	return 1;
}


