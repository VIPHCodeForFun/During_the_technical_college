

#include <stdio.h>

#define DIM 10

void emptymatrix(char matrix[DIM][DIM], int len);
void printmatrix(char matrix[DIM][DIM], int len);

int main()
{
    char feld[DIM][DIM];
    int len = DIM;

    y = 3, x = 3; //Startwert der Schlange

    for (i = 0;)
        char eingabe;
    int move = 0;
    scanf("%c", &eingabe);
    printf("%c", eingabe);
    move = eingabe;
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
        y--;
    }
    if (move == 119) //w
    {
        y++;
    }

    emptymatrix(feld, len);

    feld[y][x];

    //Ausgabe
    printmatrix(feld, len);

    system("cls"); // löscht die console

    return 0;
}

// Matrix ausgeben
// printfmatrix(int matrix[down][right])
void printmatrix(char matrix[DIM][DIM], int len)
{
    for (int y = 0; y < len; y++)
    {
        for (int x = 0; x < len; x++)
        {
            printf("%c", matrix[y][x]);
        }
        printf("\n");
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