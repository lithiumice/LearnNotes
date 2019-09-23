/*
   �����������Ļ�������
*/
#include "stdio.h"
#include "malloc.h"

/*�����������Ĵ洢�ṹ*/
typedef int KeyType;
typedef struct{
	KeyType key;
}DataType;

typedef struct Node{
	DataType data;				/*������*/
	struct Node* left,*right;	/*���Һ���ָ����*/
}BSTNode, *BSTree;

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


/*�㷨8-5������������ɾ��*/
void BSTDelete(BSTree *r,DataType x)
{
	BSTNode *p,*q=NULL,*s;
	p=*r;
	while(p!=NULL && p->data.key!=x.key)
	{
		q=p;
		if(p->data.key<x.key)  p=p->right;
		else
			p=p->left;
	}
	if(p==NULL) return;
	s=p;
	if(s->left && s->right)     
	{		
		q=s;p=s->left;
		while(p->right!=NULL)
		{
			q=p;
			p=p->right;
		}
		if(p!=s) 
			s->data=p->data; 
	}	
    s=(p->left)?p->left:p->right;
    if(!q) 
      *r=s;
    else{ 
      if(q->left==p) 
        q->left=s; 
      else q->right=s;      
     } 
    free(p);
  } 





/*��������������*/
void CreateBSTree(BSTree *r,DataType items[],int n)
{
	int i;
	for(i=0;i<n;i++)
		BSTInsert(r,items[i]);
}

/*�����������������*/
void DisplayBST(BSTree r)
{
	if(!r) return;
	if(r->left!=NULL)
		DisplayBST(r->left);
	printf("%d\t",r->data.key);
	if(r->right!=NULL)
		DisplayBST(r->right);
}