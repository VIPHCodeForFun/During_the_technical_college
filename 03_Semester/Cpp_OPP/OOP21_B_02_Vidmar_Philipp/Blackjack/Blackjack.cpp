// Blackjack.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string> 
#include <algorithm>

enum cardcolour {
	heard,
	check,
	cross,
	spades,
	END_CO	// zum durchlaufen des ENUMS
};
enum cardnumber {
	ass,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	boy,
	queen,
	king,
	END_NR // zum durchlaufen des ENUMS 
};
struct card {
	cardcolour cc;
	cardnumber cn;
	//Enum einen String/Farbe zuweisen 
	std::string cardCol(cardcolour x)
	{
		switch (x)
		{
		case heard: return "HEARD";
		case check: return "CHECK";
		case spades: return "SPADES";
		case cross: return "CROSS";
		default:
			break;
		}
	}
	//ENUM einen Wert Zuweisen
	std::string cardNr(cardnumber x)
	{
		switch (x)
		{
		case ass: return "ASS";
		case two:return "2";
		case three:return "3";
		case four:return "4";
		case five:return "5";
		case six:return "6";
		case seven:return "7";
		case eight:return "8";
		case nine:return "9";
		case ten:return "10";
		case boy:return "Boy";
		case queen:return "Queen";
		case king:return "King";
		default:
			break;
		}
	}

	//ENUM einen Wert Zuweisen
	int cardVal(cardnumber x)
	{
		switch (x)
		{
		case ass: return 11;
		case two:return 2;
		case three:return 3;
		case four:return 4;
		case five:return 5;
		case six:return 6;
		case seven:return 7;
		case eight:return 8;
		case nine:return 9;
		case ten:return 10;
		case boy:return 10;
		case queen:return 10;
		case king:return 10;
		case END_NR:return 0;
		default:
			return 0;
		}
	}
};

void createDeck(std::vector<std::shared_ptr<card>>& Carddeck, int& times)
{
	//erstelle n Kartendecks
	int n = 0;
	for (n = 0; n < times; n++)
	{
		//Erstellen eines Cartendecks
		//Durchlaufen der Kartenfarben (ENUM)
		int i = 0;
		int j = 0;
		for (i = cardcolour::heard; i < cardcolour::END_CO; i++)
		{
			//Durchlaufen der KartenZahl
			for (j = cardnumber::ass; j < cardnumber::END_NR; j++)
			{
				//erstelle einen shared_PTR und hänge ihn im vektor Hinten an 
				Carddeck.push_back(std::make_shared<card>());
				//beschreibe die Erstellte karte mit Farbe und Zahl.
				Carddeck.back()->cc = (cardcolour)i;
				Carddeck.back()->cn = (cardnumber)j;
			}
		}
	}
}
void printDeck(std::vector<std::shared_ptr<card>> Carddeck)
{
	//Laufe alle Elemente von Carddeck durch
	for (auto& element : Carddeck)
	{
		std::cout << element->cardCol(element->cc) << " " << element->cardNr(element->cn) << std::endl;
	}
}
void shuffl(std::vector<std::shared_ptr<card>>& Carddeck)
{
	if (Carddeck.size() < 1)
	{
		return;
	}
	srand(time(NULL)); //RAND Seed
	int i = 0;
	int randnr = rand() % Carddeck.size(); // rand zahl im Bereich der Vektor größe
	for (i = 0; i < Carddeck.size(); i++)
	{
		randnr = rand() % Carddeck.size(); // new Randnr
		std::swap(Carddeck[i], Carddeck[randnr]);
	}
}
void bjBot(std::vector<std::shared_ptr<card>>& Carddeck)
{
	int sum = 0;
	while (Carddeck.size() != 0)
	{
		//hol das Val von der letzten kate im deck
		sum = sum + Carddeck.back()->cardVal(Carddeck.back()->cn);
		//schmeiss die letzte KArte weg
		Carddeck.pop_back();
		if (sum > 17 && sum <= 21)
		{
			std::cout << "gewonnen" << std::endl;
			sum = 0;
		}
		if (sum > 21)
		{
			std::cout << "verloren" << std::endl;
			sum = 0;
		}
	}
}

int main(int argc, char* argv[])
{
	int consoleIn = std::atoi(argv[1]);
	//erstellen eines Vektors der aus CARD s_PTR besteht.
	std::vector<std::shared_ptr<card>> Carddeck;
	if (consoleIn < 1)
	{
		return 0;
	}
	createDeck(Carddeck, consoleIn);
	shuffl(Carddeck);
	printDeck(Carddeck);
	bjBot(Carddeck);

	return 0;
}
