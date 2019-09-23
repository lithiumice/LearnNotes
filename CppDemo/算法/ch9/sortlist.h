/*
     顺序表的基本操作
*/

#include<stdio.h>
#include "malloc.h"

/*顺序表的存储结构*/
#define MAXSIZE	100
typedef int KeyType;	/*关键字类型*/
typedef int DataType;
typedef struct{			/*数据元素类型*/
	KeyType key;			/*关键字*/
	DataType data;		/*其他数据*/
}SortItem , SqList[MAXSIZE];

void DispSort(SqList L,int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d\t",L[i].key);
}

/*算法9-1直接插入排序*/
void InsertSort(SqList L,int n)
{
	int i,j;
	SortItem p;
	for(i=1;i<n;i++)
	{
		p=L[i];
		for(j=i-1;j>=0 && p.key<L[j].key;j--)
				L[j+1]=L[j];		
		L[j+1]=p;
	}
}

/*算法9-2折半插入排序*/
void BiInsertSort(SqList L,int n)
{
	int i,j,low,upper,mid;
	SortItem p;
	for(i=1;i<n;i++)
	{
		p=L[i];
		low=0;
		upper=i-1;
		while(low<=upper)
		{
			mid=(low+upper)/2;
			if(p.key<L[mid].key)  upper=mid-1;
			else
				low=mid+1;
		}
		for(j=i-1;j>=low;j--)
			L[j+1]=L[j];		
		L[low]=p;
	}
}


/*算法9-3Shell排序*/
void ShellSort(SqList L,int n)
{
	int i,j,k;
	SortItem p;
	for(k=n/2;k>=1;k/=2)
	{
		for(i=k;i<n;i++)
		{
			p=L[i];			
			for(j=i-k;j>=0 && p.key<L[j].key;j-=k)
				L[j+k]=L[j];				
			L[j+k]=p;
		}
		for(i=0;i<n;i++)
			printf("%d\t",L[i].key);
		printf("\n\n");
	}	
}

/*算法9-4冒泡排序*/
void BubbleSort(SqList L,int n)
{
	int i,j,over;
	SortItem p;
	for(i=0;i<n-1;i++)
	{
		over=1;
		for(j=n-1;j>i;j--)
			if(L[j].key<L[j-1].key)
			{
				p=L[j];
				L[j]=L[j-1];
				L[j-1]=p;
				over=0;
			}
		if(over)
			break;
	}
}


/*算法9-5（b）划分*/
int Partition(SqList L,int i,int j)
{
	SortItem pivot;
	pivot=L[i];
	while(i<j)
	{
		while(i<j && pivot.key<=L[j].key)
			j--;
		if(i<j)
		{
			L[i]=L[j];
			i++;
		}
		while(i<j && pivot.key>L[i].key )
			i++;
		if(i<j)
		{
			L[j]=L[i];
			j--;
		}		
	}
	L[i]=pivot;	
	return i;
}



/*算法9-5（a）快速排序*/
void QuickSort(SqList L,int low,int upper)
{
	int pivot;
	if(low<upper)
	{
		pivot=Partition(L,low,upper);//DispSort(L,8);printf("\n\n");//显示每趟排序结果		
		QuickSort(L,low,pivot-1);
		QuickSort(L,pivot+1,upper);
		
	}
}



/*算法9-6直接选择排序*/
void SelectSort(SqList L,int n)
{
	int i,j,min;
	SortItem p;
	for(i=0;i<n-1;i++)
	{
		min=i;
		for(j=i+1;j<n;j++) 
			if(L[j].key<L[min].key)
				min=j;
		if(min!=i)
		{
			p=L[i];
			L[i]=L[min];
			L[min]=p;
		}
	}
}


/*算法9-7(a)Heap排序*/
void FilterHeap(SqList heap,int r,int upper)
{
	int child;
	SortItem p;
	child=2*r+1;
	p=heap[r];
	while(child<upper)
	{
		if(child+1<upper && heap[child+1].key>heap[child].key)
			child++;
		if(p.key<heap[child].key)
		{
			heap[(child-1)/2]=heap[child];			
			child=2*child+1;
		}
		else
			break;
	}
	heap[(child-1)/2]=p;
}


/*算法9-7(b)Heap排序*/
void HeapSort(SqList heap,int n)
{
	int i;
	SortItem p;	
	for(i=(n-1)/2;i>=0;i--)
		FilterHeap(heap,i,n);
	for(i=n-1;i>0;i--)
	{
		p=heap[0];
		heap[0]=heap[i];
		heap[i]=p;		
		FilterHeap(heap,0,i);
		DispSort(heap,n);
		printf("\n\n");
	}
}



/*算法9-8（a）二路归并*/
void MergeTwo(SqList L,int low,int mid,int upper)
{
	SortItem* p;
	int low1=low;
	int low2=mid+1;
	int pos=0;
	p=(SortItem*)malloc((upper-low+1)*sizeof(SortItem));
	while(low1<=mid && low2<=upper)
		p[pos++]=(L[low1].key<=L[low2].key) ? L[low1++] : L[low2++];
	for(;low1<=mid;low1++,pos++)
		p[pos]=L[low1];
	for(;low2<=upper;low2++,pos++)
		p[pos]=L[low2];
	for(pos=0,low1=low;low1<=upper;pos++,low1++)
		L[low1]=p[pos];
	free(p);
}



/*算法9-8（b）一趟归并排序*/
void Merge(SqList L,int len,int n)
{
	int i;
	for(i=0;i+2*len-1<n;i+=2*len)
		MergeTwo(L,i,i+len-1,i+2*len-1);
	if(i+len-1<n)
		MergeTwo(L,i,i+len-1,n-1);
	for(i=0;i<n;i++)
		printf("%d\t",L[i].key);
	printf("\n\n");
}



/*算法9-8（c）二路归并排序*/
void MergeSort(SqList L,int n)
{
	int i;
	for(i=1;i<n;i*=2)
		Merge(L,i,n);
}