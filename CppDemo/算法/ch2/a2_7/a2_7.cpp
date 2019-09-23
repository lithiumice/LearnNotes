// a2_7.cpp : Defines the entry point for the console application.
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
	GetElem(L,3,&item);
	printf("\n%d\n",item);
	return 0;
}


