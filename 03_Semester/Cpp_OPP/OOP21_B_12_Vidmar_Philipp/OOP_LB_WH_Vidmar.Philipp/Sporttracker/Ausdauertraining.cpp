#include "Ausdauertraining.h"

void Ausdauertraining::print()
{
	std::cout
		<< "<Ausdauertraining ><"
		<< this->gelaufeneDistanz
		<< "> <" << this->trainingZzeit
		<< "> <" << this->gegenWind
		<< ">"
		<< std::endl;
}