#pragma once
#include "Rechteck.h"
class Quadrat : public Rechteck
{
private:
protected:
public:
	Quadrat(int a) :Rechteck(a, a) {}

	Quadrat(const Quadrat& copy) : Rechteck(copy) {}//CCtor
	Quadrat(Rechteck&& move) noexcept : Rechteck(move) {}; //Move
};

