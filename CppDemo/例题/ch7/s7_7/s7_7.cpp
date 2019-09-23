// s7_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../adjlist.h"

int main(int argc, char* argv[])
{
	AdjList g;					
	int p;
	int i;
	int m[][MAXVEX]={{0,1,1,0,0},{1,0,0,1,1},{1,0,0,0,0}
,{0,1,0,0,1},{0,1,0,1,0}};	
	CreateGraph(&g,m,5);		
	printf("\n1:\n");
	DispGraph(g);					
	printf("\n\n\n2:\n");
	for(i=0;i<g->vexs;i++)
	{
		p=GetFirst(g,i);
		if(p!=-1)	
			printf("\nLine%d\t[%d]",i,p);
		else	
			printf("\nLine%d",i);
		while(p!=-1)
		{
			p=GetNext(g,i,p); 
			if(p!=-1)	
				printf("\t[%d]",p);
		}
	}
	return 0;
}
