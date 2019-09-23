// a4_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

int main(int argc, char* argv[])
{
	SqString S;
	SqString T;		
	//InitString(&S,"Strings"	);
	//InitString(&T,"Strings"	);
	InitString(&S,"abcczym"	);
	InitString(&T,"abccyzm"	);

	printf("%d",StrCmp(S,T));
	printf("\n");
	return 0;
}
