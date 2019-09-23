// a4_14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../linkstring.h"

int main()
{	
	LinkString S;
	InitString(&S,"Str");
	Print(S);

	LinkString T;
	InitString(&T,"ing");
	StrInsert(&S,0,T);
	Print(S);

	StrDelete(&S,1,3);
	Print(S);

	return 0;
}

