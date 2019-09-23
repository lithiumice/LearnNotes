/*
   单链表的基本操作
*/
#include "malloc.h"
#include "stdio.h"

/*单链表的存储结构*/
typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node *next;
}LNode,*PNode,*LinkList;

/*算法2-9初始化单链表*/
int InitList(LinkList *h)
{
	*h=(LinkList)malloc(sizeof(LNode));
	if(!h)
	{
		printf("初始化链表错误！\n");
		return 0;
	}
	(*h)->next=NULL;
	return 1;
}

/*算法2-10求单链表表长*/
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

/*算法2-11判断单链表是否为空*/
int ListEmpty(LinkList h)
{
	if(h->next)
		return 0;
	else
		return 1;
}

/*算法2-12插入*/
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
		printf("插入位置不合法！\n");
		return 0;
	}
	q=(PNode)malloc(sizeof(LNode));
	if(!q)
	{
		printf("不能生成新结点\n");
		return 0;
	}
	q->data=x;
	q->next=p->next;
	p->next=q;
	return 1;
}

/*算法2-13删除*/
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
		printf("删除位置不合法！\n");
		return 0;
	}	
	
	q=p->next;
	p->next=q->next;
	*item=q->data;
	free(q);
	return 1;
}

/*算法2-14查找指定元素在单链表中的位置*/
PNode Find(LinkList h,DataType item)
{
	PNode p=h->next;
	while(p  && p->data!=item)
		p=p->next;
	return p;
}

/*算法2-15获取单链表中指定位置上的数据元素*/
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
		printf("位置参数不合法！\n");
		return 0;
	}
	*item=p->data;
	return 1;
}

/*算法2-16销毁单链表*/
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

/*算法2-17遍历单链表*/
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

