// a4_11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqvstring.h"

int main(int argc, char* argv[])
{	
	int i;
	SqVString S,T,R;
	InitString(&S,"strings");
	InitString(&T," Demo");
	InitString(&R,"");	
	
	SubStr(S,3,2,&R);
	for(i=0;i<R.length;i++)
		printf("%c",R.ch[i]);
	printf("\n");
	Concat(&S,T);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
	return 0;
}

