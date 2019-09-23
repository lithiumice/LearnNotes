#include "stdio.h"
#include "string.h"
#include "stdlib.h"
int main()
{
	int insertChar(char* sv,char sr,char re);
	char r,p,q[50];
	char* s=q;
	int i;
	scanf("%s",&q);
	p=getchar();
	r=getchar();
	i=insertChar(s,p,r);
	if(!i)
	{
	puts(q);
	}
	else printf("error!");
	return 0;
}

int insertChar(char* sv,char sr,char re)
	{
		int i,j;
		char* temp,*cha;
		for(temp=sv;temp!='\0';temp++)
			{
				;
			}
		cha=strchr(sv,sr);
		for(;temp>=cha;temp--)
		{
		*(temp+1)=*temp;
		}
		*cha=re;
		return 0;
	}
