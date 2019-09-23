#define MAXVEX 50
//return -1: error
typedef int weight;
typedef int DataType;
typedef struct 
{
	weight arcs[MAXVEX][MAXVEX]; //the matrix itself
	DataType data[MAXVEX];
	int vexs; //the number of points
}MGraph, *AdjMetrix;


/*****************************************
*Function: CreateGraph
*Description: an algorithm for creating graph
*params: @AdjMetrix g
*		 @int m[][MAXVEX]: the weights
*		 @DataType d[]: the points
*		 @int n: orders
*Return: NULL
******************************************/
void CreateGraph(AdjMetrix g, int m[][MAXVEX], DataType d[], int n)
{
	int i, j;
	g -> vexs = n;
	for(i = 0; i < n; i++)
	{
		g -> data[i] = d[i];
		for(j = 0; j < n; j++)
			g -> arcs[i][j] = m[i][j];
	}
}


void DispGraph(AdjMetrix g)
{
	int i, j;
	printf("the points:\n\t");
	for (i = 0; i < g -> vexs; ++i)
		printf("%c\t", g -> data[i]);
	printf("\n\nthe matrix of graph:\n");
	for (i = 0; i < g -> vexs; ++i)
	{
		printf("\n%c:\t", g -> data[i]);
		for (j = 0; j < g -> vexs; ++j)
			printf("%d\t", g -> arcs[i][j]);
	}
	printf("\n\n");
}


/*****************************************
*Function: GetFirst
*Description: find the first point
*params: @AdjMetrix g
*		 @int k
*Return: i or -1 if failed
******************************************/
int GetFirst(AdjMetrix g, int k)
{
	int i;
	if(k < 0 || k > g -> vexs)
	{
		printf("the k is out of range!\n");
		return -1;
	}
	for(i = 0; i < g -> vexs; i++)
		if(g ->arcs[k][i] == 1)
			return i;
	return -1;
}


/*****************************************
*Function: GetNext
*Description: find the next
*params: @AdjMetrix g
*		 @int k
*		 @int t
*Return: i
******************************************/
int GetNext(AdjMetrix g, int k, int t)
{
	int i;
	if(k < 0 || k > g -> vexs || t < 0 || t > g -> vexs)
	{
		printf("the k or t is out of range!\n");
		return -1;
	}
	for(i = t + 1; i < g -> vexs; i++)
		if(g ->arcs[k][i] == 1)
			return i;
	return -1;
}


void PutVex(AdjMetrix g, int k, DataType x)
{
	if(k < 0 || k > g -> vexs)
	{
		printf("the k is out of range!\n");
		return;
	}
	g -> data[k] = x;
}

DataType GetVex(AdjMetrix g, int k)
{
	if(k < 0 || k > g -> vexs)
	{
		printf("the k is out of range!\n");
		return;
	}
	return g -> data[k];
}


void InsertArc(AdjMetrix g, int u, int v, weight w)
{
	if(u < 0 || u > g -> vexs || v < 0 || v > g -> vexs)
	{
		printf("the u or v is out of range!\n");
		return;
	}
	g -> arcs[u][v] = w;
}


void DeleteArc(AdjMetrix g, int u, int v)
{
	if(u < 0 || u > g -> vexs || v < 0 || v > g -> vexs)
	{
		printf("the u or v is out of range!\n");
		return;
	}
	g -> arcs[u][v] = 0;
}