// S4_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string.h"
#include "stdio.h"

void Change(char *cname,char* ename)
{
	char* r;
	r=strchr(cname,' ');
	*r='\0';
	strcpy(ename,r+1);
	strcat(ename," ");
	strcat(ename,cname);
}


int main(int argc, char* argv[])
{
	char cn[]="wang zhiqiang";
	char en[20];
	Change(cn,en);
	printf("%s\n",en);
	return 1;

}
