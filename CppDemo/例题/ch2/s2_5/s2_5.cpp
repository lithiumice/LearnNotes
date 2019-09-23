// s2_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\linklist.h"

int main(int argc, char* argv[])
{
	int i;
	int data[7]={0,1,1,2,3,5,8};
	DataType item;
	LinkList h=NULL;
	InitList(&h);
	for(i=0;i<7;i++)
	{
		if(!ListInsert(h,i+1,data[i]))
		{
			printf("插入操作出错！\n");
			return 0;
		}
	}
	printf("\n\n删除前单链表中的数据元素\n");
	TraverseList(h);
	if(!ListDelete(h,7,&item))
	{
		printf("删除操作出错！\n");
		return 0;
	}
	printf("\n\n删除后单链表中的数据元素\n");
	TraverseList(h);
	DestroyList(h);
	return 0;
}

