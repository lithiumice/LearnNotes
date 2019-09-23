// a3_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstack.h"

int main(int argc, char* argv[])
{
	SqStack S;
	int x;
	InitStack(&S);
	for(int i=0;i<4;i++)
		Push(&S,i);
	for(i=0;i<4;i++)
	{
		Pop(&S,&x);
		printf("%d\t",x);
	}

	return 0;
}
