// instance2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "carstop.h"



void main()
{
	SqStack park,way;
	LinkQueue pavement;
	int choice;
	float UnitPrice=5;/*单价*/
	InitStack(&park); /*初始化停车场*/ 
	InitStack(&way); /*初始化让路的临时栈*/
	InitQueue(&pavement); /*初始化便道*/
	do
	{ 
		printf("\n		停车场管理系统				\n");
		printf("\n------------------主菜单----------------------\n");
		printf("	(1) 车辆到达...		\n");
		printf("	(2) 车辆离开...		\n");
		printf("	(3) 显示停车场信息...		\n");
		printf("	(4) 显示等待车辆信息...		\n");
		printf("	(5) 修改单价...		\n");
		printf("	(0) 退出系统...		\n");
		printf("\n请选择(1,2,3,4,0)：");
		scanf("%d",&choice);
		if(choice<0 && choice>4) continue;		
		switch(choice)
		{ 
		case 1:Reach(&park,&pavement);break; /*车辆到达停车场*/
		case 2:Leave(&park,&way,&pavement,UnitPrice);break; /*车辆离开*/
		case 3:DispPark(&park);break; /*显示停车场信息*/
		case 4:DispPave(&pavement);break;/*显示等待车辆信息*/
		case 5:UnitPrice=ModifyUnitPrice();break;
		case 0:exit(0); /*退出主程序*/
		default: break;
		}
	}while(1);
	
}






