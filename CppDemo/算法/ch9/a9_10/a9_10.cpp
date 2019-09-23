// a9_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sortlist.h"

int main(int argc, char* argv[])
{
	SqList L;
	KeyType items[]={85,92,43,25,76,20,3,58,15};
	int i;	
	for(i=0;i<9;i++)
		L[i].key=items[i];
	MergeSort(L,9);
	DispSort(L,8);
	return 0;
}

