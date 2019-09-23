#include<stdio.h>
#include "time.h"
#include "stdlib.h"
#include "malloc.h"

/*顺序栈存储结构*/
#define STACKSIZE 2   //停车场容量

typedef struct{
	char lisence[10];
	int type;
	clock_t reach;
	clock_t leave;
	int stop;
}CarInfo;

typedef  CarInfo DataType;

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




/*链队列存储结构*/
//typedef int DataType;
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

int Reach(SqStack *stop,LinkQueue *pave) 
{ /*车辆到达停车场*/
	DataType *car;
	car=(DataType *)malloc(sizeof(DataType));
	if(!car){printf("车辆进入出错");return 0;}
	flushall();
	printf("\n欢迎进入！请输入车牌号:");
	gets(car->lisence);
	if(stop->top>=STACKSIZE-1)/*停车场已满，车进入便道等待*/
	{
		printf("停车场已满，请进入便道等待...\n\n");
		EnQueue(pave,*car);
	}
	else/*停车场未满，进入停车场*/
	{
		car->reach=time(NULL);/*获取系统时间*/
		car->stop=stop->top+1;
		Push(stop,*car);
		printf("\n请车辆进入第%d号停车位.\n\n",car->stop);
	}
	return 1;
}


void Leave(SqStack *park,SqStack *tmp,LinkQueue *pave,double UnitPrice)
{	/*车辆离开*/
	int locate;
	DataType p,t;	
	if(!StackEmpty(*park)) /*停车场内有车*/
	{
		printf("\n请输入离开车辆的停车位号（1~%d）：",park->top+1);
		scanf("%d",&locate);
		while(park->top>locate-1) /*排在离开车辆之前的车辆进入临时栈*/
		{
			Pop(park,&p);
			Push(tmp,p);
		}
		/*离开车辆信息*/
		Pop(park,&p);
		p.leave=time(NULL);
		printf("\n----------------离开车辆信息------------------\n");
		printf("\n  停车位	车牌号		应交费用	到达时间		离开时间\n");
		printf("---------------------------------------------------\n");
		printf("%d",p.stop);
		printf("  %s ",p.lisence);		
		printf("  %4.2f元",difftime(p.leave,p.reach)/60*UnitPrice);
		printf(ctime(&p.reach));
		printf(ctime(&p.leave));
		while(tmp->top>=0)/*排在离开车辆之前的车辆从临时栈回到停车场*/
		{
			Pop(tmp,&p);
			Push(park,p);
		}
		/*如果停车场不满，而便道上不空，则便道上的车辆进入停车场*/
		if(!QueueEmpty(*pave) && park->top<STACKSIZE) 
		{			
			DeQueue(pave,&t);
			printf("\n便道上的%s号车进入第%d个停车位.",t.lisence,park->top+1);
			t.reach=time(NULL);
			t.stop=park->top+1;
			Push(park,t);
		}
		else
			printf("便道上没有车.\n");
	}
	else
		printf("\n停车场内没有车.");
}


void DispPark(SqStack *park) /*显示停车场信息*/
{
	int i;	
	if(StackEmpty(*park)) /*停车场内没有车辆*/
		printf("停车场没有车辆");
	else/*停车场内有车辆*/
	{
		printf("\n  停车位	车牌号		到达时间\n");
		printf("---------------------------------------------------\n");
		for(i=0;i<=park->top;i++)
		{
			printf("\t%d\t",i+1);
			printf(park->items[i].lisence);
			printf("\t%s\n",ctime(&(park->items[i].reach)));
		}
	}
}


void DispPave(LinkQueue *pave) /*显示等待车信息*/
{ 
	PQNode p;
	p=pave->front->next;
	if(QueueEmpty(*pave))/*判断便道上是否有等待的车辆*/
		printf("没有等待的车辆\n");
	else
	{
		printf("以下车辆处于等待状态："); 
		printf("\n----------------车牌号---------------------\n");
		while(p){
			puts(p->data.lisence);
			p=p->next;
		}
	}
}

float ModifyUnitPrice()
{
	float price=0;
	printf("\n请输入单价：");
	scanf("%f",&price);
	printf("\nOK...\n");
	return price;
}
