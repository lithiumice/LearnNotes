// a7_15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjlist.h"


int main(int argc, char* argv[])
{
	AdjList g;	
	int i;
	int m[][MAXVEX]={{0,1,1,0,0},{1,0,0,1,1},{1,0,0,0,0},{0,1,0,0,1},{0,1,0,1,0}};
	int visited[5];
	CreateGraph(&g,m,5);
	for(i=0;i<g->vexs;i++)
	{
		g->lists[i].data=i;
		visited[i]=0;
	}
	DispGraph(g);
	printf("\n\n");
	BFS(g,1,visited);
	printf("\n\n");
	return 0;
}
