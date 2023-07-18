#include "Laufeinheit.h"

void Laufeinheit::setTrainingsZeit(int trainingZzeit)
{
	this->trainingZzeit = trainingZzeit;
}

void Laufeinheit::setgelaufeneDistanz(double gelaufeneDistanz)
{
	this->gelaufeneDistanz = gelaufeneDistanz;
}

double Laufeinheit::getTrainingsEinheit()
{
	return this->trainingZzeit;
}

double Laufeinheit::getGeaufeneDistanz()
{
	return this->gelaufeneDistanz;
}

Laufeinheit Laufeinheit::operator+(Laufeinheit& toAdd)
{
	Laufeinheit temp;
	temp.trainingZzeit = this->trainingZzeit + toAdd.trainingZzeit;
	temp.gelaufeneDistanz = this->gelaufeneDistanz + toAdd.gelaufeneDistanz;
	return temp;
}

std::ostream& operator<<(std::ostream& os, const Laufeinheit& str)
{
	os << "<Zeit: " << std::to_string(str.trainingZzeit) + "><Distanz: " + std::to_string(str.gelaufeneDistanz) + ">";
	return os;
}
std::istream& operator>>(std::istream& is, Laufeinheit& nr)
{
	is >> nr.trainingZzeit;
	std::cin.ignore(10000, '\n');
	is >> nr.gelaufeneDistanz;
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	return is;
}
void Laufeinheit::print()
{
	std::cout 
		<< "<Laufzeit         ><" 
		<< this->gelaufeneDistanz 
		<< "> <" 
		<< this->trainingZzeit 
		<< ">"
		<< std::endl;
}