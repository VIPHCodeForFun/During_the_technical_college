// Kontoverwaltung.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <random>

//-----------------------KONTO---------------------
class Konto
{
	/*
	PROGRAMM WURDE AUS LB03 ÜBERNOMMEN Änderungen WURDEN MIT LB04 + "AUFGABENSTELLUNG" MAKIERT

	SAVE UND LOAD DATA  FUNKTIONIEREN NOCH WIE IN LB03 BESCHRIEBEN änderung zu LB03: VECTOR<KONTO> --> VECTOR<KONTO*> GEÄNDERT

	KÖNNTE MAN ÜBERDENKEN / UMARBEITEN, WAR ABER NICHT GEFRAGT:
	VARIABLEN IN DER KLASSE SOLLTE IN PRIVATE GESCHOBEN WERDEN UND MIT GET UND SET ABGERUFEN WERDEN //ev Ändern
	NEUEN ORDNER ANLEGEN WO ALLE TXT DATEIN HINEINGELEGT WERDEN DA SONST .\ KOMPLET ZUGEMÜLLT WIRD.

	NEUE FUNKTIONEN:
	Konto(const std::string& name, const float& startbetrag)
	Konto(const Konto& original)
	void Ueberweisung(Konto& Empfaenger, float ueberweisung)
	void LoggingToTXT(std::string info, std::string time)
	std::string aktTime()
	void Kontoschliessen()
	int createID()
	~Konto();

	TEST WURDE IN DER MAIN DURCHGEFÜHRT UND MITTELS CHECKSUMME GEPRÜFT
	*/
public:
	float betrag;					 //ev Ändern
	std::string name;				 //ev Ändern
	std::vector<float> transaktonen; //ev Ändern
	int KontoID; //LB4_a
	bool geschlossen; //LB4d

	Konto();	//konstruktor
	Konto(const std::string& name, const float& startbetrag);//LB4_a
	Konto(const Konto& original); // LB4_b
	~Konto();	//desstruktor

	void Ueberweisung(Konto& Empfaenger, float ueberweisung)
	{
		if (ueberweisung <= 0 || geschlossen == true || Empfaenger.geschlossen == true)
		{
			std::cout << "Ein Konto ist geschlossen oder der betrag ist kleiner 0" << std::endl;
			return;
		}
		if (Konto::betrag - ueberweisung < 0)
		{
			std::cout << "nicht genuegend Geld am Konto" << std::endl;
			return;
		}
		if (Empfaenger.betrag + ueberweisung > FLT_MAX)
		{
			std::cout << "Maximalbetrag Empfänger erreicht!" << std::endl;
			return;
		}
		if (KontoID == Empfaenger.KontoID)
		{
			return;
		}
		//abheben vom konto
		Konto::betrag = Konto::betrag - ueberweisung;
		Konto::transaktonen.push_back((-1) * betrag);
		Konto::LoggingToTXT("Überweisung", Konto::aktTime());

		//senden an Empfänger
		Empfaenger.betrag = Empfaenger.betrag + ueberweisung;
		Empfaenger.transaktonen.push_back(ueberweisung);
		Empfaenger.LoggingToTXT("Überweisung", Konto::aktTime());
		return;

	}
	void LoggingToTXT(std::string info, std::string time)//LB4_d
	{
		std::string path = std::to_string(Konto::KontoID);
		path = path + ".txt";
		std::ofstream oFile;
		oFile.open(path, std::ios::app); //	Alle Ausgabeoperationen werden am Ende der Datei durchgeführt, wobei der Inhalt an den aktuellen Inhalt der Datei angehängt wird.
		if (oFile.is_open())
		{
			oFile << time << " " << info << "\n";
		}
		oFile.close();
		return;
	}
	std::string aktTime() //LB4_d
	{
		// #include <time.h>
		std::time_t time1970 = std::time(NULL);		  // zeit seit 1970
		std::time_t* ptr_time1970 = &time1970;		  // Pointer auf zeit
		tm* timestap = new tm;
		char buffer[100];
		localtime_s(timestap, ptr_time1970);	  	  // wandelt zeit seit 1970 in aktuelle um
		strftime(buffer, 100, "[%T]  [%F]", timestap);// formatiert die Zeit
		return buffer;
	}
	void Kontoschliessen()
	{
		if (Konto::betrag != 0)
		{
			std::cout << "Konnto kann nicht geschlossen werden Kontostand:" << Konto::betrag << std::endl;
			return;
		}
		Konto::geschlossen = true;
		return;
	}
	int createID()//LB4_a
	{
		static int ID = 10000;
		ID++;
		return ID;
	}
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
		Konto::geschlossen = false;
		return;
	}
	void Einzahlen(const float& betrag)
	{
		if (Konto::geschlossen == true)
		{
			std::cout << "E Das Konto ist Geschlossen" << std::endl;
			return;
		}
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
		LoggingToTXT("Einzahlung", Konto::aktTime());
	}
	void Auszalen(const float& betrag)
	{
		if (Konto::geschlossen == true)
		{
			std::cout << "A Das Konto ist Geschlossen" << std::endl;
			return;
		}
		if (Konto::betrag - betrag < 0)
		{
			std::cout << "Abbuchungsbetrag ist zu hoch! (kein negativer Saldo erlabut!)" << std::endl;
			return;
		}
		Konto::betrag = Konto::betrag - betrag;
		transaktonen.push_back((-1) * betrag);
		LoggingToTXT("Auszahlung", Konto::aktTime());
		return;
	}
	void KontoAusgabe()
	{
		if (Konto::geschlossen == true)
		{
			std::cout << "Kontoinhaber/in: " << Konto::name << " Kontostand: " << Konto::betrag << " EURO  ID:" << Konto::KontoID << " Status: geschlossen" << std::endl;
		}
		else
		{
			std::cout << "Kontoinhaber/in: " << Konto::name << " Kontostand: " << Konto::betrag << " EURO  ID:" << Konto::KontoID << " Status: normal" << std::endl;
		}
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
	Konto::KontoID = Konto::createID(); //LB4_a
	Konto::geschlossen = true;
	LoggingToTXT("Kontoerstellung", Konto::aktTime());
}
Konto::Konto(const std::string& name, const float& startbetrag)//LB4_a
{
	if (startbetrag < 0 || startbetrag > FLT_MAX)
	{
		Konto::betrag = 0;
	}
	else
	{
		Konto::betrag = startbetrag;
	}
	Konto::name = name;
	transaktonen.push_back(startbetrag);
	Konto::KontoID = Konto::createID(); //LB4_a
	Konto::geschlossen = false;
	LoggingToTXT("Kontoerstellung", Konto::aktTime());
}
Konto::Konto(const Konto& original) // LB4_b
{
	std::cout << "wird kopiert" << std::endl;
	Konto::name = original.name;
	Konto::betrag = 0;
	Konto::transaktonen.clear();
	Konto::transaktonen.push_back(0);
	Konto::KontoID = Konto::createID();
	Konto::geschlossen = false;
	LoggingToTXT("Konto Kopie", Konto::aktTime());
}
Konto::~Konto()
{
	LoggingToTXT("Konto wird Zersört", Konto::aktTime());
}
//------------------------------------------------
void BankKonto(std::vector<Konto*>& Bank, const std::string& name, const float& startbetrag)
{
	//Fügt ein neues Konto in eine Bank ein
	Konto* newptr = new Konto(name, startbetrag);
	Bank.push_back(newptr);
}
void SaveBankDataIntoTxT(std::vector<Konto*> Bank, std::string path)
{
	std::ofstream oFile;
	oFile.open(path); // überschreibt das komplette FILE!

	if (oFile.is_open())
	{
		for (Konto* konto : Bank) // Geh alle Elemente Konto von Bank durch
		{
			oFile << konto->name << "\n"; //schreibt den namen in die erste zeile
			oFile << konto->betrag << "\n"; //schreibt den konntostand in File
			for (float wert : konto->transaktonen)
			{
				oFile << wert << " "; // schreibt alle Transaktionen ins file
			}
			oFile << "\n";
		}
	}
	oFile.close();
	return;
}
void LoadBankDataFromTXT(std::vector<Konto*>& Bank, std::string path)
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
				auto* ptr = Bank.back();
				ptr->transaktonen = transaktionen;
				transaktionen.clear();
				zeile = 0;
			}

		}
	}
}

int main()
{
	//std::vector<Konto*> Bank; //KONTAINER DA SIND VILE KONTOS DRINNEN.
	//LoadBankDataFromTXT(Bank, "SICHERUNG_BANK_DATEN.txt");
	/*
	Konto p1("p1", 100); //TEST  LB04_a
	Konto p2("p2", 200); //TEST  LB04_a
	Konto p3("p3", 300); //TEST  LB04_a
	Konto p3copy = p3;   //TEST  LB04_b
	Konto p4;
	p1.Einzahlen(20);		//TEST  LB04_c
	p4.Einzahlen(30);		//TEST  LB04_c
	p3.Kontoschliessen();	 //TEST  LB04_c
	p3copy.Kontoschliessen();//TEST  LB04_c

	p1.KontoAusgabe();
	p2.KontoAusgabe();
	p3.KontoAusgabe();
	p3copy.KontoAusgabe();
	p4.KontoAusgabe();
	//TEST TXT FILE LB04_d

	p1.Ueberweisung(p2, 10); //TEST  LB04_e
	p1.Ueberweisung(p2, 200); //TEST  LB04_e
	p1.KontoAusgabe();
	p2.KontoAusgabe();
	*/
	//TXT LB04_G---------------------------------------------------------
	//erzeugt 10 Kontos in einen Vektor
	float checksumm = 0;
	std::vector <Konto*> LB04_G;
	/*ERSTELLEN EINES VECTORS [10] für  LOAD TXT   SICHERUNG_BANK_DATEN.txt mit 10 Konten
	for (int i = 0; i < 10; i++)
	{
		std::string testname = "TestKonto " + std::to_string(i);
		LB04_G.push_back(new Konto(testname, (float)1000 * i));
		LB04_G[i]->KontoAusgabe();
	}*/

	LoadBankDataFromTXT(LB04_G, "SICHERUNG_BANK_DATEN.txt");

	//Ausgabe Konto

	for (int i = 0; i < 10; i++)
	{
		LB04_G[i]->KontoAusgabe();
		checksumm = checksumm + LB04_G[i]->betrag;
	}

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// INDEX //#include <random>
			std::random_device deviceINDEX;
			std::mt19937 generatorINDEX(deviceINDEX());
			std::uniform_int_distribution<int> distributionINDEX(0, 9);
			int randomINDEX = distributionINDEX(generatorINDEX);

			// BETRAG //#include <random>
			std::random_device deviceBETRAG;
			std::mt19937 generatorBETRAG(deviceBETRAG());
			std::uniform_int_distribution<int> distributionBETRAG(-100, 2000);
			int randomBETRAG = distributionBETRAG(generatorBETRAG);

			LB04_G[j]->Ueberweisung(*LB04_G[randomINDEX], randomBETRAG);
		}
	}

	SaveBankDataIntoTxT(LB04_G, "SICHERUNG_BANK_DATEN.txt");

	//Ausgabe Konto
	float checksumm2 = 0;
	for (int i = 0; i < 10; i++)
	{
		LB04_G[i]->KontoAusgabe();
		checksumm2 = checksumm2 + LB04_G[i]->betrag;
	}
	//auflösen des vectors LB04_G
	for (int i = 0; i < LB04_G.size(); i++)
	{
		delete LB04_G[i]; //Destruktor aufruf
	}
	// Kontrolle des Geldflusses :)
	std::cout << "CHECKSUMME1: " << checksumm << "  CHECKSUMM2:" << checksumm2 << std::endl;

	return 0;
}//TEST TXT FILE LB04_f 
