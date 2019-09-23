// a6_11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bitreelink.h"

int main(int argc, char* argv[])
{
	BiTreeLink root;
	int i;
	char nodes[]="#RABCDE  F  G   ";
	root=CreateBiTree(nodes,1,16);
	printf("输入序列：\n");
	for(i=1;i<16;i++)
		printf("(%c)",nodes[i]);
	printf("\n\n\n后序遍历序列：\n");	
	NonPostOrder(root);	
	return 0;
}

