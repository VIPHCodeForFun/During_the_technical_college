
//  C:\\Users\\phili\\Desktop\\test.txt

#include <stdio.h>

int main(int argc, char *argv[]) // bzw. void main(...)
{
    printf("%s", argv[0]);

    FILE *fp; // fp ist ein Pointer auf FILE

    //  FILE *fopen(const char *filename, const char *mode)
    /*
"r"	    Textdatei zum lesen und eröffnen
"w"	    Textdatei zum Schreiben erzeugen; gegebenenfalls alten Inhalt wegwerfen
"a"	    anfügen; Textdatei zum Schreiben am Dateiende eröffnen oder erzeugen
"r+"	Textdatei zum Ändern eröffnen (Lesen und Schreiben)
"w+"	Textdatei zum Ändern erzeugen; gegebenenfalls alten Inhalt wegwerfen
"a+"	anfügen; Textdatei zum Ändern eröffnen oder erzeugen, Schreiben am Ende*/

    int d = 100;
    int e = 0;

    //Schreiben in ein .TXT FILE
    fp = fopen("C:\\Users\\phili\\Desktop\\score.txt", "w"); // fp zeigt auf das FILE
    if (fp == NULL)
    {
        printf("Fehler beim Oeffnen der Datei\n");
    }
    else
    {
        printf("Datei wurde geoeffnet!\n");
        //Löscht alles was in der Datei steht und fühgt den String hinzu
        fprintf(fp, "%d \n", d);
        fprintf(fp, "Das ist der String der in die Datei Kommt .\n");
        fclose(fp); // schließst das FILE wieder
    }

    //Lesen aus einem .TXT FILE
    fp = fopen("C:\\Users\\phili\\Desktop\\score.txt", "r");
    if (fp == NULL)
    {
        printf("Fehler beim Oeffnen der Datei");
    }
    else
    {
        printf("Datei wurde geoeffnet :D !\n");
        fscanf(fp, "%d", &e);
        fclose(fp); // schließst das FILE wieder
        printf("%d", e);
    }
    return 0;
}