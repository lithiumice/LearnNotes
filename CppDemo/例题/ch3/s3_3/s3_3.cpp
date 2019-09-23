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
	printf("原始序列：\n");
	
	for(i=0;i<length;i++)
	{
		if(!Push(&sta,fab[i]))
		{
			printf("无法完成逆转操作！\n");
			return 0;
		}
		printf("%d\t",fab[i]);
	}
	printf("\n逆转后的序列：\n");
	
	while(!StackEmpty(sta))
	{
		if(!Pop(&sta,&e))
		{
			printf("无法完成逆转操作！\n");
			return 0;
		}
		printf("%d\t",e);
	}
	return 1;
}
