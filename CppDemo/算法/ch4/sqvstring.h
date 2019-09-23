/*
     串的变长顺序存储
*/

#include<stdio.h>
#include "malloc.h"
#include "string.h"

/*存储结构*/
typedef struct{
	char *ch;
	int length;
}SqVString;

/*算法4-7初始化串*/
void InitString(SqVString *S, char *str)
{
	int i;
	char *c;
	int len=0;		
    c=str;
	while(*c!='\0'){len++;c++;}  /*求str的长度*/
	S->ch = (char *)malloc(len*sizeof(char));	/*申请动态数组空间*/
	S->length = len;/*置串的当前长度值*/
	for(i = 0; i < S->length; i++)
		S->ch[i] = str[i];					/*赋值串值*/
}

/*算法4-8串插入*/
int StrInsert(SqVString *S,int pos,SqVString T)
{
	int i;
	int len;	
	if(pos<0 || pos>S->length)
	{
		printf("插入位置不合法，其取值范围应该是[0,length]");
		return 0;
	}
	len=S->length+T.length;
	S->ch=(char*)realloc(S->ch,len*sizeof(char));
	if(!S->ch)
	{
		printf("分配空间出错，无法完成串插入操作");
		return 0;
	}	
	for(i=S->length-1;i>=pos;i--)
		S->ch[i+T.length]=S->ch[i];
	for(i=0; i<T.length; i++)
		S->ch[i+pos]=T.ch[i];	
	S->length=len;	
	return 1;
}

/*算法4-9串删除*/
int StrDelete(SqVString *S,int pos,int len)
{
	int i;
	int length;	
	char *str;
	if(pos<0 || len<=0 || pos>S->length || S->length<=0)
	{
		printf("删除位置pos及删除长度len不合法，无法完成删除操作！");
		return 0; 
	}
	length=S->length-len;
	if(length<=0) length=pos;  /*若pos+len大于串长，则从pos删到串尾*/
	str=(char*)malloc(length*sizeof(char));
	if(!str)
	{
		printf("分配空间出错，无法完成串删除操作");
		return 0;
	}	
	for(i=0; i<pos; i++)
		str[i]=S->ch[i];
	for(i=pos+len; i<S->length; i++)
		str[i-len]=S->ch[i];
	free(S->ch);
	S->length=length;
	S->ch=str;		
	return 1; 
}

/*算法4-10求子串*/
int SubStr(SqVString S,int pos,int len,SqVString *T)
{
	int i;	
	if(S.length<=0)
	{
		printf("空串，无法完成求子串操作！");
		return 0; 
	}
	if(pos<0 || pos>S.length || len<=0)
	{
		printf("子串位置pos及子串长度len不合法，无法完成求子串操作！");
		return 0; 
	}
	if(pos+len>S.length) len=S.length-pos+1;	/*当子串长度超过主串长度，则只取到串尾即可*/
	if(T->length) free(T->ch);  /*释放S的原有空间*/
	T->ch=(char*)malloc(len*sizeof(char));
	if(!T->ch)
	{
		printf("分配空间出错，无法完成求子串操作");
		return 0;
	}	
	for(i=0;i<len;i++)
		T->ch[i]=S.ch[i+pos];
	T->length=len;
	return 1; 
}


/*算法4-11串连接*/
int Concat(SqVString *S,SqVString T)
{
	int i;
	int len;
	len=S->length+T.length;
	S->ch=(char*)realloc(S->ch,len*sizeof(char));
	if(!S->ch)
	{
		printf("分配空间出错，无法完成串连接操作");
		return 0;
	}
	for(i=0;i<T.length;i++)
		S->ch[i+S->length]=T.ch[i];
	S->length=len;	
	return 1; 
}

/*算法4-12串赋值*/
int StrAssign(SqVString *S,char *value)
{
	int count=0;
	int i;
	char *c;
	//S=(SqVString*)malloc(sizeof(SqVString));
	if(S->length!=0) free(S->ch);  /*释放S的原有空间*/	
	c=value;
	while(*c!='\0'){count++;c++;}  /*求value的长度*/
	if(!count)/*value为空串*/
	{
		S->ch=NULL;
		S->length=0;
	}
	else
	{
		S->ch=(char*)malloc(count);
		if(!S->ch)
		{
			printf("分配空间出错，无法完成串赋值操作");
			return 0;
		}
		for(i=0;i<count;i++)
			S->ch[i]=value[i];
		S->length=count;
	}
	return 1;
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
