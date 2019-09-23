// a7_18.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"

int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;
	char d[]={'A','B','C','D','E'};
	int m[][MAXVEX]={{MAXWEIGHT,3,5,18,MAXWEIGHT},{MAXWEIGHT,MAXWEIGHT,1,MAXWEIGHT,8},{MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,2},{MAXWEIGHT,MAXWEIGHT,3,MAXWEIGHT,MAXWEIGHT},{MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,6,MAXWEIGHT}};
	int dis[5];
	CreateGraph(g,m,d,5);	
	DispGraph(g);	
	Dijstra(g,0,dis);
	printf("\n\n");
	return 0;
}
