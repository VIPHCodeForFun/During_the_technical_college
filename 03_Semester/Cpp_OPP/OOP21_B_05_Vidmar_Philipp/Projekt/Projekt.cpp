
#include "TData.h"
#include <array>

TData Aufgabe_D()
{
	TData rTData;
	rTData.name = " Aufgabe D ";
	rTData.data.push_back('D');
	return rTData;
}

int TData::id = 111111;

int main()
{
	//Aufgabe A
	std::cout << " Aufgabe A" << std::endl;
	TData a;
	TData b = a;
	//Antwort: Es wird der CopyKonstruktor ausgeführt

	//Aufgabe B
	std::cout << " Aufgabe B" << std::endl;
	a.Aufgabe_B_CBR(b);
	a.Aufgabe_B_CBV(b);
	//Antwort: Bei CBV wird der CopyKosntruktor aufgerufen bei CBR nicht.

	//Aufgabe C
	std::cout << " Aufgabe C" << std::endl;
	TData c = a.Aufgabe_C();
	//Antwort: Es wird der MoveKonstruktor aufgerufen

	//Aufgabe D
	//Antwort: Das Verhalten ändert sich nicht.

	//Aufgabe E
	std::cout << " Aufgabe E" << std::endl;
	TData e = Aufgabe_D();
	//Die Daten des Quellobjkektes fidnen sich nicht vor;
	//Es Wird ein Destruktor für das Quellobjekt aufgerufen;

	//Aufgabe F
	std::cout << " Aufgabe F" << std::endl;
	std::cout << " Vector erstellen: " << std::endl;
	std::vector<TData> vectorF(10);
	std::cout << " Array erstellen: " << std::endl;
	std::array<TData, 10> arrayF;
	//Antowrt: Es wird immer der Stadnard Kosntruktor aufgerufen.
	//Antowrt: Da die Vrariabelen ganz normal Initialiseirt werden

	vectorF.push_back(a);
	//copy für elemennt a, Die vector elemente werden mit move verschoben
	vectorF.emplace_back(b);


	//Aufgabe G
	//Der Move und Copy konstruktor gibt leere Werte zurück:
	//Weil beim Aufruf der Konstruktoren keine Daten gesetzt werden

	//Aufgabe H

	//Aufgabe I

	//Aufgabe J
	TData j = std::move(a);

	//Aufgabe K
	TData k;
	k.setter(69);

	std::cout << " ------------------- " << std::endl;
}
