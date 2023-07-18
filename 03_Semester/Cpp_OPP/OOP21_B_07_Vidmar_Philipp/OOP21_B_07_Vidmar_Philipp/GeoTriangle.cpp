#include "GeoTriangle.h"

GeoTriangle::GeoTriangle(double a, double b, double c, double hight)
{
	setID();
	this->a = a;
	this->b = b;
	this->c = c;
	this->h = hight;
}
void GeoTriangle::output()
{
	std::cout << "GeoTriangle mit " << "Flaeche:" << this->area() << " und Umfang:" << this->circumference() << std::endl;
}
double GeoTriangle::area()
{
	return (0.5 * a * h);
}
double GeoTriangle::circumference()
{
	return (a + b + c);
}
