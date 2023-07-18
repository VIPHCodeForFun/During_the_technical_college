
/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #snake_v0.2.c                  
#README:                                                                     
#   Basis: snake_v0.1.c FutterPunkt einfügen + Zähler
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> //= rand() % 10 + 1 = 0 bis 10 random nr

#define DIM 10

void pstop();
void emptymatrix(char matrix[DIM][DIM], int len);
void printmatrix(char matrix[DIM][DIM], int len);
void surrounding(int len);

int main()
{
    char feld[DIM][DIM];
    int len = DIM;
    int count = 0;      //Zähler für Food
    int y = 3, x = 3;   //Startwert der Schlange
    int yf = 6, xf = 6; //Startwert Food
    printf("\n########################\n#         Snake        #\n#   Press any Button   #\n########################");

    while (y < DIM && y + 1 > 0 && x + 1 > 0 && x < DIM)
    {
        char move;
        scanf("%c", &move);
        if (move == 97) //a
        {
            x--;
        }
        if (move == 100) //d
        {
            x++;
        }
        if (move == 115) //s
        {
            y++;
        }
        if (move == 119) //w
        {
            y--;
        }
        system("cls"); // löscht die console
        emptymatrix(feld, len);

        //////Food Gefunden + neuer Food platz
        if (x == xf && y == yf)
        {
            count++;
            //Random Food xf und yf
            xf = rand() % DIM; //Neue Zahl für Food x
            yf = rand() % DIM; //Neue Zahl für Food y
        }

        //////Einfügen
        feld[y][x] = 'O';   //Snake Kopf
        feld[yf][xf] = 'G'; //Food

        //////Ausgabe
        printf("\n         SNAKE        \n");
        printf("X  x=%d y=%d Food=%d  X\n", x, y, count);
        surrounding(len); //Top
        printf("\n");     // Fehler da sonst eine Reihe verschoben ist ! :D
        printmatrix(feld, len);
        surrounding(len); //bottom
    }
    printf("\n########################\n#    YOUR SCORE:%4d   #\n########################", count);
    pstop();

    return 0;
}
void pstop()
{
    printf("\n########################\n# GAME OVER push ENTER #\n########################");
    fflush(stdin);
    getchar();
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

Schlange muss größer werden
eingabe Ohne ENTER eventuell eine lib suchen 
*/
