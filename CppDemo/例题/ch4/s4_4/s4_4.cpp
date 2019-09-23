// s4_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../linkstring.h"

int SortedString(LinkString S)
{
	PSNode p,q=NULL;
	p=S;
	q=p->next;	
	while(q && q->data >= p->data)
	{
		p=p->next;
		q=q->next;		
	}
	if(!q)
		return 1;
	else
		return 0;
}

int main(int argc, char* argv[])
{
	LinkString S;
	InitString(&S,"acdde");
	printf("%d\n",SortedString(S));
	return 0;
}
