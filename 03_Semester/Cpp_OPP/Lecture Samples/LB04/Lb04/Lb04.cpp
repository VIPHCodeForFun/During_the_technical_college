#include <iostream>
#include "Counter.h"
#include "Automat.h"

// static int z; // global in dieser Quelltextdatei verfügbar, nicht empfohlen

// int counter = 0; // Keine globalen Variablen!
// static verwenden wird ein mal nach dem ersten mal aufrufen initialisiert quasi Global
void Count() {
	static int counter = 0;
	std::cout << counter++ << std::endl;
}

// Überladung der Funktion print--------------
void print(int i) {
	std::cout << "Int " << i << std::endl;
}

void print(double d) {
	std::cout << "Double " << d << std::endl;
}

void print(std::string s) {
	std::cout << "String " << s << std::endl;
}
// Überladung der Funktion print--------------

int main() {
	for (int i = 0; i < 5; i++) {
		static int number = 0;
		std::cout << number++ << " ";
	}
	std::cout << std::endl;

	Count();
	Count();
	Count();

	Counter c1;
	int i = c1.ObjectCount();
	i = c1.ObjectCount();
	i = c1.ObjectCount();

	i = Counter::ClassCount();
	i = Counter::ClassCount();
	i = Counter::ClassCount();

	i = Counter::ctr;

	print(3);
	print(3.4);
	print("Hello World");

	Automat a1(1000, "Hallein");
	auto a2 = std::make_shared<Automat>(5000, "Puch");
	a2.reset();

	// Automatische Typumwandlung. Funktioniert! Aber Vorsicht, nicht besonders lesbar
	Automat a3 = 1000;
	Automat a4 = { (std::string)"Salzburg" };
	// Automat a5 = { 200, "Salzburg" }; // Geht nicht da von explicit verboten

	return 0;
}