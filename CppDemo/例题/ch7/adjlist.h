/*
   �ڽӱ�Ļ�������
*/
#include "malloc.h"
#include "stdio.h"

/*�ڽӱ�Ĵ洢�ṹ*/
#define MAXVEX 50
typedef int DataType;
typedef struct arc{				/*�߱�������*/
	int adjvex;					/*�������*/
	struct arc* next;			/*ָ����һ���ڽӵ�*/
}ArcNode,*PArcNode;
typedef struct{					/*�����������*/
	DataType data;				/*������Ϣ*/
	ArcNode* head;				/*�߱�ͷָ��*/
}VexNode;
typedef struct{					/*�ڽӱ�����*/
	VexNode lists[MAXVEX];		/*�����*/
	int edges,vexs;				/*������������*/
}VGraph,*AdjList;




/*�㷨7-9�����ڽӱ�*/
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


/*�㷨7-10��ʾ�ڽӱ�*/
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

/*�㷨7-11��һ���ڽӵ�*/
int GetFirst(AdjList g,int k)
{
	if(k<0 || k>g->vexs)
	{
		printf("����k������Χ��\n");
		return -1;
	}
	if(g->lists[k].head==NULL)
		return -1;
	else
		return g->lists[k].head->adjvex;
}



/*�㷨7-12��һ���ڽӵ�*/
int GetNext(AdjList g,int k,int u)
{
	PArcNode p;
	if(k<0 || k>g->vexs || u<0 || u>g->vexs)
	{
		printf("����k��u������Χ��\n");
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


/*�㷨7-�����㸳ֵ*/
void PutVex(AdjList g,int k,DataType x)
{
	if(k<0 || k>g->vexs)
	{
		printf("����k������Χ��\n");
		return ;
	}
	g->lists[k].data=x;
}


/*�㷨7-ȡ����ֵ*/
DataType GetVex(AdjList g,int k)
{
	if(k<0 || k>g->vexs)
	{
		printf("����k������Χ��\n");
		return NULL;
	}
	return g->lists[k].data;
}



/*�㷨7-�����*/
void InsertArc(AdjList g,int a1,int a2)
{
	PArcNode p;
	if(a1<0 || a1>g->vexs || a2<0 || a2>g->vexs)
	{
		printf("����a1��a2������Χ��\n");
		return ;
	}
	p=(PArcNode)malloc(sizeof(ArcNode));
	p->adjvex=a2;
	p->next=g->lists[a1].head;
	g->lists[a1].head=p;
	g->edges++;
}


/*�㷨7-ɾ����*/
void DeleteArc(AdjList g,int a1,int a2)
{
	PArcNode p,q=NULL;
	if(a1<0 || a1>g->vexs || a2<0 || a2>g->vexs)
	{
		printf("����a1��a2������Χ��\n");
		return ;
	}
	p=g->lists[a1].head;
	while(p!=NULL && p->adjvex!=a2)
	{
		q=p;p=p->next;
	}
	if(p==NULL)
	{
		printf("��(%d,%d)������",a1,a2);
		return;
	}
	if(p!=NULL && q!=NULL)
		q->next=p->next;
	else
		g->lists[a1].head=p->next;
	free(p);
	g->edges--;
}

/*�㷨7-��ͨͼ���������������*/
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



/*�㷨7-����ͨͼ���������������*/
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


/*�㷨7-15��ͨͼ���������������*/
void BFS(AdjList g,int v,int visited[])
{	
	int u;
	int queue[MAXVEX];/*ѭ������*/
	int front=0,rear=0;			/*��ͷ����βָ��*/
	int w;							/*v���ڽӵ�*/
	printf("%d",g->lists[v].data);	/*���ʶ���v*/
	visited[v]=1;							/*�ñ�ʶΪ�ѷ��ʹ�*/
	queue[rear]=v;	/*v���*/
	rear=(rear+1)%MAXVEX;	
	while(front<rear)
	{
		u=queue[front];
		front=(front+1)%MAXVEX;
		w=GetFirst(g,u);						/*ȡv�ĵ�һ���ڽӵ�w*/
		while(w!=-1)
		{
			if(visited[w]==0)/*wδ���ʹ�����ݹ����w���ڽӵ�*/
			{
				printf("%d",g->lists[w].data);
				visited[w]=1;	
				queue[rear]=w;
				rear=(rear+1)%MAXVEX;
			}
			w=GetNext(g,u,w);		/*ȡ��һ���ڽӵ�*/
		}
	}
}



/*�㷨7-16����ͨͼ���������������*/
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