#include "test.h"

int test::GetElement(std::vector<int> _vec)
{
	int temp = 0;
	for (auto elem : _vec)
	{
		temp = temp + elem;
	}
	return temp;
}