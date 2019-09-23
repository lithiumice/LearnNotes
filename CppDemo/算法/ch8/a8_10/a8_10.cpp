// a8_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../hash.h"

int main(int argc, char* argv[])
{
	DataType x;
	DataType items[6]={15,59,22,34,7,78};
	HashTable ht;
	CreateHash(ht,items,6);
	DisplayHash(ht);
	x.key=7;
	HashDelete(ht,x);
	DisplayHash(ht);	
	return 0;
}
