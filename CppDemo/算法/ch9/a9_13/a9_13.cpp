// a9_13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "radix.h"


int main(int argc, char* argv[])
{
	DataType L[10];
	KeyType items[]={983,259,123,173,285,274,111,546,744,372};
	int i;	
	for(i=0;i<10;i++)
		L[i].key=items[i];
	RadixSort(L,10,3,10);	
	return 0;
}