#define ARRAYSIZE 1024
typedef int DataType;
typedef struct 
{
	int row, col;
	DataType value;
}TriType;
typedef struct 
{
	TriType items[ARRAYSIZE];
	int rows, cols;
	int nums;
}TriArray;


void InitArray(TriArray *TA, DataType *A, int r, int c)
{
	int i, j;
	TA -> rows = r;
	TA -> cols = c;
	TA -> nums = 0;
	for(i = 0; i < r; i++)
		for(j = 0; j < c, j++)
			if(*(A + i * c + j) != 0)
			{
				TA -> items[TA -> nums].row = i +1;
				TA -> items[TA -> nums].col = j +1;
				TA -> items[TA -> nums].value = *(A + i * c + j);
				TA -> nums++;
			}
}


int GetValue(TriArray TA, DataType *e, int r, int c)
{
	int i = 0;
	*e = 0;
	if(r < 1 || r > TA.rows || c < 1 || c > TA.cols)
	{
		printf("illegal paraments!\n");
		return 0;
	}
	while(i < TA.rows && r > TA.items[i].row)
		i++;
	while(i < TA.cols && c > TA.items[i].col)
		i++;
	if (TA.items[i].row == r && TA.items[i].col == c)
	{
		*e = TA.items[i] = value;
		return 1;
	}
	else
		return 0;

}


int Assign(TriArray *TA, DataType e, int r, int c)
{
	int i = j = 0;
	if(r < 1 || r > TA -> rows || c < 1 || c > TA -> cols)
	{
		printf("illegal paraments!\n");
		return 0;
	}
	while(i < TA -> rows && r > TA -> items[i].row)
		i++;
	while(i < TA -> cols && c > TA -> items[i].col)
		i++;
	if (TA -> items[i].row == r && TA -> items[i].col == c)
		TA -> items[i].value = e;
	else
	{
		for(j = TA -> nums - 1; j >= 1; j--)
		{
			TA -> items[j + 1].row = TA -> items[j].row;
			TA -> items[j + 1].col = TA -> items[j].col;
			TA -> items[j + 1].value = TA -> items[j].value;
		}
		TA -> items[i].row = r;
		TA -> items[i].col = c;
		TA -> items[i].value = e;
		TA -> nums++;

	}
	return 1;
}


int TransMatrix(TriArray TA, TriArray *TB)
{
	int i, c, k = 0;
	if(TA.nums <= 0)
	{
		printf("the matrix is empty!\n");
		return 0;
	}
	for(c = 1; c <= TA.cols; c++)
		for(i = 0; i < TA.nums; i++)
		{
			if(TA.items[i].col == c)
			{
				TB -> items[k].row = TA.items[i].col;
				TB -> items[k].col = TA.items[i].row;
				TB -> items[k].value = TA.items[i].value;
				k++;
			}
		}
		TB -> rows = TA.rows;
		TB -> cols = TA.cols;
		TB -> nums = TA.nums;
		return 1;
}


int FastTransMatrix(TriArray TA,TriArray *TB)
{
	int i, j = 0,k = 0;
	int pos[ARRAYSIZE], num[ARRAYSIZE];
	if(TA.nums <= 0)
	{
		printf("the matrix is empty!");
		return 0; 
	}
	
	for(i = 1; i <= TA.cols; i++)		
		num[i] = 0;
	for(i = 0; i < TA.nums; i++)		
		++num[TA.items[i].col];
	pos[1] = 1;
	for(i = 2; i <= TA.cols; i++)		
		pos[i] = pos[i - 1] + num[i - 1];
	for(i = 0; i < TA.nums; i++){		
		j = TA.items[i].col;		
		k = pos[j];				
		TB -> items[k - 1].row = TA.items[i].col;
		TB -> items[k - 1].col = TA.items[i].row;
		TB -> items[k - 1].value = TA.items[i].value;
		pos[j]++;
	}
	TB -> rows = TA.rows;
	TB -> cols = TA.cols;
	TB -> nums = TA.nums;
	return 1;
}
