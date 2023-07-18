#include "Complex.h"
#include "FixedQueue.h"

template <typename T, typename U >
int sizeCompare(T a, U b)
{
	int size1 = 0, size2 = 0, result = 0;
	size1 = sizeof(a);
	size2 = sizeof(b);
	if (size1 == size2)
	{
		result = 0;
	}
	else if (size1 > size2)
	{
		result = 1;
	}
	else
	{
		result = -1;
	}
	return result;
}

//using namespace VidP;

int main()
{
	//std::string b = "Hallo";
	//std::cout << sizeCompare(552, 21321.2123) << std::endl;

	VidP::Complex<int> x(2, 3);
	VidP::Complex<int> y(1, 2);

	std::cout << "x= " << x << "\ny= " << y << std::endl;
	if (x == y)
	{
		std::cout << "x == y" << std::endl;
	}
	if (x <= y)
	{
		std::cout << "x <= y" << std::endl;
	}
	if (x >= y)
	{
		std::cout << "x >= y" << std::endl;
	}
	std::cout << x + y << std::endl;
	std::cout << x - y << std::endl;
	std::cout << x * y << " * " << std::endl;
	std::cout << x / y << std::endl;

	FixedQueue<int, 3> mq;
	mq.push(1);
	mq.push(2);
	mq.push(3);
	std::cout << mq.pop() << std::endl;
	mq.push(4);
	mq.push(5);
	mq.push(6);
	mq.push(7);
	mq.push(8);
	std::cout << mq.front() << " " << mq.back() << " " << mq.getsize();
	return 0;
}


