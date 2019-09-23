// a7_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"


int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;	
	int i;
	char d[]={'A','B','C','D'};
	int m[][MAXVEX]={{0,1,0,1},{1,0,0,0},{0,1,0,0},{0,0,0,0}};
	CreateGraph(g,m,d,4);
	DispGraph(g);		
	for(i=0;i<g->vexs;i++)
		PutVex(g,i,i+68);
	for(i=0;i<g->vexs;i++)		
		printf("m[%d]=%c\t",i,GetVex(g,i));
	return 0;
}


