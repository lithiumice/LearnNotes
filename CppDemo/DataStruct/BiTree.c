#include <malloc.h>
#include <stdio.h>

#define MAXSIZE 100
typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node *left, *right;
}BTNode, *PBTNode, *BiTreeLink;


/****************************
*Function: CreateBiTree
*Description: create bi tree
*Params: @char *nodes: the string
*		 @int pos
*		 @int num
*Return: BiTreeLink
*****************************/
BiTreeLink CreateBiTree(char *nodes, int pos, int num)
{
	PBTNode p;
	if(nodes[pos] == "" || pos > num)
		return NULL;
	p = (PBTNode)malloc(sizeof(BTNode));
	if(!p)
	{
		printf("error while initialization!\n");
		return 0;
	}
	p -> data = nodes[pos];
	p -> left = CreateBiTree(nodes, 2*pos, num);
	p -> right = CreateBiTree(nodes, 2*pos + 1, num);
	return p;
}


/****************************
*Function: DispBiTree
*Description: create bi tree
*Params: @BiTreeLink root
*Return: NULL
*****************************/
void DispBiTree(BiTreeLink root)
{
	int front, rear;
	PBTNode queue[MAXSIZE];
	PBTNode p;
	if(root == NULL)
		return;
	queue[0] = root;
	front = 0;
	rear = 1;
	while(front < rear)
	{
		p = queue[front];
		front = (front + 1)%MAXSIZE;
		if(p == NULL)
			printf("( )");
		else
		{
			printf("(%c)", p -> data);		
			queue[rear] = p -> left;
			rear = (rear + 1)%MAXSIZE;
			queue[rear] = p -> right;
		}		
	}
}


/****************************
*Function: InsertRight
*Description: insert right node
*Params: @PBTNode r
*		 @DataType x
*Return: PBTNode
*****************************/
PBTNode InsertRight(PBTNode r, DataType x)
{
	PBTNode p;
	if(!r)
		return NULL;
	p = (PBTNode)malloc(sizeof(BTNode));
	p -> data = x;
	p -> left = NULL;
	p -> right = r -> right;
	r ->right = p;
	return p;
}


/****************************
*Function: InsertLeft
*Description: insert left node
*Params: @PBTNode r
*		 @DataType x
*Return: PBTNode
*****************************/
PBTNode InsertLeft(PBTNode r, DataType x)
{
	PBTNode p;
	if(!r)
		return NULL;
	p = (PBTNode)malloc(sizeof(BTNode));
	p -> data = x;
	p -> right = NULL;
	p -> left = r -> left;
	r ->left = p;
	return p;
}


/****************************
*Function: ReleaseTree
*Description: release all the nodes behind
*Params: @PBTNode *r
*Return: NULL
*****************************/
void ReleaseTree(PBTNode *r)
{
	if(*r)
	{
		ReleaseTree(&(*r) -> left);
		ReleaseTree(&(*r) -> right);
		free(*r);
	}
}


void DeleteRight(PBTNode r)
{
	if(!r)
		return;
	ReleaseTree(&r -> right);
	r -> right = NULL;
}


void DeleteLeft(PBTNode r)
{
	if(!r)
		return;
	ReleaseTree(&r -> left);
	r -> left = NULL;
}


void PreOrder(BiTreeLink r)
{
	if(r != NULL)
	{
		printf("%c\t", r -> data);
		PreOrder(r -> left);
		PreOrder(r -> right);
	}
}


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


void InOrder(BiTreeLink r)
{
	if(r!=NULL)
	{
		InOrder(r->left);
		printf("%c",r->data);
		InOrder(r->right);
	}

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


void PostOrder(BiTreeLink r)
{
	if(r != NULL)
	{
		PostOrder(r -> left);		
		PostOrder(r -> right);
		printf("%c", r -> data);
	}
}


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


/****************************
*Function: BiTreeCount
*Description: count the number of all nodes
*Params: @BiTreeLink r
*Return: int
*****************************/
int BiTreeCount(BiTreeLink r)
{
	if(r == NULL) 
		return 0;
	else
		return BiTreeCount(r -> left) + BiTreeCount(r -> right) + 1;
}


/****************************
*Function: BiTreeDepth
*Description: count the depth of bitree
*Params: @BiTreeLink r
*Return: int
*****************************/
int BiTreeDepth(BiTreeLink r)
{
	int ld, rd;
	if(r == NULL)
		return 0;
	else
	{
		ld = BiTreeDepth(r -> left);
		rd = BiTreeDepth(r -> right);
		return ld > rd ? ld + 1: rd + 1;
	}
}


/****************************
*Function: FindNode
*Description: find the node of given data
*Params: @BiTreeLink r
*		 @DataType x
*Return: PBTNode
*****************************/
PBTNode FindNode(BiTreeLink r,DataType x)
{
	PBTNode p;
	if(r == NULL)
		return NULL;
	if(r -> data == x)
		return r;
	p=FindNode(r -> left, x);
	if(p)  
		return p;
	else
		return FindNode(r->right,x);
}
