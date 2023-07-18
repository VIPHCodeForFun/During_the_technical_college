/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:                                                                     
Unter dem Begri "Stack" versteht man eine abstrakte Datenstruktur, die nach dem LIFO1-Prinzip arbeitet. 
In der heutigen Einheit besteht deine Aufgabe darin, einen solchen Stack ineiner Kleingruppe mit deinen KommilitonInnen konzeptionell auszuarbeiten.
Euer Programm hat folgende Funktionalität bereitzustellen:
• Das Erstellen eines neuen, leeren Stacks.
• Die Funktionpush, welche ein Element an oberster Stelle des Stacks ablegt.
• Die Funktionpop, welche das oberste Element des Stacks zurückgibt und vom Stackentfernt.
• Die Funktionpeek, welche den Wert des obersten Elements des Stacks zurückliefert.
Baut hierfür auf der doppelt verketteten Liste der letzten Übung auf, 
sodass der Stack auseiner Reihe von Elementen besteht, die über einen Double-Wert sowie über Referenzen derbenachbarten Elemente des Stacks verfügen.
//////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>

struct stack_head
{
    int leng;
    struct stack_node *p_first;
};
struct stack_node
{
    double value;
    struct stack_node *p_next;
    struct stack_node *p_prev;
};

struct stack_head *create_stack();
struct stack_node *push(struct stack_head *p_stack, double element);
struct stack_node *pop(struct stack_head *p_stack);
double peek(struct stack_head *p_p_stack);

int main()
{
    struct stack_head *p_stack = create_stack();
    push(p_stack, 1);
    peek(p_stack);
    push(p_stack, 2);
    pop(p_stack);
    peek(p_stack);
    push(p_stack, 3);
    peek(p_stack);
    push(p_stack, 4);
    push(p_stack, 5);
    push(p_stack, 6);
    push(p_stack, 7);
    peek(p_stack);

    return 0;
}
struct stack_head *create_stack()
{
    struct stack_head *temp = malloc(sizeof(struct stack_head));
    if (temp == NULL)
    {
        printf("ERROR CREATE_STACK MALLOC\n");
        return NULL;
    }
    temp->leng = 0;
    temp->p_first = NULL;
    return temp;
}
struct stack_node *push(struct stack_head *p_stack, double element)
{
    struct stack_node *new_node = malloc(sizeof(struct stack_node));
    if (new_node == NULL)
    {
        printf("ERROR PUSH MALLOC\n");
        return NULL;
    }
    if (p_stack->leng > 5) // MAX LENG
    {
        printf("SACK IS FULL WITH %d ELEMENTS\n", p_stack->leng);
        return NULL;
    }
    new_node->value = element;
    new_node->p_next = NULL;
    new_node->p_prev = NULL;

    //struckt is empty
    if (p_stack->leng == 0)
    {
        p_stack->leng = 1;
        p_stack->p_first = new_node;
    }
    else
    {
        p_stack->leng++;
        new_node->p_next = p_stack->p_first; //P_NEXT
        p_stack->p_first->p_prev = new_node; //P_PREV from FRONT
        p_stack->p_first = new_node;         //new FORNT
    }
    return new_node;
}
struct stack_node *pop(struct stack_head *p_stack)
{
    struct stack_node *temp = p_stack->p_first;
    if (p_stack->leng == 0)
    {
        return NULL;
    }
    else if (p_stack->leng == 1)
    {
        p_stack->p_first = NULL;
        p_stack->leng--;
    }
    else
    {
        temp->p_next->p_prev = NULL;     //NEW P_FIRST == P_Prev ==NULL
        p_stack->p_first = temp->p_next; // P_FIRST == NEW P_FIRST
        p_stack->leng--;
    }
    free(temp);
    return p_stack->p_first;
}

double peek(struct stack_head *p_stack)
{
    printf("//////[%.2lf]//////\n", p_stack->p_first->value);
    return p_stack->p_first->value;
}