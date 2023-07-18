#include "Intervalltraining.h"

void Intervalltraining::print()
{
	std::cout
		<< "<Intervalltraining><"
		<< this->gelaufeneDistanz
		<< "> <" << this->trainingZzeit
		<< "> <" << this->anzahlWiederholungen
		<< ">"
		<< std::endl;
}