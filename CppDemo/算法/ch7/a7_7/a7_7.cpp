// a7_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"


int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;	
	char d[]={'A','B','C','D'};
	int m[][MAXVEX]={{0,1,0,1},{1,0,0,0},{0,1,0,0},{0,0,0,0}};
	CreateGraph(g,m,d,4);
	DispGraph(g);		
	InsertArc(g,1,3,1);
	DispGraph(g);
	return 0;
}

