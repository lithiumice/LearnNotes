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
		printf("*	1.增加社团  		*\n");
		printf("*	2.增加会员  		*\n");
		printf("*	3.修改社团信息  	*\n");
		printf("*	4.修改会员信息  	*\n");
		printf("*	5.撤销社团  		*\n");
		printf("*	6.查询社团信息  	*\n");
		printf("*	7.查询会员信息  	*\n");
		printf("*	8.显示所有信息  	*\n");
		printf("*	0.退出			*\n");
		printf("*********************************\n");
		printf("\nPlease select(1,2,3,4,5,6,7,8,0):");
		scanf("%d",&choice);
		if(choice<0 || choice>8)
			continue;
		switch(choice)
		{
		case 1:			
			Receive("\n请输入社团名字:",x.name);
			x.type=0;
			Receive("\n请输入社团联系电话:",x.phone);
			Receive("\n请输入插入在哪个社团的后边:",y.name);
			y.type=0;
			InsertSilbling(root,y,x);
			break;
		case 2:			
			break;
		case 3:
			Receive("\n请输入社团名字:",x.name);			
			x.type=0;
			Receive("\n请输入新的社团名字:",y.name);			
			y.type=0;			
			Receive("\n请输入新的社团联系电话:",y.phone);					
			Update(root,x,y);
			break;
		case 4:			
			break;
		case 5:
			break;
		case 6:			
			Receive("\n请输入社团名字:",x.name);
			x.type=0;			
			DispNode(root,x);
			break;		
		case 7:
			Receive("\n请输入会员名字:",x.name);			
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

