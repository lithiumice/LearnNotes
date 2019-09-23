// a9_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sortlist.h"

int main(int argc, char* argv[])
{
	SqList L;
	KeyType items[]={25,6,23,11,67,45};
	int i;	
	for(i=0;i<6;i++)
		L[i].key=items[i];
	InsertSort(L,6);
	DispSort(L,6);
	return 0;
}
