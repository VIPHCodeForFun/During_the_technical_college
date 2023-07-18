/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #                   
#README:                                                                     
#
 Besonders angenehm für den Menschen ist der Bereich zwischen 500 und 4.000 Hertz.
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <windows.h>

int main()
{
    int i = 0;
    int s = 1;
    printf("BEEEEEP");
    // (37 32767 Hz , millisekond)
    /*for (i = 500; i < 4000; i = i + 100)
    {
        Beep(4000 - i, 50);
    }
    */
    Beep(500, 5);
    Beep(1000, 5);
    Beep(500, 5);
    Beep(500, 5);
    Beep(1000, 5);
    Beep(500, 5);
    Beep(500, 5);
    Beep(1000, 5);
    Beep(500, 5);
    if (s == 1)
    {
        for (i = 500; i < 1000; i = i + 100)
        {
            Beep(i, 100);
        }
    }

    return 0;
}
