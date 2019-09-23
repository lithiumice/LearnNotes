/*
     三元组顺序表
*/

#include<stdio.h>
#define  DataType int

/*存储结构*/
#define ARRAYSIZE 1024

typedef struct{
	int row,col;	//非零元素的行号和列号
	DataType value;	//非零元素的值
}TriType;

typedef struct{
	TriType items[ARRAYSIZE];
	int rows,cols,nums;			//稀疏矩阵的行数、列数和非零元素个数
}TriArray;


/*算法5-1初三元组顺序表*/
void InitArray(TriArray *TA,DataType *A,int r,int c)
{
	int i, j;
	TA->rows=r;
	TA->cols=c;
	TA->nums=0;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			if(*(A+i*c+j)!=0)
			{
				TA->items[TA->nums].row=i+1;
				TA->items[TA->nums].col=j+1;
				TA->items[TA->nums].value=*(A+i*c+j);
				TA->nums++;
			}
	
}


/*算法5-2取值*/
int GetValue(TriArray TA,DataType *e,int r,int c){
	int i=0;
	*e=0;
	if(r<1 || r>TA.rows || c<1 || c>TA.cols){
		printf("参数不正确，请重新输入参数！");
		return 0;
	}
	while(i<TA.rows && r>TA.items[i].row) i++;	//找行
	while(i<TA.cols && c>TA.items[i].col) i++;	//找列
	if(TA.items[i].row==r && TA.items[i].col==c){	//找到该位置
		*e=TA.items[i].value;
		return 1;
	}
	else
		return 0;
}


/*算法5-3赋值*/
int Assign(TriArray *TA,DataType e,int r,int c){
	int i=0,j=0;
	if(r<1 || r>TA->rows || c<1 || c>TA->cols){
		printf("参数不正确，请重新输入参数！");
		return 0;
	}
	while(i<TA->rows && r>TA->items[i].row) i++;	//找行
	while(i<TA->cols && c>TA->items[i].col) i++;	//找列
	if(TA->items[i].row==r && TA->items[i].col==c)	//找到该位置，则赋值
		TA->items[i].value=e;
	else{									//没找到该位置，则插入
		for(j=TA->nums-1;j>=i;j--){
			TA->items[j+1].row= TA->items[j].row;
			TA->items[j+1].col= TA->items[j].col;
			TA->items[j+1].value= TA->items[j].value;
		}
		TA->items[i].row=r;
		TA->items[i].col=c;
		TA->items[i].value=e;
		TA->nums++;
	}
	return 1;
}


/*算法5-4矩阵转置*/
int TransMatrix(TriArray TA,TriArray *TB)
{
	int i,c,k=0;
	if(TA.nums<=0)
	{
		printf("所给矩阵为空，无法完成矩阵转置操作！");
		return 0; 
	}
	
	for(c=1;c<=TA.cols;c++)			//扫描原三元组顺序表A中元素的列下标
		for(i=0;i<TA.nums;i++){		//扫描整个三元组顺序表A
			if(TA.items[i].col==c){	//找到相应列序的三元组
				TB->items[k].row=TA.items[i].col;
				TB->items[k].col=TA.items[i].row;
				TB->items[k].value=TA.items[i].value;
				k++;
			}
		}
		TB->rows=TA.rows;
		TB->cols=TA.cols;
		TB->nums=TA.nums;
		return 1;
}




/*算法5-5快速转置*/
int FastTransMatrix(TriArray TA,TriArray *TB)
{
	int i,j=0,k=0;
	int pos[ARRAYSIZE],num[ARRAYSIZE];
	if(TA.nums<=0)
	{
		printf("所给矩阵为空，无法完成矩阵转置操作！");
		return 0; 
	}
	
	for(i=1;i<=TA.cols;i++)		//每列非零元素个数数组num初始化
		num[i]=0;
	for(i=0;i<TA.nums;i++)		//计算每列非零元素个数
		++num[TA.items[i].col];
	pos[1]=1;
	for(i=2;i<=TA.cols;i++)		//计算每列第一个非零元素的位置
		pos[i]=pos[i-1]+num[i-1];
	for(i=0;i<TA.nums;i++){		//扫描整个三元组顺序表A
		j=TA.items[i].col;		
		k=pos[j];				//该元素在TB中的位置
		TB->items[k-1].row=TA.items[i].col;
		TB->items[k-1].col=TA.items[i].row;
		TB->items[k-1].value=TA.items[i].value;
		pos[j]++;
	}
	TB->rows=TA.rows;
	TB->cols=TA.cols;
	TB->nums=TA.nums;
	return 1;
}



