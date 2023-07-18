#ifndef PHILIPPVIDMAR_H_
#define PHILIPPVIDMAR_H_

typedef struct block
{
  char *sart_adr;
  int size;
  char name[10];
  int free;
} BLOCK;

typedef struct list_element
{
  BLOCK block;
  struct list_element *next;
  struct list_element *prev;
} NODE;

typedef struct list_head
{
  int count;
  int strategy;
  struct list_element *first;
  struct list_element *last;
  struct list_element *position;
} HEAD;
/*1:    firstFit
  2:    nextFit
  3:    bestfit
  4:    worstFit*/

//Funktionen---------------------------------------------------------------------------

/*Initialisiert einen Heap mit einer beliebigen Größe,
legt die internen Verwaltungsstrukturen an und bestimmt die Belegungsstrategie*/
HEAD *mminit(int size, int strat);

/*Gibt den Heap und alle Verwaltungsstrukturen wieder frei*/
HEAD *mmterm(HEAD *p_header);

/*Allokiert auf dem Heap einen Speicherblock mit einer beliebigen Größe;
  optional sollte über einen zusätzlichen Parameter noch ein Blockname angegeben werden können. 
  Die Funktion liefert die Startadresse des Speicherblocks.*/
char *mmmalloc(HEAD *p_header, int blocksize, char name[]);
//char *mmmalloc(int, char[]) //int blocksize, char[] name

/*Gibt einen bestimmten Speicherblock, adressiert über die Startadresse wieder frei.
  Nebeneinanderliegende freie Blöcke sollten zu einem größeren freien Speicherblock vereint werden.*/
void mmfree(HEAD *p_header, char *);

/*setzt den Namen eines belegten Speicherblocks;
  nimmt hierzu die Startadresse eines belegten Blocks und den Namen entgegen*/
void mmrename(HEAD *p_header, char *address, char new_name[]);

/*Gibt die aktuelle Belegung des Heaps in folgendem Textform auf stdout aus:*/
void mmdump(HEAD *p_header);

//LISTE---------------------------------------------------------------------

/*Legt einen Header an*/
HEAD *c_head(int strategy);

/*Legt ein node an*/
NODE *c_node(char *start_adr, int size, char name[], int free);

/*Fügt ein Node zur Liste hinzu*/
NODE *insert_node(HEAD *p_header, NODE *new_element, NODE *position);

/*Löscht ein Node*/
void delete_node(HEAD *p_header, NODE *del_node);

//HILFSFUNKTIONEN---------------------------------------------------------------------

void print_strat(int strat);

#endif
