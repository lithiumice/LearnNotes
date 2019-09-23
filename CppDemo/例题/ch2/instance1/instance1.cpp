// instance1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define LISTSIZE 100
#define MAXSIZE 50
/*�ľ߷�����Ϣ�Ľṹ*/
typedef struct
{
	int SortNumber;			/*�ľ߷����*/
	char SortName[10];		/*�ľ߷�����*/
}DataType,SortType;

typedef struct 
{
	SortType items[MAXSIZE];
	int length;
} SqList;
typedef SqList SortList;		/*�ľ߷���˳���*/

/*�ľ���Ϣ�Ľṹ*/
typedef struct
{
	int SortNumber;			/*�ľ߷����*/
	char StockName[10];		/*�ľ�����*/
	int amount;				/*�ľ�����*/
}StockType;

typedef struct Node			/*���*/
{
	StockType data;
	struct Node *next;
}LNode,*PNode,*LinkList;

typedef LinkList StockList;		/*�ľ�����*/

int InitList(LinkList *h)
{
	*h=(LinkList)malloc(sizeof(LNode));
	if(!h)
	{
		printf("��ʼ���������\n");
		return 0;
	}
	(*h)->next=NULL;
	return 1;
}


int Insert(LinkList h,int pos,StockType x)
{
	PNode p=h,q;
	int i=0;
	while(p && i<pos-1)
	{
		p=p->next;
		i++;
	}
	if(!p || i>pos-1)
	{
		printf("����λ�ò��Ϸ���\n");
		return 0;
	}
	q=(PNode)malloc(sizeof(LNode));
	if(!q)
	{
		printf("���������½��\n");
		return 0;
	}
	q->data=x;
	q->next=p->next;
	p->next=q;
	return 1;
}

int Delete(LinkList h,int pos,StockType *item)
{
	PNode p=h,q;
	int i=0;
	while(p->next  && i<pos-1)
	{
		p=p->next;
		i++;
	}
	if(!p->next  || i>pos-1)
	{
		printf("ɾ��λ�ò��Ϸ���\n");
		return 0;
	}	
	
	q=p->next;
	p->next=q->next;
	*item=q->data;
	free(q);
	return 1;
}


void Destroy(LinkList h)
{
	PNode p=h->next;
	while(h)
	{
		p=h;
		h=h->next;
		free(p);
	}
}


int CreateStockList(StockList *SL)
{
	int i,num=0;
	StockType sty;
	/*ʹ�õ������InitList������ʼ��������*/
	if(!InitList(SL))	
	{
		printf("��������\n");
		return 0;
	}
	printf("�������ľ�������\n");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf("�������ľ߷���ţ�\n");
		scanf("%d",&sty.SortNumber);
		printf("�������ľ����ƣ�\n");
		scanf("%s",&sty.StockName);
		printf("�������ľ�������\n");
		scanf("%d",&sty.amount);
/*ʹ�õ������Insert�����ڵ������в�����*/
		Insert(*SL,i+1,sty);
	}
	printf("\nOK...\n");
	return 1;
}


int AddStock(StockList SL)
{
	StockType sty;
	int pos=0;
	PNode p=SL->next;
	printf("�������ľ߷���ţ�\n");
	scanf("%d",&sty.SortNumber);
	printf("�������ľ�����\n");
	scanf("%s",&sty.StockName);
	printf("�������ľ�������\n");
	scanf("%d",&sty.amount);
	while(p)
	{
		if(!strcmp(p->data.StockName,sty.StockName))
		{
			p->data.amount+=sty.amount;
			break;
		}
		p=p->next;
		pos++;
	}
	if(!p)
		Insert(SL,pos+1,sty);
	printf("\nOK...\n");
	return 1;
}

int RemoveStock(StockList SL)
{
	StockType sty;
	PNode p=SL->next;
	int pos=0;
	printf("�������ľ�����\n");
	scanf("%s",&sty.StockName);
	printf("���������������\n");
	scanf("%d",&sty.amount);

	while(p && strcmp(p->data.StockName,sty.StockName))
	{
		p=p->next;
		pos++;
	}
	p->data.amount-=sty.amount;
	if(p->data.amount<=0)
		Delete(SL,pos+1,&sty);
	printf("\nOK...\n");
	return 1;
} 





int QueryStock(StockList SL)
{
	int no;
	PNode p=SL->next;
	//char name[10];
	printf("�������ľ߷���ţ�\n");
	scanf("%d",&no);
	//printf("�������ľ�����\n");
	//scanf("%s",name);
	//��ѯ�����и��ľ߷���ŵ��ľ���Ϣ
	printf("\nNumber	StockName	amount\n");
	while(p)
	{
		if(p->data.SortNumber==no)
		{
			printf("%d\t",p->data.SortNumber);
			printf("%s\t",p->data.StockName);
			printf("%d\t",p->data.amount);
			printf("\n");
		}
		p=p->next;
	}
	return 1;
}

void DispStock(StockList SL)
{
	PNode p=SL->next;
	printf("\nNumber	StockName	amount\n");
	while(p)
	{
		printf("%d\t",p->data.SortNumber);
		printf("%s\t",p->data.StockName);
		printf("%d\t",p->data.amount);
		printf("\n");
		p=p->next;
	}	
}

int InitList_Sq(SqList *L)
{
	L->length=0;
	return 1;
}

int ListInsert_Sq(SqList *L,int pos,DataType item)
{
	int i;
	if(L->length>=LISTSIZE)
	{
		printf("˳����������޷����в��������");
		return 0;
	}
	if(pos<=0 || pos>L->length+1)
{
		printf("����λ�ò��Ϸ�����ȡֵ��ΧӦ����[1,length+1]");
		return 0;
	}
	for(i=L->length-1; i>=pos-1; i--)
		L->items[i+1]=L->items[i];
	L->items[pos-1]=item;
	L->length++;
	return 1;
}


int CreateSortList(SortList *SL)
{
	int i,num=0;
	SortType sty;
	/*ʹ��˳����InitList������ʼ��˳���*/
/*Ϊ�����ֵ������ͬ����������˳����InitList��������ΪInitList_Sq*/
	InitList_Sq(SL);			
	printf("�������ľ����������\n");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf("�������ľ߷���ţ�\n");
		scanf("%d",&sty.SortNumber);
		printf("�������ľ߷������ƣ�\n");
		scanf("%s",&sty.SortName);
/*ʹ��˳����Insert������˳����в�����*/
/*Ϊ�����ֵ������ͬ����������˳����ListInsert��������ΪInsert_Sq*/
		ListInsert_Sq(SL,i+1,sty);
	}
	printf("\nOK...\n");
	return 1;
}


int AddSort(SortList *L)
{
	SortType st;
	printf("�������ľ߷���ţ�\n");
	scanf("%d",&st.SortNumber);
	printf("�������ľ߷�������\n");
	scanf("%s",&st.SortName);
	if(!ListInsert_Sq(L,L->length+1,st))
		return 0;
	printf("\nOK...\n");
	return 1;
}


int main(int argc, char* argv[])
{	
	int choice;
	StockList SL;
	SortList L;
	do
	{ 
		printf("\n		�ľߵ��Ʒ����ϵͳ			\n");
		printf("\n------------------���˵�----------------------\n");
		printf("	(1) �����ľ߷����...		\n");
		printf("	(2) ��ʼ���ľ߱�...		\n");
		printf("	(3) �ľ����...		\n");
		printf("	(4) �ľ߳���...		\n");
		printf("	(5) ��ѯ�ľ���Ϣ...		\n");
		printf("	(6) ��ʾ�ľ���Ϣ...		\n");
		printf("	(7) ������ľ����...		\n");
		printf("	(0) �˳�ϵͳ...		\n");
		printf("\n��ѡ��(1,2,3,4,0)��");
		scanf("%d",&choice);
		if(choice<0 && choice>7) continue;		
		switch(choice)
		{ 
		case 1:CreateSortList(&L);break; /*��ʼ���ľ߷���˳���*/
		case 2:CreateStockList(&SL);break; /*��ʼ���ľ߱�*/
		case 3:AddStock(SL);break;	 /*�ľ����*/
		case 4:RemoveStock(SL);break;/*�ľ߳���*/
		case 5:QueryStock(SL);break;/*��ѯ�ľ���Ϣ*/
		case 6:DispStock(SL);break;/*��ʾ�ľ���Ϣ*/
		case 7:AddSort(&L);break;/*������ľ����*/
		case 0:exit(0); /*�˳�������*/
		default: break;
		}
	}while(1);	
	return 0;
}
