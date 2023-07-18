// OOP21_B_06.cpp : 
/*
a) Erstellen Sie die Klasse Rectangle mit den zwei Attributen Höhe und Breite.
 > Die Klasse Rectangle soll die Methode display() bereitstellen, die Höhe und Breite getrennt durch ein Leerzeichen auf cout ausgibt.
 > Die Klasse Rectangle soll eine Methode readInput() bekommen, die Höhe und Breite über cin entgegennimmt und in die vererbten Attribute speichert.
 > Achten Sie hierfür auf passende Zugriffsattribute. Höhe und Breite müssen wie folgt beschränkt werden: höhe > 1, breite ≤ 100.
   Sollte diese Beschränkungen nicht eingehalten werden sollen die jeweiligen Werte default initialisiert werden: höhe = 2, breite = 0 (Siehe Precheck für Hilfe).
Das Programm darf bei einer Fehleingabe nicht abstürzen.

Auch wenn cerr für Fehler zu bevorzugen ist, verwenden Sie für alle Ausgaben cout.
----------------------------------------
Beispiel einer Eingabe
10 5
Beispiel einer Ausgabe
h=10 b=5
----------------------------------------
Beispiel einer Eingabe:
0 150

Beispiel einer Ausgabe:
Fehler: Hohe zu gering, verwende Default (2)
Fehler: Breite zu hoch, verwende Default (0)
h=2 b=0

Answer:(penalty regime: 10, 20, ... %)
*/

#include <iostream>

class Rectangle
{
public:
	Rectangle()
	{
		this->height = 2;
		this->width = 0;
	}

	void display()
	{
		if (this->height != 1)
		{
			std::cout << "h=" << height << " b=" << width << std::endl;
		}
	}
	void readInput()
	{
		int i_height = 2;
		int i_width = 0;

		if ((std::cin >> i_height) && (std::cin >> i_width))
		{
			if (i_height > 2)
			{
				this->height = i_height;
			}
			else
			{
				std::cout << "Fehler: Hohe zu gering, verwende Default (2)" << std::endl;
				this->height = 2;
			}
			if (i_width <= 100)
			{
				this->width = i_width;
			}
			else
			{
				std::cout << "Fehler: Breite zu hoch, verwende Default (0)" << std::endl;
				this->width = 0;
			}

		}
		else
		{
			std::cout << "Eingabe fehlgeschlagen" << std::endl;
			this->height = 1;
		}
		std::cin.clear(); //löscht Fehler Flag in cin
		std::cin.ignore(10000, '\n'); // Ignoriert die nächsten 10000 Zeichen bis \n
	}
protected:
	int width;
	int height;
};
/*
b) Leiten Sie von Rectangle aus a) die Klasse RectangleArea ab.
   Überladen Sie die display() Methode von RectangleArea um zusätzlich zu Höhe und Breite die Fläche auszugeben.
*/
class RectangleArea : public Rectangle
{
public:

	RectangleArea() : Rectangle()
	{
		this->aeria = this->height * this->width;
	}

	void display()
	{
		if (this->height != 1)
		{
			this->aeria = this->height * this->width;
			std::cout << "h=" << this->height << " b=" << this->width << " A=" << this->aeria << std::endl;
		}
	}
private:
	int aeria;
};

int main() {
	Rectangle r1;
	r1.readInput();
	r1.display();

	RectangleArea ra1;
	ra1.readInput();
	ra1.display();

	return 0;
}

