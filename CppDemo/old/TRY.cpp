//#include "stdafx.h"
#include <fstream>
#include <iostream>
using namespace std;
#define SCREEN 1
#define FILE 2
#define MUL(a,b) (a)*\
(b)
int main(int argc, char * argv[])
{
	int x=5,y=1;
	cout<<MUL(x,y);
	int Writer=SCREEN;
	ofstream fc;
	try{
		try{
			fc=ofstream("D:\\STR.cpp");
			Writer=FILE;
		}
		catch(...){
			cout<<"error openingfile\n";};
			if(y==0) throw 1;
			if(Writer==SCREEN)
				std::cout<<x<<'/'<<y<<"="<<x/y<<std::endl;
			else fc<<x/y;
		
	}
	catch(int){
		std::cout<<"error 0!";
		return 0;
	}
	catch(...){
		std::cout<<"sdjahdfhas";
	}
}
#undef SCREEN
