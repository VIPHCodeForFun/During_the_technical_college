/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:   
Unser Ziel ist es, Eishockeyspieler der Colorado Avalanche1 mit deren Rückennummern aus
der Textdatei players.txt einzulesen, und diese nach Rückennummer aufsteigend sortiert in
die von uns denierte doppelt verkettete Liste abzuspeichern.
Das Datenformat ist dabei folgendermaßen deniert:
<Name>, <Rückennummer>
<Name>, <Rückennummer>
Beginne mit dem Defnieren der Datenstrukturen für einen Spieler, den Listenkopf und das
Listenelement. Stell sicher, dass das Erstellen einer neuen, leeren Liste und eines neuen
Listenelements mittels zweier dafür vorgesehener Funktionen möglich ist. Realisiere danach
eine Funktion, die das Einlesen der Textdatei übernimmt. Der Dateiname der einzulesenden
Textdatei wird deinem Programm dabei als Kommandozeilenparameter mitgegeben. Das
Hinzufügen der Spieler aus der Datei in die doppelt verkettete Liste sollte ebenso über eine
Funktion realisiert werden.
Stelle bereits beim Einfügen von Elementen in die Liste sicher, dass die Elemente bereits
zum Zeitpunkt des Hinzufügens in die Liste an der richtigen Stelle eingefügt werden. Zum
Abschluss ist zu implementieren, dass die Spieler in der Liste sowohl aufsteigend als                                                                  
///////////////////////////////////////////////////////////////////////////*/
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> //string funk

#include <windows.h>
typedef struct data
{
    char name[100];
    int number;
} DATA;
typedef struct node
{
    struct data player;
    struct node *p_next;
    struct node *p_prev;
} NODE;
typedef struct head
{
    int count;
    struct node *p_first;
    struct node *p_last;
} HEAD;

HEAD *create_head();
NODE *create_node(DATA player);
void read_file(HEAD *p_head, char path[]);
void insert_list(HEAD *p_head, DATA p_player, char sort);
//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#
int main()
{

    return 0;
}
//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#
HEAD *create_head()
{
    HEAD *p_head = malloc(sizeof(HEAD));
    if (p_head == NULL)
    {
        return NULL;
    }
    p_head->count = 0;
    p_head->p_first = NULL;
    p_head->p_last = NULL;
    return p_head;
}
NODE *create_node(DATA player)
{
    NODE *p_temp = malloc(sizeof(NODE));
    if (p_temp == NULL)
    {
        return NULL;
    }
    p_temp->player = player;
    p_temp->p_next = NULL;
    p_temp->p_prev = NULL;
}
void read_file(HEAD *p_head, char path[])
{
    if (p_head == NULL)
    {
        return NULL;
    }
    FILE *p_file = fopen(path, "r");
    char buffer[100];
    DATA temp_player;

    while (fgets(buffer, sizeof(buffer), p_file) != NULL)
    {
        strcpy(temp_player.name, strtok(buffer, ","));
        temp_player.number = atoi(strtok(NULL, "\0"));
        // einfügen temp_player
    }
    fclose(p_file);
    return;
}
void insert_list(HEAD *p_head, DATA p_player, char sort)
{
    if (p_head == NULL)
    {
        return;
    }
    NODE *p_node = create_node(p_player);
    if (p_node == NULL)
    {
        return;
    }
    if (sort == 'n' || sort == 'N') //nach Namen Sortieren
    {
    }
    else if (sort == 'z' || sort == 'Z') //nach Spielernumemr sortieren
    {
        if (p_head->count == 0)
        {
            p_head->count++;
            p_head->p_first = p_node;
            p_head->p_last = p_node;
        }
        else if (p_node->player.number < p_head->p_first->player.number)
        {
            p_node->p_next = p_head->p_first;
            p_head->p_first->p_prev = p_node;
            p_head->p_first = p_node;
            p_head->count++;
        }
        else if (p_node->player.number > p_head->p_first->player.number)
        {
            p_node->p_prev = p_head->p_last;
            p_head->p_last->p_next = p_node;
            p_head->p_last = p_node;
            p_head->count++;
        }
        else
        {
            NODE *p_temp_run = p_head->p_first;
            while (p_temp_run->player.number < p_node->player.number)
            {
                p_temp_run = p_temp_run->p_next;
            }
            p_node->p_next = p_temp_run;
            p_node->p_prev = p_temp_run->p_prev;
            p_node->p_next->p_prev = p_node;
            p_node->p_prev->p_next = p_node;
            p_head->count++;
        }
    }
    else
    {
        free(p_node);
        return;
    }
    return;
}
/*
while (fscanf(playerFile, "%[^,], %d\n", name, &number) > 0)
    {
        PLAYER *player = createPlayer(name, number);
        insertNode(list, player);
    }
*/