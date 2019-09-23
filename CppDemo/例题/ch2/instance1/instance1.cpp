// instance1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define LISTSIZE 100
#define MAXSIZE 50
/*文具分类信息的结构*/
typedef struct
{
	int SortNumber;			/*文具分类号*/
	char SortName[10];		/*文具分类名*/
}DataType,SortType;

typedef struct 
{
	SortType items[MAXSIZE];
	int length;
} SqList;
typedef SqList SortList;		/*文具分类顺序表*/

/*文具信息的结构*/
typedef struct
{
	int SortNumber;			/*文具分类号*/
	char StockName[10];		/*文具名称*/
	int amount;				/*文具数量*/
}StockType;

typedef struct Node			/*结点*/
{
	StockType data;
	struct Node *next;
}LNode,*PNode,*LinkList;

typedef LinkList StockList;		/*文具链表*/

int InitList(LinkList *h)
{
	*h=(LinkList)malloc(sizeof(LNode));
	if(!h)
	{
		printf("初始化链表错误！\n");
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
		printf("插入位置不合法！\n");
		return 0;
	}
	q=(PNode)malloc(sizeof(LNode));
	if(!q)
	{
		printf("不能生成新结点\n");
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
		printf("删除位置不合法！\n");
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
	/*使用单链表的InitList操作初始化单链表*/
	if(!InitList(SL))	
	{
		printf("创建错误\n");
		return 0;
	}
	printf("请输入文具总数：\n");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf("请输入文具分类号：\n");
		scanf("%d",&sty.SortNumber);
		printf("请输入文具名称：\n");
		scanf("%s",&sty.StockName);
		printf("请输入文具数量：\n");
		scanf("%d",&sty.amount);
/*使用单链表的Insert操作在单链表中插入结点*/
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
	printf("请输入文具分类号：\n");
	scanf("%d",&sty.SortNumber);
	printf("请输入文具名：\n");
	scanf("%s",&sty.StockName);
	printf("请输入文具数量：\n");
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
	printf("请输入文具名：\n");
	scanf("%s",&sty.StockName);
	printf("请输入出库数量：\n");
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
	printf("请输入文具分类号：\n");
	scanf("%d",&no);
	//printf("请输入文具名：\n");
	//scanf("%s",name);
	//查询出所有该文具分类号的文具信息
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
		printf("顺序表已满，无法进行插入操作！");
		return 0;
	}
	if(pos<=0 || pos>L->length+1)
{
		printf("插入位置不合法，其取值范围应该是[1,length+1]");
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
	/*使用顺序表的InitList操作初始化顺序表*/
/*为了区分单链表的同名函数，把顺序表的InitList函数名改为InitList_Sq*/
	InitList_Sq(SL);			
	printf("请输入文具类别总数：\n");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf("请输入文具分类号：\n");
		scanf("%d",&sty.SortNumber);
		printf("请输入文具分类名称：\n");
		scanf("%s",&sty.SortName);
/*使用顺序表的Insert操作在顺序表中插入结点*/
/*为了区分单链表的同名函数，把顺序表的ListInsert函数名改为Insert_Sq*/
		ListInsert_Sq(SL,i+1,sty);
	}
	printf("\nOK...\n");
	return 1;
}


int AddSort(SortList *L)
{
	SortType st;
	printf("请输入文具分类号：\n");
	scanf("%d",&st.SortNumber);
	printf("请输入文具分类名：\n");
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
		printf("\n		文具店货品管理系统			\n");
		printf("\n------------------主菜单----------------------\n");
		printf("	(1) 设置文具分类表...		\n");
		printf("	(2) 初始化文具表...		\n");
		printf("	(3) 文具入库...		\n");
		printf("	(4) 文具出库...		\n");
		printf("	(5) 查询文具信息...		\n");
		printf("	(6) 显示文具信息...		\n");
		printf("	(7) 添加新文具类别...		\n");
		printf("	(0) 退出系统...		\n");
		printf("\n请选择(1,2,3,4,0)：");
		scanf("%d",&choice);
		if(choice<0 && choice>7) continue;		
		switch(choice)
		{ 
		case 1:CreateSortList(&L);break; /*初始化文具分类顺序表*/
		case 2:CreateStockList(&SL);break; /*初始化文具表*/
		case 3:AddStock(SL);break;	 /*文具入库*/
		case 4:RemoveStock(SL);break;/*文具出库*/
		case 5:QueryStock(SL);break;/*查询文具信息*/
		case 6:DispStock(SL);break;/*显示文具信息*/
		case 7:AddSort(&L);break;/*添加新文具类别*/
		case 0:exit(0); /*退出主程序*/
		default: break;
		}
	}while(1);	
	return 0;
}
