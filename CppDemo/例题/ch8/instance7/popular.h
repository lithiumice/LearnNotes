/*
   Hash��Ļ�������
*/
#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "stdlib.h"
//#include "time.h"


#define HASHSIZE 41
#define NULLKEY "\0"
/*typedef struct{
	int key;
}DataType;*/


/*
   �����������Ļ�������
*/
/*�����������Ĵ洢�ṹ*/
typedef int KeyType;
typedef struct{
	KeyType key;
	char pinyin[20];
	char name[10];
	char song[50];
	//clock_t date;
}DataType;

typedef struct Node{
	DataType data;				/*������*/
	struct Node* left,*right;	/*���Һ���ָ����*/
}BSTNode, *BSTree;

typedef struct{
	DataType data;
	//int offset;
}HashItem,HashTable[HASHSIZE];




/*hash����*/
int HashFunc(char key[])//
{
	int addr=0;
	int i=0;
	while(key[i]!='\0')
	{
		addr+=(int)key[i];
		i++;
	}
	return addr % HASHSIZE;
}

/*����̽��*/
int Collision(int d)
{
	return (d+1) % HASHSIZE;
}


/*�㷨8-7Hash����*/
int HashSearch(HashTable ht,DataType x)
{
	int addr;
	addr=HashFunc(x.pinyin);
	while(strcmp(ht[addr].data.pinyin,NULLKEY) && strcmp(ht[addr].data.pinyin,x.pinyin))//
		addr=Collision(addr);
	if(!strcmp(ht[addr].data.pinyin,x.pinyin))
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
	else
		ht[-addr].data=x;
	//ht[-addr].times=1;
	return 1;
}

/*�㷨8-9����Hash*/
void CreateHash(HashTable ht,DataType items[],int n)
{
	int i;
	for(i=0;i<HASHSIZE;i++)
	{
		strcpy(ht[i].data.pinyin,NULLKEY);
		//ht[i].times=0;
	}
	for(i=0;i<n;i++)
		HashInsert(ht,items[i]);
}

/*�㷨8-11��ʾHash*/
void DisplayHash(HashTable ht)
{
	int i;
	printf("\n��ϣ��\n��ϣ��ַ��\t");
	printf("\n�ؼ��֣�\t");
	for(i=0;i<HASHSIZE;i++)
		if(ht[i].data.pinyin!=NULLKEY)
			printf("%s\t",ht[i].data.pinyin);
		else
			printf("\t");	
	printf("\n");
}




/*�㷨8-3�����������Ĳ���*/
BSTNode* BSTSearch(BSTree r,DataType x)
{
	BSTNode *p;
	p=r;
	if(r==NULL) return NULL;
	while(p!=NULL)
	{
		if(p->data.key==x.key) return p;
		if(p->data.key<x.key) p=p->right;
		else
			p=p->left;
	}
	return NULL;
}


/*�㷨8-4�����������Ĳ���*/
void BSTInsert(BSTree *r,DataType x)
{
	BSTNode *p,*q=NULL;
	p=*r;
	while(p!=NULL)
	{
		q=p;
		if(p->data.key==x.key) return;
		if(p->data.key<x.key) p=p->right;
		else
			p=p->left;
	}
	p=(BSTNode*)malloc(sizeof(BSTNode));
	p->data=x;
	p->left=NULL;
	p->right=NULL;
	if(q==NULL)
	{
		*r=p;
		return;
	}
	if(q->data.key>x.key) q->left=p;
	else
		q->right=p;
}




/*��������������*/
void CreateBSTree(BSTree *r,DataType items[],int n)
{
	int i;
	*r=NULL;
	for(i=0;i<n;i++)
		BSTInsert(r,items[i]);
}

/*�����������������*/
void DisplayBST(BSTree r)
{
	if(!r) return;
	if(r->left!=NULL)
		DisplayBST(r->left);
	if(r->data.key>0)
		printf("\t%s[%d]\n",r->data.name,r->data.key);
	if(r->right!=NULL)
		DisplayBST(r->right);
}


int ReadBoard(char filename[],DataType items[])
{
	FILE *fp;
	int n=0;
	HashItem hi[HASHSIZE];
	fp=fopen(filename,"rb");
	if(fp==NULL)
	{
		printf("���ܴ��ļ�!");
		return -1;
	}
	while(!feof(fp))
	{
		fread(&hi[n],sizeof(HashItem),1,fp);
		items[n]=hi[n].data;
		n++;
	}	
	fclose(fp);
	return n;
}



int WriteBoard(char filename[],DataType x,long offset)
{
	FILE* fp;
	HashItem item;
	item.data=x;	
	fp=fopen(filename,"r+b");
	if(fp==NULL)
	{
		printf("���ܴ��ļ�!");
		return 0;
	}
	fseek(fp,offset*sizeof(HashItem),SEEK_SET);
	fwrite(&item,sizeof(HashItem),1,fp);	
	fclose(fp);
	return 1;
}




void CreateBoard(HashTable ht,char filename[])
{
	DataType items[HASHSIZE];
	int n=0;
	n=ReadBoard(filename,items);
	CreateHash(ht,items,n);
	//DisplayHash(ht);
}

void Vote(HashTable ht,char filename[],DataType x)
{
	int addr;	
	addr=HashSearch(ht,x);
	if(addr>0)
	{
		ht[addr].data.key++;		
		x=ht[addr].data;		
	}
	else
	{
		addr=-addr;
		//x.date=time(NULL);
		ht[addr].data=x;
	}
	
	WriteBoard(filename,x,addr);	
	printf("\n--OK!--\n\n");
}


void DispBoard(char filename[])
{
	BSTree r;
	int n=0;
	DataType items[HASHSIZE];
	n=ReadBoard(filename,items);
	CreateBSTree(&r,items,n);
	printf("\n\n\tʮ�����и������а�\n");
	printf("\t��������[��Ʊ��]\n");
	printf("------------------------------------\n");
	DisplayBST(r);
	printf("\n\n");
}

void DispVote(HashTable ht,DataType x)
{	
	int addr;	
	addr=HashSearch(ht,x);
	if(addr>=0)
		printf("\n\n����%s��Ʊ��Ϊ[%d]\n\n",ht[addr].data.name,ht[addr].data.key);
	else
		printf("\nû����Ҫ���ҵĸ���\n");
}

void DispSong(HashTable ht,DataType x)
{	
	int addr;	
	addr=HashSearch(ht,x);
	if(addr>=0)
		printf("\n\n����%s���������Ϊ[%s]\n\n",ht[addr].data.name,ht[addr].data.song);
	else
		printf("\nû����Ҫ���ҵĸ���\n");
}