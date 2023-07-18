#pragma once
#include "IGeomObj.h" //abstrakte Klasse

class GeoRect : virtual public IGeomObj
{
public:
	GeoRect() = default;
	GeoRect(double width, double hight);
	void output();
	double area();
	double circumference();

	//protected:
	double width;
	//private:
	double hight;
};

