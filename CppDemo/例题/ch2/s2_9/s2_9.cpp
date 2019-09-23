// s2_9.cpp : Defines the entry point for the console application.
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


void Link(LinkList ha,LinkList hb)
{
	PNode p=ha, q=hb;
	while( p->next!=ha) 
		p=p->next;
	
	while( q->next!=hb) 
		q=q->next;
	p->next=hb->next;
	free(hb);
	q->next=ha;
}


int main(int argc, char* argv[])
{
	int i;
	PNode item;
	LinkList ha;
	InitList(&ha);
	for(i=0;i<7;i++)
	{
		if(!ListInsert(ha,i+1,2*i))
		{
			printf("插入操作出错！\n");
			return 0;
		}
	}
	item=Find(ha,12);
	item->next=ha;
	Print(ha);

	LinkList hb;
	InitList(&hb);
	for(i=0;i<5;i++)
	{
		if(!ListInsert(hb,i+1,i))
		{
			printf("插入操作出错！\n");
			return 0;
		}
	}
	item=Find(hb,4);
	item->next=hb;
	Print(hb);
	Link(ha,hb);	
	Print(ha);
	return 0;
}

