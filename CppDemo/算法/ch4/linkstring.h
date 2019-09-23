/*
   串的链式存储
*/
#include "malloc.h"
#include "stdio.h"

/*存储结构*/
typedef struct Node{
	char data;
	struct Node * next;
}SNode,*PSNode;

typedef SNode * LinkString;

/*算法4-12初始化串*/
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
			printf("分配空间错，不能完成初始化串的任务");
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

/*算法4-13串插入*/
int StrInsert(LinkString *S,int pos,LinkString T)
{
	int j=0;
	LinkString p,r;
	p=*S;
	if(!*S)						/*若S为空串，则T即为S串*/	
	{
		*S=T;
		return 1;
	}
	while(p && j<pos-1)			/*寻找插入位置*/
	{
		j++;
		p=p->next;
		
	}
	if(!p || j>pos)
	{
		printf("插入位置不合法，不能完成串插入的任务");
		return 0;
	}
	r=T;
	while(r->next)  r=r->next;	/*寻找T串的尾*/
	if(pos==0)					/*在串S的最前面插入T*/
	{
		r->next=p;
		*S=T;
	}
	else						/*在其他位置插入*/
	{
		r->next=p->next;		
		p->next=T;
	}
	return 1;
}

/*算法4-14串删除*/
int StrDelete(LinkString* S,int pos,int len)
{
	int j=1,k=0;
	PSNode p=NULL,q=NULL,r;
	p=*S;
	while(p&&j<pos)		/*寻找删除位置，并用q指向它*/
	{
		q=p;
		p=p->next;
		j++;
	}
	if(!p || j>pos)		
	{
		printf("删除位置不合法，不能完成串删除任务");
		return 0;
	}
	while(p && k<len-1)	/*寻找被删子串尾位置，并用p指向它*/
	{
		p=p->next;
		k++;
	}
	if(!p || k>len-1)
	{
		printf("删除长度不合法，不能完成串删除任务");
		return 0;
	}
	if(!q)				/*被删子串在S的最前面*/
	{
		r=*S;
		*S=p->next;
	}
	else				/*被删子串在其他位置*/
	{
		r=q->next;
		q->next=p->next;
	}
	p->next=NULL;
	while(r)			/*依次释放被删子串的每一个结点*/
	{
		p=r;
		r=r->next;
		free(p);
	}
	return 1;
}


/*算法4-15求子串*/
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
		printf("位置不合法，不能完成求子串任务");
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
		printf("子串长度不合法，不能完成求子串任务");
		return 0;
	}
	q->next=NULL;
	return 1;
}

/*算法4-16串连接*/
int Concat(LinkString *S,LinkString T)
{
	PSNode p;
	if(!*S)		/*若S为空串，则直接返回T串*/
	{
		*S=T;
		return 0;
	}
	p=*S;
	while(p->next) p=p->next;	/*寻找S串的最后一个结点*/
	p->next=T;					/*连接*/
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