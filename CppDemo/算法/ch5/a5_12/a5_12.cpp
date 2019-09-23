// a5_12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glink.h"

int main(int argc, char* argv[])
{
	GLink p,q;
	char str[]="(a,b,(c,d,e,(f)))";
	p=InitGLink(str);
	DispGLink(p);
	q=GetHead(p);
	printf("\n\n");
	DispGLink(q);
	printf("\n\n");
	return 0;
}
