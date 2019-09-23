#include "stdio.h"
#define N 10
int main()
{
	int num[N];
	void input(int num[]);
	void change_value(int num[]);
	void output(int num[]);
	input(num);
	change_value(num);
	output(num);
	return 0;
}

void change_value(int* v)
{
	int i,a,t,flag;
	a=v[0];
	for(i=1;i<N;i++)
	{
		if(a>v[i])
		{
			a=v[i];
			flag=i;
		}
	}
	t=v[0];
	v[0]=v[flag];
	v[flag]=t;
}

void input(int* v)
{
	int i;
	for(i=0;i<N;i++)
	{
		v[i]=getchar()-48;
	}
}
void output(int* v)
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("%d",v[i]);
	}
}
