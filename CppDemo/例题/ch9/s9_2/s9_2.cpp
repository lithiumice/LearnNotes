// s9_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sortlist.h"

int main(int argc, char* argv[])
{
	SqList L;
	KeyType items[]={25,6,23,11,67,45};
	int i,n=6;	
	for(i=0;i<n;i++)				
		L[i].key=items[i];
	InsertSort(L,n);				
	for(i=0;i<n;i++)				
		printf("%d\t",L[i].key);
	return 0;
}

