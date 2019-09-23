/*
   Hash��Ļ�������
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

/*hash����*/
int HashFunc(int key)
{
	return key % HASHSIZE;
}

/*����̽��*/
int Collision(int d)
{
	return (d+1) % HASHSIZE;
}

/*ƽ��̽��*/
int Collision2(int d,int i)
{
	return (int)(d+pow(-1,i-1)*i*i) % HASHSIZE;
}



/*�㷨8-7Hash����*/
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

/*�㷨8-8Hash����*/
int HashInsert(HashTable ht,DataType x)
{
	int addr;
	addr=HashSearch(ht,x);
	if(addr>0) return 0;
	ht[-addr].data=x;
	ht[-addr].times=1;
	return 1;
}

/*�㷨8-9����Hash*/
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

/*�㷨8-11��ʾHash*/
void DisplayHash(HashTable ht)
{
	int i;
	printf("\n��ϣ��\n��ϣ��ַ��\t");
	for(i=0;i<HASHSIZE;i++)
		printf("%d\t",i);
	printf("\n�ؼ��֣�\t");
	for(i=0;i<HASHSIZE;i++)
		if(ht[i].data.key!=NULL)
			printf("%d\t",ht[i].data.key);
		else
			printf("\t");	
	printf("\n");
}

/*�㷨8-10Hashɾ��*/
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
