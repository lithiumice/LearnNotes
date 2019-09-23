/*
   邻接矩阵的基本操作
*/
#include "malloc.h"
#include "stdio.h"

/*邻接矩阵的存储结构*/
#define MAXWEIGHT 100
#define MAXVEX 50  					/*最大顶点个数*/
typedef char DataType;
typedef int weight;					/*权值*/
typedef struct{
	weight arcs[MAXVEX][MAXVEX];	/*邻接矩阵*/
	DataType data[MAXVEX];			/*顶点信息*/
	int vexs;						/*顶点数*/
}MGraph,*AdjMetrix;





/*算法7-1创建邻接矩阵*/
void CreateGraph(AdjMetrix g,int m[][MAXVEX],DataType d[],int n)
{
	int i,j;	
	g->vexs=n;
	for(i=0;i<n;i++)
	{
		g->data[i]=d[i];
		for(j=0;j<n;j++)
			g->arcs[i][j]=m[i][j];		
	}
}


/*算法7-2显示邻接矩阵*/
void DispGraph(AdjMetrix g)
{
	int i,j;
	printf("顶点：\n\t");
	for(i=0;i<g->vexs;i++)	
		printf("%c\t",g->data[i]);
	printf("\n\n邻接矩阵：");
	for(i=0;i<g->vexs;i++)
	{
		printf("\n%c:\t",g->data[i]);
		for(j=0;j<g->vexs;j++)
			printf("%d\t",g->arcs[i][j]);		
	}
	printf("\n\n");
}

/*算法7-3第一个邻接点*/
int GetFirst(AdjMetrix g,int k)
{
	int i;
	if(k<0 || k>g->vexs)
	{
		printf("参数k超出范围！\n");
		return -1;
	}
	for(i=0;i<g->vexs;i++)
		if(g->arcs[k][i]==1)
			return i;
	return -1;
}



/*算法7-4下一个邻接点*/
int GetNext(AdjMetrix g,int k,int t)
{	
	int i;
	if(k<0 || k>g->vexs || t<0 || t>g->vexs)
	{
		printf("参数k或t超出范围！\n");
		return NULL;
	}
	for(i=t+1;i<g->vexs;i++)
		if(g->arcs[k][i]==1)
			return i;		
	return -1;
}


/*算法7-5给顶点赋值*/
void PutVex(AdjMetrix g,int k,DataType x)
{
	if(k<0 || k>g->vexs)
	{
		printf("参数k超出范围！\n");
		return ;
	}
	g->data[k]=x;
}


/*算法7-6取顶点值*/
DataType GetVex(AdjMetrix g,int k)
{
	if(k<0 || k>g->vexs)
	{
		printf("参数k超出范围！\n");
		return -1;
	}
	return g->data[k];
}



/*算法7-7插入边*/
void InsertArc(AdjMetrix g,int u,int v,weight w)
{	
	if(u<0 || u>g->vexs || v<0 || v>g->vexs)
	{
		printf("参数u或v超出范围！\n");
		return ;
	}
	g->arcs[u][v]=w;
	//g->arcs[v][u]=w;
}


/*算法7-8删除边*/
void DeleteArc(AdjMetrix g,int u,int v)
{
	if(u<0 || u>g->vexs || v<0 || v>g->vexs)
	{
		printf("参数u或v超出范围！\n");
		return ;
	}
	g->arcs[u][v]=0;
}


/*算法7-13连通图深度优先搜索遍历*/
/*以邻接矩阵作为存储结构*/
void DFS(AdjMetrix g,int k,int visited[])
{
	int u;
	printf("%c",g->data[k]);
	visited[k]=1;
	u=GetFirst(g,k);
	while(u!=-1)
	{
		if(visited[u]==0)
			DFS(g,u,visited);
		u=GetNext(g,k,u);
	}
}



/*算法7-14非连通图深度优先搜索遍历*/
/*以邻接矩阵作为存储结构*/
void DFSTraverse(AdjMetrix g)
{
	int i;
	int visited[MAXVEX];
	for(i=0;i<g->vexs;i++)
		visited[i]=0;
	for(i=0;i<g->vexs;i++)
		if(visited[i]==0)
			DFS(g,i,visited);
}



/*算法7-17普里姆算法*/
void Prim(AdjMetrix g,int v)
{
	weight lowcost[MAXVEX];
	int uset[MAXVEX];
	int i,j,MinEdge,MinWeight,k;
	
	for(i=0;i<g->vexs;i++)
	{
		lowcost[i]=g->arcs[v][i];
		uset[i]=1;
	}
	uset[v]=0;
	printf("起始点%c\n",g->data[v]);
	for(i=1;i<g->vexs;i++)
	{
		MinWeight=MAXWEIGHT;
		for(j=0;j<g->vexs;j++)
		{
			if(uset[j] && lowcost[j]<MinWeight)
			{
				MinWeight=lowcost[j];
				MinEdge=j;
			}
		}
		for(j=0;j<g->vexs;j++)
			if(g->arcs[j][MinEdge]==MinWeight)
				k=j;

		printf("边(%c,%c)\t权值[%d]\n",g->data[k],g->data[MinEdge],MinWeight);
		uset[MinEdge]=0;
		v=MinEdge;
		for(j=0;j<g->vexs;j++)
			if(uset[j] && g->arcs[v][j]<lowcost[j])
				lowcost[j]=g->arcs[v][j];
	}
}


/*算法7-18迪杰斯特拉算法*/
void Dijstra(AdjMetrix g,int v,int dis[])
{
	int vset[MAXVEX];
	int MinDis,i,j,w;
	for(i=0;i<g->vexs;i++)
	{
		vset[i]=1;
		dis[i]=g->arcs[v][i];
	}
	vset[v]=0;
	for(i=1;i<g->vexs;i++)
	{
		MinDis =MAXWEIGHT;
		for(j=0;j<g->vexs;j++)
			if(vset[j] && dis[j]<MinDis)
			{
				w=j;
				MinDis=dis[j];				
			}
			printf("顶点%c到顶点%c的最短路径值为：%d\n",g->data[v],g->data[w],MinDis);
			if(MinDis==MAXWEIGHT)
				return;
			vset[w]=0;
			for(j=0;j<g->vexs;j++)
			{
				if(vset[j] && g->arcs[w][j]<MAXWEIGHT && dis[w]+g->arcs[w][j]<dis[j])
					dis[j]=dis[w]+g->arcs[w][j];
			}
	}
}


void Ppath(int path[][MAXVEX],int i,int j)
{
	int k;
	k=path[i][j];
	if(k==-1) return;
	Ppath(path,i,k);
	printf("%d,",k);
	Ppath(path,k,j);
}

void Dispath(int A[][MAXVEX],int path[][MAXVEX],int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(A[i][j]!=MAXWEIGHT && i!=j)
			{
				printf(" from %d to %d path:",i,j);
				printf("%d,",i);
				Ppath(path,i,j);
				printf("%d",j);
				printf(" length:%d\n",A[i][j]);
			}
		}
}



/*算法7-19弗洛伊德算法*/
void Floyd(AdjMetrix g,int F[][MAXVEX])
{
	int path[MAXVEX][MAXVEX];
	int i,j,k;
	for(i=0;i<g->vexs;i++)
		for(j=0;j<g->vexs;j++)
		{
			F[i][j]=g->arcs[i][j];
			path[i][j]=-1;
		}
	for(k=0;k<g->vexs;k++)
		for(i=0;i<g->vexs;i++)
			for(j=0;j<g->vexs;j++)
				if(F[i][j]>F[i][k]+F[k][j])
				{
					F[i][j]=F[i][k]+F[k][j];
					path[i][j]=k;
				}
	printf("\n每对顶点间最短路径长度：\n");
	for(i=0;i<g->vexs;i++)
		for(j=0;j<g->vexs;j++)
			if(F[i][j]!=MAXWEIGHT && i!=j)
				printf("%c->%c：[%d]\n",g->data[i],g->data[j],F[i][j]);
	//Dispath(F,path,g->vexs);
}
				
			

