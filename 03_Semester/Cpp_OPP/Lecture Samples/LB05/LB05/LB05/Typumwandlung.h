#pragma once
#include <iostream>
class Typumwandlung {
	int id;
	std::string name;
public:
	Typumwandlung(int id, std::string name) : id{ id }, name{ name }{}
	Typumwandlung(int id) : id{ id }, name{ "default" }{}
};

