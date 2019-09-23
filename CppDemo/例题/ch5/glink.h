#include <stdio.h>
#include <malloc.h>


#define DataType char 
/*广义表的结构类型定义如下：*/
typedef struct node
{	
	int flag;        /*标志域*/
	union			 /*第二个域*/
	{
		DataType data;
		struct node* sublist;
	};
	struct node* next;  /*指针域*/	
}GNode, *PGNode, *GLink;

//char *str;
/*算法5-8 初始化广义表*/
GLink InitGLink(char *str)
{
	PGNode p;
	char c;
	c=*str;
	str++;
	if(c!='\0')
	{
		switch(c)
		{
		case '(':		
			p=(PGNode)malloc(sizeof(GNode));
			if(!p){printf("无法生成结点");return 0;}
			p->flag=1;
			p->sublist=InitGLink(str);
			break;
		case ')':
			return NULL;
		default:
			p=(PGNode)malloc(sizeof(GNode));
			if(!p){printf("无法生成结点");return 0;}
			p->flag=0;
			p->data=c;
			break;	
		}
	}
	else	
		p=NULL;
	c=*str;
	str++;
	if(p)
	{
		if(c==',')
			p->next=InitGLink(str);
		else //if(c==')' || c=='\0')
			p->next=NULL;
	}
	return p;
}



/*算法5-9 求广义表长度*/
int GLinkLength(GLink GL)
{
	int num=0;
	PGNode p;
	p=GL->sublist;
	while(p!=NULL)
	{
		num++;
		p=p->next;
	}
	return num;
}
	
	

/*算法5-10 求广义表深度*/
int GLinkDepth(GLink GL)
{
	int max=0,dep;
	PGNode p;
	if(GL->flag==0)
		return 0;
	for(p=GL->sublist; p; p=p->next)
	{ 
		dep=GLinkDepth(p);
		if(dep>max)  max=dep;
	}
	return max+1;
}

	

/*算法5-11 复制广义表*/
GLink GLinkCopy(GLink GL)
{
	PGNode p;
	if(GL==NULL)
		return NULL;
	p=(PGNode)malloc(sizeof(GNode));
	p->flag=GL->flag;
	if(GL->flag==1)
		p->sublist=GLinkCopy(GL->sublist);
	else
		p->data=GL->data;
	p->next=GLinkCopy(GL->next);
	return p;
}


/*算法5-12 求广义表表头*/
GLink GetHead(GLink GL)
{
	GLink p=GL->sublist;
	PGNode q,t;
	if(p==NULL)
	{
		printf("空表，不能求表头");
		return 0;
	}
	else if(GL->flag==0)
	{
		printf("原子，不能求表头");
		return 0;
	}
	if(p->flag==0)
	{
		q=(PGNode)malloc(sizeof(GNode));
		q->flag=0;
		q->data=p->data;
		q->next=NULL;
	}
	else
	{
		t=(PGNode)malloc(sizeof(GNode));
		t->flag=1;
		t->sublist=p->sublist;
		t->next=NULL;q=GLinkCopy(t);
		free(t);
	}
	return q;
}

/*算法5-13 求广义表表尾*/
GLink GetTail(GLink GL)
{
	GLink p=GL->sublist;
	PGNode q,t;
	if(p==NULL)
	{
		printf("空表，不能求表尾");
		return 0;
	}
	else if(GL->flag==0)
	{
		printf("原子，不能求表尾");
		return 0;
	}
	p=p->next;
	t=(PGNode)malloc(sizeof(GNode));
	t->flag=1;
	t->sublist=p;
	t->next=NULL;
	q=GLinkCopy(t);
	free(t);	
	return q;
}


