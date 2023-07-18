
//Memory Allocation malloc

/*
Speicher reservieren mit malloc
Mit Memory Allocation reservieren wir zur Laufzeit des Programms auf sichere Art Speicherplatz, 
z.B. für Felder. Mit dem Parameter size wird die Größe des Speicherbedarfs in Byte übergeben. 
Der Rückgabewert ist ein void-Zeiger auf den Anfang des Speicherbereichs oder ein NULL-Zeiger, 
wenn kein freier Speicher mehr zur Verfügung steht. Der void-Zeiger soll aussagen, 
dass der Datentyp des belegten Speicherbereichs unbekannt ist.

Speicher freigeben mit free
Wenn Speicher reserviert wurde, sollte er tunlichst auch wieder freigegeben werden, sobald er nicht mehr benötigt wird. 
Wird regelmäßig Speicher reserviert, ohne ihn wieder freizugeben, bringt man eventuell die Kapazitäten zum Erschöpfen. 
Ist dadurch der Speicher komplett belegt, werden die Daten auf die Festplatte ausgelagert, was viel Zeit in Anspruch nimmt.
*   free kann nur Speicher freigeben, welcher mit malloc oder calloc reserviert wurde
*   free kann nur Speicher freigeben, welcher vorher noch nicht freigegeben wurde
*/
#include <stdio.h>
#include <stdlib.h>

//void *malloc(size_t size);

int main()
{
    int size = 0;
    int *array;

    printf("Array-Groesse eingeben: ");
    scanf("%d", &size);

    // Speicher reservieren
    array = (int *)malloc(size * sizeof(int));

    if (array != NULL)
    {
        printf("\nSpeicher ist reserviert\n");
    }
    else
    {
        printf("\nKein freier Speicher vorhanden.\n");
    }
    // Speicher freigeben
    free(array);
    return 0;
}
