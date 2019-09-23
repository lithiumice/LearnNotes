// s7_14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjlist.h"

int Connected(AdjList g,int visited[])
{
	int i;
	int n=0;
	for(i=0;i<g->vexs;i++)
		visited[i]=0;
	DFS(g,1,visited);
	for(i=0;i<g->vexs;i++)
		n+=visited[i];
	if(n==g->vexs)
		return 1;
	else
		return 0;
}




int main(int argc, char* argv[])
{
	AdjList g;	
	int visited[5];
	int m[][MAXVEX]={{0,1,1,0,0},{1,0,1,0,1},{1,1,0,1,0},{0,0,1,0,0},{0,1,0,0,0	}};
	CreateGraph(&g,m,5);	
	printf("\n邻接表：");
	DispGraph(g);
	printf("\n\n1:连通图，0：非连通图\n");
	printf("\n%d\n",Connected(g,visited));	
	printf("\n\n");
	return 0;
}


