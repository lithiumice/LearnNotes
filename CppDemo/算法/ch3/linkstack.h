/*
	链栈的基本操作
 */
#include "stdio.h"
#include "malloc.h"

/*链栈存储结构*/
typedef int DataType;
typedef struct SNode{
	DataType data;
	struct SNode* next;
}SNode, *LinkStack;



/*算法3-6初始化链栈*/
int InitStack(LinkStack *top)
{
	*top=(LinkStack)malloc(sizeof(SNode));
	if(*top==NULL)
	{
		printf("初始化链栈出错！\n");
		return 0;
	}
	(*top)->next=NULL;
	return 1;
}



/*算法3-7判空栈*/
int StackEmpty(LinkStack top)
{
	if(top->next==NULL)
		return 1;
	else
		return 0;
}



/*算法3-8入栈*/
int Push(LinkStack top,DataType e)
{
	SNode *p;
	p=(SNode*)malloc(sizeof(SNode));
	if(!p)
	{
		printf("入栈操作出错！\n");
		return 0;
	}
	p->data=e;
	p->next=top->next;
	top->next=p;
	return 1;
}



/*算法3-9出栈*/
int Pop(LinkStack top,DataType* e)
{
	SNode *p;
	if(!top->next)
	{
		printf("栈已空，无法完成出栈操作！\n");
		return 0;
	}
	p=top->next;
	top->next=p->next;
	*e=p->data;
	free(p);
	return 1;
}



/*算法3-10 取栈顶元素*/
int GetTop(LinkStack top,DataType* e)
{
	SNode *p;
	if(!top->next)
	{
		printf("栈已空，无法完成取栈顶元素操作！\n");
		return 0;
	}
	p=top->next;	
	*e=p->data;	
	return 1;
}



/*算法3-11销毁链栈*/
int Destroy(LinkStack top)
{
	SNode *p;
	while(top)
	{
		p=top;
		top=top->next;
		free(p);		
	}
	return 1;
}
