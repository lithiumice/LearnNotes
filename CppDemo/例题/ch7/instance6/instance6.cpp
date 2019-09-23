// instance6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "travel.h"

int main(int argc, char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;
	DataType d[]={{1,"午门","午门是紫禁城的正门，午门有五个门洞，明三暗五。"},{2,"太和殿","俗称金銮殿，是紫禁城最高最大的宫殿，是朝廷举行重大典礼的地方。"},{3,"乾清宫","是后三宫中最大的宫殿，是清朝康熙帝以前的皇帝居住的寝宫"},{4,"御花园","宫中最大花园，供帝后玩赏"},{5,"神武门","紫禁城北门，故宫博物院正门"},{6,"养心殿","雍正时期，皇帝的寝宫"},{7,"西六宫","西六宫包括储秀宫，翊坤宫，永寿宫，咸福宫，长春宫，太极殿。"},{8,"东六宫","东六宫包括钟翠宫，承乾宫，景仁宫，景阳宫，永和宫，延禧宫。"}};
	int m[][MAXVEX]={{MAXWEIGHT,1500,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},{1500,MAXWEIGHT,1000,MAXWEIGHT,MAXWEIGHT,800,MAXWEIGHT,MAXWEIGHT},{MAXWEIGHT,1000,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,300,200,200},{MAXWEIGHT,MAXWEIGHT,400,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,100,100},{MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,200,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},{MAXWEIGHT,800,300,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,50,400},{MAXWEIGHT,MAXWEIGHT,200,100,250,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},{MAXWEIGHT,MAXWEIGHT,200,100,260,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT}};
	int dis[5],path[MAXVEX];
	int choice=0,start,end;
	char vname[20];
	DataType x;
	CreateGraph(g,m,d,8);
	do{
		printf("*************************************************\n");
		printf("*		故宫导游咨询系统		*\n");
		printf("*-----------------------------------------------*\n");
		printf("*	1.查询景点信息 				*\n");
		printf("*	2.给出到某个景点的最佳路线		*\n");
		printf("*	3.给出到所有景点的最佳路线 		*\n");
		printf("*	4.修改景点信息  			*\n");
		printf("*	5.添加景点		  		*\n");
		printf("*	6.撤销旅游线路  			*\n");
		printf("*	0.退出					*\n");
		printf("*************************************************\n");
		printf("\nPlease select(1,2,3,4,5,6,0):");
		scanf("%d",&choice);
		if(choice<0 || choice>8)
			continue;
		switch(choice)
		{
		case 1:
			printf("\n请输入景点名字:");
			scanf("%s",vname);			
			QueryVex(g,vname);			
			break;
		case 2:	
			printf("\n请输入你现在所在的景点名称:");
			scanf("%s",vname);
			start=Locate(g,vname);
			printf("\n请输入你要去的景点名称:");
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
			printf("\n请输入景点名称:");
			scanf("%s",vname);
			start=Locate(g,vname);
			printf("\n请输入修改后的景点名称:");
			scanf("%s",vname);
			strcpy(x.name,vname);
			printf("\n请输入修改后的景点编号:");
			scanf("%d",&end);
			x.no=end;
			printf("\n请输入修改后的景点简介:");
			scanf("%s",vname);
			strcpy(x.desc,vname);
			PutVex(g,start,x);
			break;
		case 5:			
			break;
		case 6:
			printf("\n请输入起始景点名称:");
			scanf("%s",vname);
			start=Locate(g,vname);
			printf("\n请输入结束景点名称:");
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

