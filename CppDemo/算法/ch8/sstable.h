/*
   静态查找表的基本操作
*/
#include "stdio.h"
#include "../sqlist.h"


/*算法8-1顺序查找*/
int SeqSearch(SqList L,DataType x)
{
	int i=L.length;	
	L.items[0].key=x.key;
	while(L.items[i].key!=x.key) i--;
	return i;
}

/*算法8-2折半查找*/
int BinarySearch(SqList L,DataType x)
{
	int low=0,upper=L.length-1,mid;
	while(low<=upper)
	{
		mid=(low+upper)/2;
		if(L.items[mid].key==x.key) return mid;
		if(L.items[mid].key<x.key)  low=mid+1;
		else
			upper=mid-1;
	}
	return -1;
}



