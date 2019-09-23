typedef struct Node{
	DataType data;
	struct node *left, *right;
}BSTNode, *BSTree;
typedef int KeyType;
typedef struct{
	KeyType key;
}DataType;


BSTNode* BSTSearch(BSTree r, DataType x)
{
	BSTNode *p;
	p = r;
	if(r == NULL)
		return NULL;
	while(p != NULL)
	{
		if(p -> data.key == x.key)
			return p;
		if(p -> data.key < x.key)
			p = p -> right;
		else 
			p = p -> left;
	}
	return NULL;
}