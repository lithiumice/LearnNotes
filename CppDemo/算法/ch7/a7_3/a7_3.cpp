// a7_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"

int main(int argc, char* argv[])
{
	MGraph g;
	int pos;
	int k=1;
	char d[]={'A','B','C','D'};
	int m[][MAXVEX]={{0,1,0,1},{1,0,0,0},{0,1,0,0},{0,0,0,0}};
	CreateGraph(&g,m,d,4);
	DispGraph(&g);	
	pos=GetFirst(&g,k);	
	printf("\n%c�ĵ�һ���ڽӵ���%c\n",g.data[k],g.data[pos]);
	return 0;
}

