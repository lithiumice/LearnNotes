typedef int DataType;
typedef struct node
{
	int row, col;
	DataType value;
	struct node *right, *down;
}CNode, *PCNode;

typedef struct 
{
	PCNode* rhead, *chead;
	int rows, cols, nums;
	
}*CrossLink;

/*************************************
*Function: InitCrossLnik
*Description: initialize the crosslink
*Params: @CrossLink *CL
*		 @DataType *A
*		 @int r & c
*Return: 1 if success
*************************************/
int InitCrossLink(CrossLink *CL, DataType *A, int r, int c)
{
	int i, j;
	PCNode p, q;
	(*CL) = (CrossLink)malloc(sizeof(CrossLink));
	if(!(*CL) -> rhead) 
	{
		printf("cannot initialize crosslink!\n");
		return 0;
	}
	(*CL) -> rows = r;
	(*CL) -> cols = c;
	(*CL) -> nums = 0;
	(*CL) -> rhead = (PCNode*)malloc(r*sizeof(PCNode));
	if(!(*CL) -> rhead)
	{
		printf("cannot initialize rhead!\n");
		return 0;
	}
	for(i = 0; i < r; i++)
		(*CL) -> rhead[i] = NULL;
	(*CL) -> chead = (PCNode*)malloc(c*sizeof(PCNode));
	if(!(*CL) -> chead)
	{
		printf("cannot initialize chead!\n");
		return 0;
	}
	for(i = 0; i < c; i++)
		(*CL) -> chead[i] = NULL;
	for(i = 0; i < c; i++)
		for (j = 0; j < c; ++j)
		{
			if(A[i * c + j] != 0)
			{
				p = (PCNode)malloc(sizeof(CNode));
				p -> row = i + 1;
				p -> col = j + 1;
				p -> value = A[i * c + j];
				p -> right = NULL;
				p -> down = NULL;
				(*CL) -> nums++;
				if((*CL) -> rhead[i] != NULL)
				{
					q = (*CL) -> rhead[i];
					while(q -> right != NULL && q -> col < j+1)
						q = q -> right;
					p -> right = q -> right;
					q -> right = p;
				}
				else
					(*CL) -> rhead[i] = p;
				if((*CL) -> chead[j] != NULL)
				{
					q = (*CL) -> chead[j];
					while(q -> down != NULL && q -> row < i + 1)
						q = q -> down;
					p -> down = q -> down;
					q -> down = p;
				}
				else
					(*CL) -> chead[j] = p;

			}
		}
		return 1;
}


/*************************************
*Function: GetValue
*Description: get value in (r, c)
*Params: @CrossLink CL
*		 @DataType *e
*		 @int r & c
*Return: 1 if success
*************************************/
int GetValue(CrossLink CL, DataType *e, inr r, int c)
{
	PCNode p;
	*e = 0;
	if(CL -> num <= 0)
	{
		printf("the cross link is empty!\n");
		return 0;
	}
	if(r < 1 || r > CL -> rows || c < 1 || c > CL -> cols)
	{
		printf("error paraments!\n");
		return 0;
	}
	p = CL -> rhead[r - 1];
	while(p != NULL && p -> col != c)
		p = p -> right;
	if(p)
		*e = p -> value;
	return 1;
}


/*************************************
*Function: FindIndex
*Description: find the position of given value
*Params: @CrossLink CL
*		 @DataType e
*		 @int *r & *c: store the position
*Return: 1 if success
*************************************/
int FindIndex(CrossLink CL, DataType e, int *r, int *c)
{
	PCNode p;
	int i;
	*r = 0;
	*c = 0;
	if(CL -> num <= 0)
	{
		printf("the cross link is empty!\n");
		return 0;
	}
	for(i = 0; i < CL -> rows; i++)
	{
		p = CL -> rhead[i];
		while(p != NULL)
		{
			if(p -> value == e)
			{
				*r = p -> row;
				*c = p -> col;
				return 1;
			}
			p = p -> right;
		}
	}
	return 0;
}