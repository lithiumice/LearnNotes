/************************************
*Function: GetNext
*Description: count next val for KMP
*Input: string T, array next to store values
*Return: NULL
*Others: ...
*************************************/
void GetNext(SqVString T, int next[])
{
	int j = 1, k = 0;
	next[0] = -1;
	next[1] = 0;
	while(j < T.length)
	{
		if(T.ch[j] == T.ch[k])
		{
			k++;
			j++;
			next[j] = k;
		}
		else if(k == 0)
		{
			j++;
			next[j] = 0;
		}
		else
			k = next[k];
	}
}


/************************************
*Function: GetNextval
*Description: count next val for KMP
*Input: string T, array nextval to store values
*Return: NULL
*************************************/
void GetNextval(SqVString T, int nextval[])
{
	int j = 0, k = -1;
	nextval[0] = -1;
	while(j < T.length)
	{
		if (k == -1 || T.ch[j] == T.ch[k])
		{
			j++;
			k++;
			if(T.ch[j] == T.ch[k])
				nextval[j] = nextval[k];
			else
				nextval[j] = k;
		}
		else
			k = nextval[k];
	}
}


/************************************
*Function: KMPIndex
*Description: an algorithm for searching substring
*Input: S: main string; pos: start position; next: the array you get; T: substring
*Return: position
*Others: ...
*************************************/
int KMPIndex(SqVString S, int pos, int next[], SqVString T)
{
	//S为主串, pos为起始位置, next存放next函数值, T为模式串
	int i = pos, j = 0, r = -1;
	while(i < S.length && j < T.length)
	{
		if(S.ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else if(j == 0)
			i++;
		else 
			j = next[j];
	}
	if(j >= T.length)
		r = i - T.length;
	return r;
}


/************************************
*Function: BFIndex
*Description: an algorithm for searching substring
*params: @SqVString S
*		 @SqVString T
*Return: int position
*************************************/
int BFIndex(SqVString S, SqVString T)
{
	//S为主串, T为模式串
	int i = 0, j = 0, k = -1;
	while(i < S.length && j < T.length)
	{
		if(S.ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= T.length)
		k = i - T.length;
	return k;
}

