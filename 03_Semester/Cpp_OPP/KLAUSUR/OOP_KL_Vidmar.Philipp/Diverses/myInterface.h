#pragma once
#include <vector>
template <class T>
class myInterface
{
private:
protected:
public:
	virtual T GetElement(std::vector<T> _vec) = 0;
};

