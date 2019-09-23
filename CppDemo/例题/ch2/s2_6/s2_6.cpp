// s2_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\linklist.h"

void Reverse(LinkList *h)
{
	PNode p=*h,q=NULL,r;
	while(p)
	{
		r=q;
		q=p;
		p=p->next;
		q->next=r;
	}
	*h=q;
}


int main(int argc, char* argv[])
{
	int i;
	LinkList h;
	InitList(&h);

	for(i=0;i<4;i++)
		ListInsert(h,i+1,2*i);
	printf("\n\nbefore\n");
	TraverseList(h);
	Reverse(&(h->next));	
	printf("\n\nafter\n");
	TraverseList(h);
	return 0;
}
