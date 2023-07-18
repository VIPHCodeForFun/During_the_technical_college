#pragma once
#include "myInterface.h"
class test : public myInterface<int>
{
private:
protected:
public:
	virtual int GetElement(std::vector<int> _vec);
};

