// a6_16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../thrlink.h"

int main(int argc, char* argv[])
{
	PTBNode r,p;	
	char nodes[]="#RABC DE  ";
	r=CreateBiTree(nodes,1,9);
	CreateInThread(&p,r);	
	return 0;
}