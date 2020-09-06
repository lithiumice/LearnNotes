# include "stdio.h"
# include "string.h"
int main()
{
	char ch[50];
	int i;
	while(ch!="\n")
	{
		printf("YOU:");
		gets(ch);
		i=strlen(ch);
		if(ch[i-1]=='?')
		{
			ch[i-1]='!';
		}
		else
		{
			ch[i]='!';
			ch[i+1]='\0';
		}
		printf("Robot:%s\n",ch);
	}
	return 0;
}
