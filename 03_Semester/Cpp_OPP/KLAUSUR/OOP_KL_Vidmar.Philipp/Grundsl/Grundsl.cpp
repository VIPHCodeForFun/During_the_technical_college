//Philipp Vidmar, C++ , 630868---	B, Grundsl

#include <iostream>
#include <string>

#include "Fruit.h"
#include "Vegetables.h"
#include "AufgabeE.h"


int main()
{
	Produce p1{ 10, std::vector<int>{1,2,3} };
	Fruit f1{ 5, std::vector<int>{1,2,3,4,5} };
	Vegetables v1{ 10, std::vector<int>{7,8,9} };
	Produce p2 = f1 + p1;
	Fruit f2 = f1 + v1;
	Vegetables v2 = p1 + f2;

	std::vector < std::shared_ptr<Produce>> Templatecontainer;
	fillvec(Templatecontainer);
	for (auto elem : Templatecontainer)
	{
		static int i = 0;
		std::cout << i << " " << elem->GetNutrition() << std::endl;
		i++;
	}
}
