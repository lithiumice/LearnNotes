// s2_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqlist.h"

int main(int argc, char* argv[])
{
	int i;
	int data[7]={0,1,1,2,3,5,8};
	DataType item;
	SqList fibo;
	printf("\n\n����˳���\n\n");
	InitList(&fibo);
	for(i=0;i<7;i++)
	{
		if(!ListInsert(&fibo,i+1,data[i]))
		{
			printf("\n���д���!\n");
			return 0;
		}
	}
	printf("\n\n˳����е�Ԫ��\n");
	TraverseList(fibo);
	if(!ListDelete(&fibo,7,&item))
	{
		printf("\n���д���!\n");
		return 0;
	}
	printf("\n\nɾ�����˳����е�Ԫ��\n");
	TraverseList(fibo);
	return 1;
}


