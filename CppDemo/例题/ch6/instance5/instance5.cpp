// instance5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "assn.h"


int main(int argc, char* argv[])
{
	BiTreeLink root;
	DataType x,y;	
	int choice=0;
	int n=0;
	InitBiTree(&root);
	do{
		printf("*********************************\n");
		printf("*		menu		*\n");
		printf("*-------------------------------*\n");
		printf("*	1.��������  		*\n");
		printf("*	2.���ӻ�Ա  		*\n");
		printf("*	3.�޸�������Ϣ  	*\n");
		printf("*	4.�޸Ļ�Ա��Ϣ  	*\n");
		printf("*	5.��������  		*\n");
		printf("*	6.��ѯ������Ϣ  	*\n");
		printf("*	7.��ѯ��Ա��Ϣ  	*\n");
		printf("*	8.��ʾ������Ϣ  	*\n");
		printf("*	0.�˳�			*\n");
		printf("*********************************\n");
		printf("\nPlease select(1,2,3,4,5,6,7,8,0):");
		scanf("%d",&choice);
		if(choice<0 || choice>8)
			continue;
		switch(choice)
		{
		case 1:			
			Receive("\n��������������:",x.name);
			x.type=0;
			Receive("\n������������ϵ�绰:",x.phone);
			Receive("\n������������ĸ����ŵĺ��:",y.name);
			y.type=0;
			InsertSilbling(root,y,x);
			break;
		case 2:			
			break;
		case 3:
			Receive("\n��������������:",x.name);			
			x.type=0;
			Receive("\n�������µ���������:",y.name);			
			y.type=0;			
			Receive("\n�������µ�������ϵ�绰:",y.phone);					
			Update(root,x,y);
			break;
		case 4:			
			break;
		case 5:
			break;
		case 6:			
			Receive("\n��������������:",x.name);
			x.type=0;			
			DispNode(root,x);
			break;		
		case 7:
			Receive("\n�������Ա����:",x.name);			
			x.type=1;
			DispNode(root,x);
			break;
		case 8:
			DispBiTree(root);
			printf("\n\n");
			break;
		case 0:			
			exit(0);
		}
	}while(1);
	return 0;
}

