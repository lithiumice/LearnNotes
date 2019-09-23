// a6_14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bitreelink.h"

int main(int argc, char* argv[])
{
	BiTreeLink root;
	PBTNode p;
	int i;
	char nodes[]="#RABC  F H    ";
	root=CreateBiTree(nodes,1,13);
	printf("输入序列：\n");
	for(i=1;i<14;i++)
		printf("(%c)",nodes[i]);
	printf("\n\n\n二叉树的结点个数：");
	p=FindNode(root,'F');
	if(p)
		printf("%c\n",p->data);	
	return 0;
}

