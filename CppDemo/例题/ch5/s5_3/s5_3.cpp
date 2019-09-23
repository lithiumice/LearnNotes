// s5_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../triarray.h"

int AddDiag(TriArray TA,DataType *e){
	int i;
	if(TA.nums<=0){
		printf("三元组为空，无法完成操作！");
		return 0;
	}
	*e=0;
	for(i=0;i<TA.nums;i++)
		if(TA.items[i].row==TA.items[i].col)
			*e+=TA.items[i].value;
	return 1;
}


int main(int argc, char* argv[])
{
	DataType A[3][3]={{10,0,2},{18,0,20},{0,0,30}};
	TriArray TA;
	DataType e;
	
	InitArray(&TA,&A[0][0],3,3);
	for(int i=0;i<TA.nums;i++)
		printf("(%d,%d,%d)\t",TA.items[i].row,TA.items[i].col,TA.items[i].value);
	AddDiag(TA,&e);
	printf("\n\n%d\n",e);	
	return 0;
}

