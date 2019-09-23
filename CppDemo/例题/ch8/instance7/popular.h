/*
   Hash表的基本操作
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
   二叉排序树的基本操作
*/
/*二叉排序树的存储结构*/
typedef int KeyType;
typedef struct{
	KeyType key;
	char pinyin[20];
	char name[10];
	char song[50];
	//clock_t date;
}DataType;

typedef struct Node{
	DataType data;				/*数据域*/
	struct Node* left,*right;	/*左右孩子指针域*/
}BSTNode, *BSTree;

typedef struct{
	DataType data;
	//int offset;
}HashItem,HashTable[HASHSIZE];




/*hash函数*/
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

/*线性探查*/
int Collision(int d)
{
	return (d+1) % HASHSIZE;
}


/*算法8-7Hash查找*/
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

/*算法8-8Hash插入*/
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

/*算法8-9创建Hash*/
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

/*算法8-11显示Hash*/
void DisplayHash(HashTable ht)
{
	int i;
	printf("\n哈希表\n哈希地址：\t");
	printf("\n关键字：\t");
	for(i=0;i<HASHSIZE;i++)
		if(ht[i].data.pinyin!=NULLKEY)
			printf("%s\t",ht[i].data.pinyin);
		else
			printf("\t");	
	printf("\n");
}




/*算法8-3二叉排序树的查找*/
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


/*算法8-4二叉排序树的插入*/
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




/*创建二叉排序树*/
void CreateBSTree(BSTree *r,DataType items[],int n)
{
	int i;
	*r=NULL;
	for(i=0;i<n;i++)
		BSTInsert(r,items[i]);
}

/*中序遍历二叉排序树*/
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
		printf("不能打开文件!");
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
		printf("不能打开文件!");
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
	printf("\n\n\t十大流行歌手排行榜\n");
	printf("\t歌手名字[得票数]\n");
	printf("------------------------------------\n");
	DisplayBST(r);
	printf("\n\n");
}

void DispVote(HashTable ht,DataType x)
{	
	int addr;	
	addr=HashSearch(ht,x);
	if(addr>=0)
		printf("\n\n歌手%s的票数为[%d]\n\n",ht[addr].data.name,ht[addr].data.key);
	else
		printf("\n没有你要查找的歌手\n");
}

void DispSong(HashTable ht,DataType x)
{	
	int addr;	
	addr=HashSearch(ht,x);
	if(addr>=0)
		printf("\n\n歌手%s的主打歌曲为[%s]\n\n",ht[addr].data.name,ht[addr].data.song);
	else
		printf("\n没有你要查找的歌手\n");
}