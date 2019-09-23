// a8_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"

#define MAXM 20
typedef int KeyType;
typedef struct Node{
	int keynum;
	KeyType keys[MAXM];
	struct Node* parent;
	struct Node* children[MAXM];
}BMTNode, *BMTree;

BMTNode *SearchBTree(BMTree r,KeyType x,int *pos)
{
	int i=0;
	BMTNode* p=NULL;
	while(i<p->keynum && p->keys[i]<x) i++;	
	if(p->keys[i]==x)
	{
		*pos=i;
		return p;
	}		
	if(!r->children[i]) 
		return NULL; 
	return SearchBTree(r->children[i],x,pos);
 }


int main(int argc, char* argv[])
{
	return 0;
}
