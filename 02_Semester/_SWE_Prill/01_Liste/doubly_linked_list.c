/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:                                                                     
DOUBLY LINKED LIST 
///////////////////////////////////////////////////////////////////////////*/

#include "doubly_linked_list.h"

void note_minsort();

int main()
{
    printf("#Linked List\n");
    p_head = create_head(); //Pointer auf den Struktur Head
    note_enque_back(30);
    note_enque_back(2);
    note_enque_back(1);
    note_enque_back(14);
    note_enque_back(63);
    note_enque_back(50);
    note_enque_back(7);
    note_print_all();

    note_minsort();
    //delete_note(note_search(3));
    note_print_all();

    return 0;
}
// SORT_FUNKTION
void note_minsort()
{
    struct note *main_pos = p_head->p_first;
    struct note *compare = main_pos->p_next;
    struct note *temp_pos = NULL;
    struct note *temp_data = malloc(sizeof(struct note));
    temp_data->data = 0;
    temp_data->p_next = NULL;
    temp_data->p_prev = NULL;
    int bool = 0;

    int i = 0, j = 0;

    if (p_head->p_first == NULL || p_head->p_last == NULL)
    {
        printf("[List is EMPTY]\n");
        return;
    }
    //suchen und speichern
    while (i < p_head->count)
    {
        printf("i=%d ", i);
        while (j < p_head->count)
        {
            printf("j=%d ", j);
            if (main_pos->data == compare->data)
            {
                temp_pos = compare;
                bool = 1;
            }
            compare = compare->p_next;
            j++;
        }
        printf("j=i %d ", j);
        //Tauschen
        if (bool == 1)
        {
            temp_data->data = temp_pos->data;
            temp_pos->data = main_pos->data;
            main_pos->data = temp_data->data;
            bool = 0;
        }
        main_pos = main_pos->p_next;
        compare = main_pos->p_next;
        i++;
        j = i;
    }
    free(temp_data);
    return;
}
/*
    //Suchen und speichern
    while (main_pos != p_head->p_last)
    {
        while (compare != p_head->p_last)
        {
            if (main_pos->data > compare->data) //vergleich
            {
                temp_pos = compare; //speichern der Addresse
                bool = 1;           //es wurde getauscht
            }
            compare = compare->p_next; //nächste pos
        }
        if (compare == p_head->p_last) //letzte pos
        {
            if (main_pos->data > compare->data)
            {
                temp_pos = compare;
                bool = 1;
            }
        }

        //Tauschen
        if (bool == 1)
        {
            temp_data->data = temp_pos->data;
            temp_pos->data = main_pos->data;
            main_pos->data = temp_data->data;
            temp_pos = NULL;
            bool = 0;
        }
        //nächstes main element und neu starten
        compare = main_pos->p_next;
        main_pos = main_pos->p_next;
    }
    if (main_pos == p_head->p_last)
    {
        while (compare != p_head->p_last)
        {
            if (main_pos->data > compare->data) //vergleich
            {
                temp_pos = compare; //speichern der Addresse
                bool = 1;           //es wurde getauscht
            }
            compare = compare->p_next; //nächste pos
        }
        if (compare == p_head->p_last)
        {
            if (main_pos->data > compare->data)
            {
                temp_pos = compare;
                bool = 1;
            }
        }
        compare = main_pos->p_next;
        //Tauschen
        if (bool == 1)
        {
            temp_data->data = temp_pos->data;
            temp_pos->data = main_pos->data;
            main_pos->data = temp_data->data;
            temp_pos = NULL;
            bool = 0;
        }
    }


*/
