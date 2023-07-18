#pragma once
#include <iostream>
class Person {
protected:
	std::string name;
public:
	Person(std::string name) : name{name} {}

	void print() {
		std::cout << "Person, " << name << std::endl;
	}
};