// S4_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../SqString.h"

int concat(SqString *s,SqString t)
{
	StrInsert(s,s->length,t);
	return 1;
}


int main(int argc, char* argv[])
{
	int i;	
	SqString S={"String",6};
	SqString T={" Operation",10};
	concat(&S,T);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);	
	return 1;

}