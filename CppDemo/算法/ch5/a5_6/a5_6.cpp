// a5_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../crosslink.h"

int main(int argc, char* argv[])
{
	DataType A[3][3]={{10,0,2},{18,0,20},{0,0,30}};
	CrossLink TA;
	PCNode p;
	
	InitCrossLink(&TA,&A[0][0],3,3);
	for(int i=0;i<3;i++)
	{
		p=TA->chead[i];
		while(p)
		{
			printf("T(%d,%d,%d)\t",p->row,p->col,p->value);	
			p=p->down;
		}
		printf("\n");
	}
	return 0;
}
