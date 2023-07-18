/*////////////////////////////////////////////////////////////////////////////
#Author:    Philipp Vidmar            
#Semester:  2/2021                                       
#Programm:  C  
#README:                                                                     

ITSB-B: SWE Tutorium 01
Max Schirl
April 22, 2021
Aufgabe 1
In der ersten Einheit des Tutoriums beschäftigen wir uns mit dem Programmieren eines kleines
Glücksspiels, welches für zwei SpielerInnen ausgelegt ist. Beide SpielerInnen wählen eine
Zahl zwischen 1 und 100, danach wird vom Programm eine zufällige Zahl im eben genannten
Wertebereich ermittelt.
Außerdem sind vor Spielbeginn bestimmte Informationen zu Alter, Geschlecht und Name der
SpielerInnen anzugeben, welche im folgenden Format als Textdatei abgelegt werden:
Max Mustermann
28
Männlich
Erika Musterfrau
17
Weiblich
Diese Textdatei ist einzulesen, und die darin enthaltenen Informationen in eine geeignete Struktur
zu speichern. Die in der Textdatei festgelegten Spieler werden nach der Reihe aufgerufen,
um ihren Tipp abzugeben (bspw. per CLI), davor werden die SpielerInnen je nach Geschlecht
und Alter unterschiedlich begrüßt:
• "Guten Tag Herr <name>!" für erwachsene Männer.
• "Guten Tag Frau <name>!" für erwachsene Frauen.
• "Hallo <name>!" für Jugendliche unter 18 Jahren.
Gewonnen hat jene/r SpielerIn, der/die näher an der zufällig ausgewählten Zahl liegt. Bedenke,
dass auch der Fall eines Unentschiedens abzudecken ist und gib das Ergebnis des Glücksspiels
auf der Konsole aus.
///////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <string.h> //strcyp
#include <stdlib.h> //atoi
#include <time.h>   //time

struct personendaten
{
    char vname[100];
    char nname[100];
    int alter;
    char gender[100];
    int tipp;
};

void read_file(char *path, struct personendaten *p_player_1, struct personendaten *p_player_2);
int vote(struct personendaten *p_player);
void winner(struct personendaten *p_player_1, struct personendaten *p_player_2);

int main()
{
    //Erstellen von 2 struckts
    struct personendaten player_1;
    struct personendaten player_2;
    //erstellen von 2 Pointern die auf die structs zeigen. //Dienen zur übergabe an die Funktionen
    struct personendaten *p_player_1 = &player_1;
    struct personendaten *p_player_2 = &player_2;

    read_file("personen.txt", p_player_1, p_player_2);

    printf("Player 1\n%s%s%d\n%s", p_player_1->vname, p_player_1->nname, p_player_1->alter, p_player_1->gender);
    printf("Player 2\n%s%s%d\n%s\n", p_player_2->vname, p_player_2->nname, p_player_2->alter, p_player_2->gender);

    vote(p_player_1);
    vote(p_player_2);

    winner(p_player_1, p_player_2);

    return 0;
}
//liest die daten von dem File in die 2 Structs ein
void read_file(char *path, struct personendaten *p_player_1, struct personendaten *p_player_2)
{
    char buffer[100];
    int count = 0;
    struct personendaten *temp = p_player_1;
    FILE *filetemp;
    filetemp = fopen(path, "r");

    while (fgets(buffer, 100, filetemp) != NULL)
    {
        if (count == 0) //Zeile 1 Vormane
        {
            strcpy(temp->vname, buffer);
            count++;
        }
        else if (count == 1) //Zeile 2 Nachname
        {
            strcpy(temp->nname, buffer);
            count++;
        }
        else if (count == 2) //Zeile 3 Alter
        {
            temp->alter = atoi(buffer);
            count++;
        }
        else if (count == 3) //Zeile 4 Geschlecht
        {
            strcpy(temp->gender, buffer);
            temp = p_player_2; // eventuell Liste für mehr Spieler anlegen
            count = 0;
        }
    }
    fclose(filetemp);
}
int vote(struct personendaten *p_player)
{
    if (p_player->alter >= 18)
    {
        if (p_player->gender[0] == 'M')
        {
            printf("Guten Tag Herr %s\n", p_player->nname); //für erwachsene Männer
            printf("Bitte geben sie ihren Tipp ab:\n");
            scanf("%d", &p_player->tipp);
            fflush(stdin);
        }
        else
        {
            printf("Guten Tag Frau %s\n", p_player->nname); //für erwachsene Frauen
            printf("Bitte geben sie ihren Tipp ab:\n");
            scanf("%d", &p_player->tipp);
            fflush(stdin);
        }
    }
    else
    {
        printf("Hallo %s\n", p_player->vname); // für Jugendliche unter 18 Jahren
        printf("Bitte gib einen Tipp ab:\n");
        scanf("%d", &p_player->tipp);
        fflush(stdin);
    }
    return 0;
}

void winner(struct personendaten *p_player_1, struct personendaten *p_player_2)
{
    srand(time(NULL));
    int lucknumber = rand() % 100 + 1;
    int diffplayer1 = lucknumber - p_player_1->tipp;
    int diffplayer2 = lucknumber - p_player_2->tipp;
    printf("Die Glueckszahl war %d\n", lucknumber);

    if (diffplayer1 < 0)
    {
        diffplayer1 = (-1) * diffplayer1;
    }
    if (diffplayer2 < 0)
    {
        diffplayer2 = (-1) * diffplayer2;
    }
    printf("Player1 %d  Player2 %d\n", diffplayer1, diffplayer2);
    if (diffplayer1 < diffplayer2)
    {
        printf("GEWONNEN hat %s", p_player_1->nname);
    }
    else if (diffplayer1 > diffplayer2)
    {
        printf(" GEWONNEN hat %s", p_player_2->nname);
    }
    else if (diffplayer1 == diffplayer2)
    {
        printf("Unentschieden \n");
    }
}