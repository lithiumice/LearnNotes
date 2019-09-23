// a7_8.cpp : Defines the entry point for the console application.
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
	DeleteArc(g,0,3);
	DispGraph(g);
	return 0;
}
