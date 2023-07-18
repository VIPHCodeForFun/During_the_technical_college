/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:                                                                     
SWE2 Labor
Lauflängenkodierung (Run Length Encoding)
Aufgabe 1 (Run Length En-/Decoder) Ein Grossteil der Daten mit denen wir taeglich arbeiten, enthalten viel
redundante Information. Ein Beispiel sind Bilder mit grossen einfarbigen Flaechen (z.B. Logos) oder Tabellen und Log-Dateien mit immer
wiederkehrenden Eintraegen. Diese Daten sind bereits mit verlustfreien Methoden relativ gut
komprimierbar. Die erreichbare Kompressionsrate fuer einen bestimmten Algorithmus haengt dabei stark von den Daten ab.
Ein simples Schema zur Kompression ist die Lauflaengenkodierung. Hierbe werden haeufig hintereinander auftretende Zeichen durch einen Zaehler und
das Zeichen selbst repraesentiert. Die Zeichenfolge AAAAAABBBBBBCDEFGG wird dann zu A6B6C1D1E1F1G2.

Schreiben Sie ein Kommandozeilen-Programm, welchem als Parameter der gewuenschte Modus (De-/Kodierung), die Eingabe-Datei und die Ausgabe-Datei
uebergeben werden. Der Aufruf erfolgt also so: ./rle (encode|decode) eingabe_datei ausgabe_datei
Anbei finden Sie zwei Test-Dateien:

1) aabbcc.txt Eine einfache Textdatei, welche das Alphabet enhaelt, bei dem einige Buchstaben dupliziert wurden.
2) fhs_logo_bw.png Unkomprimierte Schwarz-Weiss Version des FH-Salzburg Logos. Enthaelt viele weisse Bereiche, getrennt von kleinen schwarzen Bereichen.

Tipp: 
verwenden Sie einen Hex-Editor um den Inhalt der Datei darzustellen (z.B. dhex, ghex oder direkt als VSCode Plugin) Schreiben Sie intern dazu zwei 
Funktionen: 
void encode(FILE* fin, FILE* fout);  
void decode(FILE* fin, FILE* fout);

Das Programm soll die Dateien Byte-weise verarbeiten. Achten Sie ebenfalls darauf, dass Ihr Programm auch Zeichenfolgen laenger als 255 Bytes 
verarbeiten kann.
///////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <string.h>

void encode(FILE *fin, FILE *fout);
/*Diese Funktion nimmt den input stream fin entgegen, und wandelt eine Folge von 1..255 Byte in eine Folge aus Wertepaaren
(value, count) und schreibt diese in den stream fout.*/
void decode(FILE *fin, FILE *fout);
/*Diese Funktion erwartet die mit der Funktion encode() erzeugten Wertepaare im stream fin und dekodiert diese Wertepaare (value, count)
in eine Folge von gleichen Zeichen ‚value‘ mit der Laenge ‚count‘. Das ergebnis wird in den stream fout geschrieben. Und fangen Sie fehlerhafte 
Argumente und deren Kombinationen ab.*/

int main(int argc, char *argv[])
{
    /*./rle (encode|decode) eingabe_datei ausgabe_datei
    [0] C:\Users\phili\Desktop\FH_Salzburg\c_Programms\rle 
    [1] encode | decode
    [2] eingabe_datei
    [3] ausgabe_datei
    */
    FILE *p_src_file = NULL;
    FILE *p_des_file = NULL;

    if (strcmp(argv[1], "encode") == 0 && argc == 4)
    {
        p_src_file = fopen(argv[2], "rb"); //r = read b = binär
        p_des_file = fopen(argv[3], "wb"); //w = write b = binär
        //FUNKTION
        encode(p_src_file, p_des_file);
        fclose(p_src_file);
        fclose(p_des_file);
    }
    else if (strcmp(argv[1], "decode") == 0 && argc == 4)
    {
        p_src_file = fopen(argv[2], "rb"); //r = read b = binär
        p_des_file = fopen(argv[3], "wb"); //w = write b = binär
        //FUNKTION
        decode(p_src_file, p_des_file);
        fclose(p_src_file);
        fclose(p_des_file);
    }
    else
    {
        printf("Falsche eingabe\n");
    }

    return 0;
}
void encode(FILE *fin, FILE *fout)
{

    int N = 1;   // Anzahl an gleichen werten
    char buffer; //Zwischenspeicher
    char temp;   //Zum vergleichen
    fpos_t pos;  //Merken der Position im File

    while (fread(&buffer, sizeof(buffer), 1, fin) == 1) // Returnwert = immer 1 till EOF
    {
        fgetpos(fin, &pos); //Speichert die aktuelle Position im FILE
        temp = getc(fin);   //Nächsten parameter in Temp --> position++
        fsetpos(fin, &pos); //Setzt die Position im FILE wieder um eins zurück

        if (buffer == temp)
        {
            N++;
        }
        else
        {
            fwrite(&N, sizeof(int), 1, fout);
            fwrite(&buffer, sizeof(char), 1, fout);
            N = 1;
        }
    }
    return;
}

void decode(FILE *fin, FILE *fout)
{
    int N = 0;       // Anzahl an gleichen werten
    int i = 0;       // for loop
    char buffer = 0; // der zu schreibende Charakter

    while (fread(&N, sizeof(int), 1, fin) == 1) // Lesen der Zahl
    {
        fread(&buffer, sizeof(char), 1, fin); // Lesen des Buchstabens
        for (i = 0; i < N; i++)
        {
            fwrite(&buffer, sizeof(char), 1, fout); //in Binärfiles nur mit fwrite arbeiten
        }
    }
    return;
}