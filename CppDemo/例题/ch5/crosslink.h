
#include <stdio.h>
#include <malloc.h>
#define DataType int 
/*ʮ������Ľṹ���Ͷ������£�*/
typedef struct node
{	
	int row,col;        /*����Ԫ�ص��к����±�*/
	DataType value;
	struct node *right;  /*����Ԫ�������б��б�ĺ������*/
	struct node *down; 
}CNode, *PCNode;

typedef struct 
{	
	PCNode *rhead;  /*�С��������ͷָ������*/
	PCNode *chead;
	int rows,cols,nums;               /*ϡ����������������������Ԫ�صĸ���*/
}*CrossLink;

/*�㷨5-6 ��ʼ��ʮ������*/
int InitCrossLink(CrossLink* CL,DataType *A,int r,int c)
{
	int i,j;
	PCNode p,q;	
	(*CL)=(CrossLink)malloc(sizeof(CrossLink));
	if(!(*CL)->rhead){printf("�޷�����ʮ������");return 0;}
	(*CL)->rows=r;
	(*CL)->cols=c;
	(*CL)->nums=0;
	(*CL)->rhead=(PCNode*)malloc(r*sizeof(PCNode));/*������ָ������*/
	if(!(*CL)->rhead){printf("�޷�������ָ������");return 0;}
	for(i=0;i<r;i++)	/*��ʼ����ָ������*/
		(*CL)->rhead[i]=NULL;
	(*CL)->chead=(PCNode*)malloc(c*sizeof(PCNode));/*������ָ������*/
	if(!(*CL)->chead){printf("�޷�������ָ������");return 0;}
	for(i=0;i<c;i++)	/*��ʼ����ָ������*/
		(*CL)->chead[i]=NULL;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			if(A[i*c+j]!=0)
			{
				p=(PCNode)malloc(sizeof(CNode));
				p->row=i+1;
				p->col=j+1;
				p->value=A[i*c+j];
				p->right=NULL;
				p->down=NULL;
				(*CL)->nums++;
				if((*CL)->rhead[i]!=NULL)/*���������в���*/
				{
					q=(*CL)->rhead[i];
					while(q->right!=NULL && q->col<j+1)  /*Ѱ���������еĲ���λ��*/
						q=q->right;
					p->right=q->right;/*����*/
					q->right=p;
				}
				else/*������ĵ�һ�����*/
					(*CL)->rhead[i]=p;
				if((*CL)->chead[j]!=NULL)/*���������в���*/
				{
					q=(*CL)->chead[j];
					while(q->down!=NULL && q->row<i+1)	/*Ѱ���������еĲ���λ��*/
						q=q->down;
					p->down=q->down;/*����*/
					q->down=p;
				}
				else/*������ĵ�һ�����*/
					(*CL)->chead[j]=p;
			}
		}
		return 1;
}


/*�㷨5-7 ���ʮ������ָ��λ�õĽ��ֵ*/
int GetValue(CrossLink CL,DataType *e,int r,int c)
{	
	PCNode p;	
	*e=0;
	if(CL->nums<=0){printf("��ʮ�������޷���ɲ�����");return 0;}
	if(r<1 || r>CL->rows || c<1 || c>CL->cols){printf("���������޷���ɲ�����");return 0;}
	p=CL->rhead[r-1];
	while(p!=NULL && p->col!=c)
		p=p->right;
	if(p)
		*e=p->value;
	return 1;
}

