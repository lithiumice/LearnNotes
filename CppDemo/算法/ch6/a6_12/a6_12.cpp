// a6_12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bitreelink.h"

int main(int argc, char* argv[])
{
	BiTreeLink root;
	int i;
	char nodes[]="#RABC  F H    ";
	root=CreateBiTree(nodes,1,13);
	printf("�������У�\n");
	for(i=1;i<14;i++)
		printf("(%c)",nodes[i]);
	printf("\n\n\n�������Ľ�������");
	
	printf("[%d]\n",BiTreeCount(root));	
	return 0;
}
