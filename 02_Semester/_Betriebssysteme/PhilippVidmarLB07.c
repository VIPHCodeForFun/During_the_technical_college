/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
///////////////////////////////////////////////////////////////////////////*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "philippvidmar.h"

int main()
{
    char *p_add_block[100];
    HEAD *p_heap_head = mminit(10000, 1);
    /*1:    firstFit OK
      2:    nextFit OK
      3:    bestfit OK
      4:    worstFit OK
    */
    p_add_block[1] = mmmalloc(p_heap_head, 1000, "P1");
    p_add_block[2] = mmmalloc(p_heap_head, 1000, "P2");
    p_add_block[3] = mmmalloc(p_heap_head, 500, "P3");
    p_add_block[4] = mmmalloc(p_heap_head, 500, "P4");
    p_add_block[5] = mmmalloc(p_heap_head, 2000, "P5");
    p_add_block[6] = mmmalloc(p_heap_head, 1000, "P6");
    p_add_block[7] = mmmalloc(p_heap_head, 200, "P7");
    p_add_block[8] = mmmalloc(p_heap_head, 200, "P8");
    p_add_block[9] = mmmalloc(p_heap_head, 200, "P9");
    p_add_block[10] = mmmalloc(p_heap_head, 200, "P10");

    mmdump(p_heap_head);
    mmfree(p_heap_head, p_add_block[1]); // FREE PASST NICHT ZU 100%
    mmfree(p_heap_head, p_add_block[3]);
    mmfree(p_heap_head, p_add_block[5]);
    mmfree(p_heap_head, p_add_block[7]);
    mmfree(p_heap_head, p_add_block[9]);
    mmfree(p_heap_head, p_add_block[10]);
    p_add_block[11] = mmmalloc(p_heap_head, 500, "P11");

    //mmrename
    mmrename(p_heap_head, p_add_block[4], "4P4");
    mmrename(p_heap_head, p_add_block[5], "5P5");
    mmdump(p_heap_head);
    //Strat Testen
    //printf("xxxxxxxxxxxx%s\n", p_heap_head->position->block.name);
    p_add_block[12] = mmmalloc(p_heap_head, 2000, "P12");
    p_add_block[13] = mmmalloc(p_heap_head, 1000, "P13");
    mmdump(p_heap_head);

    //mmterm
    p_heap_head = mmterm(p_heap_head);
    mmdump(p_heap_head);

    return 0;
}
//-----------------------------------------------------------------------------------------------------
//Funktionen-------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
HEAD *mminit(int size, int strat)
{
    char *p_heap = calloc(size, sizeof(char));
    if (p_heap == NULL)
    {
        printf("Heap konnte nicht initialisiert werden\n");
        return NULL;
    }
    HEAD *p_heap_head = c_head(strat);
    if (p_heap_head == NULL)
    {
        printf("Heap_Head konnte nicht initialisiert werden\n");
    }
    //First Fit
    if (strat == 1)
    {
        insert_node(p_heap_head, c_node(p_heap, size, "-", 1), NULL); // Fehler Abfrage
        p_heap_head->strategy = 1;
        return p_heap_head;
    }
    //next Fit
    else if (strat == 2)
    {
        insert_node(p_heap_head, c_node(p_heap, size, "-", 1), NULL); // Fehler Abfrage
        p_heap_head->strategy = 2;
        return p_heap_head;
    }
    //best Fit
    else if (strat == 3)
    {
        insert_node(p_heap_head, c_node(p_heap, size, "-", 1), NULL); // Fehler Abfrage
        p_heap_head->strategy = 3;
        return p_heap_head;
    }
    //worst Fit
    else if (strat == 4)
    {
        insert_node(p_heap_head, c_node(p_heap, size, "-", 1), NULL); // Fehler Abfrage
        p_heap_head->strategy = 4;
        return p_heap_head;
    }
    else
    {
        printf("Wrong strat.\n");
    }
    return NULL;
}
HEAD *mmterm(HEAD *p_header)
{
    NODE *p_run = p_header->first;
    while (p_run != NULL)
    {
        if (p_run->block.free == 0)
        {
            mmfree(p_header, p_run->block.sart_adr);
        }
        p_run = p_run->next;
    }

    free(p_header->first->block.sart_adr);
    delete_node(p_header, p_header->first);
    free(p_header);
    return NULL;
}
char *mmmalloc(HEAD *p_header, int blocksize, char name[])
{
    printf("malloc %d %s \n", blocksize, name);
    //First Fit
    if (p_header->strategy == 1)
    {
        NODE *p_run = p_header->first;
        while (p_run != NULL)
        {
            if (p_run->block.size == blocksize && p_run->block.free != 0)
            {
                strcpy(p_run->block.name, name);
                p_run->block.free = 0;
                return p_run->block.sart_adr;
            }
            else if (p_run->block.size > blocksize && p_run->block.free != 0)
            {
                insert_node(p_header, c_node(p_run->block.sart_adr, blocksize, name, 0), p_run);
                p_run->block.size = p_run->block.size - blocksize;
                p_run->block.sart_adr = &p_run->block.sart_adr[blocksize];
                return p_run->prev->block.sart_adr;
            }
            else
            {
                p_run = p_run->next;
            }
        }
    }
    //next Fit
    else if (p_header->strategy == 2)
    {
        int i = 0;
        for (i = 0; i < p_header->count; i++)
        {
            if (p_header->position == NULL)
            {
                p_header->position = p_header->first;
            }
            if (p_header->position->block.size == blocksize && p_header->position->block.free != 0)
            {
                strcpy(p_header->position->block.name, name);
                p_header->position->block.free = 0;
                return p_header->position->block.sart_adr;
            }
            else if (p_header->position->block.size > blocksize && p_header->position->block.free != 0)
            {
                insert_node(p_header, c_node(p_header->position->block.sart_adr, blocksize, name, 0), p_header->position);
                p_header->position->block.size = p_header->position->block.size - blocksize;
                p_header->position->block.sart_adr = &p_header->position->block.sart_adr[blocksize];
                return p_header->position->prev->block.sart_adr;
            }
            else
            {
                p_header->position = p_header->position->next;
            }
        }
    }
    //best Fit
    else if (p_header->strategy == 3)
    {
        NODE *p_run = p_header->first;
        NODE *p_temp = NULL;
        //find smalest fit free
        while (p_run != NULL)
        {
            if (p_run->block.free != 0 && p_temp == NULL && p_run->block.size >= blocksize)
            {
                p_temp = p_run;
                p_run = p_run->next;
            }
            else if (p_run->block.free != 0 && p_temp != NULL)
            {
                if (p_run->block.size < p_temp->block.size && p_run->block.size >= blocksize)
                {
                    p_temp = p_run;
                }
                p_run = p_run->next;
            }
            else
            {
                p_run = p_run->next;
            }
        }
        //input
        if (p_temp == NULL)
        {
            printf("Stack over flow !!! with %d %s\n", blocksize, name);
            return NULL;
        }
        else if (p_temp->block.size == blocksize)
        {
            strcpy(p_temp->block.name, name);
            p_temp->block.free = 0;
            return p_temp->block.sart_adr;
        }
        else if (p_temp->block.size > blocksize)
        {
            insert_node(p_header, c_node(p_temp->block.sart_adr, blocksize, name, 0), p_temp);
            p_temp->block.size = p_temp->block.size - blocksize;
            p_temp->block.sart_adr = &p_temp->block.sart_adr[blocksize];
            return p_temp->prev->block.sart_adr;
        }
    }
    //worst Fit
    else if (p_header->strategy == 4)
    {
        NODE *p_run = p_header->first;
        NODE *p_temp = NULL;
        //find bigest free
        while (p_run != NULL)
        {
            if (p_run->block.free != 0 && p_temp == NULL)
            {
                p_temp = p_run;
                p_run = p_run->next;
            }
            else if (p_run->block.free != 0 && p_temp != NULL)
            {
                if (p_run->block.size > p_temp->block.size)
                {
                    p_temp = p_run;
                }
                p_run = p_run->next;
            }
            else
            {
                p_run = p_run->next;
            }
        }
        //input
        if (p_temp == NULL)
        {
            printf("Stack over flow !!! with %d %s\n", blocksize, name);
            return NULL;
        }
        else if (p_temp->block.size == blocksize)
        {
            strcpy(p_temp->block.name, name);
            p_temp->block.free = 0;
            return p_temp->block.sart_adr;
        }
        else if (p_temp->block.size > blocksize)
        {
            insert_node(p_header, c_node(p_temp->block.sart_adr, blocksize, name, 0), p_temp);
            p_temp->block.size = p_temp->block.size - blocksize;
            p_temp->block.sart_adr = &p_temp->block.sart_adr[blocksize];
            return p_temp->prev->block.sart_adr;
        }
    }
    printf("Stack over flow !!! with %d %s\n", blocksize, name);
    return NULL;
}
void mmfree(HEAD *p_header, char *address)
{
    printf("mmfree %p \n", address);
    if (p_header == NULL || address == NULL)
    {
        printf("free Pointer == NULL");
        return;
    }
    NODE *p_run = p_header->first;
    while (p_run != NULL)
    {
        //check for address
        if (p_run->block.sart_adr == address)
        {
            //check for free
            if (p_run->block.free == 0)
            {
                //Element is solo
                if (p_run->next == NULL && p_run->prev == NULL)
                {
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                //Front/Back with a taken neighbour
                else if (p_run->prev == NULL && p_run->next->block.free == 0)
                {
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                else if (p_run->next == NULL && p_run->prev->block.free == 0)
                {
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                //Front/Back with a free neighbour
                else if (p_run->prev == NULL && p_run->next->block.free != 0)
                {
                    //delete next node Adresse stays
                    int temp_size = p_run->next->block.size;
                    delete_node(p_header, p_run->next);

                    p_run->block.size = p_run->block.size + temp_size;
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                else if (p_run->next == NULL && p_run->prev->block.free != 0)
                {
                    //delete prev node save prev Address
                    int temp_size = p_run->prev->block.size;
                    char *temp_adr = p_run->prev->block.sart_adr;
                    delete_node(p_header, p_run->prev);

                    p_run->block.size = p_run->block.size + temp_size;
                    p_run->block.sart_adr = temp_adr;
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                //element with 2 taken neighbours
                else if (p_run->next->block.free == 0 && p_run->prev->block.free == 0)
                {
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                //element with one taken neighbour
                else if (p_run->prev->block.free == 0 && p_run->next->block.free != 0)
                {
                    //delete next node und vergrößere den Speciher
                    int temp_size = p_run->next->block.size;
                    delete_node(p_header, p_run->next);

                    p_run->block.size = p_run->block.size + temp_size;
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                else if (p_run->next->block.free == 0 && p_run->prev->block.free != 0)
                {
                    //delete prev node und vergrößere den Speciher
                    int temp_size = p_run->prev->block.size;
                    char *temp_adr = p_run->prev->block.sart_adr;
                    delete_node(p_header, p_run->prev);

                    p_run->block.size = p_run->block.size + temp_size;
                    p_run->block.sart_adr = temp_adr;
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                //element with 2 free neighbours
                else
                {
                    //Delete prev und next und vergrößere den speicher
                    int temp_size_next = p_run->next->block.size;
                    int temp_size_prev = p_run->prev->block.size;
                    char *temp_adr__prev = p_run->prev->block.sart_adr;

                    delete_node(p_header, p_run->prev);
                    delete_node(p_header, p_run->next);

                    p_run->block.size = p_run->block.size + temp_size_next + temp_size_prev;
                    p_run->block.sart_adr = temp_adr__prev;
                    strcpy(p_run->block.name, "--");
                    p_run->block.free = 1;
                }
                return;
            }
            printf("Address is already free\n");
            return;
        }
        p_run = p_run->next;
    }
    printf("Address for Free not found !\n");
    return;
}
void mmrename(HEAD *p_header, char *address, char new_name[])
{

    NODE *p_run = p_header->first;
    while (p_run != NULL)
    {
        if (p_run->block.sart_adr == address && p_run->block.free == 0)
        {
            printf("mmrename %s --> %s\n", p_run->block.name, new_name);
            strcpy(p_run->block.name, new_name);
            return;
        }
        p_run = p_run->next;
    }
    printf("mmrename Address not found the block is free !\n");
    return;
}
void mmdump(HEAD *p_header)
{
    if (p_header == NULL)
    {
        printf("no Header\n");
        return;
    }
    int heapsize = 0;
    int free_size = 0;
    int free_blocks = 0;
    int taken_size = 0;
    int taken_blocks = 0;
    NODE *p_run = p_header->first;
    while (p_run != NULL)
    {
        heapsize = heapsize + p_run->block.size;
        if (p_run->block.free == 0)
        {
            taken_size = taken_size + p_run->block.size;
            taken_blocks++;
        }
        else
        {
            free_size = free_size + p_run->block.size;
            free_blocks++;
        }
        p_run = p_run->next;
    }
    double taken_percent = (100.00 / heapsize) * taken_size;
    double free_percent = (100.00 / heapsize) * free_size;
    printf("\n-----------------------------------------------\n");
    print_strat(p_header->strategy);
    printf("Heapsize:        %d Byte\n", heapsize);                                              //Heapsize: 10000
    printf("Belegte Bloecke: %d  (%d Byte %.2lf%%)\n", taken_blocks, taken_size, taken_percent); //Belegte Bloecke: 3 (1700 Byte / 17%)
    printf("Freie Bloecke:   %d  (%d Byte %.2lf%%)\n", free_blocks, free_size, free_percent);    //Freie Bloecke: 2 (8300 Byte / 83%)
    printf("-----------------------------------------------\n");
    printf("Startadresse    \tGroesse\tStatus \tName\n");

    p_run = p_header->first;
    while (p_run != NULL)
    {
        if (p_run->block.free == 0)
        {
            printf("%p\t%d  \ttaken\t%s\n", p_run->block.sart_adr, p_run->block.size, p_run->block.name);
        }
        else
        {
            printf("%p\t%d  \tfree\t%s\n", p_run->block.sart_adr, p_run->block.size, p_run->block.name);
        }
        p_run = p_run->next;
    }
    printf("-----------------------------------------------\n");
    return;
}
//-----------------------------------------------------------------------------------------------------
//LISTE------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
HEAD *c_head(int strategy)
{
    HEAD *p_head = malloc(sizeof(HEAD));
    p_head->count = 0;
    p_head->strategy = strategy;
    p_head->first = NULL;
    p_head->last = NULL;
    p_head->position = NULL;
    return p_head;
}
NODE *c_node(char *start_adr, int size, char name[], int free)
{
    NODE *p_node = malloc(sizeof(NODE));
    if (p_node == NULL)
    {
        return NULL;
    }
    p_node->block.sart_adr = start_adr;
    p_node->block.size = size;
    strcpy(p_node->block.name, name);
    p_node->block.free = free;
    p_node->next = NULL;
    p_node->prev = NULL;
    return p_node;
}
NODE *insert_node(HEAD *p_header, NODE *new_element, NODE *position)
{
    if (new_element == NULL || p_header == NULL)
    {
        printf("new_element konnte nicht initialisiert werdent\n");
        return NULL;
    }
    //liste ist empty
    if (p_header->count == 0)
    {
        p_header->first = new_element;
        p_header->last = new_element;
        p_header->count++;
    }
    // input in front of first node
    else if (position == p_header->first)
    {
        new_element->next = p_header->first;
        p_header->first->prev = new_element;
        p_header->first = new_element;
        p_header->count++;
    }
    //input in front of node
    else
    {
        new_element->next = position;
        new_element->prev = position->prev;
        new_element->next->prev = new_element;
        new_element->prev->next = new_element;
        p_header->count++;
    }
    return new_element;
}
void delete_node(HEAD *p_header, NODE *del_node)
{
    if (p_header == NULL || del_node == NULL)
    {
        printf("element can not be deleted\n");
        return;
    }
    //list is empty
    if (p_header->count == 0)
    {
        printf("list is empty\n");
        return;
    }
    //only one element
    if (del_node->next == NULL && del_node->prev == NULL)
    {
        p_header->first = NULL;
        p_header->last = NULL;
        p_header->position = NULL; //NEXTFIT
        p_header->count--;
        free(del_node);
    }
    //del_node is last element
    else if (del_node == p_header->last)
    {
        del_node->prev->next = NULL;
        p_header->last = del_node->prev;
        p_header->count--;
        if (del_node == p_header->position) //NEXTFIT
        {
            p_header->position = del_node->next;
        }
        free(del_node);
    }
    //del_node is first element
    else if (del_node == p_header->first)
    {
        del_node->next->prev = NULL;
        p_header->first = del_node->next;
        p_header->count--;
        if (del_node == p_header->position) //NEXTFIT
        {
            p_header->position = del_node->next;
        }
        free(del_node);
    }
    //element with 2 neighbour
    else
    {
        del_node->next->prev = del_node->prev;
        del_node->prev->next = del_node->next;
        p_header->count--;
        if (del_node == p_header->position) //NEXTFIT
        {
            p_header->position = del_node->prev;
        }
        free(del_node);
    }
    return;
}
//-----------------------------------------------------------------------------------------------------
//HILFSFUNKTIONEN--------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
void print_strat(int strat)
{
    if (strat == 1)
    {
        printf("FIRST-FIT\n");
    }
    else if (strat == 2)
    {
        printf("NEXT-FIT\n");
    }
    else if (strat == 3)
    {
        printf("BEST-FIT\n");
    }
    else if (strat == 4)
    {
        printf("WORST-FIT\n");
    }
    else
    {
        printf("ERROR Strat!!\n");
    }
}