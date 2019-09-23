/*
	˳����еĻ�������
 */
#include "stdio.h"

/*ѭ�����д洢�ṹ*/
#define QUEUESIZE 100
typedef int DataType;

typedef struct{
	DataType items[QUEUESIZE];
	int front,rear;
}SqQueue;

/*�㷨3-12��ʼ��ѭ������*/
int InitQueue(SqQueue *Q)
{
	Q->front=0;
	Q->rear=0;
	return 1;
}

/*�㷨3-13�пն�*/
int QueueEmpty(SqQueue Q)
{
	if(Q.rear==Q.front)
		return 1;
	else
		return 0;
}

/*�㷨3-14���г���*/
int QueueLength(SqQueue Q)
{
	return(Q.rear-Q.front+QUEUESIZE)%QUEUESIZE;
}

/*�㷨3-15���*/
int EnQueue(SqQueue *Q,DataType e)
{	
	if((Q->rear+1)%QUEUESIZE==Q->front)
	{
		printf("�������������������Ӳ�����\n");
		return 0;
	}
	Q->items[Q->rear]=e;
	Q->rear=(Q->rear+1)%QUEUESIZE;
	return 1;
}

/*�㷨3-16����*/
int DeQueue(SqQueue *Q,DataType *e)
{	
	if(Q->front==Q->rear)
	{
		printf("�����ѿգ�������ɳ��Ӳ�����\n");
		return 0;
	}	
	*e=Q->items[Q->front];
	Q->front=(Q->front+1)%QUEUESIZE;
	return 1;
}

/*�㷨3-17 ȡ��ͷԪ��*/
int GetHead(SqQueue Q,DataType *e)
{	
	if(Q.front==Q.rear)
	{
		printf("�����ѿգ�������ɳ��Ӳ�����\n");
		return 0;
	}	
	*e=Q.items[Q.front];
	return 1;
}

/*�㷨3-18 ��������*/
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