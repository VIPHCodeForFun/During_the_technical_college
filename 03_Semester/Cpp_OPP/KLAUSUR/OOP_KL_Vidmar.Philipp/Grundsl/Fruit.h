#pragma once
#include "Produce.h"
class Fruit : public Produce
{
private:
protected:
public:
	Fruit(double _price, std::vector<int> _vitamins) : Produce(_price, _vitamins) {}
	Fruit(const Produce& copy)
	{
		std::cout << "Fruit / Fruit" << std::endl;
		this->price = copy.Produce::getprice();
		this->vitamins = copy.Produce::getvitamins();
	}

	virtual int GetNutrition()
	{
		return this->vitamins.size() / 2;
	}
};

