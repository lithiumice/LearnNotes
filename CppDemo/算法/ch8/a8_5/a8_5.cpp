// a8_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bstree.h"

int main(int argc, char* argv[])
{	
	BSTree root=NULL;
	DataType items[]={5,9,4,1,15,8,2,7};
	CreateBSTree(&root,items,8);
	DisplayBST(root);
	BSTDelete(&root,items[2]);
	printf("\n\n");
	DisplayBST(root);
	return 0;
}
