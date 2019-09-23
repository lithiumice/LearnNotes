// a8_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sstable.h"

int main(int argc, char* argv[])
{
	int i;
	SqList L;
	DataType x,y;
	x.key=4;
	InitList(&L);
	for(i=0;i<4;i++)
	{
		y.key=2*i;
		ListInsert(&L,i+1,y);
	}
	printf("%d\n",BinarySearch(L,x));
	return 0;
}

