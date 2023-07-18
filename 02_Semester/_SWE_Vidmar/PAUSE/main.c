#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int get_time = atoi(argv[1]) * 1000 * 60;
    int time = 0;
    int space = 0;
    while (time < get_time)
    {
        if (i < time)
        {
            printf("#Rest(t) = %d Minuten\n", (get_time - time) / (1000 * 60));
            i = i + 1000 * 60;
        }
        if (space % 2 == 0)
        {
            printf("\n");
        }
        printf("#%s \n", argv[2]);
        Sleep(1000);
        time = time + 1000;
        space++;
    }
    printf("ENDE :D;");
    return 0;
}