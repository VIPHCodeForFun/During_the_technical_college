/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #                   
#README:                                                                     
#
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> //= rand() % 10 + 1 = 0 bis 10 random nr
#include <time.h>   // for int mashup(int check[]);

int mashup(int array[]);

int main()
{
    srand(time(NULL)); // sonst kommen immer die Gleichen zahlen!!
    int test[10];
    mashup(test);
    printf("\n\n");
    for (int t = 0; t < 10; t++)
    {
        printf("%d ", test[t]);
    }

    return 0;
}

//needs #include <stdlib.h> //= rand() % 10 + 1
int mashup(int check[])
{
    int count = 0;
    //setz random nr in the check array from [0 to 10]
    for (int c = 0; c < 10; c++)
    {
        check[c] = rand() % 10;
        printf("\n%d", check[c]);
    }
    //Checks if a number is double and switches it if it is with a new random nr
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (check[i] == check[j])
            {
                count++;
            }
        }
        if (count != 1)
        {
            check[i] = rand() % 10;
            count = 0;
            i--;
        }
        else
        {
            count = 0;
        }
    }
    return 0;
}
