/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #woerterbuch.c         #22.11.2020                   
#README:                                                                     
#
Erstellen Sie ein Programm für ein interaktives Deutsch-Englisch
Wörterbuch/Lerntrainer. Die Vokabeln speichern Sie dabei in zwei konstanten,
globalen String-Arrays mit den Namen deutsch und englisch.
Zum funktionalen Test ihres Programms reichen einige wenige Vokabeln natürlich aus.
Belegen Sie die Arrays deutsch und englisch mit sinnvollen Inhalten
(zum Testen reichen ca. 10 Vokabeln) und fragen Sie den Benutzer nun nach dem
jeweils korrekten englischen Begriff für ein deutsches Wort ab. Erstellen
Sie dabei nach jeder Runde (alle Vokabeln abgefragt) eine Ergebnis-Statistik
(Anzahl/Anteil der richtigen und falschen Vokabeln).

(a) Erweitern Sie ihr Programm so, dass die Vokabeln in zufälliger Reihenfolge
abgefragt werden. Dazu können Sie die Funktion int rand() aus stdlib.h benutzen.

(b) Erweitern Sie ihr Programm so, dass die Richtung der Abfrage ebenfalls für jede
neue Vokabel zufällig gewählt wird, d.h. deutsch → englisch oder englisch → deutsch
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h> //strcmp(english[i], eingabe)
#include <stdlib.h> //= rand() % 10 + 1 = 0 bis 10 random nr
#include <time.h>   // for int mashup(int check[]);

int mashup(int check[]); //random Nr only once!
void pstop();

char german[10][10] = {"Null", "Eins", "Zwei", "Drei", "Vier", "Fuenf", "Sechs", "Sieben", "Acht", "Neun"};
char english[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
    char eingabe[10]; //Eingabe mit der wird verglichen
    int i = 0;        // für die FOR
    int true = 0;     // für sie Statistik
    int false = 0;    // für sie Statistik
    int random2 = 0;  // Englisch nach Deutsch
    int random10[10]; // Reinfolge

    srand(time(NULL));

    mashup(random10); // vergiebt 0 bis 9 gemischt in das Array random10

    for (i = 0; i < 10; i++)
    {
        random2 = rand() % 2; // random 0 or 1

        if (random2 == 0)
        {
            printf("\n%d Schreiben sie \"%s\" in Englisch bestaetigen mit ENTER\n:   ", i, german[random10[i]]);

            scanf("%s", eingabe);

            if (strcmp(english[random10[i]], eingabe) == 0)
            {
                printf(" #### Richtig du Lauser #### ");
                true ++;
            }
            else
            {
                printf(" #### Leider Falsch #### \n #### richtig waer \"%s\" ####  ", english[random10[i]]);
                false ++;
            }
        }

        else
        {
            printf("\n%d Schreiben sie \"%s\" in Deutsch bestaetigen mit ENTER\n:   ", i, english[random10[i]]);

            scanf("%s", eingabe);

            if (strcmp(german[random10[i]], eingabe) == 0)
            {
                printf(" #### Richtig du Lauser #### ");
                true ++;
            }
            else
            {
                printf(" #### Leider Falsch #### \n #### richtig waer \"%s\" ####  ", german[random10[i]]);
                false ++;
            }
        }
    }
    printf("\n #### Statistik #### \nRICHTIG\twaren\t: %d Woerter\nFALSCH\twaren\t: %d Woerter", true, false);
    pstop();
    return 0;
}
void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}

//needs #include <stdlib.h> //= rand() % 10 + 1
//needs #include <time.h>
int mashup(int check[])
{
    int count = 0;
    //setz random nr in the check array from [0 to 10]
    for (int c = 0; c < 10; c++)
    {
        check[c] = rand() % 10;
        //printf("\n%d", check[c]);
    }
    //Checks if a number is double and switches it if it is with a new random nr
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (check[i] == check[j])
            {
                count++;
            }
        }
        if (count != 1)
        {
            check[i] = rand() % 10;
            count = 0;
            i--;
        }
        else
        {
            count = 0;
        }
    }
    return 0;
}
