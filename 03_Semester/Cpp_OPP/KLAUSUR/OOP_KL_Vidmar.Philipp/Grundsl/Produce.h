#pragma once
#include <iostream>
#include <vector>

class Produce
{
private:
protected:
	double price;
	std::vector<int> vitamins;
public:
	Produce(double _price = 0, std::vector<int> _vitamins = {}) : price{ _price }, vitamins{ _vitamins }{}
	Produce(const Produce& copy);

	void setpice(double _price) { this->price = _price; }
	double getprice() const { return this->price; }
	std::vector<int> getvitamins() const { return this->vitamins; }

	Produce operator+(const Produce& toAdd);

	virtual int GetNutrition() { return this->vitamins.size(); }

};

