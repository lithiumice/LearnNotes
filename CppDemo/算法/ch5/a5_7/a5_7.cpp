// a5_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../crosslink.h"

int main(int argc, char* argv[])
{
	DataType A[3][3]={{10,0,2},{18,0,20},{0,0,30}};
	CrossLink TA;
	PCNode p;
	DataType v;
	
	InitCrossLink(&TA,&A[0][0],3,3);	
	GetValue(TA,&v,2,1);
	printf("%d",v);	
	
	return 0;
}
