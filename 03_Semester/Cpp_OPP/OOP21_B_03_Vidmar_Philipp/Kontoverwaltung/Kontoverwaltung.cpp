// Kontoverwaltung.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//-----------------------KONTO---------------------
class Konto
{
public:
	float betrag;					 //ev Ändern
	std::string name;				 //ev Ändern
	std::vector<float> transaktonen; //ev Ändern

	Konto();	//konstruktor
	~Konto();	//desstruktor

	void Kontoeroeffnung(const std::string& name, const float& startbetrag)
	{
		if (startbetrag < 0)
		{
			std::cout << "kein negativer Saldo erlabut!" << std::endl;
			return;
		}
		if (startbetrag > FLT_MAX)
		{
			std::cout << "Maximalbetrag erreicht!" << std::endl;
			return;
		}
		Konto::name = name;
		Konto::betrag = startbetrag;
		transaktonen.push_back(startbetrag);
		return;
	}
	void Einzahlen(const float& betrag)
	{
		if (betrag < 0)
		{
			std::cout << "kein negative Einzahlung erlabut!" << std::endl;
			return;
		}
		if (Konto::betrag + betrag > FLT_MAX)
		{
			std::cout << "Maximalbetrag erreicht!" << std::endl;
			return;
		}
		Konto::betrag = Konto::betrag + betrag;
		transaktonen.push_back(betrag);
	}
	void Auszalen(const float& betrag)
	{
		if (Konto::betrag - betrag < 0)
		{
			std::cout << "Abbuchungsbetrag ist zu hoch! (kein negativer Saldo erlabut!)" << std::endl;
			return;
		}
		Konto::betrag = Konto::betrag - betrag;
		transaktonen.push_back((-1) * betrag);
		return;
	}
	void KontoAusgabe()
	{
		std::cout << "Kontoinhaber/in: " << Konto::name << " Kontostand: " << Konto::betrag << " EURO" << std::endl;
		return;
	}
	void Kontoauszug()
	{
		int position = 1;
		int ausgabeleange = 10;
		float zwischenusmme = 0;
		std::cout << "-----------Kontoauszug-----------" << std::endl;
		KontoAusgabe();
		for (float i : transaktonen) // läuft bis zum ende Durch
		{
			std::cout << "Buchung [" << position << "] :  " << i << " EURO" << std::endl;

			zwischenusmme = zwischenusmme + i;

			if (position >= ausgabeleange) // generiert jede 10 Transaktion eine Zwischensumme
			{
				std::cout << "Zwischensumme: " << zwischenusmme << " EURO" << std::endl;
				ausgabeleange = ausgabeleange + 10;
			}
			position++;
		}
	}
private:
};
Konto::Konto()
{
	Konto::name = "---";
	Konto::betrag = 0;
}
Konto::~Konto()
{
}
//------------------------------------------------
void BankKonto(std::vector<Konto>& Bank, const std::string& name, const float& startbetrag)
{
	//Fügt ein neues Konto in eine Bank ein
	Konto neuesKonto;
	neuesKonto.Kontoeroeffnung(name, startbetrag);
	Bank.push_back(neuesKonto);
}
void SaveBankDataIntoTxT(std::vector<Konto> Bank, std::string path)
{
	std::ofstream oFile;
	oFile.open(path); // überschreibt das komplette FILE!

	if (oFile.is_open())
	{
		for (Konto konto : Bank) // Geh alle Elemente Konto von Bank durch
		{
			oFile << konto.name << "\n"; //schreibt den namen in die erste zeile
			oFile << konto.betrag << "\n"; //schreibt den konntostand in File
			for (float wert : konto.transaktonen)
			{
				oFile << wert << " "; // schreibt alle Transaktionen ins file
			}
			oFile << "\n";
		}
	}
	oFile.close();
	return;
}
void LoadBankDataFromTXT(std::vector<Konto>& Bank, std::string path)
{
	std::ifstream iFile;
	iFile.open(path);
	if (iFile.is_open())
	{
		std::string buffer;
		std::string name;
		std::vector<float> transaktionen;
		float betrag = 0;
		int zeile = 0;

		while (getline(iFile, buffer))
		{
			if (zeile == 0)//Name
			{
				name = buffer;
				zeile++;
			}
			else if (zeile == 1)//Betrag
			{
				betrag = (float)std::atof(buffer.c_str());
				zeile++;
				BankKonto(Bank, name, betrag);
			}
			else if (zeile == 2)//transaktion
			{
				std::istringstream iss(buffer);
				std::string token;
				//string buffer aufteilen
				while (getline(iss, token, ' '))
				{
					transaktionen.push_back((float)std::atof(token.c_str()));
				}
				auto* ptr = &Bank.back();
				ptr->transaktonen = transaktionen;
				transaktionen.clear();
				zeile = 0;
			}

		}
	}
}

int main()
{
	std::vector<Konto> Bank; //KONTAINER DA SIND VILE KONTOS DRINNEN.
	LoadBankDataFromTXT(Bank, "SICHERUNG_BANK_DATEN.txt");

	BankKonto(Bank, "1Bene", 1000);
	BankKonto(Bank, "2Berni", 900);
	BankKonto(Bank, "3Klaus", 800);
	BankKonto(Bank, "4Seppl", 700);
	BankKonto(Bank, "5Maxi", 10000);
	Bank[0].Einzahlen(200);
	Bank[0].Auszalen(600);
	Bank[0].Einzahlen(200);
	Bank[0].Auszalen(600);
	Bank[0].Einzahlen(200);
	Bank[0].Auszalen(600);
	Bank[0].Einzahlen(200);
	Bank[0].Auszalen(700);
	Bank[0].Einzahlen(500);
	Bank[0].Auszalen(600);
	Bank[0].Einzahlen(2000);
	Bank[0].Auszalen(600);
	Bank[0].Kontoauszug();

	Bank[2].Einzahlen(300);

	SaveBankDataIntoTxT(Bank, "SICHERUNG_BANK_DATEN.txt");
	return 0;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
