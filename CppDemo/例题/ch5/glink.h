#include <stdio.h>
#include <malloc.h>


#define DataType char 
/*�����Ľṹ���Ͷ������£�*/
typedef struct node
{	
	int flag;        /*��־��*/
	union			 /*�ڶ�����*/
	{
		DataType data;
		struct node* sublist;
	};
	struct node* next;  /*ָ����*/	
}GNode, *PGNode, *GLink;

//char *str;
/*�㷨5-8 ��ʼ�������*/
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
			if(!p){printf("�޷����ɽ��");return 0;}
			p->flag=1;
			p->sublist=InitGLink(str);
			break;
		case ')':
			return NULL;
		default:
			p=(PGNode)malloc(sizeof(GNode));
			if(!p){printf("�޷����ɽ��");return 0;}
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



/*�㷨5-9 ��������*/
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
	
	

/*�㷨5-10 ���������*/
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

	

/*�㷨5-11 ���ƹ����*/
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


/*�㷨5-12 �������ͷ*/
GLink GetHead(GLink GL)
{
	GLink p=GL->sublist;
	PGNode q,t;
	if(p==NULL)
	{
		printf("�ձ��������ͷ");
		return 0;
	}
	else if(GL->flag==0)
	{
		printf("ԭ�ӣ��������ͷ");
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

/*�㷨5-13 �������β*/
GLink GetTail(GLink GL)
{
	GLink p=GL->sublist;
	PGNode q,t;
	if(p==NULL)
	{
		printf("�ձ��������β");
		return 0;
	}
	else if(GL->flag==0)
	{
		printf("ԭ�ӣ��������β");
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


