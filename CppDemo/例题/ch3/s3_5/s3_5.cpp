// s3_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstack.h"

DataType GetBottom(SqStack S)
{
	DataType x,y;
	SqStack tmp;
	InitStack(&tmp);				/*ʹ���㷨3-1*/
	/*��ȡջ��Ԫ�أ�����ʹ���㷨3-2��3-3��3-4*/
	while(!StackEmpty(S)){Pop(&S,&x);	Push(&tmp,x);	}
	/*�ָ�ԭ��ջ*/
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
	printf("\n");

	x=GetBottom(sta);	
	printf("%d\n",x);	
	return 1;
}

