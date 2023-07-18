#pragma once
#include "IGeomObj.h"

class GeoEllipse : public IGeomObj
{
public:
	GeoEllipse() = default;
	GeoEllipse(double rad_a, double rad_b);
	void output();
	double area();
	double circumference();

	//protected:
	double rad_a;
	double rad_b;
};

