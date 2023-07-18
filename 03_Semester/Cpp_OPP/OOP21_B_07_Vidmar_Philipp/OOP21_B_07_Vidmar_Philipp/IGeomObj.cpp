#include "IGeomObj.h"

void IGeomObj::setID()
{
	static int ID = 0;
	ID++;
	this->uniqueID = ID;
}