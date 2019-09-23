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
			printf("�����������\n");
			return 0;
		}
	}
	printf("\n\nɾ��ǰ�������е�����Ԫ��\n");
	TraverseList(h);
	if(!ListDelete(h,7,&item))
	{
		printf("ɾ����������\n");
		return 0;
	}
	printf("\n\nɾ���������е�����Ԫ��\n");
	TraverseList(h);
	DestroyList(h);
	return 0;
}

