#include "GeoEllipse.h"
#include <cmath>

GeoEllipse::GeoEllipse(double rad_a, double rad_b)
{
	setID();
	this->rad_a = rad_a;
	this->rad_b = rad_b;
}
void GeoEllipse::output()
{
	std::cout << "GeoEllipse mit " << "Flaeche:" << this->area() << " und Umfang:" << this->circumference() << std::endl;
}
double GeoEllipse::area()
{
	return rad_a * rad_b * pi;
}
double GeoEllipse::circumference()
{
	//Näherungsformel Umfang ist halbwegs genau:
	return 3 * pi * (rad_a + rad_b) / 2 - pi * sqrt(rad_a * rad_b);
}