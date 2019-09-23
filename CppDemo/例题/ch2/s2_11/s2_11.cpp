// s2_11.cpp : Defines the entry point for the console application.
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

void PrintReverse(DLinkList h)
{
	PDNode p=h->prior;
	while(p!=h)
	{
		printf("%d\t",p->data);
		p=p->prior;
	}
	printf("\n");
}

void CreateList(DLinkList *h,int n)
{
	int i;
	PDNode p,q;
	*h=(DLinkList)malloc(sizeof(DNode));
	
	(*h)->next=*h;
	//(*h)->prior=*h;
	p=*h;
	for(i=0;i<n;i++)
	{
		q=(PDNode)malloc(sizeof(DNode));
		q->data=i;		
		q->next=p->next ;
		p->next=q;
	}
}



void ModifyList(DLinkList h)
{
	PDNode p=h->next, q;
	p->prior=h;
	while(p!=h)
	{
		q=p->next;
		q->prior=p;
		p=q;
	}
			
}
		


int main(int argc, char* argv[])
{
	DLinkList h;
	CreateList(&h,5);		
	Print(h);
	ModifyList(h);
	PrintReverse(h);
	return 0;
}
