// s8_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../bstree.h"

int main(int argc, char* argv[])
{	
	BSTree root=NULL;
	BSTNode* p;
	DataType items[]={5,9,4,1,15,8,2};
	DataType x={10};
	CreateBSTree(&root,items,7);
	DisplayBST(root);
	p= BSTSearch(root,items[2]);			
	printf("%d\n",p->data.key);
	BSTInsert(&root,x); 		
	DisplayBST(root);
	BSTDelete(&root,items[3]);
	DisplayBST(root);
	BSTDelete(&root,items[1]);
	DisplayBST(root);
	return 0;
}

