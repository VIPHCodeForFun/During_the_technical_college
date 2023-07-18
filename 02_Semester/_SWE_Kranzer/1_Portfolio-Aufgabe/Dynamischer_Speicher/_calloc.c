//Cleared Memory Allocation calloc

/*
Speicher reservieren mit calloc
Mit Cleared Memory Allocation wird ebenfalls Speicher reserviert, 
allerdings nicht nach Bytes, sondern nach Elementen. 
Der erste Parameter bestimmt die Anzahl der Elemente, der zweite die Größe eines Elementes. 
Im Prinzip kein großer Unterschied zu malloc, nur dass calloc alle Speicherstellen mit 0 initialisiert. 
malloc lässt den Speicherinhalt unverändert. Die Rückgabewerte sind identisch zu malloc.

Speicher freigeben mit free
Wenn Speicher reserviert wurde, sollte er tunlichst auch wieder freigegeben werden, sobald er nicht mehr benötigt wird. 
Wird regelmäßig Speicher reserviert, ohne ihn wieder freizugeben, bringt man eventuell die Kapazitäten zum Erschöpfen. 
Ist dadurch der Speicher komplett belegt, werden die Daten auf die Festplatte ausgelagert, was viel Zeit in Anspruch nimmt.
*   free kann nur Speicher freigeben, welcher mit malloc oder calloc reserviert wurde
*   free kann nur Speicher freigeben, welcher vorher noch nicht freigegeben wurde
*/
#include <stdio.h>
#include <stdlib.h>

//void *calloc(size_t n, size_t size);

int main()
{
    int size = 100;
    int *array;

    // Speicher reservieren
    array = (int *)calloc(size, sizeof(int));

    // Speicher freigeben
    free(array);

    //free kann nur Speicher freigeben, welcher mit malloc oder calloc reserviert wurde
    //free kann nur Speicher freigeben, welcher vorher noch nicht freigegeben wurde

    return 0;
}
