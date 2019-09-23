// a8_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bstree.h"

int main(int argc, char* argv[])
{	
	BSTree root=NULL;
	DataType items[]={5,9,4,1,15,8,2};
	DataType x={10};
	CreateBSTree(&root,items,7);
	DisplayBST(root);
	BSTInsert(&root,x);
	DisplayBST(root);
	return 0;
}
