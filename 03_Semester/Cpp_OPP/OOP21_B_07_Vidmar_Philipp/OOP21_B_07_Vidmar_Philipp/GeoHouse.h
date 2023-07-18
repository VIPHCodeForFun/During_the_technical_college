#pragma once
#include "GeoRect.h"
#include "GeoTriangle.h"

class GeoHouse :virtual public GeoRect, virtual public GeoTriangle
{
public:
	// Diamantproblem beide erben Von IUniqueID.h die uniqueID lösung Virtual Erben
	GeoHouse() = default;
	GeoHouse(GeoRect& rect, GeoTriangle& triangle);
	void output();
	double area();
	double circumference();
};

