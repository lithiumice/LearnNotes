/*
   �������Ļ�������
*/
#include "malloc.h"
#include "stdio.h"

#define MAXSIZE 100

/*��������Ĵ洢�ṹ*/
typedef char DataType;
typedef struct Node
{
	DataType data;
	struct Node *left;
	struct Node *right;
}BTNode,*PBTNode,*BiTreeLink;

/*�㷨6-1����������*/
BiTreeLink CreateBiTree(char *nodes,int pos,int num)
{
	PBTNode p;
	if(nodes[pos]==' ' || pos>num)
		return NULL;
	p=(PBTNode)malloc(sizeof(BTNode));
	if(!p)
	{
		printf("��ʼ���������\n");
		return 0;
	}
	p->data=nodes[pos];
	p->left=CreateBiTree(nodes,2*pos,num);
	p->right=CreateBiTree(nodes,2*pos+1,num);
	return p;
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
		p=queue[front++];
		if(p==NULL)
			printf("( )");
		else
			printf("(%c)",p->data);
		if(p!=NULL)
		{
			queue[rear++]=p->left;		
			queue[rear++]=p->right;
		}
	}
}
	

/*�㷨6-3ǰ�����*/
void PreOrder(BiTreeLink r)
{
	if(r!=NULL)
	{
		printf("%c",r->data);
		PreOrder(r->left);
		PreOrder(r->right);
	}
}


/*�㷨6-4ǰ������ǵݹ��㷨*/
void NonPreOrder(BiTreeLink r)
{
	PBTNode stack[MAXSIZE],p;
	int top=-1;
	p=r;
	while(p || top>-1)
	{
		if(p)
		{
			printf("%c",p->data);
			stack[++top]=p;
			p=p->left;
			
		}
		else
		{
			p=stack[top--];			
			p=p->right;			
		}
	}
}


/*�㷨6-5�������*/
void InOrder(BiTreeLink r)
{
	if(r!=NULL)
	{
		InOrder(r->left);
		printf("%c",r->data);
		InOrder(r->right);
	}
}

/*�㷨6-6��������ǵݹ��㷨*/
void NonInOrder(BiTreeLink r)
{
	PBTNode stack[MAXSIZE],p;
	int top=-1;
	p=r;
	while(p || top>-1)
	{
		if(!p)
		{
			p=stack[top--];
			printf("%c",p->data);
			p=p->right;
		}
		else
		{
			stack[++top]=p;
			p=p->left;
		}
	}
}


/*�㷨6-7�������*/
void PostOrder(BiTreeLink r)
{
	if(r!=NULL)
	{
		PostOrder(r->left);		
		PostOrder(r->right);
		printf("%c",r->data);
	}
}


/*�㷨6-8��������ǵݹ��㷨*/
void NonPostOrder(BiTreeLink r)
{   
	PBTNode stack[MAXSIZE],p;
	int flags[MAXSIZE];
	int top=-1;
	int flag;
	p=r;
    do
    { 
		if(p)
		{  
			flag=0;			
			stack[++top]=p;	
			flags[top]=flag;
			p=p->left;
		}
		else
		{  
			flag=flags[top];
			p=stack[top--];
			if(flag==0)
			{  
				flag=1;	
				stack[++top]=p;
				flags[top]=flag;
				p=p->right;
			}
			else
			{  
				printf("%c",p->data);
				p=NULL;
			}
		}
    }while(p||top>-1);
} 


/*�㷨6-9ͳ�ƶ������н�����*/
int BiTreeCount(BiTreeLink r)
{
	if(r==NULL) return 0;
	else
		return BiTreeCount(r->left)+BiTreeCount(r->right)+1;
}


/*�㷨6-10������������*/
int BiTreeDepth(BiTreeLink r)
{
	int ld,rd;
	if(r==NULL)
		return 0;
	else
	{
		ld=BiTreeDepth(r->left);
		rd=BiTreeDepth(r->right);
		return ld>rd ? ld+1 : rd+1;
	}
}


/*�㷨6-11���Ҷ�������ֵΪx�Ľ��*/
PBTNode FindNode(BiTreeLink r,DataType x)
{
	PBTNode p;
	if(r==NULL)
		return NULL;
	if(r->data==x)
		return r;
	p=FindNode(r->left,x);
	if(p)  return p;
	else
		return FindNode(r->right,x);
}
