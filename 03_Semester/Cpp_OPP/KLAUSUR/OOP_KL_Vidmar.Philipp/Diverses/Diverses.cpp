//Philipp Vidmar, C++ , 630868---	B, Diverses

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>

#include "test.h"


int main()
{
	//AUFGABE A
	std::string str = "a3C2fE";
	std::cout << "vor  Landba:  " << str << std::endl;

	auto landba = [](std::string& _str)
	{

		for (int i = 0; i < _str.size(); i++)
		{
			if (_str[i] >= 'A' && _str[i] <= 'Z')
			{
				_str[i] = _str[i] - ('A' - 'a');
			}
		}
	};
	landba(str);
	std::cout << "Nach Landba:  " << str << std::endl;

	//AUFGABE B
	test mytest;
	std::vector<int> myvec = { 1,2,3,4,5,6,7,8,9 };
	std::cout << mytest.GetElement(myvec) << std::endl;

	//AUFGABE C
	std::array<double, 7> arr = { 1,2,3,4,10,25,50 };
	double temp = 0;
	for (auto elem : arr)
	{
		temp = temp + elem;
		std::cout << "Das ist Temp: " << temp << std::endl;
		try
		{
			if (temp >= 50)
			{
				throw std::exception("Exception occured: Sum of Doubles to high");
			}
		}
		catch (const std::exception& exeption)
		{
			std::cout << "Exception:   " << exeption.what() << std::endl;
		}
	}

}
