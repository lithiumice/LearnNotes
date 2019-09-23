/*
   Hash表的基本操作
*/
#include "stdio.h"
#include "math.h"

#define HASHSIZE 13
#define DELFLAG -1

typedef struct{
	int key;
}DataType;
typedef struct{
	DataType data;
	int times;
}HashTable[HASHSIZE];

/*hash函数*/
int HashFunc(int key)
{
	return key % HASHSIZE;
}

/*线性探查*/
int Collision(int d)
{
	return (d+1) % HASHSIZE;
}

/*平方探查*/
int Collision2(int d,int i)
{
	return (int)(d+pow(-1,i-1)*i*i) % HASHSIZE;
}



/*算法8-7Hash查找*/
int HashSearch(HashTable ht,DataType x)
{
	int addr;
	addr=HashFunc(x.key);
	while(ht[addr].data.key!=NULL && ht[addr].data.key!=x.key)
		addr=Collision(addr);
	if(ht[addr].data.key==x.key)
		return addr;
	else
		return -addr;
}

/*算法8-8Hash插入*/
int HashInsert(HashTable ht,DataType x)
{
	int addr;
	addr=HashSearch(ht,x);
	if(addr>0) return 0;
	ht[-addr].data=x;
	ht[-addr].times=1;
	return 1;
}

/*算法8-9创建Hash*/
void CreateHash(HashTable ht,DataType items[],int n)
{
	int i;
	for(i=0;i<HASHSIZE;i++)
	{
		ht[i].data.key=NULL;
		ht[i].times=0;
	}
	for(i=0;i<n;i++)
		HashInsert(ht,items[i]);
}

/*算法8-11显示Hash*/
void DisplayHash(HashTable ht)
{
	int i;
	printf("\n哈希表\n哈希地址：\t");
	for(i=0;i<HASHSIZE;i++)
		printf("%d\t",i);
	printf("\n关键字：\t");
	for(i=0;i<HASHSIZE;i++)
		if(ht[i].data.key!=NULL)
			printf("%d\t",ht[i].data.key);
		else
			printf("\t");	
	printf("\n");
}

/*算法8-10Hash删除*/
int HashDelete(HashTable ht,DataType x)
{
	int addr;
	addr=HashSearch(ht,x);
	if(addr>=0)
	{
		ht[addr].data.key=DELFLAG;
		return 1;
	}
	return 0;
}
