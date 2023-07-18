/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #                   
#README:                                                                     
#
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
int main()
{
    int array[] = {5, 6, 5, 4, 5, 7, 19};
    int save = 0;

    printf("%d  %d\n", array[5], array[2]);

    //Tausche array[5] und array[2]
    save = array[5];
    array[5] = array[2];
    array[2] = save;

    printf("%d  %d\n", array[5], array[2]);

    return 0;
}
