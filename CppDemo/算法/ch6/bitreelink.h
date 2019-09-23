/*
   二叉树的基本操作
*/
#include "malloc.h"
#include "stdio.h"

#define MAXSIZE 100

/*二叉链表的存储结构*/
typedef char DataType;
typedef struct Node
{
	DataType data;
	struct Node *left;
	struct Node *right;
}BTNode,*PBTNode,*BiTreeLink;

/*算法6-1创建二叉树*/
BiTreeLink CreateBiTree(char *nodes,int pos,int num)
{
	PBTNode p;
	if(nodes[pos]==' ' || pos>num)
		return NULL;
	p=(PBTNode)malloc(sizeof(BTNode));
	if(!p)
	{
		printf("初始化链表错误！\n");
		return 0;
	}
	p->data=nodes[pos];
	p->left=CreateBiTree(nodes,2*pos,num);
	p->right=CreateBiTree(nodes,2*pos+1,num);
	return p;
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
			printf("(%c)",p->data);		
			queue[rear]=p->left;
			rear=(rear+1)%MAXSIZE;
			queue[rear]=p->right;
			rear=(rear+1)%MAXSIZE;
		}		
	}
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


/*算法6-4删除右子树*/
void DeleteRight(PBTNode r)
{
	if(!r) return;
	ReleaseTree(&r->right);
	r->right=NULL;	
}



/*算法6-6前序遍历*/
void PreOrder(BiTreeLink r)
{
	if(r!=NULL)
	{
		printf("%c",r->data);
		PreOrder(r->left);
		PreOrder(r->right);
	}
}


/*算法6-7前序遍历非递归算法*/
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


/*算法6-8中序遍历*/
void InOrder(BiTreeLink r)
{
	if(r!=NULL)
	{
		InOrder(r->left);
		printf("%c",r->data);
		InOrder(r->right);
	}
}

/*算法6-9中序遍历非递归算法*/
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


/*算法6-10后序遍历*/
void PostOrder(BiTreeLink r)
{
	if(r!=NULL)
	{
		PostOrder(r->left);		
		PostOrder(r->right);
		printf("%c",r->data);
	}
}


/*算法6-11后序遍历非递归算法*/
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


/*算法6-12统计二叉树中结点个数*/
int BiTreeCount(BiTreeLink r)
{
	if(r==NULL) return 0;
	else
		return BiTreeCount(r->left)+BiTreeCount(r->right)+1;
}


/*算法6-13求二叉树的深度*/
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


/*算法6-14查找二叉树中值为x的结点*/
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
