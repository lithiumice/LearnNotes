/*
	链队列的基本操作
 */
#include "stdio.h"
#include "malloc.h"

//#define MAXSIZE 10
/*链队列存储结构*/
typedef int KeyType;
typedef struct{
	KeyType key;
}DataType;
//typedef struct{
	//DataType data;
//}SqList[MAXSIZE];

typedef struct QNode{
	DataType data;
	struct QNode* next;
}LQNode, *PQNode;
typedef struct{
	PQNode front, rear;
}LinkQueue;


/*算法3-19初始化链队列*/
int InitQueue(LinkQueue *Q)
{	
	Q->front=Q->rear=(PQNode)malloc(sizeof(LQNode));
	if(!Q->front)
	{
		printf("初始化队列失败！\n");
		return 0;
	}	
	Q->front->next=NULL;

	return 1;
}


/*算法3-20判空队*/
int QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}



/*算法3-21入队*/
int EnQueue(LinkQueue *Q,DataType e)
{	
	PQNode p;
	p=(PQNode)malloc(sizeof(LQNode));
	if(!p)
	{
		printf("内存分配失败，不能完成入队操作！\n");
		return 0;
	}
	p->data=e;
	p->next=NULL;		/*初始化入队结点*/
	Q->rear->next=p;
	Q->rear=p;
	return 1;
}


/*算法3-22出队*/
int DeQueue(LinkQueue *Q,DataType *e)
{	
	PQNode p;
	if(Q->front==Q->rear)
	{
		printf("队列已空，不能完成出队操作！\n");
		return 0;
	}	
	p=Q->front->next;
	*e=p->data;
	Q->front->next=p->next;
	free(p);
	if(Q->rear==p)  /*若删除的是队列中最后一个结点，则移动队尾指针*/
		Q->rear=Q->front;
	return 1;
}


/*算法3-23 取队头元素*/
int GetHead(LinkQueue Q,DataType *e)
{		
	PQNode p;
	if(Q.front==Q.rear)
	{
		printf("队列已空，不能完成取队头元素操作！\n");
		return 0;
	}	
	p=Q.front->next;
	*e=p->data;
	return 1;
}

/*算法3-24 销毁队列*/
int DestroyQueue(LinkQueue *Q)
{	
	while(Q->front)
	{
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}	
	return 1;
}
