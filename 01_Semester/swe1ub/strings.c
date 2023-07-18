
/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #strings.c                   
#README:                                                                     
#
ufgabe 3 (Strings)
Da es in C ebenfalls keinen eigenen Datentyp fuer Strings und deren Operationen gibt, 
muessen wir diese Funktionalitaet auch seblst abbilden 
(in der Praxis wuerden Sie natuerlich eine Bibliothek dafuer verwenden). Implementieren Sie dazu folgende Funktion:

(a) Eine Funktion palindrom(), welche prueft, ob ein uebergebener String ein
Palindrom ist oder nicht. Die Rueckgabe soll entweder als 1 („wahr“) oder 0
(„falsch“) erfolgen.
Ein Palindrom ist eine Zeichenkette, welche rueckwaerts die gleiche Zeichenfolge
wie vorwaerts ergibt! Denken Sie daran, dass Gross- und Kleinbuchstaben
verschiedene Werte in der ASCII-Tabelle haben (Sie duerfen Bibliotheksfunktionen verwenden) .
Beispiele sind:
Anna
neben
Lagerregal
Rentner
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h> // strlen

#define len 20

void pstop();
void strreverse(char str[], char result[]);
int palin(char str_a[], char str_b[]);
int palindrom(char str_a[], char str_b[]);

int main()
{
    char name[len] = "";
    char memory[len] = "";
    int result = 0;

    scanf("%s", name);
    result = palindrom(name, memory);
    printf("\nResult: %d", result);

    pstop();
    return 0;
}

void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}
void strreverse(char str[], char result[])
{
    int i = 0;
    int j = strlen(str);
    for (i = 0; i < strlen(str); i++)
    {
        result[i] = str[j - 1];
        j--;
    }
}

int palin(char str_a[], char str_b[])
{

    int i = 0;
    int len_a = strlen(str_a), len_b = strlen(str_b);
    if (len_a != len_b)
    {
        printf("NO PALINDROM\nThe two Words have not the same leng..");
        return 1;
    }
    for (i = 0; i < strlen(str_a); i++)
    {
        if (str_a[i] == str_b[i])
        {
        }
        else if (str_a[i] + 32 == str_b[i])
        {
        }
        else if (str_a[i] == str_b[i] + 32)
        {
        }
        else
        {
            return 0;
        }
    }
    return 1;
}
int palindrom(char str_a[], char str_b[])
{
    int i = 0;
    int j = strlen(str_a);
    for (i = 0; i < strlen(str_a); i++)
    {
        str_b[i] = str_a[j - 1];
        j--;
    }
    for (i = 0; i < strlen(str_a); i++)
    {
        if (str_a[i] == str_b[i])
        {
        }
        else if (str_a[i] + 32 == str_b[i])
        {
        }
        else if (str_a[i] == str_b[i] + 32)
        {
        }
        else
        {
            return 0;
        }
    }
    return 1;
}