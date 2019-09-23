/*
     串的定长顺序存储
*/

#include<stdio.h>

/*存储结构*/
#define STRSIZE 100

typedef struct{
	char ch[STRSIZE];
	int length;
}SqString;


/*算法4-1初始化串*/
int InitString(SqString *S,char *str)
{	
	int i, len=0;
	char *c=str;
	while(*c!='\0'){len++;c++;}  		/*求str的长度*/	
	S->length = len;               		/*置串的当前长度值*/
	for(i = 0; i < S->length; i++)		/*赋值串值*/
		S->ch[i] = str[i];	
	return 1;
}


/*算法4-2串插入*/
int StrInsert(SqString *S,int pos,SqString T)
{
	int i;	
	if(pos<0 || pos>S->length)
	{
		printf("插入位置不合法，其取值范围应该是[0,length]");
		return 0;
	}
	/*插入后串长≤STRSIZE，则正常插入*/
	if (S->length + T.length<=STRSIZE) 
	{
		for(i=S->length-1; i>=pos-1; i--)
			S->ch[i+T.length]=S->ch[i];
		for(i=0; i<T.length; i++)
			S->ch[i+pos]=T.ch[i];
		S->length+=T.length;
	}
	/*插入后串长>STRSIZE，则串T可以全部插入，串S部分被截断*/
	else if(T.length+pos<=STRSIZE) 
	{
		for (i=STRSIZE-1;i>T.length+pos-1;i--) 
			S->ch[i]=S->ch[i-T.length];
		for (i=0;i<T.length;i++)
			S->ch[i+pos]=T.ch[i];
		S->length=STRSIZE;
	}
	/*插入后串长>STRSIZE,并且串T部分也要被截断*/
	else 
	{ 
		for (i=0;i<STRSIZE-pos;i++)
			S->ch[i+pos]=T.ch[i];
		S->length=STRSIZE;
	}
	return 1;
}

/*算法4-3串删除*/
int StrDelete(SqString *S,int pos,int len)
{
	int i;
	if(S->length<=0)
	{
		printf("空串，无法进行删除操作！");
		return 0; 
	}
	if(pos<0 || len<=0 || pos>S->length)
	{
		printf("删除位置pos以及删除长度len不合法，无法完成删除操作！");
		return 0; 
	}
	if(pos+len>S->length) len=S->length-pos+1;	/*当删除长度超过串长度，则只删到串尾即可*/
	for(i=pos+len;i<S->length;i++)
		S->ch[i-len]=S->ch[i];
	S->length-=len;
	return 1; 
}

/*算法4-4求子串*/
int SubStr(SqString S,int pos,int len,SqString *T)
{
	int i;
	if(S.length<=0)
	{
		printf("空串，无法完成求子串操作！");
		return 0; 
	}
	if(pos<0 || len<=0 || pos>S.length)
	{
		printf("子串的位置pos以及子串长度len不合法，无法完成求子串操作！");
		return 0; 
	}
	if(pos+len>S.length) len=S.length-pos+1;	/*当子串长度超过主串长度，则只取到串尾即可*/
	for(i=0;i<len;i++)
		T->ch[i]=S.ch[i+pos];
	T->length=len;
	return 1; 
}


/*算法4-5串连接*/
int Concat(SqString *S,SqString T)
{
	int i;	
	if(S->length+T.length<=STRSIZE)/*连接后串长≤STRSIZE*/
	{
		for(i=0;i<T.length;i++)
			S->ch[i+S->length]=T.ch[i];
		S->length+=T.length;
	}
	else if(S->length<STRSIZE)/*连接后串长大于STRSIZE，但串S的长度小于STRSIZE，即连接后串T的部分字符序列被舍弃*/
	{
		for(i=S->length;i<STRSIZE;i++)
			S->ch[i]=T.ch[i-S->length];
		S->length=STRSIZE;
	}	
	return 1; 
}

/**/
int StrCmp(SqString S, SqString T)
{ 
	int i;
	for (i=0;i<S.length && i<T.length;i++)
		if (S.ch[i]!=T.ch[i]) 
			return(S.ch[i] - T.ch[i]);
	return(S.length - T.length);
}

/*算法2-7串定位
int GetElem(SqList L,int pos,DataType *item)
{
	if(ListEmpty(L))
		return 0;
	if(pos<=0 || pos>L.length)
	{
		printf("位置信息输入不合法，请重新输入");
		return 0;
	}
	*item=L.ch[pos-1];
	return 0;
}*/

/*算法2-8遍历顺序表
int TraverseList(SqList L)
{
	int i;
	for(i=0;i<L.length;i++)
		printf("%d\t",L.ch[i]);
	printf("\n");
	return 1;
}*/
