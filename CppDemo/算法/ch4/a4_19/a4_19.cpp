// a4_19.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../sqstring.h"

int KMPIndex(SqString S, int pos, int next[] , SqString T)
{
          int i=pos, j=0, r;
          while (i<S.length && j<T.length)
		  {
			  if (S.ch[i] == T.ch[j])
			  { 
				  ++i; 
				  ++j; 
			  }
			  else if(j==0)
				  ++i;
			  else 
				  j = next[j];
          }
          if (j>=T.length) 
			  r=i-T.length;
          else 
			  r=-1;
		  return r;
}

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
	//SqString s={"cbaccbacbbb",11};
	SqString s={"SqString SqVString LinkString",29};
	int next[5];
	//SqString t={"cbacb",5};
	SqString t={"String",6};
	GetNext(t,next);
	for(int i=0;i<6;i++)
		printf("%d\t",next[i]);
	printf("\n%d\n",KMPIndex(s,15,next,t));

	return 0;
}


