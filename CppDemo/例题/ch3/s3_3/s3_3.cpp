// s3_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstack.h"

int main(int argc, char* argv[])
{
	SqStack sta;
	int i,e;
	int length=7;
	int fab[7]={0,1,1,2,3,5,8};
	InitStack(&sta);					
	printf("ԭʼ���У�\n");
	
	for(i=0;i<length;i++)
	{
		if(!Push(&sta,fab[i]))
		{
			printf("�޷������ת������\n");
			return 0;
		}
		printf("%d\t",fab[i]);
	}
	printf("\n��ת������У�\n");
	
	while(!StackEmpty(sta))
	{
		if(!Pop(&sta,&e))
		{
			printf("�޷������ת������\n");
			return 0;
		}
		printf("%d\t",e);
	}
	return 1;
}
