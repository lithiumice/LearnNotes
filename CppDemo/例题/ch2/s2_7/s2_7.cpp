// s2_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\linklist.h"

void Repetition(LinkList h)
{
	PNode p=h->next,q,r;
	while(p)
	{
		
		for(r=p,q=p->next;q!=NULL;q=q->next)
		{
			if(q->data==p->data)
			{
				r->next=q->next;
				free(q);
				q=r;
			}
			else
				r=r->next;
		}
		p=p->next;
		
	}
	
}

void Print(LinkList h)
{
	PNode p=h->next;
	while(p)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
	printf("\n");
}


int main(int argc, char* argv[])
{
	int i;
	int data[4]={8,0,0,8};
	LinkList h;
	InitList(&h);

	for(i=0;i<4;i++)
		ListInsert(h,i+1,data[i]);
	printf("\n\nbefore\n");
	TraverseList(h);
	Repetition(h);
	printf("\n\nafter\n");
	TraverseList(h);
	return 0;
}

