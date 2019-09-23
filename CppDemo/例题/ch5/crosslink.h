
#include <stdio.h>
#include <malloc.h>
#define DataType int 
/*十字链表的结构类型定义如下：*/
typedef struct node
{	
	int row,col;        /*非零元素的行和列下标*/
	DataType value;
	struct node *right;  /*非零元素所在行表、列表的后继链域*/
	struct node *down; 
}CNode, *PCNode;

typedef struct 
{	
	PCNode *rhead;  /*行、列链表的头指针向量*/
	PCNode *chead;
	int rows,cols,nums;               /*稀疏矩阵的行数、列数、非零元素的个数*/
}*CrossLink;

/*算法5-6 初始化十字链表*/
int InitCrossLink(CrossLink* CL,DataType *A,int r,int c)
{
	int i,j;
	PCNode p,q;	
	(*CL)=(CrossLink)malloc(sizeof(CrossLink));
	if(!(*CL)->rhead){printf("无法生成十字链表");return 0;}
	(*CL)->rows=r;
	(*CL)->cols=c;
	(*CL)->nums=0;
	(*CL)->rhead=(PCNode*)malloc(r*sizeof(PCNode));/*生成行指针数组*/
	if(!(*CL)->rhead){printf("无法生成行指针数组");return 0;}
	for(i=0;i<r;i++)	/*初始化行指针数组*/
		(*CL)->rhead[i]=NULL;
	(*CL)->chead=(PCNode*)malloc(c*sizeof(PCNode));/*生成列指针数组*/
	if(!(*CL)->chead){printf("无法生成列指针数组");return 0;}
	for(i=0;i<c;i++)	/*初始化列指针数组*/
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
				if((*CL)->rhead[i]!=NULL)/*在行链表中插入*/
				{
					q=(*CL)->rhead[i];
					while(q->right!=NULL && q->col<j+1)  /*寻找行链表中的插入位置*/
						q=q->right;
					p->right=q->right;/*插入*/
					q->right=p;
				}
				else/*行链表的第一个结点*/
					(*CL)->rhead[i]=p;
				if((*CL)->chead[j]!=NULL)/*在列链表中插入*/
				{
					q=(*CL)->chead[j];
					while(q->down!=NULL && q->row<i+1)	/*寻找列链表中的插入位置*/
						q=q->down;
					p->down=q->down;/*插入*/
					q->down=p;
				}
				else/*列链表的第一个结点*/
					(*CL)->chead[j]=p;
			}
		}
		return 1;
}


/*算法5-7 输出十字链表指定位置的结点值*/
int GetValue(CrossLink CL,DataType *e,int r,int c)
{	
	PCNode p;	
	*e=0;
	if(CL->nums<=0){printf("空十字链表，无法完成操作！");return 0;}
	if(r<1 || r>CL->rows || c<1 || c>CL->cols){printf("参数错误，无法完成操作！");return 0;}
	p=CL->rhead[r-1];
	while(p!=NULL && p->col!=c)
		p=p->right;
	if(p)
		*e=p->value;
	return 1;
}

