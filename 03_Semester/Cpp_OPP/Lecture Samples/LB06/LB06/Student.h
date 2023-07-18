#pragma once
#include "Person.h"
class Student : public Person{
protected:
	int matNummer;
public:
	Student(std::string name, int matNummer) : matNummer{ matNummer }, Person(name) {}

	// void print(Student* this) {
	void print() {
		std::cout << "Student," << name << "," << matNummer << std::endl;
	}
};