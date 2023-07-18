#include "GeoContainer.h"

void GeoContainer::output()
{
	std::cout << "GeoContainer mit " << "Flaeche:" << this->area() << " und Umfang:" << this->circumference() << std::endl;
}
double GeoContainer::area()
{
	double sum = 0;
	for (auto elem : container)
	{
		sum = sum + elem->area();
	}
	return sum;
}
double GeoContainer::circumference()
{
	double sum = 0;
	for (auto elem : container)
	{
		sum = sum + elem->circumference();
	}
	return sum;
}