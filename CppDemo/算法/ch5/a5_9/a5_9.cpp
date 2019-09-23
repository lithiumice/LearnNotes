// a5_9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glink.h"

int main(int argc, char* argv[])
{
	GLink p;
	int n;
	char str[]="(a,d,(b,c,e,(f,(g))))";
	p=InitGLink(str);
	DispGLink(p);
	n=GLinkLength(p);
	printf("\n%d\n",n);
	return 0;
}


