// a2_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\dlinklist.h"


void Print(DLinkList h)
{
	PDNode p=h->next;
	while(p!=h)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
	printf("\n");
}

void CreateList(DLinkList *h,int n)
{
	int i;
	PDNode p,q;
	*h=(DLinkList)malloc(sizeof(DNode));
	
	(*h)->next=*h;
	(*h)->prior=*h;
	p=*h;
	for(i=0;i<n;i++)
	{
		q=(PDNode)malloc(sizeof(DNode));
		q->data=i;
		q->prior=p->prior;
		p->prior->next=q;
		q->next=p;
		p->prior=q;
	}
}






int main(int argc, char* argv[])
{
	
	DLinkList h;
	InitList(&h);
	CreateList(&h,5);
		
	Print(h);
	ListInsert(h,5,20);
	Print(h);
	return 0;
}

