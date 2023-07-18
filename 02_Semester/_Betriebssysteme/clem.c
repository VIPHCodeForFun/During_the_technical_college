#include <stdio.h>

int main()
{
    int zahl1 = 5;
    int zahl2 = 2;

    printf("CLEMENS ist Toll\n");

    for (int i = 0; i < 10; i++)
    {
        zahl1 = zahl1 + zahl2;
        printf("%d\n", zahl1);
    }

    return 0;
}