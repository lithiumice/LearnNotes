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
		printf("*		十大流行歌手排行榜		*\n");
		printf("*-----------------------------------------------*\n");
		printf("*	1.给喜欢的歌手投票 			*\n");
		printf("*	2.查看上榜歌手主打歌曲			*\n");
		printf("*	3.查看歌手票数 				*\n");
		printf("*	4.排行榜  				*\n");
		printf("*	0.退出					*\n");
		printf("*************************************************\n");
		printf("\nPlease select(1,2,3,4,0):");
		scanf("%d",&choice);
		if(choice<0 || choice>4)
			continue;
		switch(choice)
		{
		case 1:	
			flushall();
			printf("\n请输入歌手名字:");
			gets(x.name);
			printf("\n请输入歌手拼音名字:");
			gets(x.pinyin);
			printf("\n请输入主打歌曲名字:");
			gets(x.song);			
			x.key=1;
			//x.date=time(NULL);
			Vote(ht,filename,x);			
			break;
		case 2:	
			flushall();
			printf("\n请输入歌手拼音名字:");
			gets(x.pinyin);
			DispSong(ht,x);
			break;
		case 3:
			flushall();
			printf("\n请输入歌手拼音名字:");
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