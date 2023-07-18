/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #snake_v0.5.c                  
#README:                                                                     
#   Basis: snake_v0.4.c
    Kein ENTER für die Eingabe : dazu wird input_time.c verwendet!
    void move(int *vert, int *hori) wird verändert

    https://www.mikrocontroller.net/topic/241318
    Food darf nicht in der Schlange spawnen 
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> //= rand() % 10 + 1 = 0 bis 10 random nr

#include <stdint.h>  // void move(int *vert, int *hori, int *direction, int *timer);
#include <windows.h> // void move(int *vert, int *hori, int *direction, int *timer);

#define DIM 10 // Größe des FELDES zb 10x10

void pstop();
void move(int *vert, int *hori, int *direction, int *timer);
void emptymatrix(char matrix[DIM][DIM], int len);
void printmatrix(char matrix[DIM][DIM], int len);
void surrounding(int len);

int main()
{
    char feld[DIM][DIM]; //FELD
    int len = DIM;       //länge des Feldes

    int y = DIM / 2, x = DIM / 2; //Startwert der Schlange
    int direction = 3;            //start Right
    int timer = 100;              //geschwindigkeit

    int xsav[1000], ysav[1000]; // Speichert die Alte Position des Kopfes für die erste Position des Körpers
    int count = 0;              // Zum Speichern der Positionen
    int bit = 0;                //Die Schlange hat sich selbst gebissen

    int yf = 2, xf = 2; //Startwert Food
    int food = 0;       //Zähler für Food

    printf("\n########################\n#         Snake        #\n#   Press any Button   #\n########################");

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
            food++;
            //Random Food xf und yf
            xf = rand() % DIM; //Neue Zahl für Food x
            yf = rand() % DIM; //Neue Zahl für Food y
        }

        //////  EINFÜGEN
        feld[y][x] = 'O';   //Snake Kopf
        feld[yf][xf] = 'G'; //Food
        //einfügen des Körpers mit der Länge = food
        for (int i = 0; i < food; i++)
        {
            if (food > i)
            {
                feld[ysav[count - i]][xsav[count - i]] = 'o'; //Body
            }
        }
        //////  AUSGABE
        printf("\n         SNAKE        \n");
        printf("X  x=%d y=%d Food=%3d X\n", x, y, food);
        printf("X  x=%d y=%d move=%3d X\n", xsav[0], ysav[0], bit);
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
    printf("\n########################\n#    YOUR SCORE:%4d   #\n########################", food);
    pstop();

    return 0;
}
//Programm ENDE
void pstop()
{
    printf("\n########################\n# GAME OVER push ENTER #\n########################");
    fflush(stdin); // WIRD NOCH GETAUSCHT!!
    getchar();
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
Menü einfügen Starten und neu Starten mit belibigtaste
*/
