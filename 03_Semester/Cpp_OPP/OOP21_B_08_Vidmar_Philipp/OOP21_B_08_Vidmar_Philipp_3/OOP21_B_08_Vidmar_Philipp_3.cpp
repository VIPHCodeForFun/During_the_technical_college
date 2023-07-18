// OOP21_B_08_Vidmar_Philipp_3.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
/*
Schreiben Sie ein Programm, das einen String („LET IT SNOW“) um x beliebige Stellen nach links oder rechts rotieren lässt.
Überschreiben Sie dazu die Operatoren << und >>.

Das Programm soll wie folgt funktionieren:
std::string input = "LET IT SNOW";
//std::cout << std::quoted(input << offset) << '\n'; // offset = 3 --> " IT SNOWLET"
//std::cout << std::quoted(input >> offset) << '\n'; // offset = 10 --> "ET IT SNOWL"

std::quoted findet sich in #include<iomanip> und erlaubt die Ausgabe von “. Als Übergabeparameter wird ein std::string erwartet
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>    // std::rotate

std::string& operator<<(std::string& str, int& offset)
{
	if (offset > (int)str.size())
	{
		offset = offset % (int)str.size();
	}
	std::rotate(str.begin(), str.begin() + offset, str.end()); //<<
	return str;
}
std::string& operator>>(std::string& str, int& offset)
{
	if (offset > (int)str.size())
	{
		offset = offset % (int)str.size();
	}
	std::rotate(str.rbegin(), str.rbegin() + offset, str.rend()); //>>
	return str;
}

int main()
{
	std::string input = "LET IT SNOW";
	std::string input2 = "LET IT SNOW";
	int offset1 = 12, offset2 = 0;
	//std::cin >> offset1;
	//std::cin >> offset2;

	std::cout << std::quoted(input << offset1) << '\n';
	std::cout << std::quoted(input2 >> offset2) << '\n';

	return 0;
}