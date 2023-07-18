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

int main()
{
    //Erzeuge einen Thread mit dem namen...
    pthread_t thread; // Initialisieren

    //Springe in den Thread mit dem Namen.... start_point, &Nummer); Kann der Funkton Parameter übergeben.
    pthread_create(&thread, NULL, start_point, NULL);

    Sleep(1000);
    printf("Main Programm 1 Thread\n");

    // Warte bis beide Funtionen Fertig sind
    pthread_join(thread, NULL);
    pthread_exit(thread); // Beendet den Thread
    return 0;
}

void *start_point(void *value)
{
    //Sleep(1000);
    printf("Second Programm 2 Thread\n");

    return NULL;
}