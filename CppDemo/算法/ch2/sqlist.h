/*
     ˳���Ļ�������
*/

#include<stdio.h>

/*�洢�ṹ*/
#define LISTSIZE 100
typedef int DataType;

typedef struct
{
	DataType items[LISTSIZE];
	int length;
}SqList;


/*�㷨2-1��ʼ��˳���*/
int InitList(SqList *L)
{
	L->length=0;
	return 1;
}

/*�㷨2-2��˳���*/
int ListLength(SqList L)
{
	return L.length;
}

/*�㷨2-3�ж�˳����Ƿ�Ϊ��*/
int ListEmpty(SqList L)
{
	if(L.length<=0)
		return 1;
	else
		return 0;
}

/*�㷨2-4����*/
int ListInsert(SqList *L,int pos,DataType item)
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

/*�㷨2-5ɾ��*/
int ListDelete(SqList *L,int pos,DataType *item)
{
	int i;
	if(ListEmpty(*L))
	{
		printf("˳���Ϊ�ձ��޷�����ɾ��������");
		return 0; 
	}
	if(pos<1 || pos>L->length)
	{
		printf("ɾ��λ�ò��Ϸ�����ȡֵ��ΧӦ����[1,length]");
		return 0; 
	}
	*item=L->items[pos-1];
	for(i=pos;i<L->length;i++)
		L->items[i-1]=L->items[i];
	L->length--;
	return 1; 
}

/*�㷨2-6����ָ��Ԫ����˳����е�λ��*/
int Find(SqList L,DataType item)
{
	int pos=0;
	if(ListEmpty(L))
	{
		printf("˳���Ϊ�ձ��޷����в��Ҳ�����");
		return 0;
	}
	while(pos<L.length && L.items[pos]!=item)
		pos++;
	if(pos<L.length)
		return pos+1;
	else
		return 0;
}

/*�㷨2-7��ȡ˳�����ָ��λ���ϵ�����Ԫ��*/
int GetElem(SqList L,int pos,DataType *item)
{
	if(ListEmpty(L))
		return 0;
	if(pos<=0 || pos>L.length)
	{
		printf("λ����Ϣ���벻�Ϸ�������������");
		return 0;
	}
	*item=L.items[pos-1];
	return 1;
}

/*�㷨2-8����˳���*/
int TraverseList(SqList L)
{
	int i;
	for(i=0;i<L.length;i++)
		printf("%d\t",L.items[i]);
	printf("\n");
	return 1;
}
