/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #snake_v0.7.c                  
#README:                                                                     
#   Basis: snake_v0.6.c
    Food darf nicht in der Schlange spawnen 
    ab jeweils 10 Punkten einen neuen Punkt einfügen der 5 Foodpunkte bringt und wenn er gegessen wird den Speed der Schlange erhöht
    xf yf umbenennen !
    Speicher übedenken
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> //= rand() % 10 + 1 = 0 bis 10 random nr

#include <stdint.h>  // void move(int *vert, int *hori, int *direction, int *timer);
#include <windows.h> // void move(int *vert, int *hori, int *direction, int *timer);

#define DIM 20 // Größe des FELDES zb 10x10

void guide();
void picsnake();
void move(int *vert, int *hori, int *direction, int *timer);
void emptymatrix(char matrix[DIM][DIM], int len);
void printmatrix(char matrix[DIM][DIM], int len);
void surrounding(int len);

int main()
{
    char eingabe = 'a';
    //////////////////INGAME/////////
    char feld[DIM][DIM]; //FELD
    int len = DIM;       //länge des Feldes

    int y = DIM / 2, x = DIM / 2; //Startwert der Schlange
    int direction = 3;            //start Right
    int timer = 100;              //geschwindigkeit

    int xsav[1000], ysav[1000]; // Speichert die Alte Position des Kopfes für die erste Position des Körpers
    int count = 0;              // Zum Speichern der Positionen
    int bit = 0;                //Die Schlange hat sich selbst gebissen

    int yf = 2, xf = 2;               //Startwert Food
    int food = 0;                     //Zähler für Food
    int yfs = DIM / 3, xfs = DIM / 3; //Startwert Boostfood
    int boostfood = 0;                //Zähler Boostfood
    //////////////////Menü/////////
    while (eingabe != 48)
    {

        system("cls"); // löscht die console
        printf("\n#X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X ");
        printf("\n#               SNAKE[v0.6]");
        printf("\n# YOUR  lasrt SCORE :[%4d]", food);
        printf("\n# Start   mit [2 und ENTER]");
        printf("\n# Guide   mit [1 und ENTER]");
        printf("\n# Beenden mit [0 und ENTER]\n");
        printf("\n#X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X ");
        picsnake();
        fflush(stdin); // WIRD NOCH GETAUSCHT!!
        eingabe = getchar();
        if (eingabe == 49)
        {
            guide();
        }
        if (eingabe == 50)
        {
            y = DIM / 2, x = DIM / 2;
            bit = 0;
            count = 0;
            food = 0;
            boostfood = 0;
            timer = 100;
            //////////////////INGAME/////////
            while (y < DIM && y + 1 > 0 && x + 1 > 0 && x < DIM && bit == 0)
            {
                xsav[count] = x; // Zum Speicher der Positionen
                ysav[count] = y;
                // Bewegung des SNAKEHEADS
                move(&y, &x, &direction, &timer); //& = addresse von x(y) für Zeiger move()

                //Schlannge wird gebissen
                for (int j = 0; j < food; j++)
                {
                    if (count > 3)
                    {
                        if (x == xsav[count - j] && y == ysav[count - j])
                        {
                            bit++;
                        }
                    }
                }
                system("cls"); // löscht die console
                emptymatrix(feld, len);

                //////Food Gefunden + neuer Food platz
                if (x == xf && y == yf)
                {
                    food = food + 1 + boostfood;
                    //Random Food xf und yf
                    xf = rand() % DIM; //Neue Zahl für Food x
                    yf = rand() % DIM; //Neue Zahl für Food y
                }
                //Boostfood
                if (x == xfs && y == yfs && food > boostfood * 10)
                {
                    boostfood++;
                    food = food + 2;
                    timer = timer * 0.95;
                    xfs = rand() % DIM;
                    yfs = rand() % DIM;
                }

                //////  EINFÜGEN
                feld[y][x] = 'O';   //Snake Kopf
                feld[yf][xf] = 'G'; //Food
                if (food > boostfood * 10)
                {
                    feld[yfs][xfs] = 'B'; //BoostFood
                }
                //einfügen des Körpers mit der Länge = food
                for (int i = 0; i < food; i++)
                {
                    if (food > i)
                    {
                        feld[ysav[count - i]][xsav[count - i]] = 'o'; //Body
                    }
                }
                //////  AUSGABE
                printf("# oooooSNAKEooooO [v0.6] Points=[%4.d]\n", food);
                surrounding(len); //Top
                printf("\n");     // Fehler da sonst eine Reihe verschoben ist ! :D
                printmatrix(feld, len);
                surrounding(len); //bottom
                count++;
                if (count > 900)
                {
                    count = 800; //für den Fall das die Schlaknge größer als der Positionsspeicher wird (1000)
                }
            }
            printf("\n");
            surrounding(len);
            printf("\n# GAME OVER push ENTER SCORE: [%4d]#\n", food);
            surrounding(len);
            fflush(stdin); // WIRD NOCH GETAUSCHT!!
            getchar();
        }
    }
    return 0;
}
//Anleitung
void guide()
{
    system("cls"); // löscht die console
    printf("\n#X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X ");
    printf("\n#               SNAKE[v0.6] by Philipp Vidmar");
    printf("\n# Steuerung: ");
    printf("\n# Die Pfeiltsten werden zum Steuern der Schlange verwendet");
    printf("\n# Ziel:");
    printf("\n# Fange mit der Schlange so viele [G] Maeuse und [B] Boosts wie moeglich, ");
    printf("\n# je mehr [B] du gefressen hast desto mehr Punkte bekommst du fuer deine [G].");
    printf("\n# Pass auf! Für alle [B] wird deine Schlange schneller! ");
    printf("\n# Beisse nicht deinen eigernen Schwanz und nicht in die Wand ");
    printf("\n#");
    printf("\n# zurück zum Hauptmenue gehts mit [ENTER]");
    printf("\n#X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X ");
    fflush(stdin); // WIRD NOCH GETAUSCHT!!
    getchar();
}

//Schlangenbild
void picsnake()
{
    printf("\nX                $$_$$");
    printf("\nX              $(.)$(.)$$$");
    printf("\nX           $$$$_____$$___$");
    printf("\nX          $_______________$");
    printf("\nX          $__________$_____$");
    printf("\nX           $$_______$$$$___$");
    printf("\nX   $    $$$_$$$___$$   $___$");
    printf("\nX    $  $$       $$$    $___$");
    printf("\nX  $$$$$                $___$");
    printf("\nX                     $$___$$");
    printf("\nX              $$$$$$$____$$");
    printf("\nX            $$$__________$$");
    printf("\nX          $$__________$$$$");
    printf("\nX         $_______$$$$$$$");
    printf("\nX        $_______$              $");
    printf("\nX       $_______$              $$");
    printf("\nX      $_______$$            $$$$");
    printf("\nX      $_______$$$        $$$$___$");
    printf("\nX      $________$$$     $$_______$");
    printf("\nX      $________$$$$$$$$$$$$____$");
}
//Bewegung A S D W
void move(int *vert, int *hori, int *direction, int *timer)
{
    uint16_t left_pressed;
    uint16_t right_pressed;
    uint16_t up_pressed;
    uint16_t down_pressed;

    left_pressed = GetAsyncKeyState(VK_LEFT);
    right_pressed = GetAsyncKeyState(VK_RIGHT);
    up_pressed = GetAsyncKeyState(VK_UP);
    down_pressed = GetAsyncKeyState(VK_DOWN);

    if (left_pressed || right_pressed || up_pressed || down_pressed)
    {
        if (left_pressed)
        {
            (*hori)--;
            *direction = 1;
        }
        if (right_pressed)
        {
            (*hori)++;
            *direction = 2;
        }
        if (up_pressed)
        {
            (*vert)--;
            *direction = 3;
        }
        if (down_pressed)
        {
            (*vert)++;
            *direction = 4;
        }
    }
    else
    {
        if (*direction == 1)
        {
            (*hori)--; // go left
        }
        if (*direction == 2)
        {
            (*hori)++; // go right
        }
        if (*direction == 3)
        {
            (*vert)--; // go up
        }
        if (*direction == 4)
        {
            (*vert)++; //go down
        }
    }
    Sleep(*timer); //Zeit zum warten 1000 = 1sek
}

// Matrix ausgeben
// printfmatrix(int matrix[down][right])
void printmatrix(char matrix[DIM][DIM], int len)
{
    for (int y = 0; y < len; y++)
    {
        printf("X");
        for (int x = 0; x < len; x++)
        {
            printf("%c ", matrix[y][x]);
        }
        printf("X\n");
    }
    return;
}
// Matrix Leeren
// emptymatrix(int matrix[down][right], [leng])
void emptymatrix(char matrix[DIM][DIM], int len)
{
    for (int y = 0; y < len; y++) //down
    {
        for (int x = 0; x < len; x++) //right
        {
            matrix[y][x] = ' ';
        }
    }
    return;
}
void surrounding(int len)
{
    for (int i = 0; i < len + 1; i++)
    {
        printf("X ");
    }
    return;
}

/* Offen
Score mit Namen Speichern :) und ausgeben an welchen Platz man gelandet ist 
Power up Spiegeln des Spielfaldes :D bewegungsrichtung !
*/
