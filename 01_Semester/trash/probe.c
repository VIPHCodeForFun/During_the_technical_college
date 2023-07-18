#include <stdio.h>
#include <string.h>

int funktion(char string[3][3], int spalte, int zeile, char zeichen);

int main()
{
    char text[3][3] = {"tes", "tzu", "aes"};
    int zahl = 0;
    zahl = funktion(text, 3, 3, 't');
    printf("%d", zahl);
    return 0;
}
int funktion(char string[3][3], int spalte, int zeile, char zeichen) //       ||  ||  ||
{
    int i = 0;
    int j = 0;
    int sum = 0;

    for (i = 0; i < spalte; i++)
    {
        for (j = 0; j < zeile; j++)
        {
            if (string[i][j] == zeichen)
                sum = sum + 1;
        }
    }

    return sum;
}