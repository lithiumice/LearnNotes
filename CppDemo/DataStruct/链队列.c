typedef int DataType;
typedef struct QNode{
	DataType data;
	struct QNode *next;
}LQNode, *PQNode;

typedef struct 
{
	PQNode front, rear;
}LinkQueue;


int InitQueue(LinkQueue *Q)
{
	Q -> front = Q -> rear = (PQNode)malloc(sizeof(LQNode));
	if (!Q -> front)
	{
		printf("initialization failed!\n");
		return 0;
	}
	Q -> front -> next =NULL;
	return 1;
}


int QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return 0;
	else
		return 1;
}


int EnQueue(LinkQueue *Q, DataType e)
{
	PQNode p = (PQNode)malloc(sizeof(LQNode));
	if(!p)
	{
		printf("cannot malloc!\n");
		return 0;
	}
	p -> data = e;
	p -> next = NULL;
	Q -> rear -> next = p;
	Q -> rear = p;
	return 1;
}


int DeQueue(LinkQueue *Q, DataType e)
{
	PQNode p;
	if (Q -> front == Q -> rear)
	{
		printf("the queue is empty!\n");
		return 0;
	}
	p = Q -> front -> next;
	*e = p -> data;
	Q -> front -> next = p -> next;
	free(P);
	if(Q -> rear == p)
	{
		Q -> rear = Q ->front;
	}
	return 1;
}


int GetHead(LinkQueue Q, DataType e)
{
	PQNode p;
	if (Q.front == Q.rear)
	{
		printf("the queue is empty, cannot read head!\n");
		return 0;
	}

	p = Q.front -> next;
	*e = p -> data;
	return 1;
}


int DestroyQueue(LinkQueue *Q)
{
	while(Q -> front)
	{
		Q -> rear = Q -> front -> next;
		free(Q -> front);
		Q -> front = Q -> rear;
	}
	return 1;
}