#include "Produce.h"

Produce::Produce(const Produce& copy)
{
	std::cout << "Produce / Produce" << std::endl;
	this->price = copy.price;
	this->vitamins = copy.vitamins;
}

Produce Produce::operator+(const Produce& toAdd)
{
	Produce temp;
	temp.price = this->price + toAdd.price;
	for (auto elem : this->vitamins)
	{
		temp.vitamins.push_back(elem);
	}
	for (auto elem : toAdd.vitamins)
	{
		temp.vitamins.push_back(elem);
	}
	return temp;
}