#pragma once
#include "Laufeinheit.h"
class Ausdauertraining : public Laufeinheit
{
private:
protected:
	bool gegenWind;
public:
	Ausdauertraining(double _trainingZzeit = 0, double _gelaufeneDistanz = 0, bool _gegenWind = false)
		: Laufeinheit(_trainingZzeit, _gelaufeneDistanz), gegenWind{ _gegenWind }
	{}

	virtual void print() override;
};
