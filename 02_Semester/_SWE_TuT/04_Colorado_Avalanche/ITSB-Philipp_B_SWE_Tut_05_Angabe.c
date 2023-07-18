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
Beginne mit dem Denieren der Datenstrukturen für einen Spieler, den Listenkopf und das
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

#include <stdio.h>  //standart IO
#include <stdlib.h> // malloc
#include <string.h> //strtock

struct player
{
    char name[100];
    int player_nr;
};
struct node
{
    struct player player;
    struct node *p_next;
    struct node *p_prev;
};
struct list_head
{
    int count; //zähler
    struct node *p_first;
    struct node *p_last;
};

struct list_head *create_head();
struct node *create_node(struct player player);
void read_file(char path[], struct list_head *p_head);
void insert_list(struct list_head *p_head, struct player x_player);
void print_lsit(struct list_head *p_head);

//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//
int main()
{
    struct list_head *p_list = create_head();

    struct player p1 = {"V. Nichushkin", 13};
    //V. Nichushkin, 13
    struct node *p_test = create_node(p1);

    //test printf("%s %d\n", p_test->player.name, p_test->player.player_nr);
    //test printf("%s %d\n", p1.name, p1.player_nr);
    printf("Print Playerslist\n");
    read_file("players.txt", p_list);

    print_lsit(p_list);
    return 0;
}
//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//#//
struct list_head *create_head()
{
    struct list_head *p_temp = malloc(sizeof(struct list_head));
    if (p_temp == NULL)
    {
        return NULL;
    }
    p_temp->count = 0;
    p_temp->p_first = NULL;
    p_temp->p_last = NULL;
    return p_temp;
}
struct node *create_node(struct player player)
{
    struct node *p_temp = malloc(sizeof(struct node));
    if (p_temp == NULL)
    {
        return NULL;
    }
    p_temp->player = player;
    p_temp->p_next = NULL;
    p_temp->p_prev = NULL;

    return p_temp;
}
void read_file(char path[], struct list_head *p_head)
{
    if (p_head == NULL)
    {
        printf("List ERROR");
        return;
    }
    FILE *p_file = NULL;
    p_file = fopen(path, "r");
    if (p_file == NULL)
    {
        printf("File ERROR");
        return;
    }
    char buffer[100] = {" "};
    char *token;
    struct player temp_player;
    while (fgets(buffer, 100, p_file) != NULL)
    {
        token = strtok(buffer, ",");
        strcpy(temp_player.name, token);
        temp_player.player_nr = atoi(strtok(NULL, "\n"));
        //printf("%s %d\n", temp_player.name, temp_player.player_nr);
        insert_list(p_head, temp_player);
    }
    fclose(p_file);
}
//insert in list ()
void insert_list(struct list_head *p_head, struct player x_player)
{
    if (p_head == NULL)
    {
        printf("p_ehad-->NULL\n");
        return;
    }
    struct node *p_node = create_node(x_player);
    /*
    player = player;
    p_next = NULL;
    p_prev = NULL;
    */
    //liste ist leer
    if (p_head->count == 0)
    {
        p_head->p_first = p_node;
        p_head->p_last = p_node;
        p_head->count++;
    }
    //front einfügen
    else if (p_node->player.player_nr < p_head->p_first->player.player_nr)
    {
        p_node->p_next = p_head->p_first;
        p_head->p_first->p_prev = p_node;
        p_head->p_first = p_node;
        p_head->count++;
    }
    //last einfügen
    else if (p_node->player.player_nr > p_head->p_last->player.player_nr)
    {
        p_node->p_prev = p_head->p_last;
        p_head->p_last->p_next = p_node;
        p_head->p_last = p_node;
        p_head->count++;
    }
    //mitte einfügen
    else
    {
        struct node *p_runNode = p_head->p_first;
        while (p_node->player.player_nr > p_runNode->player.player_nr)
        {
            p_runNode = p_runNode->p_next;
        }
        p_node->p_prev = p_runNode->p_prev;
        p_node->p_next = p_runNode;
        p_runNode->p_prev->p_next = p_node;
        p_runNode->p_prev = p_node;
        p_head->count++;
    }
    return;
}
void print_lsit(struct list_head *p_head)
{
    struct node *p_temp = p_head->p_first;
    int i = 0;
    int j = 0;
    for (i = 0; i < p_head->count; i++)
    {
        printf("%d %s %d\n", i + 1, p_temp->player.name, p_temp->player.player_nr);
        p_temp = p_temp->p_next;
    }
}