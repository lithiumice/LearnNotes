// s7_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../adjmetrix.h"


int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;
	int pos,i;
	char d[]={'A','B','C','D','E'};
	int m[][MAXVEX]={{0,1,0,1,1},{1,0,1,1,0},{0,1,0,0,0},{0,1,0,0,1},{1,0,0,1,0}};
	CreateGraph(g,m,d,5);
	DispGraph(g);
	for(i=0;i<g->vexs;i++)
	{
		pos=GetFirst(g,i);
		if(pos!=-1)
			printf("\n[%c]\t%c",g->data[i],g->data[pos]);
		else
			printf("\n[%c]",g->data[i]);
		while(pos!=-1)
		{
			pos=GetNext(g,i,pos);
			if(pos!=-1)
				printf("\t%c",g->data[pos]);
		}
	}
	return 0;
}

