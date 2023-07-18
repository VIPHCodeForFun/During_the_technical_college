/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        # Hello                 12.11.2020       
#README:                                                                     
#
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

int recr(int i)
{
    if (i == 1)
    {
        printf("#");
        return 1;
    }
    else
    {
        printf("#");
        return 1 + recr(i - 1);
    }
}
int main()
{
    int i = 5;

    printf("%d", recr(i));

    return 0;
}
