#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//für free, kann auch bool verwenden
//  1 = frei
//  0 = belegt
typedef struct Block
{
    char *startAdr;
    int size; //Segment göße/länge
    char name[5];
    int free;
} Block;

typedef struct LE
{
    struct Block block;
    struct LE *next;
    struct LE *prev;
} LE;

typedef struct LH
{
    struct LE *first;
    struct LE *last;
    int strategy;
    int cnt;
} LH;

char *heap = NULL;
int heapSize = 0;
LH *header = NULL;

//Für ersten Parameter
//  kann size_t integer usw wählen
//Für zweiten parameter enum könnte auch verwendet werden
//  1: firstFit
//  2: nextFit
//  3: bestFit
//  4: worstFit
//geben einen Pointer auf den Beginn unseres Heaps zurück (char ist genau ein byte groß)
char *mminit(int, int);

//Alles freigeben
void mmterm();

//Speicherblock einer größe am eigenen Heap reservieren und Blocknamen vergeben
//integer als Blockgröße
//char * als Name
//char Pointer als Rückgabe
char *mmalloc(int, char *);
//Block wird geprüft ob genügend Speicher vorhanden ist
int checkBlock(LE *, int);

//soll einen Speicherblock mit einer best Startadresse freigeben
//Pointer mitgeben, kein Rückgabewert
void mmfree(char *);

//Startadresse mitgeben und den neuen Namen
void mmrename(char *, char *);
LE *findAddress(char *); //Hilfsfunktion für mmfree und mmrename, gibt das gesuchte Element oder NULL zurück

//Übersicht über den Speicher (keine Parameter da keine Konfiguration notwendig)
void mmdump();
void heapUsage(int);
void printBlock();

LH *createHeader(int);
LE *createElement(char *, int, char *, int); //startadresse, größe Name und Frei|Belegt
LH *insertIntoList(LE *);

int main()
{
    char *a[100];
    mminit(10000, 1);
    a[1] = mmalloc(1000, "P1");
    a[2] = mmalloc(1000, "P2");
    a[3] = mmalloc(500, "P3");
    a[4] = mmalloc(500, "P4");
    a[5] = mmalloc(2000, "P5");
    a[6] = mmalloc(1000, "P6");
    a[7] = mmalloc(200, "P7");
    a[8] = mmalloc(200, "P8");
    a[9] = mmalloc(200, "P9");
    a[10] = mmalloc(200, "P10");

    mmdump();
    mmfree(a[1]);
    mmfree(a[3]);
    mmfree(a[5]);
    mmfree(a[7]);
    mmfree(a[9]);
    mmfree(a[10]);
    a[11] = mmalloc(500, "P11");

    mmrename(a[4], "4P4");
    mmrename(a[5], "5P5");
    mmdump();

    a[12] = mmalloc(2000, "P12");
    a[13] = mmalloc(1000, "P13");
    mmdump();
    /* mmrename(heap, "Speicher");
    mmdump();
    char *x;
    mmdump();
    mmrename(x, "Test");
    mmfree(x);
    char *a = mmalloc(100, "P1");
    mmdump();
    char *b = mmalloc(1000, "P2");
    mmdump();
    mmrename(b, "BLABLA");
    mmdump();
    char *c = mmalloc(1000, "P3");
    char *d = mmalloc(1000, "P4");
    //mmterm();
    mmdump();
    char *e = mmalloc(1000, "P5");
    char *f = mmalloc(1000, "P6");
    char *g = mmalloc(1000, "P7");
    char *h = mmalloc(1000, "P8");
    char *i = mmalloc(1000, "P9");
    char *j = mmalloc(1000, "P10");
    mmdump();
    mmfree(c);
    mmfree(d);
    mmfree(e);
    mmfree(f);
    mmdump();
    char *y = mmalloc(2300, "Test");
    mmdump();
    mmfree(j);
    mmdump();*/
    return 0;
}

LH *createHeader(int strat)
{
    header = (LH *)calloc(1, sizeof(LH));
    if (header != NULL)
    {
        header->cnt = 0;
        header->first = NULL;
        header->last = NULL;
        header->strategy = strat;
    }
    return header;
}

LE *createElement(char *startAdr, int size, char *name, int free)
{
    LE *n = (LE *)calloc(1, sizeof(LE));
    if (n != NULL)
    {
        n->block.startAdr = startAdr;
        n->block.size = size;
        strcpy(n->block.name, name);
        n->block.free = free;
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

LH *insertIntoList(LE *newElement)
{
    int tmpStrategy = 0;
    LE *runEl = header->first;
    if (newElement == NULL)
    {
        printf("Kein neues Element!\n");
        return header;
    }
    if (header == NULL)
    {
        while (tmpStrategy >= 1 && tmpStrategy <= 4)
        {
            printf("Bitte Speicherstrategie eingeben: \n");
            scanf("%1i", &tmpStrategy);
            puts("");
            createHeader(tmpStrategy);
        }
    }

    if (header->cnt == 0)
    {
        header->first = newElement;
        header->last = newElement;
        header->cnt++;
    }
    /*************************************************************************************************/
    else
    {
        //hinten einfügen wir müssen modifiziern beliebig einfügen ca. bei min 45
        // header->last->next = newElement;
        // header->last->next->prev = header->last;
        // header->last = header->last->next;
        // header->cnt++;

        if (runEl == NULL)
        {
            printf("Element konnte nicht eingefügt werden.\n");
            return header;
        }

        //FirstFit
        if (header->strategy == 1)
        {

            //füge den Block da ein wo die startAdresse gleich ist, die vom freien Bereich wird anschl. hochgezählt.
            while (newElement->block.startAdr != runEl->block.startAdr)
            {
                runEl = runEl->next;
            }
            if (runEl == header->first) //runEl == header->first
            {
                runEl->prev = newElement;
                newElement->next = header->first;
                header->first = newElement;
                header->cnt++;
            }
            else
            {
                newElement->prev = runEl->prev;
                newElement->next = runEl;
                runEl->prev = newElement;
                newElement->prev->next = newElement;
                header->cnt++;
            }
        }
        //NextFit
        else if (header->strategy == 2)
        {
            //NOT IMPLEMENTED
        }
        //BestFit
        else if (header->strategy == 3)
        {
            //NOT IMPLEMENTED
        }
        //WorstFit
        else if (header->strategy == 4)
        {
            //immer vorne einfügen wenn Block vorhanden und Block aufteilen
            if (header->cnt == 1)
            {
                //erstes Element und header first neu setzen
                header->first->block.size = header->first->block.size - newElement->block.size;
                header->first->block.startAdr = header->first->block.startAdr + newElement->block.size;
                newElement->next = header->first;
                header->first->prev = newElement;
                header->first = newElement;
                header->cnt++;
            }
            //nicht das erste Element muss nicht mit First und Last arbeiten
            else
            {
                while (runEl->block.startAdr != newElement->block.startAdr)
                {
                    runEl = runEl->next;
                }
                runEl->block.size = runEl->block.size - newElement->block.size;
                runEl->block.startAdr = runEl->block.startAdr + newElement->block.size;
                newElement->prev = runEl->prev;
                runEl->prev->next = newElement;
                newElement->next = runEl;
                runEl->prev = newElement;
                header->cnt++;
            }
        }
    }
    /*************************************************************************************************/
    return header;
}

//Reservierung unseres Speichers
char *mminit(int size, int strategy)
{
    //heap = (char*)malloc(size * sizeof(char));
    heap = (char *)calloc(size, sizeof(char));
    if (heap == NULL)
    {
        printf("Heap konnte nicht initialisiert werden!\n");
        return NULL;
    }

    heapSize = size;

    createHeader(strategy);
    insertIntoList(createElement(0, heapSize, "a", 1)); // mit dieser Liste die Hier rauskommt sollten wir die 4 belegungsstrategien realisieren min 55

    return heap;
}

//Speicherblock einer größe am eigenen Heap reservieren und Blocknamen vergeben
//integer als Blockgröße
//char * als Name
//char Pointer als Rückgabe
char *mmalloc(int size, char *Name)
{
    char *resAdr = NULL;
    //Element zum durchlaufen der Liste
    LE *runElement = NULL;
    LE *tmpElement = NULL;
    if (header == NULL)
        return NULL;
    //FirstFit
    //Prüfen welche Strategie verfolgt wird im Heap
    if (header->strategy == 1)
    {

        //durchlaufen bis ein Block frei ist oder der Letzte Block erreicht wurde
        runElement = header->first;
        while (runElement != NULL)
        {
            if (checkBlock(runElement, size) == 0)
            {
                //printf("Belegt|Nicht ausreichend Speicher vorhanden!\n");
                runElement = runElement->next;
            }
            else
            {
                insertIntoList(createElement(runElement->block.startAdr, size, Name, 0));
                resAdr = runElement->block.startAdr;
                runElement->block.startAdr = runElement->block.startAdr + size;
                runElement->block.size = runElement->block.size - size;
                if (runElement->block.size <= 0)
                {
                    runElement->prev->next = NULL;
                    free(runElement);
                    header->cnt--;
                }
                break;
            }
        }
    }
    //NextFit
    else if (header->strategy == 2)
    {
        puts("NOT IMPLEMENTED");
    }
    //BestFit
    else if (header->strategy == 3)
    {
        puts("NOT IMPLEMENTED");
    }
    //Worst Fit
    else
    {
        runElement = header->first;
        //Durchlaufen und speichern des groesten Elements
        while (runElement != NULL)
        {
            if (runElement->block.free == 1 && tmpElement == NULL)
            {
                tmpElement = runElement;
                runElement = runElement->next;
            }
            //wenn nicht belegt ist und das das SpeicherElement schon einen Wert hat
            else if (runElement->block.free != 0 && tmpElement != NULL)
            {
                //suchen ob noch größere Lücken vorhanden sind
                if (runElement->block.size > tmpElement->block.size)
                {
                    tmpElement = runElement;
                }
                runElement = runElement->next;
            }
            else
            {
                runElement = runElement->next;
            }
        }
        //Kein freies größtes Element gefunden| Fehler
        if (tmpElement == NULL)
        {
            return NULL;
        }
        //wenn das einzufuegenede Element genau den Speicher benötigt der noch frei ist muss nichts gelöscht werden
        else if (tmpElement->block.size == size)
        {
            resAdr = tmpElement->block.startAdr;
            tmpElement->block.free = 0;
            strcpy(tmpElement->block.name, Name);
            return resAdr;
        }
        //Element kann eingefügt werden
        else
        {
            resAdr = tmpElement->block.startAdr;
            insertIntoList(createElement(tmpElement->block.startAdr, size, Name, 0));
        }
    }
    return resAdr;
}

int checkBlock(LE *checkEl, int resSize)
{
    //Block muss frei sein und genügen Speicher besitzen
    if (checkEl->block.free == 1 && resSize <= checkEl->block.size)
        return 1;
    return 0;
}

void mmdump()
{
    puts("###############################################################");
    printf("Heapsize: %i\n", heapSize);
    heapUsage(0);
    heapUsage(1);

    puts("---------------------------------------------------------------");
    printf("Startadresse\tGroesse\tStatus\tName\n");
    printBlock();
    puts("###############################################################");
}

void heapUsage(int blockVal)
{
    int tempCnt = 0;
    int tempSize = 0;
    LE *runElement = NULL;
    if (header == NULL)
        return;
    runElement = header->first;
    if (runElement == NULL)
        return;
    while (runElement != NULL)
    {
        if (runElement->block.free == blockVal)
        {
            tempCnt++;
            tempSize = tempSize + runElement->block.size;
        }
        runElement = runElement->next;
    }
    if (blockVal == 0)
    {
        printf("Belegte Bloecke: %i\t(%i Byte / %.2lf %%)\n", tempCnt, tempSize, (double)((100.00 * (double)tempSize) / (double)heapSize));
    }
    else
    {
        printf("Freie Bloecke:   %i\t(%i Byte / %.2lf %%)\n", tempCnt, tempSize, (double)((100.00 * (double)tempSize) / (double)heapSize));
    }
}

void printBlock()
{
    if (header == NULL || header->first == NULL)
        return;

    LE *runElement = header->first;
    if (runElement == NULL)
        return;
    while (runElement != NULL)
    {
        if (runElement->block.free == 0)
        {
            printf("0x%08I64x\t%i\tbelegt\t%s\n", runElement->block.startAdr, runElement->block.size, runElement->block.name);
        }
        else
        {
            printf("0x%08I64x\t%i\tfrei\t%s\n", runElement->block.startAdr, runElement->block.size, runElement->block.name);
        }
        runElement = runElement->next;
    }
}

void mmterm()
{
    LE *runElement = header->first;
    LE *nextElement = NULL;
    while (runElement != NULL)
    {
        nextElement = runElement->next;
        free(runElement);
        runElement = nextElement;
    }
    free(header);
    free(heap);

    heapSize = 0;
    heap = NULL;
    header = NULL;
    return;
}

//
void mmfree(char *delAdr)
{
    if (header == NULL)
        return;
    LE *delElement = NULL;
    LE *neighbourElement = NULL;
    delElement = findAddress(delAdr);
    //prüfen ob Element gefunden wurde
    if (delElement == NULL)
        return;
    if (header->cnt == 1 && header->first->block.free == 1)
        return;
    if (header->cnt == 1 && header->first->block.free == 0)
    {
        header->first->block.free = 1;
        strcpy(header->first->block.name, "-");
        return;
    }

    //wenn zu löschendes Element am Anfang ist
    if (delElement == header->first)
    {
        //Nachbar Block ist belegt
        if (delElement->next->block.free == 0)
        {
            //nur Werte zurück setzen da next belegt ist
            delElement->block.free = 1;
            strcpy(delElement->block.name, "-");
            //size und startAdr bleiben gleich
        }
        //Nachbar Block ist frei
        else
        {
            //Blöcke zusammenführen
            neighbourElement = delElement->next;
            delElement->block.free = 1;
            strcpy(delElement->block.name, "-");
            delElement->block.size = delElement->block.size + neighbourElement->block.size;

            if (neighbourElement->next == NULL)
            {
                //free und den Ptr von delElement auf NULL
                free(neighbourElement);
                delElement->next == NULL;
                header->cnt--;
            }
            else
            {
                //Ptr setzen und free aufrufen
                delElement->next = neighbourElement->next;
                neighbourElement->next->prev = delElement;
                free(neighbourElement);
                header->cnt--;
            }
        }
    }
    //wenn zu löschendes Element am Ende ist
    else if (delElement == header->last)
    {
        //Nachbar Block ist belegt
        if (delElement->prev->block.free == 0)
        {
            //nur Werte zurück setzen da prev belegt ist
            delElement->block.free = 1;
            strcpy(delElement->block.name, "-");
            //size und startAdr bleiben gleich
        }
        //Nachbar Block ist frei
        else
        {
            //Blöcke zusammenführen
            neighbourElement = delElement->prev;
            neighbourElement->block.size = neighbourElement->block.size + delElement->block.size;
            free(delElement);
            neighbourElement->next = NULL;
            header->cnt--;
            header->last = neighbourElement;
        }
    }
    //wenn zu löschendes Element dazwischen ist
    else
    {
        //wenn beide Nachbarn belegt sind
        if (delElement->prev->block.free == 0 && delElement->next->block.free == 0)
        {
            strcpy(delElement->block.name, "-");
            delElement->block.free = 1;
        }
        //linker Nachcbar frei | rechter Nachbar Belegt -> hinzufügen Ptr umhängen und freigeben
        else if (delElement->prev->block.free == 1 && delElement->next->block.free == 0)
        {
            delElement->prev->block.size = delElement->prev->block.size + delElement->block.size;
            delElement->prev->next = delElement->next;
            delElement->next->prev = delElement->prev;
            free(delElement);
            header->cnt--;
        }
        //linker Nachbar belegt | rechter Nachbar Belegt -> hinzufügen und Last prüfen
        else if (delElement->prev->block.free == 0 && delElement->next->block.free == 1)
        {
            delElement->block.free = 1;
            strcpy(delElement->block.name, "-");
            delElement->block.size = delElement->block.size + delElement->next->block.size;
            if (delElement->next == header->last)
            {
                //header->last neu setzen
                header->last = delElement;
                free(delElement->next);
                delElement->next = NULL;
                header->cnt--;
            }
            else
            {
                delElement->prev->next = delElement->next;
                delElement->next->prev = delElement->prev;
                free(delElement);
                header->cnt--;
            }
        }
        //beide Nachbarn sind frei
        else
        {
            delElement->prev->block.size = delElement->prev->block.size + delElement->block.size + delElement->next->block.size;
            if (delElement->next == header->last)
            {
                delElement->prev->next = NULL;
                free(delElement->next);
                header->cnt--;
                free(delElement);
                header->cnt--;
            }
            else
            {
                delElement->prev->next = delElement->next->next;
                delElement->next->next = delElement->prev;
                free(delElement->next);
                header->cnt--;
                free(delElement);
                header->cnt--;
            }
        }
    }
}

LE *findAddress(char *findAdr)
{
    if (header->first == NULL || header == NULL || findAdr == NULL)
        return NULL;

    LE *checkElement = header->first;
    if (checkElement == NULL)
        return NULL;
    while (checkElement != NULL)
    {
        if (checkElement->block.startAdr == findAdr)
        {
            return checkElement;
        }
        checkElement = checkElement->next;
    }
    return NULL;
}

void mmrename(char *renameAdr, char *newValue)
{
    if (renameAdr == NULL || strlen(newValue) <= 0)
        return;
    if (header == NULL)
        return;
    LE *renameElement = NULL;
    renameElement = findAddress(renameAdr);
    if (renameElement == NULL)
        return;
    if (renameElement->block.free == 0)
    {
        strcpy(renameElement->block.name, newValue);
    }
}