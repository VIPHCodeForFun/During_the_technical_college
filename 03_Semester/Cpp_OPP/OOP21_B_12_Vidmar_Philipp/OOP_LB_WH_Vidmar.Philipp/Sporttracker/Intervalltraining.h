#pragma once
#include "Laufeinheit.h"

class Intervalltraining : public Laufeinheit
{
private:
protected:
	int anzahlWiederholungen;
public:
	Intervalltraining(double _trainingZzeit = 0, double _gelaufeneDistanz = 0, int _anzahlWiederholungen = 0)
		: Laufeinheit(_trainingZzeit, _gelaufeneDistanz), anzahlWiederholungen{ _anzahlWiederholungen }
	{}

	virtual void print() override;
};

