#include <stdio.h>
#include "BiTree.h"

int main(int argc, char const *argv[])
{
	BiTreeLink root;
	int i;
	char nodes[] = "RABCDE F G    ";
	root = CreateBiTree(nodes, 1, 15);
	DispBiTree(root);
	return 0;
}
