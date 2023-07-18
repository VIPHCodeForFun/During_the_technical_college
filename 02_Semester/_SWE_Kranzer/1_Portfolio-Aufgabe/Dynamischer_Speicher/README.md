QUELLE:// https://www.c-howto.de/tutorial/arrays-felder/speicherverwaltung/

Speicherverwaltung
In den bisherigen Kapiteln haben wir Felder deklariert, bei denen die Größe zur Compilezeit bereits feststand. Oftmals ist die wirklich benötigte Größe eines Feldes erst später zur Laufzeit des Programmes bekannt. Da es nicht sehr effizient ist, immer den größtmöglichen Speicher zu reservieren, gibt es die dynamische Speicherverwaltung.

Hier nochmal die Deklaration eines Feldes array1 mit fixer Größe, das exakt 100 Integer-Werte speichern kann. Darunter sehen wir den Versuch ein Feld array2 zu erstellen und die Größe von einer Variable size abhängig zu machen. Prinzipiell muss der Wert für die Größe bei der Deklaration eines Feldes fest und unveränderbar sein. Deshalb kann die Größe eigentlich nicht durch eine Variable bestimmt werden. Es gibt aber mittlerweile schlaue Compiler, die das erlauben, sogar wenn size durch eine Benutzereingabe zur Laufzeit gesetzt wird. Es wird aber absolut davon abgeraten, diese Variante zu wählen, da das Programm sonst möglicherweise nicht auf anderen Systemen läuft.

Dynamische Speicherverwaltung
Für die folgenden Funktionen zur dynamischen Speicherreservierung wird eine neue Bibliothek stdlib.h benötigt. Zudem sehen wir einen neuen Datentyp size_t. Dieser ist vom Typ long int und wird für die Angabe einer Datengröße in Byte verwendet. Die Funktion sizeof liefert bei Übergabe eines Datentyps wie int dessen benötigte Speichergröße in Byte. Der Datentyp des Rückgabewertes ist size_t.

Speicher reservieren mit malloc
Mit Memory Allocation reservieren wir zur Laufzeit des Programms auf sichere Art Speicherplatz, z.B. für Felder. Mit dem Parameter size wird die Größe des Speicherbedarfs in Byte übergeben. Der Rückgabewert ist ein void-Zeiger auf den Anfang des Speicherbereichs oder ein NULL-Zeiger, wenn kein freier Speicher mehr zur Verfügung steht. Der void-Zeiger soll aussagen, dass der Datentyp des belegten Speicherbereichs unbekannt ist.

In diesem Beispielprogramm hat der Benutzer durch eine Tastatureingabe die Möglichkeit, die Array-Größe zu bestimmen. Mit sizeof(int) erhalten wir die benötigte Größe zur Speicherung eines Integer-Wertes. Die Gesamtgröße ist abhängig von der Anzahl der Elemente, also wird die Einzelgröße noch mit der gewünschten Anzahl multipliziert. Da malloc einen void-Zeiger liefert, wir in diesem Fall aber einen int-Zeiger haben, casten wir die Rückgabe mit (int *). Das Casten ist nicht unbedingt notwendig, da der void-Zeiger automatisch in den richtigen Typ transformiert wird. Es ist jedoch sauberer und erleichtert die Arbeit, wenn man den Code später in C++ Projekten verwenden möchte.

Speicher reservieren mit calloc
Mit Cleared Memory Allocation wird ebenfalls Speicher reserviert, allerdings nicht nach Bytes, sondern nach Elementen. Der erste Parameter bestimmt die Anzahl der Elemente, der zweite die Größe eines Elementes. Im Prinzip kein großer Unterschied zu malloc, nur dass calloc alle Speicherstellen mit 0 initialisiert. malloc lässt den Speicherinhalt unverändert. Die Rückgabewerte sind identisch zu malloc.

Speicher freigeben mit free
Wenn Speicher reserviert wurde, sollte er tunlichst auch wieder freigegeben werden, sobald er nicht mehr benötigt wird. Wird regelmäßig Speicher reserviert, ohne ihn wieder freizugeben, bringt man eventuell die Kapazitäten zum Erschöpfen. Ist dadurch der Speicher komplett belegt, werden die Daten auf die Festplatte ausgelagert, was viel Zeit in Anspruch nimmt.
*   free kann nur Speicher freigeben, welcher mit malloc oder calloc reserviert wurde
*   free kann nur Speicher freigeben, welcher vorher noch nicht freigegeben wurde
