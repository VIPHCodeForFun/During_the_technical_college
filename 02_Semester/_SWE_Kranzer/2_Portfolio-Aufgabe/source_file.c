/*
FILES als Datenspeicher und Datenquelle
1.
Entweder binären Suchbaum oder doppelt verkettete Liste für Double-Werte implementieren (Header und Sourcefile)
Strukturen definieren, Funktionen festlegen (Header-File)
Einfügen und Suchen und Traversieren/Iterieren implementieren (Source-File)
2.
Werte aus einem Textfile (entweder zeichen oder zeilenweise oder formartiert) einlesen und in die Datenstruktur aus 1 einfügen
File lesen und Werte in 1. einfügen (fgetc, fgets, fscanf, atol)
3.
Speichern aller Werte aus der Datenstruktur in einem Binär-File
Datenstruktur iterieren und binär (fwrite) ins File schreiben
*/

#include <stdio.h>

#include "header_file.h"

int str_to_d(double werte[], char string[]);
void surce_file();

int main()
{
    double buffer[10] = {0};
    int i = 0;
    p_head = create_head();
    surce_file("input.txt"); //WICHTIG LETZTE BUCHSTABE IM FILE MUSS EIN SPACE SEIN
    note_print_all();

    note_print_double(buffer);

    input_bin_file("dest_file.bin", buffer, 10);

    //Testen was im "dest_file.bin" enthalten ist;
    double output[10] = {0};
    output_bin_file("dest_file.bin", output, 10);

    for (i = 0; i < 10; i++)
    {
        printf("output %lf \n", output[i]);
    }

    return 0;
}

//LISTE
struct head *create_head() //Header anlegen
{
    struct head *h_note = malloc(sizeof(struct head)); // Speicher reservieren
    if (h_note == NULL)                                // Fehlerabfrage malloc gibt bei einem Fehler NULL zurück
    {
        printf("Error kein freier Speicher CREATE_HEAD malloc");
        return NULL;
    }
    h_note->count = 0;
    h_note->p_first = NULL;
    h_note->p_last = NULL;
    return h_note;
}

void note_enque_front(double value)
{
    struct note *note = malloc(sizeof(struct note)); // Speicher reservieren
    if (note == NULL)                                // Fehlerabfrage malloc gibt bei einem Fehler NULL zurück
    {
        printf("Error kein freier speicher  ENQUE malloc");
        return;
    }
    //Daten setzen
    note->data = value; // setzt das value in Data
    p_head->count++;    // counter im header um 1 hoch zählen

    //Header Pointer setzen
    if (p_head->p_first == NULL)
    {
        p_head->p_first = note; //Pointer_First im Header auf das File referenzieren
    }
    if (p_head->p_last == NULL)
    {
        p_head->p_last = note; //Pointer_First im Header auf das File referenzieren
    }
    // Pointer prev setzen
    if (p_head->p_first == note)
    {
        note->p_prev = NULL;
    }
    else
    {
        p_head->p_first->p_prev = note;
        note->p_prev = NULL;
    }
    // Pointer Prev setzen
    if (p_head->p_last == note) //zeigt auf NULL
    {
        note->p_next = NULL;
    }
    else // zeigt auf p_last im header
    {
        note->p_next = p_head->p_first;
    }
    //Header Pointer last setzen
    if (p_head->p_first != NULL)
    {
        p_head->p_first = note;
    }
}

void note_deque_front()
{
    printf("#Deque_front\n");
    if (p_head->count != 0)
    {
        p_head->count--; // counter im header um 1 runter zählen
    }
    //Header Pointer last setzen

    if (p_head->p_first == NULL && p_head->p_last == NULL)
    {
        printf("Deque_back [List is EMPTY]\n");
    }
    if (p_head->p_first == p_head->p_last)
    {
        free(p_head->p_last);
        p_head->p_first = NULL;
        p_head->p_last = NULL;
    }
    else
    {
        p_head->p_first = p_head->p_first->p_next;
        free(p_head->p_first->p_prev);
        p_head->p_first->p_prev = NULL;
    }
}

void note_print_all()
{
    printf("#Print_all\n");
    int i = 0;
    struct note *temp = p_head->p_first; // Hilfspointer
    if (temp == NULL)
    {
        printf("Print_all [List is EMPTY]\n");
    }
    else
    {
        for (i = 0; i < p_head->count; i++)
        {
            printf("Note[%d] = %lf\n", i + 1, temp->data);
            temp = temp->p_next;
        }
    }
}

void note_print_double(double wert[])
{
    printf("#Print_to_double\n");
    int i = 0;
    struct note *temp = p_head->p_first; // Hilfspointer
    if (temp == NULL)
    {
        printf("Print_to_double [List is EMPTY]\n");
    }
    else
    {
        for (i = 0; i < p_head->count; i++)
        {
            wert[i] = temp->data;
            temp = temp->p_next;
        }
    }
}

//Source FILE
int str_to_d(double werte[100], char string[100])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;
    char number[100] = {0};

    while (string[i] != '\0')
    {
        number[j] = string[i];
        if (string[i] == ' ')
        {
            werte[k] = atof(number);
            i++;
            k++;
            j = 0;
            count++;
        }
        else
        {
            i++;
            j++;
        }
    }
    return count;
}

void surce_file(char path[])
{
    FILE *p_file;
    char temp[100];
    double wert[100];
    int i = 0;
    int count = 0;

    p_file = fopen(path, "r");
    if (p_file == NULL)
    {
        printf("fehler beim öffnen der Datei");
    }
    else
    {
        while (NULL != (fgets(temp, 100, p_file))) // bis fgets NULL returned erzeugt einen string
        {
        }
    }
    printf("FILE Stram = %s", temp);

    count = str_to_d(wert, temp); //Wandelt den String in einzelne Doubles um

    for (i = 0; i < count; i++)
    {
        note_enque_front(wert[i]);
    }
}

//Dest FILE
void input_bin_file(char path[], double input[], int size_of_input)
{
    FILE *p_file = NULL;

    p_file = fopen(path, "wb");

    fwrite(input, sizeof(double), size_of_input, p_file);

    fclose(p_file);
    p_file = NULL;
    return;
}

void output_bin_file(char path[], double output[], int size_of_output)
{
    FILE *p_file = NULL;

    p_file = fopen(path, "rb");
    if (p_file == NULL)
    {
        printf("File \"%c\" not found ! ", path);
    }
    fread(output, sizeof(double), size_of_output, p_file);
    fclose(p_file);
    p_file = NULL;
    return;
}