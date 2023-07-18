/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #<pthread.h>                   
#README:                                                                     
#
 thread 1 = Hauptprogramm
 thread 2 = Parallelprogramm
 Mit dem Sleeptimer kann die Ausgabenreihenfolge verändert werden
 Die 2 Funktionen laufen Parallel :) 

*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <windows.h>

#include <pthread.h>

void *start_point(void *value);

int global = 0;
int main()
{
    //Erzeuge einen Thread mit dem namen...
    pthread_t thread; // Initialisieren

    //Springe in den Thread mit dem Namen.... start_point, &Nummer); Kann der Funkton Parameter übergeben.
    pthread_create(&thread, NULL, start_point, NULL);

    global = 0;
    for (int i = 0; i < 30; i++)
    {
        Sleep(1000);
        global++;
    }
    printf("   --Main Thread Programm--\n", global);

    // Warte bis beide Funtionen Fertig sind
    pthread_join(thread, NULL);
    pthread_exit(&thread); // Beendet den Thread
    return 0;
}

void *start_point(void *value)
{
    for (int i = 0; i < 30; i++)
    {
        Sleep(1000);
        printf("[%02d] Second_Thread Programm\n", global);
    }

    return NULL;
}