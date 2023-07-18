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
    int vec_a[Vmax]{1, 2, 3};
    int vec_b[Vmax]{1, 2, 3};
    int vec_e[Vmax]{1, 2, 3};

    int a = 0;
    int b = 0;

    for (int i = 0; i < Vmax; i++)
    {
        a = 1;
        if (a > 3)
        {
            if (a % 3 == 0)
            {
                b = 0;
            }
            if (i % 3 == 1)
            {
                b = 1;
            }
            if (a % 3 == 2)
            {
                b = 2;
            }
        }

        a = i + b
                    vec_e[i] = (vec_a[a] * vec_b[a]) - (vec_a[+] * vec_b[a]);
        a++;
    }
}
return 0;
}
