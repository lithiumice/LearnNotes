// a4_20.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

void GetNextval(SqString T,int nextval[])
{
	int j=0,k=-1;
	nextval[0]=-1;
	while(j<T.length)
	{
		if(k==-1 || T.ch[j]==T.ch[k])
		{
			j++;
			k++;
			if(T.ch[j]==T.ch[k])
				nextval[j]=nextval[k];
			else
				nextval[j]=k;
		}
		else
			k=nextval[k];
	}
}


int main(int argc, char* argv[])
{
	//SqString T={"cbacb",5};
	//SqString T={"abcacbababcabcccbbaa",20};
	SqString T={"abacababcc",10};
	int next[10];
	GetNextval(T,next);
	for(int i=0;i<10;i++)
		printf("%d\t",next[i]);
	return 0;
}
