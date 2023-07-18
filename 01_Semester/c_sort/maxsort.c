/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #                   
#README:                                                                     
# Selektionsort  MAXSORT

Suche Das größte Element und tausche die Position mit  dem ersten 

*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

void pstop();
int printstring(int str[], int leng);

int main()
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
    int i = 0, j = 0;
    int swarp = 0, big = 0;
    int leng = 10;

    for (i = 0; i < leng; i++)
    {
        for (j = i; j < leng; j++)
        {
            if (big < Array[j])
            {
                big = Array[j];
                Array[j] = Array[i];
                Array[i] = big;
            }
        }
        big = 0;
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
//int printstring (String_result)
int printstring(int str[], int leng)
{
    for (int i = 0; i < leng; i++)
    {
        printf("\n|%d|", str[i]);
    }
    return 0;
}