#pragma once
#include <iostream>
#include <string>

class Laufeinheit
{
private:
protected:
	double trainingZzeit;
	double gelaufeneDistanz;
public:
	Laufeinheit(double _trainingZzeit = 0, double _gelaufeneDistanz = 0) : trainingZzeit{ _trainingZzeit }, gelaufeneDistanz{ _gelaufeneDistanz } {}
	~Laufeinheit() = default;

	void setTrainingsZeit(int trainingZzeit);
	void setgelaufeneDistanz(double gelaufeneDistanz);

	double getTrainingsEinheit();
	double getGeaufeneDistanz();

	Laufeinheit operator+(Laufeinheit& toAdd);

	friend std::ostream& operator<<(std::ostream& os, const Laufeinheit& str);
	friend std::istream& operator>>(std::istream& is, Laufeinheit& nr);

	virtual void print();

};

