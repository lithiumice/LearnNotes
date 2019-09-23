// a9_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sortlist.h"

int main(int argc, char* argv[])
{
	SqList L;
	KeyType items[]={98,25,70,36,13,85};
	int i;	
	for(i=0;i<6;i++)
		L[i].key=items[i];
	BubbleSort(L,6);
	DispSort(L,6);
	return 0;
}
