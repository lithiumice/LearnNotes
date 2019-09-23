/*
	顺序队列的基本操作
 */
#include "stdio.h"

/*循环队列存储结构*/
#define QUEUESIZE 100
typedef int DataType;

typedef struct{
	DataType items[QUEUESIZE];
	int front,rear;
}SqQueue;

/*算法3-12初始化循环队列*/
int InitQueue(SqQueue *Q)
{
	Q->front=0;
	Q->rear=0;
	return 1;
}

/*算法3-13判空队*/
int QueueEmpty(SqQueue Q)
{
	if(Q.rear==Q.front)
		return 1;
	else
		return 0;
}

/*算法3-14队列长度*/
int QueueLength(SqQueue Q)
{
	return(Q.rear-Q.front+QUEUESIZE)%QUEUESIZE;
}

/*算法3-15入队*/
int EnQueue(SqQueue *Q,DataType e)
{	
	if((Q->rear+1)%QUEUESIZE==Q->front)
	{
		printf("队列已满，不能完成入队操作！\n");
		return 0;
	}
	Q->items[Q->rear]=e;
	Q->rear=(Q->rear+1)%QUEUESIZE;
	return 1;
}

/*算法3-16出队*/
int DeQueue(SqQueue *Q,DataType *e)
{	
	if(Q->front==Q->rear)
	{
		printf("队列已空，不能完成出队操作！\n");
		return 0;
	}	
	*e=Q->items[Q->front];
	Q->front=(Q->front+1)%QUEUESIZE;
	return 1;
}

/*算法3-17 取队头元素*/
int GetHead(SqQueue Q,DataType *e)
{	
	if(Q.front==Q.rear)
	{
		printf("队列已空，不能完成出队操作！\n");
		return 0;
	}	
	*e=Q.items[Q.front];
	return 1;
}

/*算法3-18 遍历队列*/
int TraverseQueue(SqQueue Q)
{	
	int pos;
	pos=Q.front;
	while((pos+1)%QUEUESIZE<=Q.rear)
	{
		printf("%d\t",Q.items[pos]);
		pos++;
	}	
	printf("\n");
	return 1;
}