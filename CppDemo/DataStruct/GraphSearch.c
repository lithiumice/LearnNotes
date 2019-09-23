#include "AdjVex.h"


/*****************************************
*Function: DFS(Depth-First Search)
*Description: an algorithm for graph searching
*params: @AdjMetrix g
*		 @int k
*		 @int visited[]
*Return: NULL
******************************************/
void DFS(AdjList g, int k, int visited[])
{
	int u;
	printf("%c", g -> data[k]);
	visited[k] = 1;
	u = GetFirst(g, k);
	while(u != -1)
	{
		if(visited[u] == 0)
			DFS(g, u, visited);
		u = GetNext(g, k, u);
	}
}



void DFSTraverse(AdjList g)
{
	int i;
	int visited[MAXVEX];
	for(i = 0; i < g -> vexs; i++)
		visited[i] = 0;
	for(i = 0; i < g -> vexs; i++)
		if(visited[i] == 0)
			DFS(g, i, visited);
}


void BFS(AdjList g, int v, int visited[])
{
	int u;
	int queue[MAXVEX];
	int front = rear = 0;
	int w;
	printf("%d", g -> lists[v].data);
	visited[v] = 1;
	queue[rear] = v;
	rear = (rear + 1)%MAXVEX;
	while(front < rear)
	{
		u = queue[front];
		front = (front + 1)%MAXVEX;
		w = GetFirst(g, u);
		while(w != -1)
		{
			if(visited[w] == 0)
			{
				printf("%d",g -> lists[w].data);
				visited[w] = 1;
				queue[rear] = w;
				rear = (rear + 1)%MAXVEX;
			}
			w = GetNext(g, u, w);
		}
	}
}


void BFSTraverse(AdjList g)
{
	int i;
	int visited[MAXVEX];
	for(i = 0; i < g -> vexs; i++)
		visited[i] = 0;
	for(i = 0; i < g -> vexs; i++)
		if(visited[i] == 0)
			BFS(g, i, visited);
}


int isConnected(AdjList g, int visited[])
{
	int i;
	int n = 0;
	for(i = 0; i < g -> vexs; i++)
		visited[i] = 0;
	DFS(g, 1, visited);
	for(i = 0; i < g -> vexs; i++)
		n += visited[i];
	if(n == g -> vexs)
		return 1;
	else 
		return 0;
}