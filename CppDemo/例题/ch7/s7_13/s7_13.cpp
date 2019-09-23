// s7_13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjlist.h"

int main(int argc, char* argv[])
{
	AdjList g;	
	int i;
	int m[][MAXVEX]={{0,1,1,0,0},{1,0,1,0,1},{1,1,0,1,0},{0,0,1,0,0},{0,1,0,0,0	}};
	CreateGraph(&g,m,5);
	for(i=0;i<g->vexs;i++)
		g->lists[i].data=i;
	printf("\n�ڽӱ�");
	DispGraph(g);
	//printf("\n\n��������������У�\n");
	//DFSTraverse(g);
	printf("\n��������������У�\n");
	BFSTraverse(g);
	printf("\n\n");
	return 0;
}