#include "GeoCirlce.h"

GeoCirlce::GeoCirlce(double rad) : GeoEllipse(rad, rad)
{
}
void GeoCirlce::output()
{
	std::cout << "GeoCirlce mit " << "Flaeche:" << this->area() << " und Umfang:" << this->circumference() << std::endl;
}