// s2_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqlist.h"

void Repetition(SqList *L)
{
	int i,j;
	DataType item;
	for(i=0;i<L->length;i++)
	{
		j=i+1;
		while(j<L->length)
			if(L->items[j]==L->items[i])
				ListDelete(L,j+1,&item);
			else
				j++;
	}
}


int main(int argc, char* argv[])
{
	int i;
	int data[7]={0,1,1,2,3,0,8};
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
	printf("\n\n˳����е�Ԫ��\n\n");
	TraverseList(fibo);
	printf("\n\nɾ���ظ����ֵ�Ԫ��\n\n");
	Repetition(&fibo);
	TraverseList(fibo);
	return 1;
}

