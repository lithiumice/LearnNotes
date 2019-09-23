#include<stdio.h>
#include "time.h"
#include "stdlib.h"
#include "malloc.h"

/*˳��ջ�洢�ṹ*/
#define STACKSIZE 2   //ͣ��������

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


/*�㷨3-1��ʼ��˳��ջ*/
int InitStack(SqStack *S)
{
	S->top=-1;
	return 1;
}


/*�㷨3-2�п�ջ*/
int StackEmpty(SqStack S)
{
	if(S.top==-1)
		return 1;
	else
		return 0;
}


/*�㷨3-3��ջ*/
int Push(SqStack *S,DataType e)
{	
	if(S->top>=STACKSIZE-1)
	{
		printf("��ջ���������������ջ������\n");
		return 0;
	}
	S->top++;
	S->items[S->top]=e;
	return 1;
}


/*�㷨3-4��ջ*/
int Pop(SqStack *S,DataType *e)
{	
	if(S->top<=-1)
	{
		printf("��ջ�ѿգ�������ɳ�ջ������\n");
		return 0;
	}	
	*e=S->items[S->top];
	S->top--;
	return 1;
}




/*�����д洢�ṹ*/
//typedef int DataType;
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

int Reach(SqStack *stop,LinkQueue *pave) 
{ /*��������ͣ����*/
	DataType *car;
	car=(DataType *)malloc(sizeof(DataType));
	if(!car){printf("�����������");return 0;}
	flushall();
	printf("\n��ӭ���룡�����복�ƺ�:");
	gets(car->lisence);
	if(stop->top>=STACKSIZE-1)/*ͣ�������������������ȴ�*/
	{
		printf("ͣ������������������ȴ�...\n\n");
		EnQueue(pave,*car);
	}
	else/*ͣ����δ��������ͣ����*/
	{
		car->reach=time(NULL);/*��ȡϵͳʱ��*/
		car->stop=stop->top+1;
		Push(stop,*car);
		printf("\n�복�������%d��ͣ��λ.\n\n",car->stop);
	}
	return 1;
}


void Leave(SqStack *park,SqStack *tmp,LinkQueue *pave,double UnitPrice)
{	/*�����뿪*/
	int locate;
	DataType p,t;	
	if(!StackEmpty(*park)) /*ͣ�������г�*/
	{
		printf("\n�������뿪������ͣ��λ�ţ�1~%d����",park->top+1);
		scanf("%d",&locate);
		while(park->top>locate-1) /*�����뿪����֮ǰ�ĳ���������ʱջ*/
		{
			Pop(park,&p);
			Push(tmp,p);
		}
		/*�뿪������Ϣ*/
		Pop(park,&p);
		p.leave=time(NULL);
		printf("\n----------------�뿪������Ϣ------------------\n");
		printf("\n  ͣ��λ	���ƺ�		Ӧ������	����ʱ��		�뿪ʱ��\n");
		printf("---------------------------------------------------\n");
		printf("%d",p.stop);
		printf("  %s ",p.lisence);		
		printf("  %4.2fԪ",difftime(p.leave,p.reach)/60*UnitPrice);
		printf(ctime(&p.reach));
		printf(ctime(&p.leave));
		while(tmp->top>=0)/*�����뿪����֮ǰ�ĳ�������ʱջ�ص�ͣ����*/
		{
			Pop(tmp,&p);
			Push(park,p);
		}
		/*���ͣ����������������ϲ��գ������ϵĳ�������ͣ����*/
		if(!QueueEmpty(*pave) && park->top<STACKSIZE) 
		{			
			DeQueue(pave,&t);
			printf("\n����ϵ�%s�ų������%d��ͣ��λ.",t.lisence,park->top+1);
			t.reach=time(NULL);
			t.stop=park->top+1;
			Push(park,t);
		}
		else
			printf("�����û�г�.\n");
	}
	else
		printf("\nͣ������û�г�.");
}


void DispPark(SqStack *park) /*��ʾͣ������Ϣ*/
{
	int i;	
	if(StackEmpty(*park)) /*ͣ������û�г���*/
		printf("ͣ����û�г���");
	else/*ͣ�������г���*/
	{
		printf("\n  ͣ��λ	���ƺ�		����ʱ��\n");
		printf("---------------------------------------------------\n");
		for(i=0;i<=park->top;i++)
		{
			printf("\t%d\t",i+1);
			printf(park->items[i].lisence);
			printf("\t%s\n",ctime(&(park->items[i].reach)));
		}
	}
}


void DispPave(LinkQueue *pave) /*��ʾ�ȴ�����Ϣ*/
{ 
	PQNode p;
	p=pave->front->next;
	if(QueueEmpty(*pave))/*�жϱ�����Ƿ��еȴ��ĳ���*/
		printf("û�еȴ��ĳ���\n");
	else
	{
		printf("���³������ڵȴ�״̬��"); 
		printf("\n----------------���ƺ�---------------------\n");
		while(p){
			puts(p->data.lisence);
			p=p->next;
		}
	}
}

float ModifyUnitPrice()
{
	float price=0;
	printf("\n�����뵥�ۣ�");
	scanf("%f",&price);
	printf("\nOK...\n");
	return price;
}
