// a6_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bitreelink.h"



int main(int argc, char* argv[])
{
	BiTreeLink root;
	int i;
	char nodes[]="#RABCDE  F  G   ";
	root=CreateBiTree(nodes,1,16);
	printf("�������У�\n");
	for(i=1;i<16;i++)
		printf("(%c)",nodes[i]);
	printf("\n\n�����Һ���\n");
	InsertRight(root,'H');
	DispBiTree(root);	
	return 0;
}
