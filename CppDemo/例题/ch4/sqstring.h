/*
     ���Ķ���˳��洢
*/

#include<stdio.h>

/*�洢�ṹ*/
#define STRSIZE 100

typedef struct{
	char ch[STRSIZE];
	int length;
}SqString;


/*�㷨4-1��ʼ����*/
int InitString(SqString *S,char *str)
{	
	int i, len=0;
	char *c=str;
	while(*c!='\0'){len++;c++;}  		/*��str�ĳ���*/	
	S->length = len;               		/*�ô��ĵ�ǰ����ֵ*/
	for(i = 0; i < S->length; i++)		/*��ֵ��ֵ*/
		S->ch[i] = str[i];	
	return 1;
}


/*�㷨4-2������*/
int StrInsert(SqString *S,int pos,SqString T)
{
	int i;	
	if(pos<0 || pos>S->length)
	{
		printf("����λ�ò��Ϸ�����ȡֵ��ΧӦ����[0,length]");
		return 0;
	}
	/*����󴮳���STRSIZE������������*/
	if (S->length + T.length<=STRSIZE) 
	{
		for(i=S->length-1; i>=pos-1; i--)
			S->ch[i+T.length]=S->ch[i];
		for(i=0; i<T.length; i++)
			S->ch[i+pos]=T.ch[i];
		S->length+=T.length;
	}
	/*����󴮳�>STRSIZE����T����ȫ�����룬��S���ֱ��ض�*/
	else if(T.length+pos<=STRSIZE) 
	{
		for (i=STRSIZE-1;i>T.length+pos-1;i--) 
			S->ch[i]=S->ch[i-T.length];
		for (i=0;i<T.length;i++)
			S->ch[i+pos]=T.ch[i];
		S->length=STRSIZE;
	}
	/*����󴮳�>STRSIZE,���Ҵ�T����ҲҪ���ض�*/
	else 
	{ 
		for (i=0;i<STRSIZE-pos;i++)
			S->ch[i+pos]=T.ch[i];
		S->length=STRSIZE;
	}
	return 1;
}

/*�㷨4-3��ɾ��*/
int StrDelete(SqString *S,int pos,int len)
{
	int i;
	if(S->length<=0)
	{
		printf("�մ����޷�����ɾ��������");
		return 0; 
	}
	if(pos<0 || len<=0 || pos>S->length)
	{
		printf("ɾ��λ��pos�Լ�ɾ������len���Ϸ����޷����ɾ��������");
		return 0; 
	}
	if(pos+len>S->length) len=S->length-pos+1;	/*��ɾ�����ȳ��������ȣ���ֻɾ����β����*/
	for(i=pos+len;i<S->length;i++)
		S->ch[i-len]=S->ch[i];
	S->length-=len;
	return 1; 
}

/*�㷨4-4���Ӵ�*/
int SubStr(SqString S,int pos,int len,SqString *T)
{
	int i;
	if(S.length<=0)
	{
		printf("�մ����޷�������Ӵ�������");
		return 0; 
	}
	if(pos<0 || len<=0 || pos>S.length)
	{
		printf("�Ӵ���λ��pos�Լ��Ӵ�����len���Ϸ����޷�������Ӵ�������");
		return 0; 
	}
	if(pos+len>S.length) len=S.length-pos+1;	/*���Ӵ����ȳ����������ȣ���ֻȡ����β����*/
	for(i=0;i<len;i++)
		T->ch[i]=S.ch[i+pos];
	T->length=len;
	return 1; 
}


/*�㷨4-5������*/
int Concat(SqString *S,SqString T)
{
	int i;	
	if(S->length+T.length<=STRSIZE)/*���Ӻ󴮳���STRSIZE*/
	{
		for(i=0;i<T.length;i++)
			S->ch[i+S->length]=T.ch[i];
		S->length+=T.length;
	}
	else if(S->length<STRSIZE)/*���Ӻ󴮳�����STRSIZE������S�ĳ���С��STRSIZE�������Ӻ�T�Ĳ����ַ����б�����*/
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

/*�㷨2-7����λ
int GetElem(SqList L,int pos,DataType *item)
{
	if(ListEmpty(L))
		return 0;
	if(pos<=0 || pos>L.length)
	{
		printf("λ����Ϣ���벻�Ϸ�������������");
		return 0;
	}
	*item=L.ch[pos-1];
	return 0;
}*/

/*�㷨2-8����˳���
int TraverseList(SqList L)
{
	int i;
	for(i=0;i<L.length;i++)
		printf("%d\t",L.ch[i]);
	printf("\n");
	return 1;
}*/
