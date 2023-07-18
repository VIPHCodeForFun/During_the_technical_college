// OOP21_B_08_Vidmar_Philipp.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

#include <iostream>
#include <sstream>
#include <ostream>
#include <string>

/*
a) Überladen Sie die Operatoren + und << der gegebenen Komplex Klasse (komplexe Zahlen).
Der + Operator soll die komplexen Zahlen auf Basis derer Additionsregel addieren.
Der << Operator soll die jeweilige Zahl im Format a+bj auf cout ausgeben.
Befüllen Sie die Klassen über die Funktion input(std::string) welche String basierten std::cin input in das korrekte Format parst.
Passen Sie ihre Klasse so an das die gegebene Main zu dem geforderten Output führt.

Eingabe
5+4j
3+-5j

Ausgabe
8+-1j

b) Erweitern Sie die Klasse Complex von a) indem Sie den >> Operator so überladen das Complex direkt befüllt werden kann
(bringen Sie den Vorgegebenen main Code zum laufen).
*/
class Complex {
public:

	Complex() = default;
	~Complex() = default;
	Complex operator+(Complex& toAdd)
	{
		this->a = this->a + toAdd.a;
		this->b = this->b + toAdd.b;
		return (*this);
	}
	friend std::ostream& operator<<(std::ostream& os, const Complex& str);
	friend std::istream& operator>>(std::istream& is, Complex& nr);
	int a, b;

	void input(std::string s) //5+4j //3+-5j
	{
		std::istringstream istr(s);
		std::string strRe;
		std::string strIm;

		getline(istr, strRe, '+');
		getline(istr, strIm, 'j');

		a = std::stoi(strRe);
		b = std::stoi(strIm);
	}
};

std::ostream& operator<<(std::ostream& os, const Complex& str)
{
	os << std::to_string(str.a) + "+" + std::to_string(str.b) + "j";
	return os;
}
std::istream& operator>>(std::istream& is, Complex& nr)
{

	is >> nr.a;
	std::cin.ignore(10000, '+');
	is >> nr.b;
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	return is;
}


int main()
{
	//A
	/*
		Complex x, y;
		std::string s1, s2;
		std::cin >> s1;
		std::cin >> s2;
		x.input(s1);
		y.input(s2);
		Complex z = x + y;
		std::cout << z << std::endl;
	*/
	//B
	Complex x, y;
	std::cin >> x;
	std::cin >> y;
	Complex z = x + y;
	std::cout << z << std::endl;


	return 0;

}