/*
Schreiben Sie ein C-Programm, dass die BenutzerIn Zahlen eingeben lässt und die
Summe anschließend auf die Konsole (Terminal) ausgibt. Zusätzlich, soll eine zweite
beliebige Rechen-Operation, durchgeführt und ebenfalls ausgegeben werden. Die zweite
Ausgabe darf jedoch erst nach Tastendruck erfolgen.
*/

//gcc H_1.c ./a.exe

#include <stdio.h>

int main()
{
    int Eingabe1=0;
    int Eingabe2=0;
    int Summe=0;

    printf("Geben sie zwei int Zahlen ein die summiert werden sollen : \n");
    scanf("%d",&Eingabe1);   scanf("%d",&Eingabe2);
    Summe= Eingabe1 + Eingabe2;
    printf("Die Summe ist : %d\n",Summe);

    system("pause"); // Pausiert das System
    
    Summe = Summe *2 ;
    printf("\n2 mal die Summe ist : %d",Summe);

return 0;
}