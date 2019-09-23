// s2_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqlist.h"

void Split(SqList L,SqList *LA,SqList *LB)
{
	int i;
	int posa=1,posb=1;
	for(i=0;i<L.length;i++)
	{
		if(L.items[i]>0)
		{
			ListInsert(LA,posa,L.items[i]);
			posa++;
		}
		else
		{
			ListInsert(LB,posb,L.items[i]);
			posb++;
		}
	}
}



int main(int argc, char* argv[])
{
	int i;
	int data[7]={0,-1,1,2,-3,-10,8};
	SqList L,LA,LB;
	printf("\n\n建立顺序表\n\n");
	InitList(&L);
	InitList(&LA);
	InitList(&LB);
	for(i=0;i<7;i++)
	{
		if(!ListInsert(&L,i+1,data[i]))
		{
			printf("\n运行错误!\n");
			return 0;
		}
	}
	printf("\n\n顺序表中的元素\n");
	TraverseList(L);
	printf("\n\n拆分顺序表\n");
	Split(L,&LA,&LB);
	printf("\n\nLA顺序表\n");
	TraverseList(LA);
	printf("\n\nLB顺序表\n");
	TraverseList(LB);
	return 1;
}
