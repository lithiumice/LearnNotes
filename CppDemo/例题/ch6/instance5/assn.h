/*
   高校社团管理系统
*/
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXSIZE 100

/*数据结构*/
typedef struct Info{
	int type;				/*类型，0为社团，1为社团成员*/
	char name[20]; 		/*名称或姓名*/
	char date[11]; 		/*成立日期或出生日期*/
	char phone[11];		/*联系电话*/
	char duty[10];		/*职务*/
}DataType;

typedef struct Node
{
	DataType data;
	struct Node *left;
	struct Node *right;
}BTNode,*PBTNode,*BiTreeLink;



PBTNode FindName(BiTreeLink r,DataType x)/*根据类型和名称进行查找，找到则返回该结点*/
{
	PBTNode p;
	if(r==NULL)
		return NULL;
	if(!strcmp(r->data.name,x.name) && r->data.type==x.type)
		return r;
	p=FindName(r->left,x);
	if(p)  return p;
	else
		return FindName(r->right,x);
}


/*算法6-3插入右孩子*/
PBTNode InsertRight(PBTNode r,DataType x)
{
	PBTNode p;
	if(!r) return NULL;
	p=(PBTNode)malloc(sizeof(BTNode));
	p->data=x;
	p->left=NULL;
	p->right=r->right;
	r->right=p;
	return p;
}

PBTNode InsertLeft(PBTNode r,DataType x)/*如果结点的孩子不存在，则插入，否则应该作为第一个子结点的兄弟插入*/
{
	PBTNode p;
	if(!r) return NULL;
	if(r->left==NULL)
	{
		p=(PBTNode)malloc(sizeof(BTNode));
		p->data=x;
		p->left=NULL;
		p->right=NULL;
		r->left=p;
	}
	else
		p=InsertRight(r->left,x);
	return p;
}

/*插入兄弟*/
void InsertSilbling(BiTreeLink r,DataType x,DataType y)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL)
	{
		printf("插入位置不正确");
		return;
	}
	InsertRight(p,y);	
}

/*插入孩子*/
void InsertChild(BiTreeLink r,DataType x,DataType y)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL)
	{
		printf("插入位置不正确");
		return;
	}
	InsertLeft(p,y);	
}


/*算法6-2显示二叉树*/
void DispBiTree(BiTreeLink root)
{
	int front,rear;
	PBTNode queue[MAXSIZE];
	PBTNode p;
	if(root==NULL)
		return;
	queue[0]=root;
	front=0;
	rear=1;
	while(front<rear)
	{
		p=queue[front];
		front=(front+1)%MAXSIZE;
		if(p==NULL)
			printf("( )");
		else
		{
			printf("(%d,%s)",p->data.type,p->data.name);		
			queue[rear]=p->left;
			rear=(rear+1)%MAXSIZE;
			queue[rear]=p->right;
			rear=(rear+1)%MAXSIZE;
		}		
	}
}



void InitBiTree(BiTreeLink *root)
{
	DataType items[]={{0,"足球","2007-01-01","12345"," "},{0,"武术","2000-01-01","34567"," "},{0,"桥牌","2008-01-11","45678"," "},{1,"张三","1990-11-11","13567","会长"},{1,"李四","1989-01-11","13756","会员"},{1,"王五","1988-11-11","133456","副会长"},{0,"社团管理委员会","1980-01-01","23698"," "}};
	*root=(PBTNode)malloc(sizeof(BTNode));
	(*root)->left=NULL;
	(*root)->right=NULL;		
	(*root)->data=items[6];
	InsertChild(*root,items[6],items[1]);
	InsertSilbling(*root,items[6],items[5]);
	InsertChild(*root,items[1],items[3]);
	InsertSilbling(*root,items[1],items[2]);
	InsertSilbling(*root,items[3],items[4]);
	InsertChild(*root,items[2],items[4]);
	InsertSilbling(*root,items[2],items[0]);
	InsertChild(*root,items[0],items[5]);	
}

void Update(BiTreeLink r,DataType x,DataType y)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL)
	{
		printf("修改位置不正确");
		return;
	}
	p->data=y;
	printf("\n--OK--\n");
}


void Receive(char prn[],char data[])
{
	flushall();
	printf(prn);
	gets(data);
}

/*算法6-5销毁子树*/
void ReleaseTree(PBTNode *r)
{
	if(*r)
	{
		ReleaseTree(&(*r)->left);	
		ReleaseTree(&(*r)->right);
		free(*r);
	}
}


void DeleteChild(BiTreeLink r,DataType x)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL)
	{
		printf("删除位置不正确");
		return;
	}
	ReleaseTree(&p->left);
	p->left=NULL;
}

void DeleteSilbling(BiTreeLink r,DataType x)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL)
	{
		printf("删除位置不正确");
		return;
	}
	ReleaseTree(&p->right);
	p->right=NULL;
}

void DispNode(BiTreeLink r,DataType x)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL) return;
	printf("\n\n------Information--------\n");
	printf("*\tType:%d\t\t*\n*\tName:%s\t*\n*\tPhon:%s\t*",p->data.type,p->data.name,p->data.phone);
	printf("\n-------------------------\n");
}


