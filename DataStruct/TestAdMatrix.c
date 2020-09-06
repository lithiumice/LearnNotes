#include "AdjacencyMatrix.h"

int main(int argc, char const *argv[])
{
	MGraph gg;
	AdjMetrix g = &gg;
	int pos, i;
	char d[] = {'A','B','C','D','E'};
	int m[][50] = {{0,1,0,0,1},{1,0,1,1,0},{0,1,0,0,0,},{0,1,0,0,1},{1,0,0,1,0}};
	CreateGraph(g, m, d, 5);
	DispGraph(g);
	
	return 0;
}
