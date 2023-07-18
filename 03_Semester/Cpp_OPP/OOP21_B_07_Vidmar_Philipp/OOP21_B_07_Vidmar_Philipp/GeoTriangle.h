#pragma once
#include "IGeomObj.h"

class GeoTriangle : virtual  public IGeomObj
{
public:
	GeoTriangle() = default;
	GeoTriangle(double a, double b, double c, double h);
	void output();
	double area();
	double circumference();

	//protected:
	double h;
	double a;
	double b;
	double c;
};

