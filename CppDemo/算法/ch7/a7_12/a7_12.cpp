// a7_12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjlist.h"

int main(int argc, char* argv[])
{
	AdjList g;
	int u;
	int m[][MAXVEX]={{0,1,0,1},{1,0,0,0},{0,1,0,0},{0,0,0,0}};
	CreateGraph(&g,m,4);
	DispGraph(g);
	u=GetFirst(g,0);
	printf("\nThe first adjvex is %d",u);
	printf("\nThe next adjvex is %d\n",GetNext(g,0,u));
	return 0;
}
