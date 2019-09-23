// s5_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glink.h"

void DispGLink(GLink GL)
{
	if(GL)
	{
		switch(GL->flag)
		{
		case 1: 				
			printf("(");
			if(!GL->sublist)	
				printf(" ");
			else
				DispGLink(GL->sublist); 
			printf(")");
			break;
		case 0: 				
			printf("%c",GL->data); 		
			break;
		}
		if(GL->next) 			
		{
			printf(",");
			DispGLink(GL->next);
		}
	}
}


int main(int argc, char* argv[])
{
	GLink p;	
	char str[]="(a,b,(c,d,e,(f,(g))))";
	p=InitGLink(str);		
	DispGLink(p);	
	return 0;
}
