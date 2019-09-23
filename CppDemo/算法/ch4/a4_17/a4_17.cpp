// a4_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

int BFIndex(SqString S,SqString T)
{
	int i=0,j=0,k=-1;
	while(i<S.length && j<T.length)
	{
		if(S.ch[i]==T.ch[j])	//相等，则继续比较
		{
			i++;
			j++;
		}
		else						//回溯
		{
			i=i-j+1;
			j=0;
		}
	}

	if(j>=T.length)				//返回匹配位置
		k=i-T.length;
	return k;
}

int main()
{
	SqString S={"abbccabcc",9};
	SqString T={"abc",3};
	printf("%d\n",BFIndex(S,T));
	return 0;
}

