ass CRectangle
{
public:
	CRectangle();
	CRectangle(double L,double W);
	virtual ~CRectangle();
	double Perimeter(void);
	double Area(void);
private:
	double length,width;
};