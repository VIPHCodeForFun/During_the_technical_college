################################    FILE.txt   ################################ 
Öffnen 
FILE *fp = NULL;
    
FILE *fopen(const char *filename, const char *mode)
    

fp = fopen("C:\\Users\\phili\\Desktop\\score.txt", "w"); 

"r"	    Textdatei zum lesen und eröffnen
"w"	    Textdatei zum Schreiben erzeugen; gegebenenfalls alten Inhalt wegwerfen
"a"	    anfügen; Textdatei zum Schreiben am Dateiende eröffnen oder erzeugen
"r+"	Textdatei zum Ändern eröffnen (Lesen und Schreiben)
"w+"	Textdatei zum Ändern erzeugen; gegebenenfalls alten Inhalt wegwerfen
"a+"	anfügen; Textdatei zum Ändern eröffnen oder erzeugen, Schreiben am Ende
Schließen
    fclose(fp); // schließt das FILE wieder
Schreiben
    fprintf(fp, "Das ist der String der in die Datei Kommt .\n");
Lesen
    fscanf(fp, "%d", &e);

################################    FILE.bin   ################################ 

Öffnen 
    FILE *fp = NULL;
    FILE *fopen(const char *filename, const char *mode)
    Beispiel:
        Erstellt das neue File und im Schreibmodus = p_file = fopen("test.bin", "wb");
Schließen
    fclose(fp); // schließt das FILE wieder
Schreiben
    fwrite(wert, sizeof(double), sizeof(wert) / sizeof(double), p_file);
    (Pointer auf das zu lesende Array, Größe eines Elements in Bytes, Anzahl der Elemente, File Pointer)
Lesen
    read(file_data, sizeof(double), sizeof(wert) / sizeof(double), p_file);
    (Pointer auf das zu schreibende Array, Größe eines Elements in Bytes, Anzahl der Elemente, File Pointer)