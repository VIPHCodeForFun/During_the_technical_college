#include <iostream>
#include <vector>
#include <exception>
#include "IDclass.h"


namespace Vid
{
	class MyException : public std::exception
	{
	private:
	protected:
	public:
		virtual const char* what() const override
		{
			return "Exception occured : A negative Value was found in Templatecontainer";
		}
	};
}

template <typename T>
T Quadrat(T zahl)
{
	return zahl * zahl;
}
std::string Quadrat(std::string zahl)
{
	return "Quadrat" + zahl;
}


int main()
{
	std::vector<std::shared_ptr<int>> vec = {
	std::make_shared<int>(1),
	std::make_shared<int>(2),
	std::make_shared<int>(-4),
	std::make_shared<int>(6),
	std::make_shared<int>(-5),
	std::make_shared<int>(-8),
	std::make_shared<int>(-5),
	};
	for (auto elem : vec)
	{
		try
		{
			if (*elem < 0)
			{
				throw Vid::MyException();
			}
		}
		catch (Vid::MyException& MyExcep)
		{
			*elem = *elem * (-1);
			std::cout << MyExcep.what() << std::endl;
		}
	}

	auto lambda = [](std::vector<std::shared_ptr<int>> vec)
	{
		std::vector<int> temp;
		std::vector<int> temp_vec;
		for (auto elem : vec)
		{
			temp_vec.push_back(*elem);
		}
		for (int i = 0; i < 3; i++) // Anzahl der Variablen
		{
			int _temp = 0;
			int index = 0;
			for (int j = 0; j < vec.size(); j++)
			{
				if (*vec[j] % 2 == 0) // ==0 Gerade  !=0 Ungerade
				{
					if (_temp < temp_vec[j])
					{
						_temp = temp_vec[j];
						index = j;
					}
				}
			}
			temp.push_back(_temp);
			temp_vec[index] = 0;
		}
		return temp;
	};

	std::vector<int> pvec;
	pvec = lambda(vec);

	IDclass n1;
	IDclass n2;
	IDclass n3;
	IDclass n4;
	IDclass n5;

}

