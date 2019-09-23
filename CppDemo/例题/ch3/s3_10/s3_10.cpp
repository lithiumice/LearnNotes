// s3_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../linkqueue.h"

int InitQueue(PQNode* rear)
{	
	(*rear)=(PQNode)malloc(sizeof(LQNode));
	if(!(*rear))
	{
		printf("初始化队列失败！\n");
		return 0;
	}	
	(*rear)->next=(*rear);  
	return 1;
}

int EnQueue(PQNode *rear,DataType e)
{	
	PQNode p;
	p=(PQNode)malloc(sizeof(LQNode));
	if(!p)
	{
		printf("内存分配失败，不能完成入队操作！\n");
		return 0;
	}
	p->data=e;
	p->next=(*rear)->next;		
	(*rear)->next=p;
	(*rear)=p;
	return 1;
}

int DeQueue(PQNode *rear,DataType *e)
{	
	PQNode p,front;
	if((*rear)->next==(*rear))
	{
		printf("队列已空，不能完成出队操作！\n");
		return 0;
	}	
	front=(*rear)->next;
	p=front->next;
	*e=p->data;
	front->next=p->next;
	free(p);
	if(front->next==front)
		(*rear)=front;
	return 1;
}

int main(int argc, char* argv[])
{
	int x;
	PQNode rear;
	InitQueue(&rear);
	for(int i=0;i<4;i++)
		EnQueue(&rear,i);
	for(i=0;i<4;i++)
	{
		DeQueue(&rear,&x);
		printf("%d\t",x);
	}	
	return 0;
}

