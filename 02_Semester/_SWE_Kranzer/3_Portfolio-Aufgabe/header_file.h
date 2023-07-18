/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:       
Entweder einfach oder doppelt verkettete Liste (mit der Möglichkeit die Größe zu limitieren) für Integer-Werte implementieren 
(Header und Sourcefile)                                                              
Strukturen definieren, Funktionen festlegen (Header-File)
///////////////////////////////////////////////////////////////////////////*/

#ifndef HEADER_FILE_H_
#define HEADER_FILE_H_

#include <stdio.h>

struct head
{
    int count;
    int max_len;
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
//LIST
struct head *create_list(int len);
struct note *enque_back(struct head *p_head, int value);
struct note *deque_back(struct head *p_head);

struct note *enque_front(struct head *p_head, int value);
struct note *deque_front(struct head *p_head);

struct head *delete_list(struct head *p_head);

int print_list(struct head *p_head);
//QUEUE AND STACK
int peak(struct head *p_head);
int size(struct head *p_head);
int print_queue(struct head *p_head);
int print_stack(struct head *p_head);
//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//##//

#endif /* HEADER_FILE_H_*/