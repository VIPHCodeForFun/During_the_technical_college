#pragma once
#include <iostream>
#include "IUniqueID.h"

class IGeomObj : public IUniqueID
{
public:
	virtual void output() = 0;
	virtual double area() = 0;
	virtual double circumference() = 0;

	void setID() final; //final kann nicht mehr überscfhrieben werden 

protected:
	const double pi = 3.14159265359;
};