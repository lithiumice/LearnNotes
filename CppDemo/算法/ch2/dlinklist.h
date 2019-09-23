/*
   双向链表的基本操作
*/
#include "malloc.h"
#include "stdio.h"

/*双向链表的存储结构*/
typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node* prior;
	struct Node* next;
}DNode, *PDNode, *DLinkList;

/*算法2-18初始化双向链表*/
int InitList(DLinkList *h)
{
	*h=(DLinkList)malloc(sizeof(DNode));
	if(!h)
	{
		printf("初始化链表错误！\n");
		return 0;
	}
	(*h)->next=*h;
	(*h)->prior=*h;
	return 1;
}



/*算法2-19插入*/
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
		printf("插入位置不合法！\n");
		return 0;
	}
	q=(PDNode)malloc(sizeof(DNode));
	if(!q)
	{
		printf("插入操作出错！\n");
		return 0;
	}
	q->data=x;
	q->prior=p->prior;
	p->prior->next=q;
	q->next=p;
	p->prior=q;
	return 1;
}


/*算法2-20删除*/
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
		printf("删除位置不合法！\n");
		return 0;
	}	
	*item=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;	
	free(p);
	return 1;
}


