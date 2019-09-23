// instance7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "popular.h"

int main(int argc, char* argv[])
{
	HashTable ht;	
	int choice=0;	
	DataType x;			
	char filename[]="boards.dat";	
	CreateBoard(ht,filename);
	do{
		printf("*************************************************\n");
		printf("*		ʮ�����и������а�		*\n");
		printf("*-----------------------------------------------*\n");
		printf("*	1.��ϲ���ĸ���ͶƱ 			*\n");
		printf("*	2.�鿴�ϰ�����������			*\n");
		printf("*	3.�鿴����Ʊ�� 				*\n");
		printf("*	4.���а�  				*\n");
		printf("*	0.�˳�					*\n");
		printf("*************************************************\n");
		printf("\nPlease select(1,2,3,4,0):");
		scanf("%d",&choice);
		if(choice<0 || choice>4)
			continue;
		switch(choice)
		{
		case 1:	
			flushall();
			printf("\n�������������:");
			gets(x.name);
			printf("\n���������ƴ������:");
			gets(x.pinyin);
			printf("\n�����������������:");
			gets(x.song);			
			x.key=1;
			//x.date=time(NULL);
			Vote(ht,filename,x);			
			break;
		case 2:	
			flushall();
			printf("\n���������ƴ������:");
			gets(x.pinyin);
			DispSong(ht,x);
			break;
		case 3:
			flushall();
			printf("\n���������ƴ������:");
			gets(x.pinyin);
			DispVote(ht,x);
			break;
		case 4:	
			DispBoard(filename);			
			break;		
		case 0:			
			exit(0);
		}
	}while(1);
	return 0;
}