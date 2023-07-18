// U10_4.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

/*
Schreiben Sie eine Template Funktion swap3, welche die drei Parameter a, b, und c änderbar entgegennimmt und so untereinander austauscht,
dass die Parameter nach dem Funktionsaufruf jeweils der Größe nach geordnet (aufsteigend) vorliegen. Der Rückgabewert der Funktion sollte true sein,
wenn Werte getauscht wurden, andernfalls sollte false zurückgegeben werden. Setzen Sie a, b und c (std::cin) und überprüfen Sie ob bei der swap3 Funktion Werte geändert werden.
Sollten sich Werte ändern, geben Sie "swapped" auf die Konsole aus.
Sollte sich nichts ändern, geben Sie "nothing changed" auf die Konsole aus.

* Beantworten Sie für sich die Frage: Welche Voraussetzungen muss ein Datentyp erfüllen, der dem Template als Parameter übergeben werden kann?
*/

#include <iostream>
#include <vector>

template <typename T>
bool swap3(T& a, T& b, T& c)
{
	std::vector<T> vec;
	vec.push_back(a);
	vec.push_back(b);
	vec.push_back(c);
	bool swarped = false;
	for (int i = 0; i < (int)vec.size(); i++)
	{
		for (int j = i; j < (int)vec.size(); j++)
		{
			if (vec[i] > vec[j])
			{
				std::swap(vec[i], vec[j]);
				swarped = true;
			}
		}
	}
	a = vec[0];
	b = vec[1];
	c = vec[2];
	return swarped;
}

int main() {
	int a, b, c;
	std::cin >> a >> b >> c;

	bool x = swap3(a, b, c);
	std::cout << a << b << c << std::endl;
	if (x == true)
	{
		std::cout << "swapped" << std::endl;
	}
	else
	{
		std::cout << "nothing changed" << std::endl;
	}

	return 0;
}
