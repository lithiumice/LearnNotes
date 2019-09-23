/*
   Huffman树的基本操作
*/
#include "stdio.h"
#include "malloc.h"

#define MAXBIT 10
#define MAXVALUE 32767

typedef char DataType;
typedef struct node{
	DataType data;
	int weight;
	int parent;
	int left;
	int right;
}HufNode;

typedef struct{
	char code[MAXBIT];
	int start;
}HufCode;

void HuffmanTree(int weight[],char ch[],int n,HufNode hf[])
{
	int i,j;
	int mw1,mw2;
	int node1,node2;
	for(i=0;i<2*n-1;i++)
	{
		hf[i].data=ch[i];
		if(i<n)
			hf[i].weight=weight[i];
		else
			hf[i].weight=0;
		hf[i].parent=-1;
		hf[i].left=-1;
		hf[i].right=-1;
	}
	for(i=n;i<2*n-1;i++)
	{
		mw1=mw2=MAXVALUE;
		node1=node2=-1;
		for(j=0;j<=i-1;j++)
		{
			if(hf[j].parent==-1)
			{
				if(hf[j].weight<mw1)
				{
					mw2=mw1;
					node2=node1;
					mw1=hf[j].weight;
					node1=j;
				}
				else if(hf[j].weight<mw2)
				{
					mw2=hf[j].weight;
					node2=j;
				}
			}
		}		
		hf[i].weight=hf[node1].weight+hf[node2].weight;
		hf[node1].parent=i;
		hf[node2].parent=i;
		hf[i].left=node1;
		hf[i].right=node2;
	}
}


void HuffmanCode(HufNode hf[],HufCode hfc[],int n)
{
	int i,parent,left;
	HufCode hc;
	for(i=0;i<n;i++)
	{
		hc.start=n;
		left=i;
		parent=hf[i].parent;
		while(parent!=-1)
		{
			if(hf[parent].left==left)
				hc.code[hc.start--]='0';
			else
				hc.code[hc.start--]='1';
			left=parent;
			parent=hf[parent].parent;
		}
		hc.start++;
		hfc[i]=hc;
	}
}
