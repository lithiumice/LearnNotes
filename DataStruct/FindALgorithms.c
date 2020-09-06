typedef int KeyType;
typedef struct 
{
	KeyType key;
}DataType;
#define LISTSIZE 100
typedef struct{
	DataType items[LISTSIZE];
	int length;
}SqList;


int SeqSearch(SqList L, DataType x)
{
	int i = L.length;
	L.items[0] = x.key;
	while(L.items[i].key != x.key)
		i--;
	return i;
}


int BinarySearch(SqList L, DataType x)
{
	int low = 0, upper = L.length - 1, mid;
	while(low < upper)
	{
		mid = (low + upper)/2;
		if(L.items[mid].key == x.key)
			return mid;
		if(L.items[mid].key < x.key)
			low = mid + 1;
		else 
			upper = mid - 1;
	}
	return -1;
}