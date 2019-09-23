/*
   线索二叉树的基本操作
*/
#include "malloc.h"
#include "stdio.h"
//#include "../bitreelink.h"

/*线索二叉树的存储结构*/
typedef char DataType;
typedef struct Node{
	DataType data;
	int lthread,rthread;
	struct Node *left,*right;
}TBNode,*PTBNode,*TBLink;



/*算法6-12线索化二叉树中除根结点以外的结点*/
void InOrderThread(PTBNode p,PTBNode *pre)
{
	if(p)
	{
		InOrderThread(p->left,pre);
		if(!p->left)
		{
			p->left=*pre;
			p->lthread=1;
		}
		else
			p->lthread=0;
		if(!p->right)
			p->rthread=1;
		else
			p->rthread=0;
		if(!(*pre)->right)
		{
			(*pre)->rthread=1;
			(*pre)->right=p;
		}
		else
			p->rthread=0;
		*pre=p;
		InOrderThread(p->right,pre);
	}
}



/*算法6-13线索化二叉树*/
void CreateInThread(TBLink *r,PTBNode p)
{	
	PTBNode pre=p;
	*r=(PTBNode)malloc(sizeof(TBNode));
	(*r)->lthread=0;
	(*r)->left=*r;
	if(p==NULL)
	{		
		(*r)->rthread=1;
		(*r)->right=*r;
	}
	else
	{		
		(*r)->left=p;				
		pre=*r;
		InOrderThread(p,&pre);
		pre->right=*r;
		pre->rthread=1;
		(*r)->right=pre;
	}
}

	

/*算法6-14取后继结点*/
PTBNode InOrderNext(PTBNode p)
{
	PTBNode q;
	q=p->right;
	if(p->rthread==0)
	{
		while(q->lthread==0)
			q=q->left;
	}
	return q;
}




/*算法6-15取前驱结点*/
PTBNode InOrderPrior(PTBNode p)
{
	PTBNode q;
	q=p->left;
	if(p->lthread==0)
	{
		while(q->rthread==0)
			q=q->right;
	}
	return q;
}



/*算法6-16遍历线索二叉树*/
void InThreadTraverse(TBLink r)
{
	PTBNode p=r->left;
	while(p->lthread==0)		/*寻找中序遍历的第一个结点*/
		p=p->left;
	while(p!=r)
	{
		printf("%c",p->data);	/*输出结点值*/
		p=InOrderNext(p);		/*寻找后继结点*/
		
	}
}



/*建立二叉树*/
TBLink CreateBiTree(char *nodes,int pos,int num)
{
	PTBNode p;
	if(nodes[pos]==' ' || pos>num)/*递归结束条件*/
		return NULL;
	p=(PTBNode)malloc(sizeof(TBNode));/*建立根（或子树根）结点*/
	if(!p){printf("初始化链表错误！\n");return 0;}
	p->data=nodes[pos];
	p->left=CreateBiTree(nodes,2*pos,num);/* 递归建立左子树*/
	p->right=CreateBiTree(nodes,2*pos+1,num);/* 递归建立右子树*/
	return p;
}


