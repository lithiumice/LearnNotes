// a4_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

int main(int argc, char* argv[])
{
	int i;
	//SqString S={"Strings",7};
	//SqString T={" Demo",5};
	SqString S,T,R;
	InitString(&S,"Strings");
	InitString(&T," Demo");
	InitString(&R,"");	
	
	StrInsert(&S,7,T);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
	StrDelete(&S,6,5);
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
	return 0;
}
