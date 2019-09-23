// a6_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../thrlink.h"

int main(int argc, char* argv[])
{
	PTBNode r,p,q;	
	char nodes[]="#RABC DE  ";
	r=CreateBiTree(nodes,1,9);
	CreateInThread(&p,r);
	q=InOrderNext(p->left->left);	
	printf("%c",q->data);	
	return 0;
}
