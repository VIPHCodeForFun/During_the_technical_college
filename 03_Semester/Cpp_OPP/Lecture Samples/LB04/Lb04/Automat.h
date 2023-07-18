#pragma once //gleich wie #ifnend #endif in C 

//STR + Punkt --> Create definition

#include <iostream>
class Automat {
	unsigned long geld{ 0L };
	std::string standort;
public:
	// Automat() {}; // default -> gleich implizit
	// Automat() = default; // C++ 11 default
	Automat() : standort{ "unbekannt" } {}
	Automat(unsigned long geld) : geld{ geld } {}
	Automat(std::string standort) : standort{ standort } {}
	explicit Automat(unsigned long geld, std::string standort) : geld{ geld }, standort{ standort } {}
	~Automat() { // Regelt aufräumung kritischer Ressourcen
		std::cout << "Kritische Sektion freigegeben" << std::endl;
	}
};