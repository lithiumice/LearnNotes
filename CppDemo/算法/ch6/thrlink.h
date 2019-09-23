/*
   �����������Ļ�������
*/
#include "malloc.h"
#include "stdio.h"
//#include "../bitreelink.h"

/*�����������Ĵ洢�ṹ*/
typedef char DataType;
typedef struct Node{
	DataType data;
	int lthread,rthread;
	struct Node *left,*right;
}TBNode,*PTBNode,*TBLink;



/*�㷨6-12�������������г����������Ľ��*/
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



/*�㷨6-13������������*/
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

	

/*�㷨6-14ȡ��̽��*/
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




/*�㷨6-15ȡǰ�����*/
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



/*�㷨6-16��������������*/
void InThreadTraverse(TBLink r)
{
	PTBNode p=r->left;
	while(p->lthread==0)		/*Ѱ����������ĵ�һ�����*/
		p=p->left;
	while(p!=r)
	{
		printf("%c",p->data);	/*������ֵ*/
		p=InOrderNext(p);		/*Ѱ�Һ�̽��*/
		
	}
}



/*����������*/
TBLink CreateBiTree(char *nodes,int pos,int num)
{
	PTBNode p;
	if(nodes[pos]==' ' || pos>num)/*�ݹ��������*/
		return NULL;
	p=(PTBNode)malloc(sizeof(TBNode));/*���������������������*/
	if(!p){printf("��ʼ���������\n");return 0;}
	p->data=nodes[pos];
	p->left=CreateBiTree(nodes,2*pos,num);/* �ݹ齨��������*/
	p->right=CreateBiTree(nodes,2*pos+1,num);/* �ݹ齨��������*/
	return p;
}


