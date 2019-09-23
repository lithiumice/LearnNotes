#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main()
{
void sort(int* v,int m,int n);
void makearr(int* v,int m,int n);
void printarr(int** v,int m,int n);
	
	
	int m,n,i,**arr,*parr;
	scanf("%d%d",m,n);
	arr=(int **)malloc(sizeof(int*)*m);
	parr=(int *)malloc(sizeof(int)*m*n);
	arr[0]=&parr[0];
	for(i=1;i<m;i++)
	{
		arr[i]=arr[i-1]+n;
	}
	
	makearr(parr,m,n);
	sort(parr,m,n);
	printarr(arr,m,n);
	free(parr);
	free(arr);
	
	return 0;
}

void makearr(int* v,int m,int n)
{
	int i,j;
	srand((int)time(NULL));
	for(i=0;i<m;i++)
	for(j=0;j<n;j++)
	v[i*m+j]=rand()%100;
}

void printarr(int** v,int m,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	printf("%d",v[i][j]);
}

void sort(int* v,int m,int n)
{
	int i,j,t;
	for(i=0;i<n*m-1;i++)
		for(j=0;j<n*m-i-1;i++)
			if(v[j+1]<v[j])
				t=v[j],v[j]=v[j+1],v[j+1]=t;	
}
