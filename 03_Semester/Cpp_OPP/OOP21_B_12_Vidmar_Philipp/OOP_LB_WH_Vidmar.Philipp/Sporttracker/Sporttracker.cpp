

#include <iostream>
#include <vector>
#include "Laufeinheit.h"
#include "Ausdauertraining.h"
#include "Intervalltraining.h"

int main()
{
	//Der Vector belibig groß oder klein sein. und mit Index
	std::vector<std::shared_ptr<Laufeinheit>> SporttrackerContainer = {
	std::make_shared<Laufeinheit>(5,10),
	std::make_shared<Ausdauertraining>(6,16,true),
	std::make_shared<Intervalltraining>(7,17,30),
	};
	for (auto elem : SporttrackerContainer)
	{
		elem->print();
	}

	Laufeinheit bene(5, 10);
	Laufeinheit phil(10, 5);

	Laufeinheit mari = bene + phil;
	Laufeinheit mar;
	mar = bene + bene;

	std::cin >> bene;
	std::cout << bene << std::endl;


}


