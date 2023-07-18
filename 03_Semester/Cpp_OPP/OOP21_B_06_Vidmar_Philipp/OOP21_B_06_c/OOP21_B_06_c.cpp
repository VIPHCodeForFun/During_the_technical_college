/*
a) Erstellen Sie die folgende Vererbungshierarchie der Klassen:
Dreieck (Elternklasse) <-- Gleichschenklig (Kindklasse Triangle) <-- Gleichseitig (Kindklasse Gleichschenklig)

Sehen Sie die Methode print() in der Dreieck Klasse vor, welche jeweils den jeweiligen Klassennamen auf die Konsole ausgibt.
Instanzieren Sie in der Main ein Gleichseitig Objekt und rufen Sie die print() Methode des Objektes, sowie aller Elternobjekte auf.

Ausgabe
Ich bin Gleichseitig
Ich bin Gleichschenklig
Ich bin ein Dreieck

b) Erzeugen Sie die Methode printParent(), welche jeweils !!!automatisch!!! die Eltern printParent() Methoden und die Abhängikeit
der aktuellen Position in der Hierarchie ausgibt.
Da Dreieck keine Elternklasse hat, soll direkt die print Methode ausgeführt werden. Überprüfen Sie diese Methode mit dem in a) instanzierten Gleichseitig Objekt.

Ausgabe
Ich bin Gleichseitig basierend auf Gleichschenklig
Ich bin Gleichschenklig basierend auf Dreieck
Ich bin ein Dreieck
*/

#include <iostream>

class Dreieck
{
public:

	void print()
	{
		std::cout << "Ich bin ein Dreieck" << std::endl;
	}
	void printParent()
	{
		this->print();
	}
private:

};

class Gleichschenklig : public Dreieck
{
public:

	void print()
	{
		std::cout << "Ich bin Gleichschenklig" << std::endl;
	}
	void printParent()
	{
		std::cout << "Ich bin Gleichschenklig basierend auf Dreieck" << std::endl;
		this->Dreieck::printParent();
	}
private:

};
class Gleichseitig : public Gleichschenklig
{
public:

	void print()
	{
		std::cout << "Ich bin Gleichseitig" << std::endl;
	}
	void printParent()
	{
		std::cout << "Ich bin Gleichseitig basierend auf Gleichschenklig" << std::endl;
		this->Gleichschenklig::printParent();
	}
private:

};

void foo(Dreieck& currentDreieck) {
	// Ptr -> [Person][Student][Graduate]
	currentDreieck.print();
}

int main() {
	// a
	Gleichseitig g1;
	g1.print();
	g1.Gleichschenklig::print(); // Aufruf der Elternfunktionen?
	g1.Dreieck::print();
	// b
	g1.printParent();


	return 0;
}