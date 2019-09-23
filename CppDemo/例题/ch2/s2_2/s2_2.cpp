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
	printf("\n\n建立顺序表\n\n");
	InitList(&fibo);
	for(i=0;i<7;i++)
	{
		if(!ListInsert(&fibo,i+1,data[i]))
		{
			printf("\n运行错误!\n");
			return 0;
		}
	}
	printf("\n\n顺序表中的元素\n");
	TraverseList(fibo);
	if(!ListDelete(&fibo,7,&item))
	{
		printf("\n运行错误!\n");
		return 0;
	}
	printf("\n\n删除后的顺序表中的元素\n");
	TraverseList(fibo);
	return 1;
}


