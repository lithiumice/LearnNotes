// s6_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../thrlink.h"

int main(int argc, char* argv[])
{
	PTBNode r,p;	
	char nodes[]="#RAB CD   E FG  ";
	r=CreateBiTree(nodes,1,16);
	CreateInThread(&p,r);		
	InThreadTraverse(p);
	return 0;
}