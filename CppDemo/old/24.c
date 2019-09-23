#include "stdio.h"
char symbol[4]={'+','-','*','/'};

double SymCount(char sym,double a,double b)
{
	switch (sym)
	{
		case '+':return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':return a/b;
	}
}


void CountNum(int* num)
{
	int i,j,k;
	double a,b,c;
	for(i=0;i<4;i++)
	{
		a=SymCount(symbol[i],num[0],num[1]);
		for(j=0;j<4;j++)
		{
			b=SymCount(symbol[j],a,num[2]);
			for(k=0;k<4;k++)
				{
					c=SymCount(symbol[k],b,num[3]);
					if(((int)c)==24)
					{
						printf("%d %c %d %c %d %c %d=24\n",num[0],symbol[i],num[1],symbol[j],num[2],symbol[k] ,num[3]);
					}
				}
		}
	}
}


int main()
{
	int reint[4],inint[4];
	int i,j,k,t;
	for(i=0;i<4;i++)
	{
		scanf("%d",&inint[i]);
	}
	for(i=0;i<4;i++)
	{
		reint[0]=inint[i];
		for(j=0;j<4;j++)
		{
			if(i!=j)
				reint[1]=inint[j];
			for(k=0;k<4;k++)
			{
				if(i!=k&&j!=k)
					reint[2]=inint[k];
				for(t=0;t<4;t++)
				{
					if(i!=t&&j!=t&&k!=t)
						reint[3]=inint[t];
					CountNum(&reint[0]);
				}
			}
		}
	}

	return 0;
}