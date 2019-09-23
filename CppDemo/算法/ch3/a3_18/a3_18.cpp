// a3_18.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqqueue.h"

int main(int argc, char* argv[])
{
	SqQueue Q;
	InitQueue(&Q);
	for(int i=0;i<4;i++)
		EnQueue(&Q,i);
	printf("Queue Length:%d\n",QueueLength(Q));
	printf("Queue Is empty:%d\n",QueueEmpty(Q));
	TraverseQueue(Q);
	return 0;
}