#pragma once
#include <random>
#include <iostream>
#include "Fruit.h"
#include "Vegetables.h"

int getRndNr(int start, int ende);

void fillvec(std::vector < std::shared_ptr<Produce>>& _vec);

