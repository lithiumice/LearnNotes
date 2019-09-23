// a9_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sortlist.h"

int main(int argc, char* argv[])
{
	SqList L;
	KeyType items[]={70,89,3,8,25,18};
	int i;	
	for(i=0;i<6;i++)
		L[i].key=items[i];
	SelectSort(L,6);
	DispSort(L,6);
	return 0;
}
