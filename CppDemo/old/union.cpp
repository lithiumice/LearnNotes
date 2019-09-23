#include "stdio.h"
#include "stdlib.h"
#define N 3

struct personal
{
	long id;
	char name[20];
	char job;
	union {
		int salary;
		char zc[10];
	}category;
};

int main()
{
	
	struct personal person[N];
	char inbuf[20];
	int i;
	for(i=0;i<N;i++)
	{
		printf("\nInput all data of person[%d]:\n",i);
		gets(inbuf);
		person[i].id=atol(inbuf);
		gets(person[i].name);
		person[i].job=getchar();
		getchar();
		
		if(person[i].job=='w')
		{
			gets(inbuf);
			person[i].category.salary=atoi(inbuf); 
		}
		else if(person[i].job=='t')
		{
			gets(person[i].category.zc);
		}
	}
	for(i=0;i<N;i++)
	{
		printf("%d:%ld,%s",i,person[i].id,person[i].name); 
		if(person[i].job=='w')
			printf(",%d\n",person[i].category.salary);
		else
			printf(",%s\n",person[i].category.zc);
	}
	return 0;
}
