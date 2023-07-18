#include <vector>
#include "Graduate.h"

void foo(Person& currentPerson) {
	// Ptr -> [Person][Student][Graduate]
	currentPerson.print();
}

int main() {
	Person p1("Test");
	Student s1("Test", 123);
	Graduate g1("Test", 123, "Heute");
	p1.print();
	s1.print();
	g1.print();
	g1.Student::Person::print();

	int usingUsing = g1.matNummer; // protect -> public via using Student::matNummer

	foo(p1);
	foo(s1);
	foo(g1);

	std::vector<std::shared_ptr<Person>> vec; // [Person*][Person*][Person*][Person*] -> ... [Person][Student][Graduate], ... [Person]
	std::shared_ptr<Graduate> ptrg2 = std::make_shared<Graduate>("Test", 456, "Heute");
	vec.push_back(ptrg2);

	return 0;
}