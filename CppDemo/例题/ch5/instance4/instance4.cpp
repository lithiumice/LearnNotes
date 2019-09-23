// instance4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "mqube.h"


int main(int argc, char* argv[])
{	
	Qube mqq;
	MQube mq=&mqq;
	int choice=0;
	int n=0;
	do{
		printf("		  menu					\n");
		printf("--------------------------------------\n");
		printf("\n	(1)Gernerate Magic Cube....		\n");
		printf("\n	(0)exit....		\n");
		printf("\nPlease select one:");
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:
			printf("\nPlease input n:");
			scanf("%d",&n);
			InitMQube(&mq,n);
			GenerateMQube(mq);
			DispMQube(*mq);
			break;
		case 0:			
			exit(0);
		}
	}while(1);	
	return 0;
}