// a2_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqlist.h"


int main(int argc, char* argv[])
{
	int i;
	DataType item;
	SqList L;
	InitList(&L);
	for(i=0;i<3;i++)
		ListInsert(&L,i+1,2*i);
	for(i=0;i<L.length;i++)
		printf("%d\t",L.items[i]);
	ListDelete(&L,2,&item);
	for(i=0;i<L.length;i++)
		printf("%d\t",L.items[i]);
	printf("\n%d\n",item);
	return 0;
}
