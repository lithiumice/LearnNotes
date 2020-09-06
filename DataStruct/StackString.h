#include <stdio.h>
#include <stdlib.h>


typedef struct{
	char *ch;
	int length;
}SqVString;


void InitString(SqVString *S, char *str)
{
	//S为指向字符串的指针, str为字符序列
	int i, len = 0;
	char *c = str;
	while(*c != '\0')
	{
		len++;
		c++;
	}
	S -> ch = (char*)malloc(len*sizeof(char));
	S -> length = len;
	for (i = 0; i < S -> length; i++)
	{
		S -> ch[i] = str[i];
	}
}


int StrInsert(SqVString *S, int pos, SqVString T)
{
	//S为指向字符串的指针, pos为插入位置, T为待插入的子串
	int i, len;
	if(pos < 0 || pos > S -> length)
	{
		printf("illegal insert position!\n");
		return 0;
	}
	len = S -> length + T.length;
	S -> ch = (char*)realloc(S -> ch, len*sizeof(char));
	if(!S -> ch)
	{
		printf("error while realloc!\n");
		return 0;
	}
	for(i = S -> length -1; i >= pos; i--)
		S -> ch[i + T.length] = S -> ch[i];
	for(i = 0; i < T.length; i++)
		S -> ch[i + pos] = T.ch[i];
	S -> length = len;
	return 1;
}


int StrDelete(SqVString *S, int pos, int len)
{
	//S为指向字符串的指针, pos为删除位置, len为删除子串的长度
	int i, size;
	char *str;
	if(pos < 0 || pos > S -> length || len <= 0 || S -> length <= 0)
	{
		printf("illegal length or delete position!\n");
		return 0;
	}
	size = S -> length - len;
	if(size <= 0)
		size = pos;
	str = (char*)malloc(size*sizeof(char));
	if(!str)
	{
		printf("error while malloc!\n");
		return 0;
	}
	for(i = 0; i < pos; i++)
		str[i] = S -> ch[i];
	for(i = pos + len; i < S -> length; i++)
		str[i - len] = S -> ch[i];
	free(S -> ch);
	S -> length = size;
	S -> ch = str;
	return 1;
}


int SubStr(SqVString S, int pos, int len, SqVString *T)
{
	//S为指向串的指针, pos为子串的起始位置, len为子串的长度, T用于返回子串
	int i;
	if(S.length <= 0)
	{
		printf("the string is null!\n");
		return 0;
	}
	if(pos < 0 || pos > S.length || len <= 0)
	{
		printf("illegal length or position!\n");
		return 0;
	}
	if(pos + len > S.length)
		len = S.length - pos + 1;
	if(T -> length)
		free(T -> ch);
	T -> ch = (char*)malloc(len*sizeof(char));
	if(!T -> ch)
	{
		printf("error while malloc!\n");
		return 0;
	}
	for(i = 0; i < len; i++)
		T -> ch[i] = S.ch[i + pos];
	T -> length = len;
	return 1;
}


int Concat(SqVString *S, SqVString T)
{
	//S为指向字符串的指针, T为被连接字符串
	int i, len;
	len = S -> length + T.length;
	S -> ch = (char*)realloc(S -> ch, len*sizeof(char));
	if(!S -> ch)
	{
		printf("error while realloc!\n");
		return 0;
	}
	for(i = 0; i < T.length; i++)
		S -> ch[i + S -> length] = T.ch[i];
	S -> length = len;
	return 1;
}


