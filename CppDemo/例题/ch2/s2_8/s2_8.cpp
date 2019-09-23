// s2_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\linklist.h"


void Print(LinkList h)
{
	PNode p=h->next;
	while(p!=h)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
	printf("\n");
}


void DeletePrior(PNode p)
{
//删除单循环链表中指定结点的直接前趋结点
	PNode q, r;
	q=p;
	while( q->next->next!=p) 
		q=q->next;
		//删除结点
	r=q->next;
	q->next=r->next;
	free(r); //释放空间
}


int main(int argc, char* argv[])
{
	int i;
	PNode item;
	LinkList h;
	InitList(&h);
	for(i=0;i<7;i++)
	{
		if(!ListInsert(h,i+1,2*i))
		{
			printf("插入操作出错！\n");
			return 0;
		}
	}
	item=Find(h,12);
	item->next=h;
	Print(h);
	item=Find(h,2);
	printf("\nfind=%d\n",item->data);
	DeletePrior(item);
	Print(h);
	return 0;
}
