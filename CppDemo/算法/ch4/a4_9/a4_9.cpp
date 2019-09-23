// a4_9.cpp : Defines the entry point for the console application.
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
		
	StrInsert(&S,7,T);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
	StrDelete(&S,3,2);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");	
	return 0;
}


