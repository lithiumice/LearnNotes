/*
     ���ı䳤˳��洢
*/

#include<stdio.h>
#include "malloc.h"
#include "string.h"

/*�洢�ṹ*/
typedef struct{
	char *ch;
	int length;
}SqVString;

/*�㷨4-7��ʼ����*/
void InitString(SqVString *S, char *str)
{
	int i;
	char *c;
	int len=0;		
    c=str;
	while(*c!='\0'){len++;c++;}  /*��str�ĳ���*/
	S->ch = (char *)malloc(len*sizeof(char));	/*���붯̬����ռ�*/
	S->length = len;/*�ô��ĵ�ǰ����ֵ*/
	for(i = 0; i < S->length; i++)
		S->ch[i] = str[i];					/*��ֵ��ֵ*/
}

/*�㷨4-8������*/
int StrInsert(SqVString *S,int pos,SqVString T)
{
	int i;
	int len;	
	if(pos<0 || pos>S->length)
	{
		printf("����λ�ò��Ϸ�����ȡֵ��ΧӦ����[0,length]");
		return 0;
	}
	len=S->length+T.length;
	S->ch=(char*)realloc(S->ch,len*sizeof(char));
	if(!S->ch)
	{
		printf("����ռ�����޷���ɴ��������");
		return 0;
	}	
	for(i=S->length-1;i>=pos;i--)
		S->ch[i+T.length]=S->ch[i];
	for(i=0; i<T.length; i++)
		S->ch[i+pos]=T.ch[i];	
	S->length=len;	
	return 1;
}

/*�㷨4-9��ɾ��*/
int StrDelete(SqVString *S,int pos,int len)
{
	int i;
	int length;	
	char *str;
	if(pos<0 || len<=0 || pos>S->length || S->length<=0)
	{
		printf("ɾ��λ��pos��ɾ������len���Ϸ����޷����ɾ��������");
		return 0; 
	}
	length=S->length-len;
	if(length<=0) length=pos;  /*��pos+len���ڴ��������posɾ����β*/
	str=(char*)malloc(length*sizeof(char));
	if(!str)
	{
		printf("����ռ�����޷���ɴ�ɾ������");
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

/*�㷨4-10���Ӵ�*/
int SubStr(SqVString S,int pos,int len,SqVString *T)
{
	int i;	
	if(S.length<=0)
	{
		printf("�մ����޷�������Ӵ�������");
		return 0; 
	}
	if(pos<0 || pos>S.length || len<=0)
	{
		printf("�Ӵ�λ��pos���Ӵ�����len���Ϸ����޷�������Ӵ�������");
		return 0; 
	}
	if(pos+len>S.length) len=S.length-pos+1;	/*���Ӵ����ȳ����������ȣ���ֻȡ����β����*/
	if(T->length) free(T->ch);  /*�ͷ�S��ԭ�пռ�*/
	T->ch=(char*)malloc(len*sizeof(char));
	if(!T->ch)
	{
		printf("����ռ�����޷�������Ӵ�����");
		return 0;
	}	
	for(i=0;i<len;i++)
		T->ch[i]=S.ch[i+pos];
	T->length=len;
	return 1; 
}


/*�㷨4-11������*/
int Concat(SqVString *S,SqVString T)
{
	int i;
	int len;
	len=S->length+T.length;
	S->ch=(char*)realloc(S->ch,len*sizeof(char));
	if(!S->ch)
	{
		printf("����ռ�����޷���ɴ����Ӳ���");
		return 0;
	}
	for(i=0;i<T.length;i++)
		S->ch[i+S->length]=T.ch[i];
	S->length=len;	
	return 1; 
}

/*�㷨4-12����ֵ*/
int StrAssign(SqVString *S,char *value)
{
	int count=0;
	int i;
	char *c;
	//S=(SqVString*)malloc(sizeof(SqVString));
	if(S->length!=0) free(S->ch);  /*�ͷ�S��ԭ�пռ�*/	
	c=value;
	while(*c!='\0'){count++;c++;}  /*��value�ĳ���*/
	if(!count)/*valueΪ�մ�*/
	{
		S->ch=NULL;
		S->length=0;
	}
	else
	{
		S->ch=(char*)malloc(count);
		if(!S->ch)
		{
			printf("����ռ�����޷���ɴ���ֵ����");
			return 0;
		}
		for(i=0;i<count;i++)
			S->ch[i]=value[i];
		S->length=count;
	}
	return 1;
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
