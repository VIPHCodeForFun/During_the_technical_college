#pragma once
#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <cmath>

namespace  VidP
{
	//Nicht möglich die Funktionen Von Templates in eigene CPP files auszulagern.
	template <typename T>
	class Complex
	{
	protected:
		T a, b, betrag;
	public:
		Complex() : a{ 0 }, b{ 0 }, betrag{ 0 } {};
		Complex(T Re, T Im)
		{
			this->a = Re;
			this->b = Im;
			betrag = sqrt(this->a * this->a + this->b * this->b);
		}
		~Complex() = default;

		//Operatoren +, -, * und /
		Complex operator+(Complex& toAdd)
		{
			Complex<T> temp;
			temp.a = this->a + toAdd.a;
			temp.b = this->b + toAdd.b;
			temp.betrag = sqrt(temp.a * temp.a + temp.b * temp.b);
			return (temp);
		}
		Complex operator-(Complex& toSub)
		{
			Complex<T> temp;
			temp.a = this->a - toSub.a;
			temp.b = this->b - toSub.b;
			temp.betrag = sqrt(temp.a * temp.a + temp.b * temp.b);
			return (temp);
		}
		Complex operator*(Complex& toMult)
		{
			Complex<T> temp(0, 0);
			temp.a = (this->a * toMult.a) + ((this->b * toMult.b) * (-1));
			temp.b = (this->a * toMult.b) + (this->b * toMult.a);
			temp.betrag = sqrt(temp.a * temp.a + temp.b * temp.b);
			return (temp);
		}
		Complex operator/(Complex& todiw)
		{
			Complex<T> temp(0, 0);
			Complex<T> Zaehler(0, 0);
			Complex<T> Nenner(0, 0);
			Complex<T> konjugiert(0, 0);
			T DNenner = 0;
			konjugiert.a = todiw.a;
			konjugiert.b = todiw.b * (-1);
			Zaehler = *this * konjugiert;
			Nenner = todiw * konjugiert;
			DNenner = Nenner.a + Nenner.b;
			temp.a = Zaehler.a / DNenner;
			temp.b = Zaehler.b / DNenner;
			temp.betrag = sqrt(temp.a * temp.a + temp.b * temp.b);
			return (temp);
		}
		//Zuweisungsoperatoren
		// = bleibt CCtor
		Complex operator+=(Complex& toAdd)
		{
			this->a += toAdd.a;
			this->b += toAdd.b;
			this->betrag = sqrt(this->a * this->a + this->b * this->b);
			return (*this);
		}
		Complex operator-=(Complex& toSub)
		{
			this->a -= toSub.a;
			this->b -= toSub.b;
			this->betrag = sqrt(this->a * this->a + this->b * this->b);
			return (*this);
		}
		//Vergleicsoperatoren
		bool operator==(Complex& is)
		{
			bool booly = false;
			if (this->a == is.a && this->b == is.b)
			{
				booly = true;
			}
			return booly;
		}
		bool operator>=(Complex& is)
		{
			bool booly = false;
			if (this->betrag >= is.betrag)
			{
				booly = true;
			}
			return booly;
		}
		bool operator<=(Complex& is)
		{
			bool booly = false;
			if (this->betrag <= is.betrag)
			{
				booly = true;
			}
			return booly;
		}

		friend std::ostream& operator<<(std::ostream& os, const Complex<T>& str)
		{
			os << std::to_string(str.a) + "+" + std::to_string(str.b) + "j" + " |z|=" + std::to_string(str.betrag);
			return os;
		}
		friend std::istream& operator>>(std::istream& is, Complex<T>& nr)
		{
			is >> nr.a;
			std::cin.ignore(10000, '+');
			is >> nr.b;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			return is;
		}
	};
}

