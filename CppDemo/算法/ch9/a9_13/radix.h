/*
     顺序表的基本操作
*/

#include<stdio.h>
#include "malloc.h"
#include "linkqueue.h"


int digit(KeyType key,int m,int r)
{
	int i,d;
	if(m==0) return key % r;
	d=r;
	for(i=1;i<m;i++)
		d*=r;
	return ((int)(key /d) % r);
}


/*算法9-9 基数排序*/
void RadixSort(DataType L[],int n,int m,int r)
{
	LinkQueue* q;
	int i,j,k;
	q=(LinkQueue*)malloc(r*sizeof(LinkQueue));
	for(i=0;i<r;i++)
		InitQueue(&q[i]);
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			k=digit(L[j].key,i,r);
			EnQueue(&q[k],L[j]);
		}
		k=0;
		for(j=0;j<r;j++)
			for(;!QueueEmpty(q[j]);k++)
				DeQueue(&q[j],&(L[k]));
		for(j=0;j<n;j++)
			printf("%d\t",L[j].key);
		printf("\n\n");
	}
	for(i=0;i<r;i++)
		DestroyQueue(q);
}
