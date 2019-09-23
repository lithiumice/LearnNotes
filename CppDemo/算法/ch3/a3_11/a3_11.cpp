// a3_11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../linkstack.h"


int main(int argc, char* argv[])
{
	LinkStack top;
	int x;
	InitStack(&top);
	for(int i=0;i<4;i++)
		Push(top,i);
	for(i=0;i<4;i++)
	{
		Pop(top,&x);
		printf("%d\n",x);
	}
	Destroy(top);
	printf("%d\n",top->next);
	return 0;
}

