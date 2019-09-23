// instance3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "../sqvstring.h"

#define MAXSTRING 60
#define MAXLINE 24

SqVString * lines[MAXLINE];

void InputString()
{
	char buffer[MAXSTRING],str[1];
	SqVString *tmp;
	int LineNum=0;

	flushall();
	printf("\n[�������ı���ÿ���Իس�������һ����#����]\n");
	do
	{
		gets(buffer);
		tmp=(SqVString*)malloc(sizeof(SqVString));
		InitString(tmp,buffer);
		lines[LineNum]=tmp;
		LineNum++;
	}while(buffer[0]!='#');
	printf("OK...\n");
}

void DeleteString()
{
	int i;
	printf("\n������Ҫɾ���е��кţ�");
	scanf("%d",&i);
	free(lines[i-1]);
	while(lines[i]->ch[0]!='#')
	{
		lines[i-1]=lines[i];
		i++;
	}
	lines[i-1]=lines[i];
	printf("OK...\n");
}

void InsertSubstring()
{
	int i=0;
	int pos=0;
	char buffer[MAXSTRING];
	SqVString tmp;

	
	printf("\n�������Ӵ����ڵ��кţ�");
	scanf("%d",&i);
	printf("\n���������λ�ã�");
	scanf("%d",&pos);
	printf("\n�������Ӵ�ֵ��");	
	scanf("%s",buffer);
	
	InitString(&tmp,buffer);
	StrInsert(lines[i],pos,tmp);
	printf("OK...\n");
}

void DeleteSubstring()
{
	int i=0;
	int pos=0;	
	int len=0;

	
	printf("\n�������Ӵ����ڵ��кţ�");
	scanf("%d",&i);
	printf("\n������ɾ������ʼλ�ã�");
	scanf("%d",&pos);
	printf("\n������ɾ�����ַ�����");	
	scanf("%d",&len);
	StrDelete(lines[i],pos,len);
	printf("OK...\n");
}

void FindSubstring()
{
	int i=0;
	int pos=0;	
	char buffer[MAXSTRING];
	int next[MAXSTRING];
	SqVString tmp;
	
	printf("\n������Ҫ���ҵ��Ӵ���");
	scanf("%s",buffer);
	InitString(&tmp,buffer);

	GetNextval(tmp,next);
	while(lines[i]->ch[0]!='#')
	{
		if((pos=KMPIndex(*lines[i],0,next,tmp))!=-1)
		{
			printf("[�Ӵ�%s�ڵ�%d�е�%dλ���ϳ���]\n",buffer,i+1,pos);
			return;
		}
		i++;
	}

	printf("OK...\n");
}

void DisplayString()
{
	int i=0;
	while(lines[i]->ch[0]!='#')
	{
		printf("%s\n",lines[i]->ch);
		i++;
	}
	printf("OK...\n");
}

int main(int argc, char* argv[])
{
	int choice;
	do
	{		
		printf("\n");		
		printf("\n           ���˵�          \n");
		printf("\n-----------------------------------\n");
		printf("\n     1     �����ı�        \n");
		printf("\n     2     ɾ��һ��        \n");
		printf("\n     3     �����Ӵ�        \n");
		printf("\n     4     ɾ���Ӵ�        \n");
		printf("\n     5     �����Ӵ�        \n");
		printf("\n     6     ��ʾ�ı�        \n");
		printf("\n     0     �˳�            \n");
		printf("\n-----------------------------------\n");
		printf("����������ѡ��( 1, 2, 3, 4, 5, 6, 0):");

		scanf("%d",&choice);
		if(choice<0 || choice >6)
			continue;
		switch(choice)
		{
		case 1:
			InputString();
			break;
		case 2:
			DeleteString();
			break;
		case 3:
			InsertSubstring();
			break;
		case 4:
			DeleteSubstring();
			break;
		case 5:
			FindSubstring();
			break;
		case 6:
			DisplayString();
			break;
		case 0:
			exit(0);
		}
	}while(1);

	return 0;
}
