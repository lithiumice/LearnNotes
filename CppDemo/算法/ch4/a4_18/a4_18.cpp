// a4_18.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

void GetNext(SqString T, int next[])
{
          int j=1, k=0; 
		  next[0]=-1;
		  next[1]=0;
          while(j<T.length)
		  {
			  if ( T.ch[j] == T.ch[k])
			  { 
				  ++k; 
				  ++j; 
				  next[j] = k;
			  }
			  else if(k ==0)
			  {
				  ++j;
				  next[j]=0;
			  }
			  else    
				  k= next[k];
		  }
}



int main(int argc, char* argv[])
{

	//SqString s={"cbacb",5};
	SqString s={"abacababcc",10};
	int next[10];
	GetNext(s,next);
	for(int i=0;i<10;i++)
		printf("%d\t",next[i]);

	return 0;
}
