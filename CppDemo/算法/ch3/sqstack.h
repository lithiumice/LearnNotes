/*
	顺序栈的基本操作
 */
#include<stdio.h>

/*顺序栈存储结构*/
#define STACKSIZE 100
typedef int DataType;

typedef struct
{
	DataType items[STACKSIZE];
	int top;
}SqStack;


/*算法3-1初始化顺序栈*/
int InitStack(SqStack *S)
{
	S->top=-1;
	return 1;
}


/*算法3-2判空栈*/
int StackEmpty(SqStack S)
{
	if(S.top==-1)
		return 1;
	else
		return 0;
}


/*算法3-3入栈*/
int Push(SqStack *S,DataType e)
{	
	if(S->top>=STACKSIZE-1)
	{
		printf("堆栈已满，不能完成入栈操作！\n");
		return 0;
	}
	S->top++;
	S->items[S->top]=e;
	return 1;
}


/*算法3-4出栈*/
int Pop(SqStack *S,DataType *e)
{	
	if(S->top<=-1)
	{
		printf("堆栈已空，不能完成出栈操作！\n");
		return 0;
	}	
	*e=S->items[S->top];
	S->top--;
	return 1;
}


/*算法3-5 取栈顶元素*/
int GetTop(SqStack S,DataType *e)
{	
	if(S.top<=-1)
	{
		printf("堆栈已空，不能完成取栈顶元素操作！\n");
		return 0;
	}	
	*e=S.items[S.top];
	return 1;
}


/*算法3-18 遍历队列
int TraverseQueue(SqQueue Q)
{	
	int pos;
	pos=Q.front;
	while((pos+1)%QUEUESIZE<Q.rear)
	{
		printf("%d\t",Q.items[pos]);
		pos++;
	}	
	printf("\n");
	return 1;
}*/
