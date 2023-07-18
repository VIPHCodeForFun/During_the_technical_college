/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #snake_v0.8.c                  
#README:                  
gcc snake_v0.8.c -lWinmm                                                   
#   Basis: snake_v0.7.c
    Score mit Namen Speichern :) und ausgeben an welchen Platz man gelandet ist 
    Food darf nicht in der Schlange spawnen 
    xf yf umbenennen !
    Speicher übedenken
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> //= rand() % 10 + 1 = 0 bis 10 random nr

#include <stdint.h>  // void move(int *vert, int *hori, int *direction, int *timer);
#include <windows.h> // void move(int *vert, int *hori, int *direction, int *timer);

#include <mmsystem.h> // Für die WAV Datei "Sound"
#include <pthread.h>  // für den Sound Thread

#define DIM 20 // Größe des FELDES zb 10x10
#define VERS 8

void *sound(void *value);
int score(int food, FILE *fp);
void guide();
void picsnake();
void move(int *vert, int *hori, int *direction, int *timer);
void emptymatrix(char matrix[DIM][DIM], int len);
void printmatrix(char matrix[DIM][DIM], int len);
void surrounding(int len);

//Consolenausgabe
HANDLE wHnd; // Handle to write to the console.

int main()
{

    //Consolenausgabe
    SetConsoleTitle("  SNAKE by Philipp V. "); // Name der CMD Console
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 42, 25}; //30
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    //Sound
    pthread_t thread_sound; // Initialisieren

    char eingabe = 'a'; //MENÜ
    //////////////////INGAME/////////
    char feld[DIM][DIM]; //FELD
    int len = DIM;       //länge des Feldes

    int y = DIM / 2, x = DIM / 2; //Startwert der Schlange
    int direction = 3;            //start Right
    int timer = 100;              //geschwindigkeit

    int xsav[10000], ysav[10000]; // Speichert die Alte Position des Kopfes für die erste Position des Körpers
    int count = 0;                // Zum Speichern der Positionen
    int bit = 0;                  //Die Schlange hat sich selbst gebissen

    int yf = 2, xf = 2;               //Startwert Food
    int food = 1;                     //Zähler für Food
    int yfs = DIM / 3, xfs = DIM / 3; //Startwert Boostfood
    int boostfood = 0;                //Zähler Boostfood
    int newscore = 0;                 //vergleicht den Score mit dem TxT score

    FILE *fp = NULL;
    //////////////////Menü/////////
    pthread_create(&thread_sound, NULL, sound, NULL);
    while (eingabe != 48)
    {
        system("cls"); // löscht die console
        newscore = score(food, fp);
        printf("\n#               SNAKE[v0.%d]", VERS);
        printf("\n# YOUR  lasrt SCORE :[%4d]", newscore);
        printf("\n# Start   mit [2 und ENTER]");
        printf("\n# Guide   mit [1 und ENTER]");
        printf("\n# Beenden mit [0 und ENTER]");
        printf("\n#X X X X X X X X X X X X X X X X X X X X X");
        picsnake();
        fflush(stdin); // WIRD NOCH GETAUSCHT!!
        eingabe = getchar();
        if (eingabe == 49)
        {
            guide();
        }
        if (eingabe == 50)
        {
            system("cls"); // löscht die console
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
                system("cls"); // löscht die console
                printf("# oooooSNAKEooooO [v0.%d] Points=[%4.d]\n", VERS, food);
                surrounding(len); //Top
                printf("\n");     // Fehler da sonst eine Reihe verschoben ist ! :D
                printmatrix(feld, len);
                surrounding(len); //bottom
                count++;
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
void *sound(void *value)
{
    int i = 0;
    while (i = 100)
    {
        PlaySound(TEXT("Kevin MacLeod.wav"), NULL, SND_LOOP);
    }
}

//Anleitung
void guide()
{
    system("cls"); // löscht die console
    printf("\n#X X X X X X X X X X X X X X X X X X X X X");
    printf("\n# SNAKE[v0.%d] by Philipp Vidmar", VERS);
    printf("\n# Steuerung: Die Pfeiltsten werden");
    printf("\n# zum Steuern der Schlange verwendet.");
    printf("\n# Ziel:");
    printf("\n# Fange mit der Schlange so viele [G](Maeuse)");
    printf("\n# und [B] Boosts wie moeglich,");
    printf("\n# je mehr [B] du gefressen hast desto mehr ");
    printf("\n# Punkte bekommst du fuer deine [G].");
    printf("\n# Pass auf! Für alle [B] wird deine ");
    printf("\n# Schlange schneller! ");
    printf("\n# Beisse nicht deinen eigernen Schwanz ");
    printf("\n# und nicht in die Wand ");
    printf("\n# zurück zum Hauptmenue gehts mit [ENTER]");
    printf("\n#X X X X X X X X X X X X X X X X X X X X X");
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
    printf("\nX  $$$$$              $$___$");
    printf("\nX              $$$$$$$____$$");
    printf("\nX            $$$__________$$");
    printf("\nX          $$__________$$$$");
    printf("\nX         $_______$$$$$$$");
    printf("\nX       $_______$              $$");
    printf("\nX      $_______$$            $$$$");
    printf("\nX      $_______$$$        $$$$___$");
    printf("\nX      $________$$$     $$_______$");
    printf("\nX      $________$$$$$$$$$$$$____$");
}
//Score
int score(int food, FILE *fp)
{
    int newscore = 0;
    char path[1000] = {"score.txt"};
    //Lesen aus einem .TXT FILE
    fp = fopen(path, "r"); // fp zeigt auf das FILE
    if (fp == NULL)
    {
        printf("Fehler beim Oeffnen der Datei");
    }
    else
    {
        printf("Datei wurde geoeffnet r!");
        fscanf(fp, "%d", &newscore);
        fclose(fp); // schließst das FILE wieder
    }

    //schreibe einen Neuen Score wenn er neue Größer ist oder nicht vorhanden
    if (food > newscore)
    {
        fp = fopen(path, "w"); // fp zeigt auf das FILE
        if (fp == NULL)
        {
            printf("Fehler beim Oeffnen der Datei");
        }
        else
        {
            printf("Datei wurde geoeffnet w!");
            //Löscht alles was in der Datei steht und fühgt den String hinzu
            fprintf(fp, "%d ", food);
            fprintf(fp, "Speicherung des Wertes\n");
            fclose(fp); // schließst das FILE wieder
            return food;
        }
    }
    return newscore;
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

Power up Spiegeln des Spielfaldes :D bewegungsrichtung !
*/
