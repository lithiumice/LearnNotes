/*
	�����еĻ�������
 */
#include "stdio.h"
#include "malloc.h"

//#define MAXSIZE 10
/*�����д洢�ṹ*/
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


/*�㷨3-19��ʼ��������*/
int InitQueue(LinkQueue *Q)
{	
	Q->front=Q->rear=(PQNode)malloc(sizeof(LQNode));
	if(!Q->front)
	{
		printf("��ʼ������ʧ�ܣ�\n");
		return 0;
	}	
	Q->front->next=NULL;

	return 1;
}


/*�㷨3-20�пն�*/
int QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}



/*�㷨3-21���*/
int EnQueue(LinkQueue *Q,DataType e)
{	
	PQNode p;
	p=(PQNode)malloc(sizeof(LQNode));
	if(!p)
	{
		printf("�ڴ����ʧ�ܣ����������Ӳ�����\n");
		return 0;
	}
	p->data=e;
	p->next=NULL;		/*��ʼ����ӽ��*/
	Q->rear->next=p;
	Q->rear=p;
	return 1;
}


/*�㷨3-22����*/
int DeQueue(LinkQueue *Q,DataType *e)
{	
	PQNode p;
	if(Q->front==Q->rear)
	{
		printf("�����ѿգ�������ɳ��Ӳ�����\n");
		return 0;
	}	
	p=Q->front->next;
	*e=p->data;
	Q->front->next=p->next;
	free(p);
	if(Q->rear==p)  /*��ɾ�����Ƕ��������һ����㣬���ƶ���βָ��*/
		Q->rear=Q->front;
	return 1;
}


/*�㷨3-23 ȡ��ͷԪ��*/
int GetHead(LinkQueue Q,DataType *e)
{		
	PQNode p;
	if(Q.front==Q.rear)
	{
		printf("�����ѿգ��������ȡ��ͷԪ�ز�����\n");
		return 0;
	}	
	p=Q.front->next;
	*e=p->data;
	return 1;
}

/*�㷨3-24 ���ٶ���*/
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
