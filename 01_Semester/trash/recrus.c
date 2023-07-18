/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #                   
#README:                                                                     
#
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

void pstop();
int malzwei(int zahl);

int main()
{
    int zahl = 1;
    zahl = malzwei(zahl);
    printf("%d", zahl);

    pstop();
    return 0;
}

int malzwei(int zahl)
{
    if (zahl < 140000000)
    {
        printf("+");
        zahl = zahl + zahl;
        malzwei(zahl);
    }
    else
    {

        return zahl;
    }
}

void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}