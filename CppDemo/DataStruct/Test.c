#include "HuffmanCode.h"

int main(int argc, char const *argv[])
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
