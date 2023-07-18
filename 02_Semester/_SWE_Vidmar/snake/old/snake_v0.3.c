/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #snake_v0.3.c                  
#README:                                                                     
#   Basis: snake_v0.2.c Schlange muss größer werden 
Die Punkte x und Y  müssen gespeichert werden jeder Move löscht das letzte Element und fügt ein neues hinzu 
der Food Counter gibt die Länge an 
die Funktion: void move(int *vert, int *hori); wurde eingefügt damit die Main nicht mehr so voll ist 
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> //= rand() % 10 + 1 = 0 bis 10 random nr

#define DIM 5 // Größe des FELDES zb 10x10

void error();
void pstop();
void move(int *vert, int *hori);
void emptymatrix(char matrix[DIM][DIM], int len);
void printmatrix(char matrix[DIM][DIM], int len);
void surrounding(int len);

int main()
{
    char feld[DIM][DIM]; //FELD
    int len = DIM;       //länge des Feldes

    int y = 3, x = 3;           //Startwert der Schlange
    int xsav[1000], ysav[1000]; // Speichert die Alte Position des Kopfes für die erste Position des Körpers
    int count = 0;

    int yf = 2, xf = 2; //Startwert Food
    int food = 0;       //Zähler für Food

    printf("\n########################\n#         Snake        #\n#   Press any Button   #\n########################");

    while (y < DIM && y + 1 > 0 && x + 1 > 0 && x < DIM)
    {
        xsav[count] = x;
        ysav[count] = y;
        // Bewegung des SNAKEHEADS
        move(&y, &x); //& = addresse von x(y) für Zeiger move()

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
        /*if (food > 0)
        {
            feld[ysav[count]][xsav[count]] = 'o'; //Body
            if (food > 1)
            {
                feld[ysav[count - 1]][xsav[count - 1]] = 'o'; //Body
            }
            if (food > 2)
                feld[ysav[count - 2]][xsav[count - 2]] = 'o'; //Body
        }*/
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
        printf("X  x=%d y=%d          X\n", xsav[0], ysav[0], food);
        surrounding(len); //Top
        printf("\n");     // Fehler da sonst eine Reihe verschoben ist ! :D
        printmatrix(feld, len);
        surrounding(len); //bottom
        count++;
    }
    printf("\n########################\n#    YOUR SCORE:%4d   #\n########################", count);
    pstop();

    return 0;
}
//Wird nur zum Fehlersuchen verwended
void error()
{
    printf("ERRORERRORERRORERRORERRORERRORERROR");
    fflush(stdin); // WIRD NOCH GETAUSCHT!!
    getchar();
}
//Programm ENDE
void pstop()
{
    printf("\n########################\n# GAME OVER push ENTER #\n########################");
    fflush(stdin); // WIRD NOCH GETAUSCHT!!
    getchar();
}
//Bewegung A S D W
void move(int *vert, int *hori)
{
    char move = 0;

    fflush(stdin); // Kopf nicht mehr = Körper  WIRD NOCH GETAUSCHT!!
    scanf("%c", &move);
    if (move == 97) //a
    {
        (*hori)--; // INFO *hori-- würde mit Zeigern nicht funktionieren !! entwerder (*hori)-- oder --*hori
    }
    if (move == 100) //d
    {
        (*hori)++;
    }
    if (move == 115) //s
    {
        (*vert)++;
    }
    if (move == 119) //w
    {
        (*vert)--;
    }
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
Darf sich nicht selbst beissen 
eingabe Ohne ENTER eventuell eine lib suchen 
*/
