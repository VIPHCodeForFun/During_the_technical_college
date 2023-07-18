#pragma once
#include "Produce.h"
class Vegetables : public Produce
{
private:
protected:
public:
	Vegetables(double _price, std::vector<int> _vitamins) : Produce(_price, _vitamins) {}
	Vegetables(const Vegetables& copy) = default;

	Vegetables(const Produce& copy)
	{
		std::cout << "Vegetables / Vegetables" << std::endl;
		this->price = copy.Produce::getprice();
		this->vitamins = copy.Produce::getvitamins();
	}

	virtual int GetNutrition()
	{
		return this->vitamins.size() * 2;
	}
};

