
/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #snake_v0.1.c                  
#README:                                                                     
#   Basis: snake_v0.0.c wird mittels einer mehr DIMENSIONALEN MATRIX visualisiert
    Keine Printf(mehr)
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#define DIM 20

void pstop();
void emptymatrix(char matrix[DIM][DIM], int len);
void printmatrix(char matrix[DIM][DIM], int len);
void surrounding(int len);

int main()
{
    char feld[DIM][DIM];
    int len = DIM;

    int y = 3, x = 3; //Startwert der Schlange
    printf("\n########################\n#         Snake        #\n#   Press any Button   #\n########################");

    while (y < DIM + 1 && y > 0 && x > 0 && x < DIM)
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
        //system("cls"); // löscht die console
        emptymatrix(feld, len);
        feld[y][x] = 'O';
        //Ausgabe
        printf("\n         SNAKE        \n");
        printf("X  x=%d y=%d   X\n", x, y);
        surrounding(len); //Top
        printmatrix(feld, len);
        surrounding(len); //bottom
    }

    pstop();

    return 0;
}

void pstop()
{
    printf("\n########################\n# GAME OVER  push ENTER #\n########################");
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
FutterPunkt einfügen + Zähler
Schlange muss größer werden
eingabe Ohne ENTER eventuell eine lib suchen 
*/
