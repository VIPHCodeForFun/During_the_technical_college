#include <iostream>
#include <vector>
#include <fstream>
/*
Buchstabenhäufigkeit in deutschsprachigen Texten
1. 	E	17,40 %
2.	N	9,78 %
3.	I	7,55 %
4.	S	7,27

kann mit der Funktion show(); ausgegeben werden
Zuweisung: A=0, B=1, C=2, D=3, E=4 ... 0=14 ... V=21 ... Z=25

für B-HA.txt gilt
schlüssel[0] = 0 mit 21% -> O = E -> schlüssel= 14 - 4 = 10 = char K
schlüssel[1] = V mit 21% -> V = E -> schlüssel= 21 - 4 = 17 = char R
schlüssel[2] = C mit 18% -> C = E -> schlüssel= 2  - 4 = -2 = char Y
*/

/* c = (m + k) mod 26 */
char encrypt(const char m,const char k,const int mod)
{
    char asciiOffset = 'A';
    int calculate = (m - asciiOffset) + (k - asciiOffset);
    int modulo = (calculate + mod) %mod; 		// see decrypt(const char c,const char k,const int mod)
    int returnValue = modulo + asciiOffset;
    return returnValue;
}

/* m = (c - k) mod 26 */
char decrypt(const char c,const char k,const int mod)
{
    int asciiOffset = 'A';
    int calculate = (c - asciiOffset) - (k - asciiOffset);
    int modulo = (calculate + mod) %mod; 		// lol... -3 mod 26 = -3 -> calculate + mod
    int returnValue = modulo + asciiOffset;
    return returnValue;
}

void show()
{
    char charValue = 'A';
    for  (int i = 0; i < 26 ; i++)
    {
        std::cout << charValue << " " << (int)charValue - 'A' << std::endl;
        charValue++;
    }
}

int main(const int argc, const char * const argv[])
{
    /* Eingabegehlerabfrage */
    if (argc < 3)
    {
        std::cerr << "Description: Encrypts the contents of a file" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <in> <out>" << std::endl;
        std::cerr << "  in: Input file to encrypt" << std::endl;
        std::cerr << "  out: Encrypted output file" << std::endl;
        return 1;
    }

    /* Verarbeitung Key */
    std::string keyString(argv[3]);
    int keylength = keyString.length();

    /* Einlesen des zu entschlüsselnden Files */
    std::vector<char> imputVector;

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {

        char bytebuffer; // Buffer zum Auslesen und Verarbeiten

        while (inputFile.get(bytebuffer)) // lese bis EOF ein
        {
            imputVector.push_back(bytebuffer);
        }
        inputFile.close(); // Datei schließen
    }
    else
    {
        std::cout << argv[1] << "Datei konnte nicht geöffnet werden!\n";
        return 10;
    }

    /* Entschlüsseln vom imputVector */
    std::vector<char> outputVector;
    int keyPos = keylength; // 3 % 3 = 0, 4 % 3 = 1 usw....

    for ( int vecPos = 0; vecPos < (int)imputVector.size(); vecPos++)
    {
        // Abfrage ob der Wert zwischen A und Z liegt
        if(imputVector[vecPos] >= 'A' && imputVector[vecPos] <= 'Z')
        {
            int keyIndex = keyPos % keylength;
            char temp = decrypt(imputVector[vecPos], keyString[keyIndex], 26); // 26 = Anzahl vo A-Z
            outputVector.push_back(temp);
            keyPos++;
        }
        else
        {
            outputVector.push_back(imputVector[vecPos]);
        }
    }


    /* Entschlüsselung in Outputfile speichern */
    std::ofstream outputFile;
    outputFile.open(argv[2]);

    if (outputFile.is_open())   // Überprüfen, ob die Datei erfolgreich geöffnet wurde
    {
        for ( int vecPos = 0; vecPos < (int)outputVector.size(); vecPos++)
        {
            outputFile << outputVector[vecPos];
        }
        outputFile.close(); // Datei schließen
    }
    else
    {
        std::cout << "Fehler beim Öffnen der Datei.\n";
        return 11;
    }





    return 0;
}
