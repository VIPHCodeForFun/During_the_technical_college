#include <stdio.h>
#include <stdlib.h>

void str_to_d();

int main()
{
    int i = 0;
    char string[100] = {"3.500 12.66 1.027 220.0 88.93 "};
    double werte[100];
    str_to_d(werte, string);

    for (i = 0; i < 5; i++)
    {
        printf("%f\n", werte[i]);
    }

    return 0;
}
void str_to_d(double werte[100], char string[100])
{
    int i = 0;
    int j = 0;
    int k = 0;
    char number[20] = {0};

    while (string[i] != '\0')
    {
        number[j] = string[i];
        if (string[i] == ' ')
        {
            werte[k] = atof(number);

            i++;
            k++;
            j = 0;
        }
        else
        {
            i++;
            j++;
        }
    }
}
/*
int main()
{
    int i = 0;
    int j = 0;
    int k = 0;
    char string[100] = {"3.500\n12.66\n1.027\n220.0\n88.93\n"};
    char number[20] = {0};
    double werte[100];
    printf("String\n%s\n", string);

    while (string[i] != '\0')
    {
        number[j] = string[i];
        if (string[i] == '\n')
        {

            werte[k] = atof(number);
            //printf("%s\n", number);
            //printf("%f\n", werte[i]);
            i++;
            k++;
            j = 0;
        }
        else
        {
            i++;
            j++;
        }
    }
    for (i = 0; i < 5; i++)
    {
        printf("%f\n", werte[i]);
    }
    return 0;
}
*/