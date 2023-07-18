#pragma once

template <class T>
class TempKlasse
{
private:
	T wert1;
	T wert2;
protected:
public:
	TempKlasse(T eins = 0, T zwei = 0) : wert1{ eins }, wert2{ zwei } {}

};

