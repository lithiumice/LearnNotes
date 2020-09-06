#include "stdio.h"
#define LISTSIZE 100
typedef int DataType;
typedef struct 
{
	DataType item[LISTSIZE];
	int length;
}SqList;


int InitList(SqList *L)
{
	L -> length = 0;
	return 1;
}


int ListLength(SqList L)
{
	return L.length;
}


int ListEmpty(SqList L)//为空表则返回1
{
	if(L.length <= 0) return 1;
	else return 0;
}


int ListInsert(SqList *L, int pos, DataType item)
{
	int i;
	if (L -> length >=LISTSIZE)
	{
		printf("The list is full!\n");
		return 0;//失败则返回0
	}
	if (pos <= 0 || pos > L -> length + 1)
	{
		printf("the insert position is illegal!\n");
		return 0;
	}
	for (i = L -> length - 1; i >= pos - 1; i--)
	{
		L -> item[i + 1] = L -> item[i];
	}
	L -> item[pos - 1] = item;
	L -> length++; //表长增1
	return 1;
}


//item 返回被删除元素
//时间复杂度为O(n)
int ListDelete(SqList *L, int pos, DataType *item)
{
	int i;
	if (ListEmpty(*L))
	{
		printf("the list is empty, cannot delete!\n");
		return 0;
	}
	if (pos < 1 || pos > L -> length)
	{
		printf("delete position is illegle!\n");
		return 0;
	}
	*item = L -> item[pos - 1];
	for (i = pos; i <= L -> length - 1; i++)
	{
		L -> item[i - 1] = L -> item[i];
	}
	L -> length--;
	return 1;
}


int Find(SqList L, DataType item)
{
	int pos = 0;
	if (ListEmpty(L))
	{
		printf("the list is empty, cannot find!\n");
		return 0;
	}
	while (pos < L.length && L.item[pos] != item) pos++;
	if (pos < L.length) return pos++;
	else return 0;
}


int GetElem(SqList L, int pos, DataType *item)
{
	if (ListEmpty(L)) return 0;
	if (pos <= 0 || pos > L.length)
	{
		printf("illegal position!\n");
		return 0;
	}
	*item = L.item[pos - 1];
	return 1;
}


int TraverseList(SqList L)
{
	int i;
	for (i = 0; i < L.length; i++) printf("%d\t", L.item[i]);
	printf("\n");
	return 1;
}