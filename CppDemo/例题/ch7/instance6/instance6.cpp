// instance6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "travel.h"

int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;
	DataType d[]={{1,"����","�������Ͻ��ǵ����ţ�����������Ŷ����������塣"},{2,"̫�͵�","�׳ƽ��ǵ���Ͻ���������Ĺ���ǳ�͢�����ش����ĵط���"},{3,"Ǭ�幬","�Ǻ����������Ĺ�����峯��������ǰ�Ļʵ۾�ס���޹�"},{4,"����԰","�������԰�����ۺ�����"},{5,"������","�Ͻ��Ǳ��ţ��ʹ�����Ժ����"},{6,"���ĵ�","Ӻ��ʱ�ڣ��ʵ۵��޹�"},{7,"������","�������������㹬������������ٹ����̸�������������̫���"},{8,"������","�����������Ӵ乬����Ǭ�������ʹ��������������͹�����������"}};
	int m[][MAXVEX]={{MAXWEIGHT,1500,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},{1500,MAXWEIGHT,1000,MAXWEIGHT,MAXWEIGHT,800,MAXWEIGHT,MAXWEIGHT},{MAXWEIGHT,1000,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,300,200,200},{MAXWEIGHT,MAXWEIGHT,400,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,100,100},{MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,200,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},{MAXWEIGHT,800,300,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,50,400},{MAXWEIGHT,MAXWEIGHT,200,100,250,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},{MAXWEIGHT,MAXWEIGHT,200,100,260,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT}};
	int dis[5],path[MAXVEX];
	int choice=0,start,end;
	char vname[20];
	DataType x;
	CreateGraph(g,m,d,8);
	do{
		printf("*************************************************\n");
		printf("*		�ʹ�������ѯϵͳ		*\n");
		printf("*-----------------------------------------------*\n");
		printf("*	1.��ѯ������Ϣ 				*\n");
		printf("*	2.������ĳ����������·��		*\n");
		printf("*	3.���������о�������·�� 		*\n");
		printf("*	4.�޸ľ�����Ϣ  			*\n");
		printf("*	5.��Ӿ���		  		*\n");
		printf("*	6.����������·  			*\n");
		printf("*	0.�˳�					*\n");
		printf("*************************************************\n");
		printf("\nPlease select(1,2,3,4,5,6,0):");
		scanf("%d",&choice);
		if(choice<0 || choice>8)
			continue;
		switch(choice)
		{
		case 1:
			printf("\n�����뾰������:");
			scanf("%s",vname);			
			QueryVex(g,vname);			
			break;
		case 2:	
			printf("\n���������������ڵľ�������:");
			scanf("%s",vname);
			start=Locate(g,vname);
			printf("\n��������Ҫȥ�ľ�������:");
			scanf("%s",vname);
			end=Locate(g,vname);
			if(start!=-1 || end!=-1)
			{
				Dijstra(g,start,dis,path);
				DispPath(g,path,dis,start,end);
			}
			break;
		case 3:
			break;
		case 4:	
			printf("\n�����뾰������:");
			scanf("%s",vname);
			start=Locate(g,vname);
			printf("\n�������޸ĺ�ľ�������:");
			scanf("%s",vname);
			strcpy(x.name,vname);
			printf("\n�������޸ĺ�ľ�����:");
			scanf("%d",&end);
			x.no=end;
			printf("\n�������޸ĺ�ľ�����:");
			scanf("%s",vname);
			strcpy(x.desc,vname);
			PutVex(g,start,x);
			break;
		case 5:			
			break;
		case 6:
			printf("\n��������ʼ��������:");
			scanf("%s",vname);
			start=Locate(g,vname);
			printf("\n�����������������:");
			scanf("%s",vname);
			end=Locate(g,vname);
			DeleteArc(g,start,end);
			break;		
		case 0:			
			exit(0);
		}
	}while(1);
	return 0;
}

