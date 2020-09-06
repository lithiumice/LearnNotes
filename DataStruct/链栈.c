typedef int DataType;
typedef struct SNode
{
	DataType data;
	struct SNode *next;
}SNode, *LinkStack;


int InitStack(LinkStack *top)
{
	*top = (LinkStack)malloc(sizeof(SNode));
	if(*top == NUll)
	{
		printf("initialization fail!\n");
		return 0;
	}
	(*top) -> next = NUll;
	return 1;
}


int StackEmpty(LinkStack top)
{
	if(top -> next == NUll)
	{
		return 1;
	}
	else
		return 0;
}


int Push(LinkStack top, DataType e)
{
	SNode *p;
	p = (SNode)malloc(sizeof(SNode));
	if(!p)
	{
		printf("error while push!\n");
		return 0;
	}
	p -> data = e;
	p -> next = top -> next;
	top -> next = p;
	return 1;
}


int Pop(LinkStack top, DataType e)
{
	SNode *p;
	if(!top -> next)
	{
		printf("the stack is empty!\n");
		return 0;
	}

	p = top -> next;
	top -> next = p -> next;
	*e = p -> data;
	free(p);
	return 1;
}


int GetTop(LinkStack top, DataType e)
{
	SNode *p;
	if(!top -> next)
	{
		printf("the stack is empty!\n", );
		return 0;
	}
	p = top -> next;
	*e = p -> data;
	return 1;
}


int Destroy(LinkStack top)
{
	SNode *p;
	while(top)
	{
		p = top;
		top = top ->next;
		free(p);
	}
	return 1;
}


