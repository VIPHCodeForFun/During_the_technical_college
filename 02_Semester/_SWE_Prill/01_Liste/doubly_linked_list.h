#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h> //malloc
//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//

//BLUEPRINT_STRUCTS
struct head
{
    int count;
    struct note *p_first; //zeigt auf das erste note in der Liste
    struct note *p_last;  //zeigt auf das letzte note in der Liste
};

struct note
{
    int data;
    struct note *p_next; //zeigt auf das nächste note
    struct note *p_prev; //zeigt auf das vorherige note
};

//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//

// CREATE_HEAD_FUNKTION
struct head *create_head();

// ENQUE_AND DEQUE_FUNKTIONS
void note_enque_back();
void note_deque_back();
void note_enque_front();
void note_deque_front();
void note_enque_after();
void note_enque_before();
struct note *delete_note(); //Löscht ein einzelnes Note anhand der Addresse

// SERARCH_FUNKTION
struct note *note_search(); //Gibt die Addresse des ersten Notes zurück

// SORT_FUNKTION
void note_minsort();

// OUTPUT_FUNKTIONS_console
void note_print_first();
void note_print_last();
void note_print_count();
void note_print_all(); //Gibt die Ganze Liste aus

// OUTPUT_FUNKTIONS_FILE
void print_note_to_bin(); //Speichert die ganze Liste in einem File

//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//

struct head *p_head; // Globale variable, Pointer auf den Struktur Head Eingang

//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//

// ENQUE_AND DEQUE_FUNKTIONS //##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//
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

void note_enque_back(int value)
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
    // Pointer Next setzen
    if (p_head->p_last == note)
    {
        note->p_next = NULL;
    }
    else
    {
        p_head->p_last->p_next = note;
        note->p_next = NULL;
    }
    // Pointer Prev setzen
    if (p_head->p_first == note) //zeigt auf NULL
    {
        note->p_prev = NULL;
    }
    else // zeigt auf p_last im header
    {
        note->p_prev = p_head->p_last;
    }
    //Header Pointer last setzen
    if (p_head->p_last != NULL)
    {
        p_head->p_last = note;
    }
}

void note_deque_back()
{
    printf("#Deque_back\n");
    if (p_head->count != 0)
    {
        p_head->count--; // counter im header um 1 runter zählen
    }
    //Header Pointer last setzen

    if (p_head->p_first == NULL && p_head->p_last == NULL)
    {
        printf("Deque_back [List is EMPTY]\n");
        return;
    }
    if (p_head->p_first == p_head->p_last)
    {
        free(p_head->p_last);
        p_head->p_first = NULL;
        p_head->p_last = NULL;
    }
    else
    {
        p_head->p_last = p_head->p_last->p_prev;
        free(p_head->p_last->p_next);
        p_head->p_last->p_next = NULL;
    }
}

void note_enque_front(int value)
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

void note_enque_after(int element, int value)
{
    int i = 0;
    struct note *temp = p_head->p_first; // Hilfspointer
    if (temp == NULL)
    {
        printf("Enque_after [List is EMPTY]\n");
        return;
    }
    else
    {
        for (i = 1; i < element; i++) //Setze den Pointer temp auf das gewünschte Note
        {
            temp = temp->p_next;
        }
        if (temp == p_head->p_last) // Wenn wir am ende sind nur enque_back ausführen
        {
            note_enque_back(value);
            return;
        }
        struct note *note = malloc(sizeof(struct note)); // Speicher reservieren
        if (note == NULL)                                // Fehlerabfrage malloc gibt bei einem Fehler NULL zurück
        {
            printf("Error kein freier speicher ENQUE_AFTER malloc");
            return;
        }
        //Daten setzen
        note->data = value; // setzt das value in Data
        p_head->count++;    // counter im header um 1 hoch zählen

        // Pointer next setzen
        note->p_next = temp->p_next;
        note->p_prev = temp->p_next->p_prev;
        temp->p_next->p_prev = note;
        temp->p_next = note;
    }
}

void note_enque_before(int element, int value)
{
    int i = 0;
    struct note *temp = p_head->p_first; // Hilfspointer
    if (temp == NULL)
    {
        printf("Enque_after [List is EMPTY]\n");
        return;
    }
    else
    {
        for (i = 1; i < element; i++) //Setze den Pointer temp auf das gewünschte Note
        {
            temp = temp->p_next;
        }
        if (temp == p_head->p_first) // Wenn wir am ende sind nur enque_back ausführen
        {
            note_enque_front(value);
            return;
        }
        struct note *note = malloc(sizeof(struct note)); // Speicher reservieren
        if (note == NULL)                                // Fehlerabfrage malloc gibt bei einem Fehler NULL zurück
        {
            printf("Error kein freier speicher ENQUE_BEFORE malloc");
            return;
        }
        //Daten setzen
        note->data = value; // setzt das value in Data
        p_head->count++;    // counter im header um 1 hoch zählen

        // Pointer next setzen
        note->p_prev = temp->p_prev;
        note->p_next = temp->p_prev->p_next;
        temp->p_prev->p_next = note;
        temp->p_prev = note;
    }
}

struct note *delete_note(struct note *delete)
{
    struct note *temp = delete;
    if (p_head->p_first == NULL || delete == NULL)
    {
        printf("No Element found\n");
        return NULL;
    }
    if (temp == p_head->p_last)
    {
        note_deque_back();
        return p_head->p_first;
    }
    if (temp == p_head->p_first)
    {
        note_deque_front();
        return p_head->p_first;
    }
    p_head->count--;
    temp->p_prev->p_next = temp->p_next;
    temp->p_next->p_prev = temp->p_prev;
    free(temp);

    return p_head->p_first;
}

// SERARCH_FUNKTION //##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//
struct note *note_search(int value)
{
    struct note *temp = p_head->p_first; // Hilfspointer
    if (temp == NULL)
    {
        printf("Search [List is EMPTY]\n");
    }
    while (temp != p_head->p_last)
    {
        if (value == temp->data)
        {
            return temp;
        }
        temp = temp->p_next;
    }
    if (temp == p_head->p_last)
    {
        if (value == temp->data)
        {
            return temp;
        }
    }
    return NULL;
}

// OUTPUT_FUNKTIONS //##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//
void note_print_first()
{
    printf("Position[First] = %d\n", p_head->p_first->data);
}

void note_print_last()
{
    printf("Position[Last]  = %d\n", p_head->p_last->data);
}

void note_print_count()
{
    printf("Count in the Head = %d\n", p_head->count);
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
        for (i = 0; i < p_head->count; i++) //while (note->p_next != NULL)
        {
            printf("Note[%d] = %d\n", i + 1, temp->data);
            temp = temp->p_next;
        }
    }
}

void print_note_to_bin(char path[])
{
    int i = 0;
    struct note *temp = p_head->p_first; //Pointer auf note
    double temp_note = 0;
    FILE *p_file = NULL;        // Pointer auf das file
    p_file = fopen(path, "wb"); // öffnen des files

    //Schreibt die Liste "note" in das FILE.bin
    for (i = 0; i < p_head->count; i++)
    {
        temp_note = temp->data;
        fwrite(&temp_note, sizeof(double), 1, p_file);
        temp = temp->p_next; // Setzt den Pointer auf das nächste Note
    }
    fclose(p_file);
    p_file = NULL;
    return;
}

#endif /* DOUBLY_LINKED_LIST_H_ */