#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	int i=0,wordlen=0,pos=0,maxlen;
	char *pstr;
	cerr<<"error";
	cout<<setw(5)<<"ghj";
	pstr="this is a c program sjkdhfak sdkjf sakjdf ";
	while((pstr[i])!='\0')
	{
		while((pstr[i])!='\0'&&pstr[i]!=' ')
		{
			wordlen++;
			i++;
		}
		if(wordlen>maxlen)
		{
			maxlen=wordlen;
			pos=i-wordlen;
		}
		while((pstr[i])==' ')
		{
			i++;
		}
		wordlen=0;
	}
	for(i=0;i<maxlen;i++)
	{
		cout<<pstr[pos+i];
	}
	cout<<endl;
	return 0;
}
