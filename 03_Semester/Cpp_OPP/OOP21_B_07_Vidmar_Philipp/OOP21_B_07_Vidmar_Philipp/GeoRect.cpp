#include "GeoRect.h"

GeoRect::GeoRect(double width, double hight) : width{ width }, hight{ hight }
{
	setID();
}
void GeoRect::output()
{
	std::cout << "GeoRect mit " << "Flaeche:" << this->area() << " und Umfang:" << this->circumference() << std::endl;
}
double GeoRect::area()
{
	return this->width * this->hight;
}
double GeoRect::circumference()
{
	return (2 * this->width + 2 * this->hight);
}
