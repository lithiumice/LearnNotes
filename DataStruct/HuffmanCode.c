#include <stdio.h>
#include <stdlib.h>
#define MAXBIT 256 
#define MAXVALUE 256 
typedef int DataType;
typedef struct node{
	DataType data;
	int weight;
	int parent;
	int left;
	int right;
}HufNode;

typedef struct{
	char code[MAXBIT];
	int start;
}HufCode;


/*****************************************
*Function: HuffmanTree
*Description: an algorithm for HuffmanCode
*params: @int weight[]
*		 @char ch[]
*		 @int n
*		 @HufNode hf[]
*Return: NULL
******************************************/
void HuffmanTree(int weight[], char ch[], int n, HufNode hf[])
{
	int i, j, mw1, mw2, node1, node2;
	for(i = 0; i < 2*n - 1; i++)
	{
		if(i < n)
		{
			hf[i].weight = weight[i];
			hf[i].data = ch[i];
		}
		else
		{
			hf[i].weight = 0;
		}
		hf[i].parent = -1;
		hf[i].left = -1;
		hf[i].right = -1;
	}

	for(i = n; i < 2*n - 1; i++)
	{
		mw1 = mw2 = MAXVALUE;
		node1 = node2 = -1;
		for(j = 0; j <= i - 1; j++)
		{
			if(hf[j].parent == -1)
			{
				if(hf[j].weight < mw1)
				{
					mw2 = mw1;
					node2 = node1;
					mw1 = hf[j].weight;
					node1 = j;
				}
				else if(hf[j].weight < mw2)
				{
					mw2 = hf[j].weight;
					node2 = j;
				}
			}
		}
		hf[i].weight = hf[node1].weight + hf[node2].weight;
		hf[node1].parent = i;
		hf[node2].parent = i;
		hf[i].left = node1;
		hf[i].right = node2;

	}
}


/*****************************************
*Function: HuffmanCode
*Description: an algorithm for HuffmanCode
*params: @HufNode hf[]
*		 @HufCode hfc[]
*		 @int n
*Return: NULL
******************************************/
void HuffmanCode(HufNode hf[], HufCode hfc[], int n)
{
	int i, parent, left;
	HufCode hc;
	for(i = 0; i < n; i++)
	{
		hc.start = n;
		left = i;
		parent = hf[i].parent;
		while(parent != -1)
		{
			if(hf[parent].left == left)
				hc.code[hc.start--] = '0';
			else
				hc.code[hc.start--] = '1';
			parent = hf[parent].parent;
		}
		hc.start++;
		hfc[i] = hc;
	}
}


/*****************************************
*Function: TestHuffmanCode
*Description: an algorithm for HuffmanCode Test
*params: NULL
*Return: NULL
******************************************/
int TestHuffmanCode()
{
	int i, j, n = 5;
	char ch[] = "ABCDE";
	int weight[] = {3, 8, 6, 1, 5};
	HufNode *HufTree = (HufNode*)malloc(sizeof(HufNode));
	HufCode *HufCodes = (HufCode*)malloc(sizeof(HufCode));
	HuffmanTree(weight, ch, n, HufTree);
	HuffmanCode(HufTree, HufCodes, n);

	for(i = 0; i < n; i++)
	{
		printf("%c(%d):\t", ch[i], HufTree[i].weight);
		for(j = HufCodes[i].start; j <= n; j++)
			printf("%c", HufCodes[i].code[j]);
		printf("\n");
	}
	return 0;
}
