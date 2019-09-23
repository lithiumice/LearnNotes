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
	printf("\n邻接表：");
	DispGraph(g);
	//printf("\n\n深度优先搜索序列：\n");
	//DFSTraverse(g);
	printf("\n广度优先搜索序列：\n");
	BFSTraverse(g);
	printf("\n\n");
	return 0;
}