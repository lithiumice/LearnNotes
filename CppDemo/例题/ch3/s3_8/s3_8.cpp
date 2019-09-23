// s3_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#define QUEUESIZE 100
typedef int DataType;
typedef struct {
		DataType items[QUEUESIZE];
		int front;
		int count;
}SqQueue;

/*初始化队列*/
void InitQueue(SqQueue* Q)
{
	Q->front=0;
	Q->count=0;
}

/*入队*/
int EnQueue(SqQueue* Q,DataType item)
{
	int rear;
	if(Q->count>=QUEUESIZE)
	{
		printf("队列已满，不能完成入队操作！\n");
		return 0;
	}
	rear=(Q->front+Q->count)%QUEUESIZE;
	rear=(rear+1)%QUEUESIZE;		
	Q->items[rear]=item;
	Q->count++;						
	return 1;
}

/*出队*/
int DeQueue(SqQueue *Q,DataType *item)
{	
	if(Q->count<=0)
	{
		printf("队列已空，不能完成出队操作！\n");
		return 0;
	}	
	*item=Q->items[Q->front];
	Q->front=(Q->front+1)%QUEUESIZE;
	Q->count--;
	return 1;
}

void Print(SqQueue Q)
{
	int pos;
	pos=Q.front;
	while(pos<=Q.count)
	{
		printf("%d\t",Q.items[pos]);
		pos++;
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	int x;
	SqQueue Q;
	InitQueue(&Q);
	for(int i=0;i<4;i++)
		EnQueue(&Q,i);
	Print(Q);
	DeQueue(&Q,&x);
	Print(Q);
	return 0;
}

