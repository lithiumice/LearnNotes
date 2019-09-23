// a8_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bstree.h"

int main(int argc, char* argv[])
{	
	BSTree root=NULL;
	BSTNode* p;
	DataType items[]={5,9,4,1,15,8,2};
	CreateBSTree(&root,items,7);	
	p= BSTSearch(root,items[4]);
	printf("%d\n",p->data.key);
	return 0;
}
