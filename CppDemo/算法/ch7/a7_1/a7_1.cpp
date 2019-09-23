// a7_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"

int main(int argc, char* argv[])
{
	MGraph g;
	//int m[][MAXVEX]={{0,1,1,0,0},{1,0,0,1,1},{1,0,0,0,0},{0,1,0,0,1},{0,1,0,1,0}};
	char d[]={'A','B','C','D'};
	int m[][MAXVEX]={{0,1,0,1},{1,0,0,0},{0,1,0,0},{0,0,0,0}};
	CreateGraph(&g,m,d,4);
	DispGraph(&g);
	return 0;
}
