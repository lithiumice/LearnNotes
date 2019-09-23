// a9_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sortlist.h"

int main(int argc, char* argv[])
{
	SqList L;
	KeyType items[]={68,39,65,83,74,32,47,56};
	int i;	
	for(i=0;i<8;i++)
		L[i].key=items[i];
	HeapSort(L,8);
	DispSort(L,8);
	return 0;
}