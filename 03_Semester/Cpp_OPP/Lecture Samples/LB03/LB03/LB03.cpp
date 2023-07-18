#include <iostream>
#include "CPerson.h"
#include "CPersonHack.h"

namespace oop {
	std::string toString(const CPerson& p) {
		return "From oop::tostring: " + p.GetName();
	}
}

std::string toString(const CPerson& p) {
	return "From global::tostring: " + p.GetName();
}

void foo(std::unique_ptr<std::string> uPtr) {
	__noop;
}

struct Person {
	std::string vorname;
	std::string nachname;
	unsigned int plz;
};
typedef struct Person P;		// Alternativer Name P
using TPerson = struct Person;	// Alternativer Name TPerson

// using namespace oop;

int main() {
	std::shared_ptr<std::string> ptr1 = std::make_shared<std::string>("Hello World");
	int managerCounter = ptr1.use_count();
	auto ptr2 = ptr1;
	managerCounter = ptr1.use_count();
	ptr2.reset();
	managerCounter = ptr1.use_count();

	std::weak_ptr<std::string> wPtr1 = ptr1;
	managerCounter = ptr1.use_count();
	if (std::shared_ptr<std::string> lockedPtr = wPtr1.lock()) {
		managerCounter = ptr1.use_count();
	}

	managerCounter = ptr1.use_count();
	ptr1.reset();
	managerCounter = ptr1.use_count();

	auto uPtr1 = std::make_unique<std::string>("Hi");
	// auto uPtr2 = uPtr1; // Nicht erlaubt

	// foo(uPtr1); // Nicht erlaubt
	foo(std::move(uPtr1)); // Nach move leer

	struct Person p1;
	p1.vorname = "Test"; // Bei Strukturen direkt setzbar
	Person p2;

	CPerson p3;
	// p3.name = "Test"; // Default private, Zugriff nur über public: möglich

	std::cout << p3.GetName() << std::endl;

	auto p4 = std::make_unique<CPerson>();
	p4->SetName("aaaaa");

	std::cout << oop::toString(p3) << std::endl;
	std::cout << ::toString(p3) << std::endl;
	std::cout << toString(p3) << std::endl;

	// NICHT REPRODUZIEREN NUR ZUM VERSTÄNDNISS -> Zugriffsattribute != IT Security
	void* ptr = &p3;
	CPersonHack* p3Unlocked = (CPersonHack*)ptr;
	std::cout << p3Unlocked->name << " " << p3Unlocked->plz;

	return 0;
}