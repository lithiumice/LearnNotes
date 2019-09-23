/*
     顺序表的基本操作
*/

#include<stdio.h>

/*存储结构*/
#define LISTSIZE 100
typedef int DataType;

typedef struct
{
	DataType items[LISTSIZE];
	int length;
}SqList;


/*算法2-1初始化顺序表*/
int InitList(SqList *L)
{
	L->length=0;
	return 1;
}

/*算法2-2求顺序表长*/
int ListLength(SqList L)
{
	return L.length;
}

/*算法2-3判断顺序表是否为空*/
int ListEmpty(SqList L)
{
	if(L.length<=0)
		return 1;
	else
		return 0;
}

/*算法2-4插入*/
int ListInsert(SqList *L,int pos,DataType item)
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

/*算法2-5删除*/
int ListDelete(SqList *L,int pos,DataType *item)
{
	int i;
	if(ListEmpty(*L))
	{
		printf("顺序表为空表，无法进行删除操作！");
		return 0; 
	}
	if(pos<1 || pos>L->length)
	{
		printf("删除位置不合法，其取值范围应该是[1,length]");
		return 0; 
	}
	*item=L->items[pos-1];
	for(i=pos;i<L->length;i++)
		L->items[i-1]=L->items[i];
	L->length--;
	return 1; 
}

/*算法2-6查找指定元素在顺序表中的位置*/
int Find(SqList L,DataType item)
{
	int pos=0;
	if(ListEmpty(L))
	{
		printf("顺序表为空表，无法进行查找操作！");
		return 0;
	}
	while(pos<L.length && L.items[pos]!=item)
		pos++;
	if(pos<L.length)
		return pos+1;
	else
		return 0;
}

/*算法2-7获取顺序表中指定位置上的数据元素*/
int GetElem(SqList L,int pos,DataType *item)
{
	if(ListEmpty(L))
		return 0;
	if(pos<=0 || pos>L.length)
	{
		printf("位置信息输入不合法，请重新输入");
		return 0;
	}
	*item=L.items[pos-1];
	return 1;
}

/*算法2-8遍历顺序表*/
int TraverseList(SqList L)
{
	int i;
	for(i=0;i<L.length;i++)
		printf("%d\t",L.items[i]);
	printf("\n");
	return 1;
}
