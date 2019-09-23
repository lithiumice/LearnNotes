// a4_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

int main(int argc, char* argv[])
{
	int i;
	SqString S;
	SqString T;
	InitString(&S,"SubStr");
	InitString(&T,"");	
	
	SubStr(S,3,3,&T);
	for(i=0;i<T.length;i++)
		printf("%c",T.ch[i]);
	printf("\n");
	return 0;
}

