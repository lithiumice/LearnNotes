// s3_9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstack.h"

int EnQueue(SqStack* SIN,DataType item)
{
	if(SIN->top>=STACKSIZE-1)
	{
		printf("队列已满，不能完成入队操作！\n");
		return 0;
	}
	Push(SIN,item);	
	return 1;
}


int DeQueue(SqStack *SOUT,SqStack* SIN,DataType *item)
{	
	DataType x;
	if(!StackEmpty(*SOUT))
	{
		Pop(SOUT,item);
	}	
	else
	{
		while( !StackEmpty(*SIN))
		{
			Pop(SIN,&x) ;
			Push(SOUT,x) ;
		}
		Pop(SOUT,item) ;
	}
	return 1;
}


int main(int argc, char* argv[])
{
	int x;
	SqStack s1,s2;
	InitStack(&s1);
	InitStack(&s2);
	for(int i=0;i<4;i++)
		EnQueue(&s1,i);
    for(i=0;i<3;i++)
	{
		DeQueue(&s2,&s1,&x);
		printf("%d\t",x);
	}
	for(i=0;i<4;i++)
		EnQueue(&s1,i*10);
	for(i=0;i<5;i++)
	{
		DeQueue(&s2,&s1,&x);
		printf("%d\t",x);
	}
	//DeQueue(&s2,&s1,&x);
	return 0;
}

