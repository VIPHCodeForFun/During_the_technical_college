//2.(20)DE - Queue mittels Liste-- ----------------------------------------------------------------
/*VerwendenSie die folgende Strukturen und realisiere Sie die Funktionen einer dynamischen doppelt
verketteten Liste ( Double-Ended-Queue ). Eine DE-Queue kann sowohl FIFO-als auch LIFO-Verhalten 
realisieren!Verwende folgende Strukturen:
struct SList 
{
    struct elem *next;
    struct elem *prev;
    int data;
};
typedef struct SList  SLIST;

struct SList_Header 
{
    int len;
    SLIST *first, *last;
};
    typedef struct SList_Header SLIST_HEADER;

Teilen Sie die Definitionen und Deklarationen in Header-und Source-Files.
Verwender_innen der DE-Queue sollen folgende Funktionen aufrufen können:

insert_element_at_back  // XX Fügt hinten eine neues Element hinzu
insert_element_at_front // XX Fügt vorne eine neues Element hinzu
remove_last_element     // Gibt das letzte Element zurück undlöscht es aus der Liste
remove_first_element    // XX Gibt das erste Element zurück und löscht es aus der Liste
examine_last_element    // XX Gibt das letzte Element zurück ohne es aus der Liste zu löschen
examine_first_element   // Gibt das erste Element zurück ohne es aus der Liste zu löschen
get_queue_len           // Gibt die Anzahl der Elemente in der Liste zurück 

Als Elemente sollen ganze positive Zahlen zwischen 100 und999 gespeichert werden können.
Sorgen Sie dafür dass keine doppelten Werte in der Liste existieren können!
Implementieren Sie die nicht gestrichenen Funktionen!!!*/
#include <stdio.h>
#include <stdlib.h>

struct SList
{
    struct SList *next;
    struct SList *prev;
    int data;
};
typedef struct SList SLIST;

struct SList_Header
{
    int len;
    SLIST *first, *last;
};
typedef struct SList_Header SLIST_HEADER;

SLIST_HEADER *c_head();
SLIST *c_node(int data);
int remove_last_element(SLIST_HEADER *p_head);   // Gibt das letzte Element zurück und löscht es aus der Liste
int examine_first_element(SLIST_HEADER *p_head); // Gibt das erste Element zurück ohne es aus der Liste zu löschen
int get_queue_len(SLIST_HEADER *p_head);         // Gibt die Anzahl der Elemente in der Liste zurück
void p_list(SLIST_HEADER *p_head);
void i_front(SLIST_HEADER *p_head, int data);

int main()
{

    SLIST_HEADER *p_head = c_head();
    i_front(p_head, 40);
    i_front(p_head, 50);
    printf("------%d\n", remove_last_element(p_head));
    i_front(p_head, 60);
    i_front(p_head, 70);
    i_front(p_head, 80);
    i_front(p_head, 90);

    p_list(p_head);

    printf("%d  %d", examine_first_element(p_head), get_queue_len(p_head));
    return 0;
}
SLIST_HEADER *c_head()
{
    SLIST_HEADER *p_temp = malloc(sizeof(SLIST_HEADER));
    p_temp->len = 0;
    p_temp->first = NULL;
    p_temp->last = NULL;
    return p_temp;
}
SLIST *c_node(int data)
{
    SLIST *p_temp = malloc(sizeof(SLIST));

    p_temp->next = NULL;
    p_temp->prev = NULL;
    p_temp->data = data;
    return p_temp;
}
void i_front(SLIST_HEADER *p_head, int data)
{
    SLIST *p_node = c_node(data);
    if (p_head == NULL)
    {
        return;
    }
    if (p_head->len == 0)
    {
        p_head->len++;
        p_head->first = p_node;
        p_head->last = p_node;
    }
    else
    {
        p_head->len++;
        p_node->next = p_head->first;
        p_head->first->prev = p_node;
        p_head->first = p_node;
    }
    return;
}
void p_list(SLIST_HEADER *p_head)
{
    SLIST *p_temp = p_head->first;
    int i = 0;
    for (i = 0; i < p_head->len; i++)
    {
        printf("[%d] =  %d\n", i, p_temp->data);
        p_temp = p_temp->next;
    }
    return;
}
int remove_last_element(SLIST_HEADER *p_head) // Gibt das letzte Element zurück und löscht es aus der Liste
{
    if (p_head == NULL)
    {
        return INT_MAX;
    }
    SLIST *p_temp = p_head->last;
    int save = p_temp->data;
    if (p_head->len == 1)
    {
        p_head->first = NULL;
        p_head->last = NULL;
    }
    else
    {
        p_temp->prev->next == NULL;
        p_head->last = p_temp->prev;
    }
    p_head->len--;
    free(p_temp);
    return save;
}
int examine_first_element(SLIST_HEADER *p_head) // Gibt das erste Element zurück ohne es aus der Liste zu löschen
{
    if (p_head->first == NULL)
    {
        return INT_MAX;
    }
    return p_head->first->data;
}
int get_queue_len(SLIST_HEADER *p_head) // Gibt die Anzahl der Elemente in der Liste zurück
{
    if (p_head->first == NULL)
    {
        return INT_MAX;
    }
    return p_head->len;
}