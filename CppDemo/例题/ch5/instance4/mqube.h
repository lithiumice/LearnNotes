#include "stdio.h"
#include "malloc.h"


/*n阶魔方存储结构*/
typedef struct{
	int *data;		/*魔方*/
	int size;		/*魔方阶数*/
	int sum;		/*和*/
}Qube,*MQube;

int InitMQube(MQube *mq,int n)
{		
	(*mq)->data=(int*)malloc(n*n*sizeof(int));
	if(!((*mq)->data)){printf("初始化错误");	return 0;}
	(*mq)->size=n;
	(*mq)->sum=0;
	return 1;
}


int GenerateMQube(MQube mq)
{
	int i,j,k,n;
	int *p;
	p=mq->data;
	n=mq->size;
	i=0;
	j=(n-1)/2;
	*(p+j)=1;
	for(k=2;k<=n*n;k++)
	{
		i=(i-1+n)%n;
		j=(j-1+n)%n;
		if(*(p+i*n+j)>0)
		{
			i=(i+2)%n;
			j=(j+1)%n;			
		}
		*(p+i*n+j)=k;		
	}
	for(k=0;k<n;k++)
		mq->sum+=*(p+k);
	return 1;
}


void DispMQube(Qube mq)
{
	int i,j;
	printf("\n\n");
	for(i=0;i<mq.size;i++){
		for(j=0;j<mq.size;j++)
			printf("%d\t",*(mq.data+i*mq.size+j));
		printf("\n");		
	}
	printf("The sum is %d.\n",mq.sum);
}
			
