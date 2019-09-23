// a5_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glink.h"

int main(int argc, char* argv[])
{
	GLink p;
	char str[]="(a,d,(b,c,e,(f,(g))))";
	int n;
	p=InitGLink(str);
	DispGLink(p);
	n=GLinkDepth(p);
	printf("\n%d\n",n);
	return 0;
}
