#include "stdio.h"
#include "stdlib.h"
#include "time.h"
int main()
{
	void PrintArray(int** v, int m , int n);
	void MakeArray(int** v, int m , int n);
	int i , row , col ,**pArr;
	printf("input row and col:");
	scanf("%d,%d",&row, &col);
	pArr=( int ** )malloc(row*sizeof(int*));
	for(i=0;i<row;i++)
		{
			pArr[i]=(int *)malloc(col*sizeof(int));
		}
	MakeArray(pArr,row,col);
	PrintArray(pArr,row,col);
	for(i=0;i<row;i++)
		{
			free(pArr[i]);
		}
	free(pArr);
	return 0;
}

void MakeArray(int** v, int m , int n)
{
	int i,j;
	srand((int)time(NULL));
	for(i=0;i<m;i++) 
	{
		for(j=0;j<n;j++)
		{
			v[i][j]=rand()%1000;
		 } 
	} 
}
void PrintArray(int** v, int m , int n)
{
	int i,j;
	for(i=0;i<m;i++) 
	{
		for(j=0;j<n;j++)
		{
			printf("%3d\t",v[i][j]);
		 } 
		 printf("\n");
	} 
 } 
 
 
 
