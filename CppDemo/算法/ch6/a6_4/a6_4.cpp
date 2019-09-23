// a6_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bitreelink.h"


int main(int argc, char* argv[])
{
	BiTreeLink root,p;
	int i;
	char nodes[]="#RABCDE  F  G   ";
	root=CreateBiTree(nodes,1,16);
	printf(" ‰»Î–Ú¡–£∫\n");
	for(i=1;i<16;i++)
		printf("(%c)",nodes[i]);
	printf("\n\n≤Â»Î”“∫¢◊”\n");
	p=InsertRight(root,'H');
	DispBiTree(root);
	printf("\n\n…æ≥˝”“◊” ˜\n");
	DeleteRight(p);
	DispBiTree(root);
	return 0;
}
