#include "StdAfx.h"
#include "MyRectangle.h"
CRectangle::CRectangle()
{
	length=1;
	width=1;}
CRectangle::CRectangle(double L,double W)
{
	length=L;
	width=W;
}
CRectangle::~CRectangle(){}
double CRectangle::Perimeter(void){
	return 2*(length*width);
}
double CRectangle::Area(void)
{
	return (length*width);
}