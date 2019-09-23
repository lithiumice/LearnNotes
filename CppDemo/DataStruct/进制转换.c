#include "OrderStack.h"


//十进制转为d进制
void Convert(int num, int d)
{
	SqStack s;
	char ch[] = '0123456789ABCDEF';
	int tmp;
	InitStack(&s);
	do
	{
		Push(&s, ch[num% d]);
		num = num/d;
	}while(num != 0);
	while(!StackEmpty(s))
	{
		Pop(&s, &tmp);
		printf("%c", tmp);
	}
}


int main(int argc, char const *argv[])
{
	Convert(223, 8);
	return 0;
}
