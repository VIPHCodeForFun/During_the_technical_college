#ifndef DOUBLE_LIST_H_
#define DOUBLE_LIST_H_

#include <stdio.h>
#include <stdlib.h>

struct head
{
    int count;
    struct node *p_first;
    struct node *p_last;
};
struct node
{
    double element;
    struct node *p_next;
    struct node *p_prev;
};

struct head *create_list();
//erstellt eine Liste(Header)
struct node *create_node();
//erstellt ein Node
void enque_last(struct head *p_head, double value);
//erstellt ein Element am Ende mit dem Wert value
void enque_first(struct head *p_head, double value);
//erstellt ein Element am Anfang mit dem Wert value
void del_element(struct head *p_head, double value);
//Löscht alle Elemente in der Liste mit dem Wert value
void del_last(struct head *p_head);
//Löscht das letzte Element
void del_first(struct head *p_head);
//löscht das erste Element
struct head *del_list(struct head *p_head);
//Löscht die ganze Liste
void print_list(struct head *p_head);
//gib die Lista and er Console aus

#endif