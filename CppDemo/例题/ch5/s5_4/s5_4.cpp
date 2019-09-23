// s5_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../crosslink.h"

int FindIndex(CrossLink CL,DataType e,int *r,int *c)
{
	PCNode p;
	int i;
	*r=0;
	*c=0;
	if(CL->nums<=0){printf("十字链表为空，无法完成操作");return 0;}
	for(i=0;i<CL->rows;i++)
	{
		p=CL->rhead[i];
		while(p!=NULL)
		{
			if(p->value==e)
			{
				*r=p->row;
				*c=p->col;
				return 1;
			}
			p=p->right;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	DataType A[3][3]={{10,0,2},{18,0,20},{0,0,30}};
	CrossLink TA;
	DataType v;
	int r,c;
	v=30;
	InitCrossLink(&TA,&A[0][0],3,3);	
	FindIndex(TA,v,&r,&c);
	printf("%d,%d",r,c);	
	
	return 0;
}
