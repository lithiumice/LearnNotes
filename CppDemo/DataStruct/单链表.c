#include <stdio.h>
#include <malloc.h>

typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node *next;
}LNode, *PNode, *LinkList;
//linklist为头指针


int InitList(LinkList *h)
{
	*h = (LinkList)malloc(sizeof(LNode));
	if(!h)
	{
		printf("initialization fail!\n");
		return 0;
	}
	(*h) -> next = NULL;
	return 1;
}


int ListLength(LinkList h)
{
	int total = 0;
	PNode p = h -> next;
	while(p)
	{
		total++;
		p = p ->next;
	}
	return total;
}

//返回1则为空
int ListEmpty(LinkList h)
{
	if(h -> next)
		return 0;
	else
		return 1;
}


//插入时间复杂度为O(n)
int ListInsert(LinkList h, int pos, DataType x)
{
	PNode p = h, q;
	int i = 0;
	while(p && i < pos - 1)
	{
		p = p -> next;
		i++; 
	}
	if(!p || i > pos - 1)
	{
		printf("illegal insert position!\n");
		return 0;
	}	
	q = (PNode)malloc(sizeof(LNode));
	if(!q)
	{
		printf("cannot malloc new node!\n");
		return 0;
	}
	q -> data = x;
	q -> next = p -> next;
	p -> next = q;
	return 1;
}


//item接受删除的值
int ListDelete(LinkList h, int pos, DataType *item)
{
	PNode p = h, q;
	int i = 0;
	while(p -> next && i < pos - 1)
	{
		p = p -> next;
		i++;
	}
	if(!p -> next || i > pos - 1)
	{
		printf("illegal position!\n");
		return 0;
	}
	q = p ->next;
	p -> next = q -> next;
	*item = q -> data;
	free(q);
	return 1;
}


PNode Find(LinkList h, DataType item)
{
	PNode p = h -> next;
	while(p && p -> data != item )
	{
		p = p -> next;
	}
	return p;
}


int GetElem(LinkList h, int pos, DataType *item)
{
	int i = 0;
	PNode p = h -> next;
	while(p && i < pos - 1)
	{
		i++;
		p = p -> next;
	}
	if(!p || i > pos - 1)
	{
		printf("illegal position!\n");
		return 0;
	}
	*item = p ->data;
	return 1;
}


void DestroyList(LinkList h)
{
	 PNode p = h -> next;
	 while(h)
	 {
	 	p = h;
	 	h = h -> next;
	 	free(p);
	 }
}


void TraverseList(LinkList h)
{
	PNode p = h -> next;
	while(p)
	{
		printf("%d\t", p -> data);
		p = p -> next;
	}
	printf("\n");
}


int main(int argc, char const *argv[])
{
	int i = 0;
	int data[7] = {0, 1, 1, 2, 3, 5, 8};
	DataType item;
	LinkList h = NULL;
	InitList(&h);
	for (i = 0; i < 7; i++)
	{
		if(!ListInsert(h, i+1, data[i]))
		{
			printf("error while insert!\n");
			return 0;
		}
	}

	TraverseList(h);
	if(!ListDelete(h, 7, &item))
	{
		printf("error while delete\n");
		return 0;
	}
	TraverseList(h);
	DestroyList(h);
	return 0;
}
