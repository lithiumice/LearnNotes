// a6_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bitreelink.h"

int main(int argc, char* argv[])
{
	BiTreeLink root;
	int i;
	char nodes[]="#RABC  F H     I   ";
	root=CreateBiTree(nodes,1,18);
	printf("�������У�\n");
	for(i=1;i<18;i++)
		printf("(%c)",nodes[i]);
	printf("\n\n\n��ȫ��������������У�\n");
	DispBiTree(root);
	//printf("\n%d\n",Count(root));	
	return 0;
}
