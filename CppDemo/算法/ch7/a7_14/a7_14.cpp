// a7_14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"

int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;
	int i;
	char d[]={'A','B','C','D','E'};
	int m[][MAXVEX]={{0,0,0,0,1},{0,0,1,0,0},{0,1,0,0,0},{0,0,0,0,1},{1,0,0,1,0}};
	int visited[5];
	CreateGraph(g,m,d,5);		
	for(i=0;i<g->vexs;i++)		
		visited[i]=0;
	DispGraph(g);	
	DFSTraverse(g);
	printf("\n\n");
	return 0;
}
