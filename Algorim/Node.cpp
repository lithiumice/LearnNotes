#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int id;
	struct Node* next;
}NODE;

NODE* NewNode()
{
	return (NODE*)malloc(sizeof(NODE));
}

NODE* CreateNode(int n)
{
	NODE *p,*h;
	int i;
	char inbuf[10];
	h=NewNode();
	h->next=NULL;
	for(i=n;i>0;i--)
	{
		p=NewNode();
		p->id=i;
		//gets(inbuf);
		//p->id=atof(inbuf);
		p->	next=h->next;
		h->next=p;
	}
	return h;
}

void InsertNode(NODE* h,int n)
{
	NODE *p,*old,*last;
	char inbuf[20];
	p=NewNode();
	puts("New nodes:");
	scanf("%d",p->id);
	last=h->next;
	while((last->id==n)&&(last->next!=NULL))
	{
		old=last;
		last=last->next;
	}
	if(last->next!=NULL)
	{
		old->next=p;
		p->next=last;
	}
	else
	{
		last->next=p;
		p->next=NULL;
	}
}

void PrintList(NODE* h)
{
	NODE* cur_node=h;
	while(cur_node!=NULL)
	{
		cur_node=cur_node->next;
		printf("%d\n",cur_node->id);
	}
}

void DeleteAll(NODE* h)
{
	NODE *p=h->next,*q=p->next;
	while(h->next!=NULL)
	{
		h->next=q;
		q=q->next;
		free(p);
		p=h->next;
		
	}
	free(h);
}

int main()
{
	NODE *h;
	int n;
	h=CreateNode(10);
	puts("insert after what?:");
	n=getchar()-'0';
	InsertNode(h,n);
	PrintList(h);
	return 0;
 } 
 
 
