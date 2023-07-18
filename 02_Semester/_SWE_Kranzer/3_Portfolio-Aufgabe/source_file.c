/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:                                                                     
LISTE als Stack und Queue

Entweder einfach oder doppelt verkettete Liste (mit der Möglichkeit die Größe zu limitieren) für Integer-Werte implementieren 
(Header und Sourcefile)

Einfügen (vorne, hinten) und Herausnehmen (vorne, hinten) implementieren (Source-File)

Queue unter Verwendung der in 1 implentierten Liste (Header und Sourcefile)
FIFO (first in First out)
enque()
deque()
peak()
size()
Stack unter Verwendung der in 1 implemnetierten Liste (Header und Sourcefile)
push()
pop ()
size()
peak()
///////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h> // malloc
#include "header_file.h"

int main(int argc, char *argv[])
{
    printf("\n");
    //QUEUE
    printf("//##//##// QUEUE //##//##//\n");
    struct head *p_queue = NULL;

    p_queue = create_list(5);
    enque_front(p_queue, 1);              // enque
    enque_front(p_queue, 2);              // enque
    enque_front(p_queue, 3);              // enque
    printf("PEAK = %d\n", peak(p_queue)); // show peak
    enque_front(p_queue, 4);              // enque
    enque_front(p_queue, 5);              // enque
    enque_front(p_queue, 6);              // enque passt nicht mehr in die Liste und wird ignoriert
    printf("PEAK = %d\n", peak(p_queue)); // show peak
    printf("SIZE = %d\n", size(p_queue)); // show size
    deque_back(p_queue);                  // deque
    deque_back(p_queue);                  // deque
    printf("PEAK = %d\n", peak(p_queue)); // show peak
    print_queue(p_queue);                 // print queue

    delete_list(p_queue); // delete queue

    printf("\n");
    //STACK
    printf("//##//##// STACK //##//##//\n");
    struct head *p_stack = NULL;

    p_stack = create_list(5);             // Stack mit 5 Tiefe
    enque_back(p_stack, 2);               // push
    printf("PEAK = %d\n", peak(p_stack)); // show peak
    enque_back(p_stack, 3);               // push
    printf("PEAK = %d\n", peak(p_stack)); // show peak
    enque_back(p_stack, 4);               // push
    printf("PEAK = %d\n", peak(p_stack)); // show peak
    printf("SIZE = %d\n", size(p_stack)); // show size
    enque_back(p_stack, 11);              // push
    enque_back(p_stack, 12);              // push
    enque_back(p_stack, 13);              // push passt nicht mehr in die Liste und wird ignoriert
    deque_back(p_stack);                  // pull
    print_stack(p_stack);                 // print Stack

    delete_list(p_stack); // delete Stack

    return 0;
}
struct head *create_list(int len)
{
    struct head *p_head = NULL;
    p_head = malloc(sizeof(struct head));
    if (p_head == NULL)
    {
        printf("FEHLER MALLOC\n");
        return NULL;
    }
    p_head->count = 0;
    p_head->max_len = len;
    p_head->p_first = NULL;
    p_head->p_last = NULL;
    return p_head;
}
struct note *enque_back(struct head *p_head, int value)
{
    struct note *note = malloc(sizeof(struct note));
    if (note == NULL)
    {
        printf("FEHLER MALLOC\n");
        return NULL;
    }
    if (p_head->count == p_head->max_len)
    {
        printf("LIST IS FULL WITH %d ELEMENTS\n", p_head->max_len);
        return NULL;
    }

    note->data = value;
    note->p_next = NULL;
    note->p_prev = NULL;
    //Liste ist leer
    if (p_head->p_last == NULL && p_head->p_first == NULL)
    {
        p_head->count++;
        p_head->p_last = note;
        p_head->p_first = note;
        return note;
    }
    //Liste ist mit midestens einem Element befüllt
    else
    {
        p_head->count++;
        p_head->p_last->p_next = note;
        note->p_prev = p_head->p_last;
        p_head->p_last = note;
        return note;
    }
    return NULL;
}
struct note *deque_back(struct head *p_head)
{
    struct note *temp = p_head->p_last;
    //Liste ist Leer
    if (p_head->p_last == NULL || p_head->p_first == NULL || p_head->count == 0)
    {
        printf("LIST IS EMPTY\n");
        return NULL;
    }
    //Liste hat nur ein Element
    if (p_head->p_last == p_head->p_first)
    {
        p_head->count--;
        p_head->p_first = NULL;
        p_head->p_last = NULL;
        return NULL;
    }
    //Liste hat noch mehrere Elemente
    else
    {
        p_head->count--;
        p_head->p_last = p_head->p_last->p_prev;
        p_head->p_last->p_next = NULL;

        free(temp);
        return p_head->p_last;
    }
}

struct note *enque_front(struct head *p_head, int value)
{
    struct note *note = malloc(sizeof(struct note));
    if (note == NULL)
    {
        printf("FEHLER MALLOC\n");
        return NULL;
    }
    if (p_head->count == p_head->max_len)
    {
        printf("LIST IS FULL WITH %d ELEMENTS\n", p_head->max_len);
        return NULL;
    }
    note->data = value;
    note->p_next = NULL;
    note->p_prev = NULL;
    //Liste ist leer
    if (p_head->p_last == NULL && p_head->p_first == NULL)
    {
        p_head->count++;
        p_head->p_last = note;
        p_head->p_first = note;
        return note;
    }
    //Liste ist mit midestens einem Element befüllt
    else
    {
        p_head->count++;
        p_head->p_first->p_prev = note;
        note->p_next = p_head->p_first;
        p_head->p_first = note;
        return note;
    }
    return NULL;
}
struct note *deque_front(struct head *p_head)
{
    struct note *temp = p_head->p_first;
    //Liste ist Leer
    if (p_head->p_last == NULL || p_head->p_first == NULL || p_head->count == 0)
    {
        printf("LIST IS EMPTY\n");
        return NULL;
    }
    //Liste hat nur ein Element
    if (p_head->p_last == p_head->p_first)
    {
        p_head->count--;
        p_head->p_first = NULL;
        p_head->p_last = NULL;
        return NULL;
    }
    //Liste hat noch mehrere Elemente
    else
    {
        p_head->count--;
        p_head->p_first = p_head->p_first->p_next;
        p_head->p_first->p_prev = NULL;

        free(temp);
        return p_head->p_first;
    }
}
struct head *delete_list(struct head *p_head)
{
    int i = 0;
    for (i = 0; i < p_head->count; i++)
    {
        //Löscht alle Notes
        deque_back(p_head);
    }
    //Löscht den Header
    free(p_head);
    printf("LIST IS DELETED\n");
    return NULL;
}

int print_list(struct head *p_head)
{
    int i = 0;
    struct note *temp = p_head->p_first;
    for (i = 0; i < p_head->count; i++)
    {
        printf("Element[%d] value= %d \n", i + 1, temp->data);
        temp = temp->p_next;
    }
    return p_head->count;
}
//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//
//QUEUE AND STACK
int peak(struct head *p_head)
{
    return p_head->p_last->data;
}
int size(struct head *p_head)
{
    return p_head->count;
}
int print_queue(struct head *p_head)
{
    int i = 0;
    struct note *temp = p_head->p_first;
    printf("-");
    for (i = 0; i < p_head->count; i++)
    {
        printf("[%d]-", temp->data);
        temp = temp->p_next;
    }
    printf("\n");
    return p_head->count;
}
int print_stack(struct head *p_head)
{
    int i = 0;
    struct note *temp = p_head->p_last;
    for (i = 0; i < p_head->count; i++)
    {
        printf("///// %d /////\n", temp->data);
        temp = temp->p_prev;
    }
    printf("/////////////\n");
    return p_head->count;
}
