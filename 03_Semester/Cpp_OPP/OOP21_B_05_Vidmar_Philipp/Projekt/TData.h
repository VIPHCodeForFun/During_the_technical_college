#pragma once
#include <iostream>
#include <vector>

class TData
{
public:
	std::string name;
	std::vector<char> data;
	/*
	TData() = default; //Konstruktor
	TData(const TData& copy) = default; //Copy
	TData(TData&& move) = default; //Move
	~TData() = default; //Destruktor
	*/

	TData(); //Konstruktor
	TData(const TData& copy); //Copy
	TData(TData&& move) noexcept; //Move
	~TData(); //Destruktor

	void Aufgabe_B_CBV(TData x);
	void Aufgabe_B_CBR(TData& x);
	TData Aufgabe_C();

	int getter();
	void setter(int idx);

private:
	static int id;
};

