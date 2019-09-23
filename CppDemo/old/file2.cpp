#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

int main()
{
	int yesno(char* s);
	 FILE* in,*out;
	 char ch,sfn[50],tfn[50];
	 puts("input:");
	 gets(sfn);
	 if((in=fopen(sfn,"rb"))==NULL)
	 {
	 	printf("fail!\n");
	 	return -1;
	 }
	 while(yesno("copy to toggle."))
	 {
	 	puts("file name");
	 	gets(tfn);
	 	rewind(in);
	 	if((in=fopen(tfn,"wb"))==NULL)
	 {
	 	printf("fail!\n");
	 	return -1;
	 }
	 	while(1)
	 	{
	 		ch=fgetc(in);
	 		if(!feof(in))
	 		{
	 			fputc(ch,out);
	 			
			 }
			 else
			 break;
			 
		 }
		 fclose(in);
		 return 0;
	 }
	
	
	return 0;
}

int yesno(char* s)
{
	char c;
	while(1)
	{
		printf("%s(y/n?)",s);
		c=getch();
		switch(c)
		{
			case 'Y':return 1;
			case 'N':return 0;
			default:break;
		}
	}
}
