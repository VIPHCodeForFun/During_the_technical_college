#include "AufgabeE.h"

int getRndNr(int start, int ende)
{
	std::random_device RND;
	std::mt19937 rng(RND());
	std::uniform_int_distribution<std::mt19937::result_type> rnd_NR(start, ende); //range [start, ende]
	return rnd_NR(rng);
}
void fillvec(std::vector < std::shared_ptr<Produce>>& _vec)
{
	int rnd = 0;
	for (int i = 0; i < 10; i++)
	{
		rnd = getRndNr(0, 2);
		if (rnd == 0)
		{
			_vec.push_back(std::make_shared <Produce>(1, std::vector<int>{1, 2, 3}));
		}
		else if (rnd == 1)
		{
			_vec.push_back(std::make_shared <Fruit>(1, std::vector<int>{1, 2, 3}));
		}
		else
		{
			_vec.push_back(std::make_shared <Vegetables>(1, std::vector<int>{1, 2, 3}));
		}
	}
}
