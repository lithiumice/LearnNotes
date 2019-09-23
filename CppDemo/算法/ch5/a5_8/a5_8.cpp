// a5_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glink.h"

int main(int argc, char* argv[])
{
	GLink p;
	char str[]="(a,(b,c))";
	p=InitGLink(str);
	DispGLink(p);	
	return 0;
}
