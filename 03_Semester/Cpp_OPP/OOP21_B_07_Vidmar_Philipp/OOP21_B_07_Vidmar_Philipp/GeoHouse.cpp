#include "GeoHouse.h"

GeoHouse::GeoHouse(GeoRect& rect, GeoTriangle& triangle)
{
	this->a = triangle.a;
	this->b = triangle.b;
	this->c = triangle.c;
	this->h = triangle.h;
	this->width = rect.width;
	this->hight = rect.hight;
	setID();
}
void GeoHouse::output()
{
	std::cout << "Ich bin ein Haus" << std::endl;
}
double GeoHouse::area()
{
	return (GeoRect::area() + GeoTriangle::area());
}
double GeoHouse::circumference()
{
	return this->a;
}
