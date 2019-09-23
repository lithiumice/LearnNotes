#include <stdio.h>
#define MAXVEX 50
typedef char DataType;
typedef struct arc
{
	int adjvex;
	struct arc* next;
}ArcNode, *PArcNode;
typedef struct 
{
	DataType data;
	ArcNode* head;
}VexNode;
typedef struct 
{
	VexNode lists[MAXVEX];
	int edges, vexs;
}VGraph, *AdjList;


void CreateGraph(AdjList *g, int m[][MAXVEX], int n)
{
	int i, j;
	PArcNode p;
	*g = (AdjList)malloc(sizeof(VGraph));
	(*g) -> edges = 0;
	(*g) -> vexs = n;
	for(i = 0; i < n; i++)
	{
		(*g) -> lists[i].head = NULL;
		for(j = n - 1; j >= 0; j--)
			if(m[i][j] != 0)
			{
				p = (PArcNode)malloc(sizeof(ArcNode));
				p -> adjvex = j;
				p -> next = (*g) -> lists[i].head;
				(*g) -> lists[i].head = p;
				(*g) -> edges ++;
			}
	}

}


void DispGraph(AdjList g)
{
	int i;
	PArcNode p;
	for(i = 0; i < g -> vexs; i++)
	{
		printf("\nLine%d:\t", i);
		p = g -> lists[i].head;
		while(p != NULL)
		{
			printf("[%d]\t", p -> adjvex);
			p = p -> next;
		}
	}
}


/*****************************************
*Function: GetFirst
*Description: find the first point
*params: @AdjList g
*		 @int k
*Return: i or -1 if failed
******************************************/
int GetFirst(AdjList g, int k)
{
	if(k < 0 || k > g -> vexs)
	{
		printf("the k is out of range!\n");
		return -1;
	}
	if(g -> lists[k].head == NULL)
		return -1;
	else
		return g -> lists[k].head -> adjvex;
}


/*****************************************
*Function: GetNext
*Description: find the next
*params: @AdjList g
*		 @int k
*		 @int t
*Return: i
******************************************/
int GetNext(AdjList g, int k, int t)
{
	PArcNode p;
	if(k < 0 || k > g -> vexs || t < 0 || t > g -> vexs)
	{
		printf("the k or t is out of range!\n");
		return -1;
	}
	p = g -> lists[k].head;
	while(p -> next != NULL && p -> adjvex != t)
		p = p -> next;
	if(p -> next == NULL)
		return -1
	else 
		return p -> next -> adjvex;
}


