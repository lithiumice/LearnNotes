// a7_11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../adjlist.h"

int main(int argc, char* argv[])
{
	AdjList g;	
	int m[][MAXVEX]={{0,1,0,1},{1,0,0,0},{0,1,0,0},{0,0,0,0}};
	CreateGraph(&g,m,4);
	DispGraph(g);
	printf("\nThe first adjvex is %d",GetFirst(g,1));
	return 0;
}

