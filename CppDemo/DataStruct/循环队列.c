#define QUEUESIZE 100
typedef int DataType;
typedef struct 
{
	DataType items[QUEUESIZE]
	int front, rear;
}SqQueue;


int InitQueue(SqQueue *Q)
{
	Q -> front = 0;
	Q -> rear = 0;
	return 1;
}


int QueueEmpty(SqQueue Q)
{
	if (Q.rear == Q.front)
	{
		return 1;
	}
	else
		return 0;
}


int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + QUEUESIZE)%QUEUESIZE
} //为了保证不为负值


int EnQueue(SqQueue *Q, DataType e)
{
	if((Q -> rear + 1)%QUEUESIZE == Q -> front)
	{
		printf("the queue is full!\n");
		return 0;
	}
	Q -> items[Q -> rear] = e;
	Q -> rear = (Q -> rear + 1)%QUEUESIZE;
	return 1;
}


int DeQueue(SqQueue *Q, DataType e)
{
	if (Q -> front == Q -> rear)
	{
		printf("the queue is empty, cannot dequeue!\n");
		return 0;
	}
	*e = Q -> items[Q -> front];
	Q -> front = (Q -> front + 1)%QUEUESIZE;
	return 1;
}


int GetHead(SqQueue Q, DataType *e)
{
	if (Q.front == Q.rear)
	{
		printf("the queue is empty, cannot push!\n");
		return 0;
	}
	*e = Q.items[Q.front];
	return 1;
}


int TraverseQueue(SqQueue Q)
{
	int pos;
	pos = Q.front;
	while((pos + 1)%QUEUESIZE <= Q.rear)
	{
		printf("%d\t", Q.items[pos]);
		pos++;
	}
	printf("\n");
	return 1;
}