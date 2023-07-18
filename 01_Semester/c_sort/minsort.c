/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #                   
#README:                                                                     
# Selektionsort  MINSORT

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
    int smal = 2147483647; // Größst mögliche int Zahl
    int leng = 10;

    for (i = 0; i < leng; i++)
    {
        for (j = i; j < leng; j++)
        {
            if (smal > Array[j])
            {
                smal = Array[j];
                Array[j] = Array[i];
                Array[i] = smal;
            }
        }
        smal = 2147483647;
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