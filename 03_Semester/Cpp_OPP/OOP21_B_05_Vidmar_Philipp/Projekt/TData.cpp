#include "TData.h"

TData::TData() //Konstruktor
{
	std::cout << " Konstruktor " << std::endl;
	this->name = "---";
	this->data.clear();

}
TData::TData(const TData& copy) //Copy
{
	std::cout << " CopyKonstruktor " << std::endl;
	this->name = copy.name;
	this->data = copy.data;
}
TData::TData(TData&& move) noexcept
{
	std::cout << " MoveKonstruktor " << std::endl;
	this->name = move.name;
	this->data = move.data;
}
TData::~TData() //Destruktor
{
	std::cout << " Destruktor " << std::endl;
}

void TData::Aufgabe_B_CBV(TData x)
{
	std::cout << " Ich nehem TData entgegen CBV " << std::endl;
}
void TData::Aufgabe_B_CBR(TData& x)
{
	std::cout << " Ich nehem TData entgegen CBR" << std::endl;
}
TData TData::Aufgabe_C()
{
	TData rTData;
	rTData.name = " Aufgabe C ";
	rTData.data.push_back('C');
	return rTData;
}

int TData::getter()
{
	return TData::id;
}

void TData::setter(int idx)
{
	TData::id = idx;
}

