// s3_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstack.h"

DataType GetBottom(SqStack S)
{
	DataType x,y;
	SqStack tmp;
	InitStack(&tmp);				/*使用算法3-1*/
	/*获取栈底元素，其中使用算法3-2、3-3和3-4*/
	while(!StackEmpty(S)){Pop(&S,&x);	Push(&tmp,x);	}
	/*恢复原堆栈*/
	while(!StackEmpty(tmp)){Pop(&tmp,&y);Push(&S,y);}
	return x;
}


int main(int argc, char* argv[])
{
	SqStack sta;
	int i;
	int length=7;
	int fab[7]={0,1,1,2,3,5,8};
	DataType x;
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
	printf("\n");

	x=GetBottom(sta);	
	printf("%d\n",x);	
	return 1;
}

