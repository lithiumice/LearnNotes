// a5_13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../glink.h"

int main(int argc, char* argv[])
{
	GLink p,q;
	char str[]="(a,d,(b,c,e,(f,(g))))";
	p=InitGLink(str);
	DispGLink(p);	
	q=GetTail(p);
	printf("\n\n");
	DispGLink(q);
	printf("\n\n");
	return 0;
}
