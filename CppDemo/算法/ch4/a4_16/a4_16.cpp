// a4_16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../linkstring.h"

int main(int argc, char* argv[])
{
	LinkString S;
	LinkString T;
	LinkString R;
	InitString(&S,"Data");
	InitString(&T," Struct");
	Concat(&S,T);
	Print(S);
	SubStr(S,9,2,&R);
	Print(R);
	return 0;
}
