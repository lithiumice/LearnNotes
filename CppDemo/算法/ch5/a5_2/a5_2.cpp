// a5_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../triarray.h"

int main(int argc, char* argv[])
{
	DataType A[3][3]={{0,0,2},{18,0,0},{0,0,30}};
	TriArray TA;
	DataType e;
	InitArray(&TA,*A,3,3);
	GetValue(TA,&e,1,3);	
	printf("%d\t",e);
	return 0;
}
