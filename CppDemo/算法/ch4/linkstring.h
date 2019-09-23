/*
   ������ʽ�洢
*/
#include "malloc.h"
#include "stdio.h"

/*�洢�ṹ*/
typedef struct Node{
	char data;
	struct Node * next;
}SNode,*PSNode;

typedef SNode * LinkString;

/*�㷨4-12��ʼ����*/
int InitString(LinkString *S,char * str)
{
	char *ch;
	PSNode p,r;	
	r=NULL;
	ch=str;
	*S=NULL;	
	while(*ch!='\0')
	{
		p=(PSNode)malloc(sizeof(SNode));
		if(!p)
		{
			printf("����ռ��������ɳ�ʼ����������");
			return 0;
		}
		p->data=*ch;
		p->next=NULL;
		if(!*S) *S=p;
		else
			r->next=p;
		r=p;
		ch++;
	}
	return 1;
}

/*�㷨4-13������*/
int StrInsert(LinkString *S,int pos,LinkString T)
{
	int j=0;
	LinkString p,r;
	p=*S;
	if(!*S)						/*��SΪ�մ�����T��ΪS��*/	
	{
		*S=T;
		return 1;
	}
	while(p && j<pos-1)			/*Ѱ�Ҳ���λ��*/
	{
		j++;
		p=p->next;
		
	}
	if(!p || j>pos)
	{
		printf("����λ�ò��Ϸ���������ɴ����������");
		return 0;
	}
	r=T;
	while(r->next)  r=r->next;	/*Ѱ��T����β*/
	if(pos==0)					/*�ڴ�S����ǰ�����T*/
	{
		r->next=p;
		*S=T;
	}
	else						/*������λ�ò���*/
	{
		r->next=p->next;		
		p->next=T;
	}
	return 1;
}

/*�㷨4-14��ɾ��*/
int StrDelete(LinkString* S,int pos,int len)
{
	int j=1,k=0;
	PSNode p=NULL,q=NULL,r;
	p=*S;
	while(p&&j<pos)		/*Ѱ��ɾ��λ�ã�����qָ����*/
	{
		q=p;
		p=p->next;
		j++;
	}
	if(!p || j>pos)		
	{
		printf("ɾ��λ�ò��Ϸ���������ɴ�ɾ������");
		return 0;
	}
	while(p && k<len-1)	/*Ѱ�ұ�ɾ�Ӵ�βλ�ã�����pָ����*/
	{
		p=p->next;
		k++;
	}
	if(!p || k>len-1)
	{
		printf("ɾ�����Ȳ��Ϸ���������ɴ�ɾ������");
		return 0;
	}
	if(!q)				/*��ɾ�Ӵ���S����ǰ��*/
	{
		r=*S;
		*S=p->next;
	}
	else				/*��ɾ�Ӵ�������λ��*/
	{
		r=q->next;
		q->next=p->next;
	}
	p->next=NULL;
	while(r)			/*�����ͷű�ɾ�Ӵ���ÿһ�����*/
	{
		p=r;
		r=r->next;
		free(p);
	}
	return 1;
}


/*�㷨4-15���Ӵ�*/
int SubStr(LinkString S,int pos,int len,LinkString* T)
{
	int i=1;
	PSNode p,q,r;
	p=S;
	while(p && i<pos)
	{
		p=p->next;
		i++;
	}
	if(!p || i>pos)
	{
		printf("λ�ò��Ϸ�������������Ӵ�����");
		return 0;
	}
	*T=(PSNode)malloc(sizeof(SNode));
	(*T)->data=p->data;
	(*T)->next=NULL;
	i=1;
	q=*T;
	while(p->next&& i<len)
	{
		p=p->next;
		i++;	
		r=(PSNode)malloc(sizeof(SNode));
		r->data=p->data;
		q->next=r;
		q=r;
	}
	if(i<len)
	{
		printf("�Ӵ����Ȳ��Ϸ�������������Ӵ�����");
		return 0;
	}
	q->next=NULL;
	return 1;
}

/*�㷨4-16������*/
int Concat(LinkString *S,LinkString T)
{
	PSNode p;
	if(!*S)		/*��SΪ�մ�����ֱ�ӷ���T��*/
	{
		*S=T;
		return 0;
	}
	p=*S;
	while(p->next) p=p->next;	/*Ѱ��S�������һ�����*/
	p->next=T;					/*����*/
	return 1; 
}

void Print(LinkString S)
{
	PSNode p;
	p=S;
	while(p)
	{
		printf("%c",p->data);
		p=p->next;		
	}
	printf("\n");
}