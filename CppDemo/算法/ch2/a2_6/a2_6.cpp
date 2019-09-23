// a2_6.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "../sqlist.h"

int main(int argc, char* argv[])
{
	int i;
	DataType item=4;
	SqList L;
	InitList(&L);
	for(i=0;i<3;i++)
		ListInsert(&L,i+1,2*i);
	for(i=0;i<L.length;i++)
		printf("%d\t",L.items[i]);
	printf("\n%d\n",Find(L,item));
	return 0;
}

