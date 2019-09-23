// a9_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sortlist.h"

int main(int argc, char* argv[])
{
	SqList L;
	KeyType items[]={58,43,29,76,10,35,66,15};
	int i;	
	for(i=0;i<8;i++)
		L[i].key=items[i];
	ShellSort(L,8);
	//DispSort(L,8);
	return 0;
}
