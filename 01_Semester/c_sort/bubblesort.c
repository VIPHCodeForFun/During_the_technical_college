// C:\Users\phili\Desktop\Algorithmen_und_Datenstruckturen\Hausaufgaben\3.Aufgabe
// Bubblesort Sortier Algorithmus
// bubblesort.c

#include <stdio.h>

void pstop();
int printstring(int str[], int leng);

int main(void)
{
    int Array[10];
    Array[0] = 3;
    Array[1] = 1;
    Array[2] = 8;
    Array[3] = 9;
    Array[4] = 10;
    Array[5] = 2;
    Array[6] = 4;
    Array[7] = 7;
    Array[8] = 6;
    Array[9] = 5;
    //////////////////////////////////////

    int leng = 10;
    int first = 0, second = 0, swap_f = 0, swap_s = 0, counter = 0, swap_counter = 1, index = 0;

    while (swap_counter > 0)
    {
        swap_counter = 0;
        index = 0;

        for (counter = 0; counter < 9; counter++)
        {
            first = Array[index];
            second = Array[index + 1];

            if (first > second) // Tauschen
            {
                swap_f = first;
                swap_s = second;
                Array[index] = swap_s;
                Array[index + 1] = swap_f;
                swap_counter = swap_counter + 1;
            }
            index = index + 1;
        }
    }

    printstring(Array, leng);
    pstop();
    return 0;
}

void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}

// String ausgeben
int printstring(int str[], int leng)
{
    for (int i = 0; i < leng; i++)
    {
        printf("\n|%d|", str[i]);
    }
    return 0;
}