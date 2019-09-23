// a3_24.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../linkqueue.h"

int main(int argc, char* argv[])
{
	int x;
	LinkQueue Q;
	InitQueue(&Q);
	for(int i=0;i<4;i++)
		EnQueue(&Q,i);
	for(i=0;i<4;i++)
	{
		DeQueue(&Q,&x);
		printf("%d\t",x);
	}
	DestroyQueue(&Q);
	return 0;
}
