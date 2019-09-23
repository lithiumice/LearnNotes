// s4_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../SqVString.h"

int StrReplace(SqVString *S,int pos,int len,SqVString T)
{
	int i,size;	
	char *str;
	if(pos<0 || len<=0 || pos>S->length || pos+len-1>S->length)
	{
		printf("参数不合法，无法完成串替换操作！");
		return 0; 
	}	
	size=S->length-len+T.length;
	str=(char*)malloc(size*sizeof(char));
	if(!str)
	{
		printf("分配空间出错，无法完成串替换操作");
		return 0;
	}	
	for(i=0; i<pos; i++)
		str[i]=S->ch[i];
	for(i=0;i<T.length;i++)
		str[pos+i-1]=T.ch[i];
	for(i=pos;i<S->length;i++)
		str[i+len-1]=S->ch[i+1];

	free(S->ch);			
	S->length=size;			
	S->ch=str;	
	return 1; 
}


int main(int argc, char* argv[])
{
	int i;
	SqVString S,T;
	InitString(&S,"acdefkl");
	InitString(&T,"xyz");
	StrReplace(&S,5,2,T);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);

	return 0;
}

