// s6_9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bitreelink.h"

int LeafCount(BiTreeLink r)
{
	if(!r) return 0;
	else if(!r->left && !r->right)
		return 1;
	else
		return LeafCount(r->left)+LeafCount(r->right);
}



int main(int argc, char* argv[])
{
	PBTNode r;	
	char nodes[]="#RABC DE  ";
	r=CreateBiTree(nodes,1,9);
	printf("leaf's count is %d\n",LeafCount(r));
	return 0;
}
