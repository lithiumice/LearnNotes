/*
   ��У���Ź���ϵͳ
*/
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXSIZE 100

/*���ݽṹ*/
typedef struct Info{
	int type;				/*���ͣ�0Ϊ���ţ�1Ϊ���ų�Ա*/
	char name[20]; 		/*���ƻ�����*/
	char date[11]; 		/*�������ڻ��������*/
	char phone[11];		/*��ϵ�绰*/
	char duty[10];		/*ְ��*/
}DataType;

typedef struct Node
{
	DataType data;
	struct Node *left;
	struct Node *right;
}BTNode,*PBTNode,*BiTreeLink;



PBTNode FindName(BiTreeLink r,DataType x)/*�������ͺ����ƽ��в��ң��ҵ��򷵻ظý��*/
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


/*�㷨6-3�����Һ���*/
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

PBTNode InsertLeft(PBTNode r,DataType x)/*������ĺ��Ӳ����ڣ�����룬����Ӧ����Ϊ��һ���ӽ����ֵܲ���*/
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

/*�����ֵ�*/
void InsertSilbling(BiTreeLink r,DataType x,DataType y)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL)
	{
		printf("����λ�ò���ȷ");
		return;
	}
	InsertRight(p,y);	
}

/*���뺢��*/
void InsertChild(BiTreeLink r,DataType x,DataType y)
{
	PBTNode p;
	p=FindName(r,x);
	if(p==NULL)
	{
		printf("����λ�ò���ȷ");
		return;
	}
	InsertLeft(p,y);	
}


/*�㷨6-2��ʾ������*/
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
	DataType items[]={{0,"����","2007-01-01","12345"," "},{0,"����","2000-01-01","34567"," "},{0,"����","2008-01-11","45678"," "},{1,"����","1990-11-11","13567","�᳤"},{1,"����","1989-01-11","13756","��Ա"},{1,"����","1988-11-11","133456","���᳤"},{0,"���Ź���ίԱ��","1980-01-01","23698"," "}};
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
		printf("�޸�λ�ò���ȷ");
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

/*�㷨6-5��������*/
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
		printf("ɾ��λ�ò���ȷ");
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
		printf("ɾ��λ�ò���ȷ");
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


