#include "GeoSquare.h"

GeoSquare::GeoSquare(double len) : GeoRect(len, len)
{
}
void GeoSquare::output()
{
	std::cout << "GeoSquare mit " << "Flaeche:" << this->area() << " und Umfang:" << this->circumference() << std::endl;
}