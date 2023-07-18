// U10_2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
/*
Definieren Sie einen Vektor mit mehreren ganzen Zahlen welcher über std::cin befüllt wird.

Programmieren Sie eine std::for_each Schleife (algorithm Bibliothek), welche über den Vektor iteriert und dabei einen Lambda Ausdruck verwendet
, um zu bestimmen, wie viele Zahlen gerade / ungerade sind und wie viele Zahlen grösser als eine bestimmte Zahl sind. Diese Zahl wird ebenfalls über std::cin angegeben.
Die Ausgabe der Zahlenfolge soll im Lambda Ausdruck erfolgen.

Eingabe Beispiel
1 2 3 4 5 6 STOP
2
Ausgabe Beispiel
1,2,3,4,5,6,
ungerade:3,gerade:3
kleiner-gleich:2,groesser:4
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::vector<int> vec;
	std::string str = "";
	while (true) {
		std::cin >> str;
		if (str == "STOP")
			break;
		vec.push_back(std::stoi(str)); // TODO
	}

	int ungerade = 0, kleiner = 0, grenzwert;
	std::cin >> grenzwert;

	std::for_each(vec.begin(), vec.end(), [&kleiner, &ungerade, &grenzwert](int vecNr)
		{
			if (vecNr <= grenzwert)
			{
				kleiner++;
			}
			if (vecNr % 2 != 0)
			{
				ungerade++;
			}
			std::cout << vecNr << ",";
		});// TODO


	std::cout << std::endl;
	//Außerhalb des Labdas soll die Anzahl der geraden, ungeraden, größeren und kleineren Zahlen ausgegeben werden..
	std::cout << "ungerade:" << ungerade << ",gerade:" << vec.size() - ungerade << std::endl;  // TODO
	std::cout << "kleiner-gleich:" << kleiner << ",groesser:" << vec.size() - kleiner << std::endl;

	return 0;
}