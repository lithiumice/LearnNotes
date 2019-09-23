// a7_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"

int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;
	char d[]={'1','2','3','4','5'};
	int m[][MAXVEX]={{MAXWEIGHT,4,8,5,MAXWEIGHT},{4,MAXWEIGHT,3,MAXWEIGHT,7},{8,3,MAXWEIGHT,6,6},{5,MAXWEIGHT,6,MAXWEIGHT,9},{MAXWEIGHT,7,6,9,MAXWEIGHT}};
	CreateGraph(g,m,d,5);	
	DispGraph(g);	
	Prim(g,0);
	printf("\n\n");
	return 0;
}
