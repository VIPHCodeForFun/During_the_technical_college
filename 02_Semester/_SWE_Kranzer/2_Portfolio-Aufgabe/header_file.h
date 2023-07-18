#ifndef HEADER_FILE_H_
#define HEADER_FILE_H_

#include <stdio.h>
#include <stdlib.h> //malloc

struct head
{
    int count;
    struct note *p_first; //zeigt auf das erste note in der Liste
    struct note *p_last;  //zeigt auf das letzte note in der Liste
};

struct note
{
    double data;
    struct note *p_next; //zeigt auf das nächste note
    struct note *p_prev; //zeigt auf das vorherige note
};

struct head *create_head();

void note_enque_front();
void note_deque_front();

void note_print_all();
void note_print_double();

void input_bin_file();
void output_bin_file();

struct head *p_head; // Globale variable, Pointer auf struckt_Head (p_head = create_head())

#endif /* HEADER_FILE_H_*/