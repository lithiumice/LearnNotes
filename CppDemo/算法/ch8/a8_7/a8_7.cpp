// a8_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../hash.h"

int main(int argc, char* argv[])
{
	int addr;
	DataType x;
	DataType items[6]={15,59,22,34,7,78};
	HashTable ht;
	CreateHash(ht,items,6);
	DisplayHash(ht);
	x.key=7;
	addr=HashSearch(ht,x);
	if(addr>=0)
		printf("����������Ԫ��(%d)�Ĺ�ϣ��ַΪ[%d]\n",x.key,addr);
	else
		printf("��ϣ���в���������Ԫ��(%d)",x.key);	
	return 0;
}
