/*
Zur Bestimmung des wahrscheinlichsten Schl¨ussels soll zun¨achst die obige Nachricht
in drei Teile zerlegt werden – einen pro Schl¨usselposition. Schreiben Sie
ein Programm, dem der Pfad zu einer Textdatei als Argument ¨ubergeben wird,
das eine H¨aufigkeitsanalyse der in der Datei vorkommenden Zeichen 'A'...'Z'

f¨ur jede Schl¨usselposition durchf¨uhrt. Das Programm soll diese Zeichen mit zugeh
¨origer relativer H¨aufigkeit (bezogen nur auf die zu analysierenden Zeichen
pro Schl¨usselposition) in absteigender Reihenfolge und pro Schl¨usselposition
spaltenweise auf std::cout stabil sortiert ausgeben. Die H¨aufigkeiten sind
pro Zeichen in Prozent auf ganze Zahlen kaufm¨annisch gerundet und zeilenumbruchgetrennt
exakt (d.h. inklusive Leerzeichen und Trennzeichen) wie folgt
auszugeben (die Zahlenwerte sind nur Beispiele):
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

struct PAIR
{
    char charValue;
    int intValue;
};

#define KEYLENGHT 3

int main(const int argc, const char * const argv[])
{
	if (argc < 2)
	{
		return -1;
	}
    /* Speichern der eingelsenen Werte die Länge ist mit 3 gegeben */
    std::vector<char> csarRoll[KEYLENGHT];

    /* Öffnet das Dokument aus argv 1 */
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {
        // Hier wird bis EOF jedes Byte eingelesen und verarbeitet.
        char bytebuffer; // Buffer zum auslesen und verarbeiten
        int numberForIndexCount = 3; // @count gibt an in welchen vector wir uns bewegen
        while (inputFile.get(bytebuffer))
        {
            // Abfrage ob der Wert zwischen A und Z liegt
            if(bytebuffer >= 'A' && bytebuffer <= 'Z')
            {
                // Die Modulo berechnung sorgt dafür das immer 0,1,2 als Index durchlaufen wird.
                csarRoll[numberForIndexCount%KEYLENGHT].push_back(bytebuffer);
                numberForIndexCount++;
            }
        }
        // Einlesen wurde beendet
        inputFile.close();
    }
    else
    {
        std::cout << argv[1] << "Datei konnte nicht geöffnet werden!\n";
    }

    /* Drei Vektoren zum Speichern von zwei Werten */
    std::vector<struct PAIR> csarRollpair[KEYLENGHT];

    /* Gehe durch alle drei Vektoren durch und ... */
    for (int vectorIndex = 0; vectorIndex < 3 ; vectorIndex++)
    {
        /* finde die Anzahl an elementen in einem Vector */
        for (int i = 'A'; i <= 'Z'; i++)
        {
        	int sizeOfAllElements = csarRoll[vectorIndex].size();

            int count = std::count(csarRoll[vectorIndex].begin(), csarRoll[vectorIndex].end(), i);

            struct PAIR temp;
            temp.charValue = i;
            // BErechung des % Wertes der Häufigkeit
			temp.intValue = round( ( (double)count / (double)sizeOfAllElements) * 100.0 );

            csarRollpair[vectorIndex].push_back(temp);
        }
        /* Sortiere den Vector  absteigend nach der Häufigkeit */
        std::sort(csarRollpair[vectorIndex].rbegin(), csarRollpair[vectorIndex].rend(), [](const PAIR& a, const PAIR& b) { return a.intValue < b.intValue; });
    }

     /* Ausgabe "E: 17% ; F: 17% ; D: 16%" */
	for ( int i = 0; i < (int)csarRollpair[0].size(); i++ )
	{
		std::cout << csarRollpair[0][i].charValue  << ": " << csarRollpair[0][i].intValue << "% ; "
			      << csarRollpair[1][i].charValue  << ": " << csarRollpair[1][i].intValue << "% ; "
		          << csarRollpair[2][i].charValue  << ": " << csarRollpair[2][i].intValue << "%" << std::endl;
	}
    return 0;
}
