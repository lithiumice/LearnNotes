// s2_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "malloc.h"
#include "stdio.h"

typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node* prior;
	struct Node* next;
}DNode, *PDNode, *DLinkList;


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



void Reverse(DLinkList h)
{
	PDNode p=h->next ,q;
	while(p!=h)
	{
		q=p->next;
		p->next=p->prior;
		p->prior=q;
		p=q;
	}
	q=h->next;
	h->next=p->prior;
	h->prior=q;	
}
		


int main(int argc, char* argv[])
{
	DLinkList h;
	CreateList(&h,5);		
	Print(h);
	Reverse(h);
	Print(h);
	return 0;
}
