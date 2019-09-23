// a2_15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\linklist.h"


int main(int argc, char* argv[])
{
	int i;
	PNode p;
	LinkList h=NULL;
	InitList(&h);
	p=h;
	for(i=0;i<5;i++)
		ListInsert(h,i+1,i*2);
	for(i=0;i<5;i++)
	{
		p=p->next;
		printf("%d\n",p->data);
	}
    
	DestroyList(h);
	for(i=0;i<5;i++)
	{
		p=p->next;
		printf("%d\n",p->data);
	}
	return 0;
}

