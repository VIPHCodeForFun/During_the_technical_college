/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:                                                                     
Verkettete Listen sind eine dynamische Datenstruktur. Sie ermöglichen es, neue Elemente an
beliebiger Stelle einzufügen oder zu entfernen, ohne dass vorhandene Elemente verschobenwerden
müssen. Darin liegt ihr Vorteil gegenüber dynamischen Arrays. Andere Datenstrukturen
können z.B. wiederum auf Listen basieren, so etwa Stacks, Queues oder ganze Dateisysteme.

Schreibe eine eigene Implementierung einer doppelt verketteten Liste, welche aus zwei Datenstrukturen
besteht: einer Struktur für die einzelnen Elemente in der Liste und die Struktur als
sogenannten Listenkopf (Header), welcher sich die Referenzen auf das jeweils erste und letzte
Element und die aktuelle Länge der Liste merkt. Die einzelnen Listenelemente sollen dabei
jeweils über einen Double-Wert verfügen.

Realisiere Methoden um die folgenden Funktionalitäten zu unterstützen:
Das Erstellen einer neuen, leeren Liste.
Das Erstellen eines neuen Elements.
Das Hinzufügen eines neuen Elements an die Liste, sowohl an die erste, die letzte als auch eine bestimmte Position.
Das Löschen eines bestimmten Elements.
Das Löschen eines Elements an einer bestimmten Position.
Das Löschen der gesamten Liste.
Das Darstellen der Liste auf der Konsole.
///////////////////////////////////////////////////////////////////////////*/

#include "double_list.h"

int main()
{
    struct head *p_list = create_list();
    enque_last(p_list, 1);
    enque_last(p_list, 2);
    enque_last(p_list, 3);
    enque_first(p_list, 4);
    del_last(p_list);
    enque_last(p_list, 5);
    del_first(p_list);
    enque_first(p_list, 6);
    enque_last(p_list, 7);
    enque_last(p_list, 1);
    enque_last(p_list, 2);
    enque_last(p_list, 1);
    enque_last(p_list, 2);
    printf("%d count\n", p_list->count);
    print_list(p_list);

    del_element(p_list, 2);
    printf("%d count\n", p_list->count);
    print_list(p_list);

    p_list = del_list(p_list);
    print_list(p_list);

    return 0;
}
struct head *create_list()
{
    struct head *p_temp = malloc(sizeof(struct head));
    if (p_temp == NULL)
    {
        return NULL; //ERROR
    }
    p_temp->count = 0;
    p_temp->p_first = NULL;
    p_temp->p_last = NULL;
    return p_temp;
}
struct node *create_node()
{
    struct node *p_temp = malloc(sizeof(struct node));
    if (p_temp == NULL)
    {
        return NULL; //ERROR
    }
    p_temp->element = 0;
    p_temp->p_next = NULL;
    p_temp->p_prev = NULL;
    return p_temp;
}
void enque_last(struct head *p_head, double value)
{
    struct node *p_node = create_node();
    if (p_node == NULL)
    {
        printf("ERROR");
        return;
    }

    p_node->element = value; //Value to note

    if (p_head->count == 0) //List is empty
    {
        p_head->p_first = p_node;
        p_head->p_last = p_node;
        p_head->count++; //element counter ++;
    }
    else //List have at least one element
    {
        p_head->p_last->p_next = p_node; //Last node Ptr next to new node
        p_node->p_prev = p_head->p_last; //node Prev to Last node
        p_head->p_last = p_node;         //set header Ptr to new node
        p_head->count++;                 //element counter ++;
    }
    return;
}
void enque_first(struct head *p_head, double value)
{
    struct node *p_node = create_node();
    if (p_node == NULL)
    {
        printf("ERROR");
        return;
    }

    p_node->element = value; //Value to note

    if (p_head->count == 0) //List is empty
    {
        p_head->p_first = p_node;
        p_head->p_last = p_node;
        p_head->count++; //element counter ++;
    }
    else //List have at least one element
    {
        p_head->p_first->p_prev = p_node; //Last node Ptr next to new node
        p_node->p_next = p_head->p_first; //node Prev to Last node
        p_head->p_first = p_node;         //set header Ptr to new node
        p_head->count++;                  //element counter ++;
    }
    return;
}
void del_element(struct head *p_head, double value)
{
    int i = 0;
    struct node *p_temp = p_head->p_first;
    struct node *p_delete = NULL;
    int temp = p_head->count;

    for (i = 0; i < temp; i++)
    {
        if (p_temp->element == value)
        {
            if (p_temp->p_prev == NULL)
            {
                del_first(p_head);
                p_temp = p_temp->p_next;
            }
            else if (p_temp->p_next == NULL)
            {
                del_last(p_head);
                p_temp = p_temp->p_next;
            }
            else
            {
                p_delete = p_temp;
                p_temp = p_temp->p_next;

                p_delete->p_next->p_prev = p_delete->p_prev;
                p_delete->p_prev->p_next = p_delete->p_next;
                p_head->count--;
                free(p_delete);
            }
        }
        else
        {
            p_temp = p_temp->p_next;
        }
    }
    return;
}

void del_last(struct head *p_head)
{
    struct node *p_temp = p_head->p_last;

    if (p_head->count == 1)
    {
        p_head->p_first = NULL;
        p_head->p_last = NULL;
        p_head->count = 0;
        free(p_temp);
    }
    else
    {
        p_head->p_last->p_prev->p_next = NULL;
        p_head->p_last = p_head->p_last->p_prev;
        free(p_temp);
        p_head->count--;
    }
}
void del_first(struct head *p_head)
{
    struct node *p_temp = p_head->p_first;

    if (p_head->count == 1)
    {
        p_head->p_first = NULL;
        p_head->p_last = NULL;
        p_head->count = 0;
        free(p_temp);
    }
    else
    {
        p_head->p_first->p_next->p_prev = NULL;
        p_head->p_first = p_head->p_first->p_next;
        free(p_temp);
        p_head->count--;
    }
}
struct head *del_list(struct head *p_head)
{
    while (p_head->count != 0)
    {
        del_first(p_head);
    }
    free(p_head);
    return NULL;
}
void print_list(struct head *p_head)
{
    if (p_head == NULL)
    {
        return;
    }
    int i = 0;
    struct node *p_temp = p_head->p_first;

    printf("-");
    for (i = 0; i < p_head->count; i++)
    {
        printf("[%.2lf]-", p_temp->element);

        p_temp = p_temp->p_next;
    }
    printf("\n");

    return;
}