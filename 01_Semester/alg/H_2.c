/*Schreiben Sie ein C-Programm, dass einen String einliest und anschließend auf der
Konsole (Terminal) in umgedrehter Reihenfolge ausgibt.*/

// H_2.c
#include <stdio.h>
#include <string.h>

int main()
{
char Eingabe[100]= "  " ; //1). Wichtig string leer = " ";
int i=0;            
int j=0;
printf("    Hallo, ich bin der Verdreherautomat   \n");
printf("Gib mir ein Wort (max 100 Zeichen) zum verdrehen ein\n");
scanf("%s",&Eingabe);

j = strlen(Eingabe);  //2). strlen() ermittelt die Länge eines Strings

    for(i=0;i<strlen(Eingabe)+1;i++)   //3). strlen()+1 Sonst wird das Ergebniss um 1 abgechnitten 
                                       //3). Damit wird die Dunktion variabel abhängig von der String länge
    {
    printf("%c",*(Eingabe+j)); //0= Erster Beuchstabe 10 = letzter Buchstabe
    j-- ;
    }

return 0;
}

