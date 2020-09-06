#define STRSIZE 100
typedef struct 
{
	char ch[STRSIZE];
	int length;
}SqString;


int InitString(SqString *S, char *STR)
{
	int i, len = 0;
	char *c = str;
	while(*c != '\0')
	{
		len++;
		c++;
	}
	S -> length = len;
	for (i = 0; i < S -> length; i++)
	{
		S -> ch[i] = str[i];
	}
	return 1;
}


int StrInsert(SqString *S, int pos, SqString T)
{
	int i;
	if(pos < 0 || pos > S -> length)
	{
		printf("illegal insert position!\n");
		return 0;
	}
	if(S -> length + T.length <= STRSIZE)
	{
		for(i = S -> length - 1; i >= pos - 1; i--)
			S -> ch[i + T.length] = S -> ch[i];
		for(i = 0; i < T.length; i++)
			S -> ch[i + pos] = T.ch[i]
		S -> length += T.length;
	}
	else if(T.length + pos <= STRSIZE)
	{
		for(i = STRSIZE - 1; i > T.length + pos - 1; i--)
			S -> ch[i] = S -> ch[i - T.length];
		for(i = 0; i < T.length; i++)
			S -> ch[i + pos] = T.ch[i];
		S -> length = STRSIZE;
	}
	else
	{
		for(i = 0; i < STRSIZE - pos; i++)
			S -> length = STRSIZE;
	}
	return 1;
}