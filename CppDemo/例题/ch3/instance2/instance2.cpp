// instance2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "carstop.h"



void main()
{
	SqStack park,way;
	LinkQueue pavement;
	int choice;
	float UnitPrice=5;/*����*/
	InitStack(&park); /*��ʼ��ͣ����*/ 
	InitStack(&way); /*��ʼ����·����ʱջ*/
	InitQueue(&pavement); /*��ʼ�����*/
	do
	{ 
		printf("\n		ͣ��������ϵͳ				\n");
		printf("\n------------------���˵�----------------------\n");
		printf("	(1) ��������...		\n");
		printf("	(2) �����뿪...		\n");
		printf("	(3) ��ʾͣ������Ϣ...		\n");
		printf("	(4) ��ʾ�ȴ�������Ϣ...		\n");
		printf("	(5) �޸ĵ���...		\n");
		printf("	(0) �˳�ϵͳ...		\n");
		printf("\n��ѡ��(1,2,3,4,0)��");
		scanf("%d",&choice);
		if(choice<0 && choice>4) continue;		
		switch(choice)
		{ 
		case 1:Reach(&park,&pavement);break; /*��������ͣ����*/
		case 2:Leave(&park,&way,&pavement,UnitPrice);break; /*�����뿪*/
		case 3:DispPark(&park);break; /*��ʾͣ������Ϣ*/
		case 4:DispPave(&pavement);break;/*��ʾ�ȴ�������Ϣ*/
		case 5:UnitPrice=ModifyUnitPrice();break;
		case 0:exit(0); /*�˳�������*/
		default: break;
		}
	}while(1);
	
}






