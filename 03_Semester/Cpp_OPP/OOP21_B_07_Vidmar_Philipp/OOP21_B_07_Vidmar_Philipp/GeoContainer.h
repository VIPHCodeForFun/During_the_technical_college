#pragma once
#include "IGeomObj.h"
#include <vector>

class GeoContainer : public IGeomObj
{
public:
	GeoContainer() = default;
	std::vector<IGeomObj*> container;


	void output();
	double area();
	double circumference();
};
