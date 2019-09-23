/*
   邻接表的基本操作
*/
#include "malloc.h"
#include "stdio.h"

/*邻接表的存储结构*/
#define MAXVEX 50
typedef int DataType;
typedef struct arc{				/*边表结点类型*/
	int adjvex;					/*顶点序号*/
	struct arc* next;			/*指向下一个邻接点*/
}ArcNode,*PArcNode;
typedef struct{					/*顶点表结点类型*/
	DataType data;				/*顶点信息*/
	ArcNode* head;				/*边表头指针*/
}VexNode;
typedef struct{					/*邻接表类型*/
	VexNode lists[MAXVEX];		/*顶点表*/
	int edges,vexs;				/*边数，顶点数*/
}VGraph,*AdjList;




/*算法7-9创建邻接表*/
void CreateGraph(AdjList *g,int m[][MAXVEX],int n)
{
	int i,j;
	PArcNode p;
	*g=(AdjList)malloc(sizeof(VGraph));
	(*g)->edges=0;
	(*g)->vexs=n;
	for(i=0;i<n;i++)
	{
		(*g)->lists[i].head=NULL;
		for(j=n-1;j>=0;j--)
		{
			if(m[i][j]!=0)
			{
				p=(PArcNode)malloc(sizeof(ArcNode));
				p->adjvex=j;
				p->next=(*g)->lists[i].head;
				(*g)->lists[i].head=p;
				(*g)->edges++;
			}
		}
	}
}


/*算法7-10显示邻接表*/
void DispGraph(AdjList g)
{
	int i;
	PArcNode p;
	for(i=0;i<g->vexs;i++)
	{
		printf("\nLine%d:\t",i);
		p=g->lists[i].head;
		while(p!=NULL)
		{
			printf("[%d]\t",p->adjvex);
			p=p->next;
		}
	}
}

/*算法7-11第一个邻接点*/
int GetFirst(AdjList g,int k)
{
	if(k<0 || k>g->vexs)
	{
		printf("参数k超出范围！\n");
		return -1;
	}
	if(g->lists[k].head==NULL)
		return -1;
	else
		return g->lists[k].head->adjvex;
}



/*算法7-12下一个邻接点*/
int GetNext(AdjList g,int k,int u)
{
	PArcNode p;
	if(k<0 || k>g->vexs || u<0 || u>g->vexs)
	{
		printf("参数k或u超出范围！\n");
		return -1;
	}

	p=g->lists[k].head;
	while(p->next!=NULL && p->adjvex!=u)
		p=p->next;
	if(p->next==NULL)
		return -1;
	else
		return p->next->adjvex;
}


/*算法7-给顶点赋值*/
void PutVex(AdjList g,int k,DataType x)
{
	if(k<0 || k>g->vexs)
	{
		printf("参数k超出范围！\n");
		return ;
	}
	g->lists[k].data=x;
}


/*算法7-取顶点值*/
DataType GetVex(AdjList g,int k)
{
	if(k<0 || k>g->vexs)
	{
		printf("参数k超出范围！\n");
		return NULL;
	}
	return g->lists[k].data;
}



/*算法7-插入边*/
void InsertArc(AdjList g,int a1,int a2)
{
	PArcNode p;
	if(a1<0 || a1>g->vexs || a2<0 || a2>g->vexs)
	{
		printf("参数a1或a2超出范围！\n");
		return ;
	}
	p=(PArcNode)malloc(sizeof(ArcNode));
	p->adjvex=a2;
	p->next=g->lists[a1].head;
	g->lists[a1].head=p;
	g->edges++;
}


/*算法7-删除边*/
void DeleteArc(AdjList g,int a1,int a2)
{
	PArcNode p,q=NULL;
	if(a1<0 || a1>g->vexs || a2<0 || a2>g->vexs)
	{
		printf("参数a1或a2超出范围！\n");
		return ;
	}
	p=g->lists[a1].head;
	while(p!=NULL && p->adjvex!=a2)
	{
		q=p;p=p->next;
	}
	if(p==NULL)
	{
		printf("边(%d,%d)不存在",a1,a2);
		return;
	}
	if(p!=NULL && q!=NULL)
		q->next=p->next;
	else
		g->lists[a1].head=p->next;
	free(p);
	g->edges--;
}

/*算法7-连通图深度优先搜索遍历*/
void DFS(AdjList g,int v,int visited[])
{
	int u;
	printf("%d",g->lists[v].data);
	visited[v]=1;
	u=GetFirst(g,v);
	while(u!=-1)
	{
		if(visited[u]==0)
			DFS(g,u,visited);
		u=GetNext(g,v,u);
	}
}



/*算法7-非连通图深度优先搜索遍历*/
void DFSTraverse(AdjList g)
{
	int i;
	int visited[MAXVEX];
	for(i=0;i<g->vexs;i++)
		visited[i]=0;
	for(i=0;i<g->vexs;i++)
		if(visited[i]==0)
			DFS(g,i,visited);
}


/*算法7-15连通图广度优先搜索遍历*/
void BFS(AdjList g,int v,int visited[])
{	
	int u;
	int queue[MAXVEX];/*循环队列*/
	int front=0,rear=0;			/*队头、队尾指针*/
	int w;							/*v的邻接点*/
	printf("%d",g->lists[v].data);	/*访问顶点v*/
	visited[v]=1;							/*置标识为已访问过*/
	queue[rear]=v;	/*v入队*/
	rear=(rear+1)%MAXVEX;	
	while(front<rear)
	{
		u=queue[front];
		front=(front+1)%MAXVEX;
		w=GetFirst(g,u);						/*取v的第一个邻接点w*/
		while(w!=-1)
		{
			if(visited[w]==0)/*w未访问过，则递归访问w的邻接点*/
			{
				printf("%d",g->lists[w].data);
				visited[w]=1;	
				queue[rear]=w;
				rear=(rear+1)%MAXVEX;
			}
			w=GetNext(g,u,w);		/*取下一个邻接点*/
		}
	}
}



/*算法7-16非连通图广度优先搜索遍历*/
void BFSTraverse(AdjList g)
{
	int i;
	int visited[MAXVEX];
	for(i=0;i<g->vexs;i++)
		visited[i]=0;
	for(i=0;i<g->vexs;i++)
		if(visited[i]==0)
			BFS(g,i,visited);
}