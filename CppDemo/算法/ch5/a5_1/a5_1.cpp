// a5_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../triarray.h"

int main(int argc, char* argv[])
{
	DataType A[3][3]={{0,0,2},{18,0,0},{0,0,30}};
	TriArray TA,TB;
	
	InitArray(&TA,*A,3,3);
	//InitArray(&TB,*A,3,3);
	//TransMatrix(TA,&TB);
	for(int i=0;i<TA.nums;i++)
		printf("TA[%d][%d]=%d\t",TA.items[i].row,TA.items[i].col,TA.items[i].value);		

	return 0;
}

