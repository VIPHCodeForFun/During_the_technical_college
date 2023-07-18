QUELLE://  https://www.c-howto.de/tutorial/zeiger/


Unsere Datenmengen liegen im Speicher und haben eine Adresse.Ein Zeiger „zeigt“ auf die Menge,
indem er lediglich die Adresse der Menge speichert.Wenn wir dann einer Funktion unsere Datenmenge überliefern möchten,
teilen wir ihr lediglich mit dem Zeiger die Adresse mit.Die Datenmenge wird somit nicht transportiert,
stattdessen greift die Funktion über die Adresse auf die Daten zu.Diese Datenmengen werden durch Variablen repräsentiert.Ein Zeiger speichert also nur die Adresse einer anderen Variablen und leitet somit die Anfrage auf einen Wert weiter.*


/*int zahl = 7; // normale Variable

int *zeiger; //iniz Zeiger int *zeiger= NULL; währe schöner (zeiger zeigt auf "0")

zeiger = &zahl; // setzt den Pointer auf die Adresse der Variable

printf("Zeiger-Wert: %d\n", *zeiger);
gibt den Wert aus von der Variable auf die der Zeiger zeigt

 
