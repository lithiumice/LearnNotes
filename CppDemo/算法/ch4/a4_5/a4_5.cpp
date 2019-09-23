// a4_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

int main(int argc, char* argv[])
{
	int i;
	SqString S;
	SqString T;
	InitString(&S,"Strings");
	InitString(&T," Demo");
	
	Concat(&S,T);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
	return 0;
}
