/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #                   
#README:                                                                   
#Aufgabe 1 (String-Funktionen)Wie wir wissen, sind Strings in ANSI-C nichts weiter als Arrays vom Typs char.
Um ein besseres Gefuehl fuer den Umgang mit Arrays zu bekommen,
sollen Sie eigene Implementierungen fuer folgende Funktionen aus string.h schreiben: 
(a) char* strcpy(char dest[],constchar src[])
(b) int strcmp(constchar str1[],constchar str2[])
(c) char* strcat(char dest[],constchar src[]) 
(d) char*strncat(char dest[],constchar src[], int n)
(e) char* strchr(constchar str[],int c)
(f) char* strstr(constchar s1[],constchar s2[])
Dabei ist char* die Adresse einer char-Variable im Speicher,
an welche wir mit dem Adressoperator & gelangen koennen. Das Schluesselwort const sagt aus,
dass das betreffende Argument nicht veraendert wird. Recherchieren Sie, welche Werte die 
Bibliotheksvarianten der Funktionen zurueckgeben und Programmieren Sie die entsprechende Programmlogik. 
Schreiben Sie ein Testprogramm, welche alle Funktionen mit verschiedenen Eingabeparametern aufruft.
Testen Sie ausserdem, was passiert, wenn der Ergebnis-Puffer zu klein ist.
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

char *strstr(char s1[], char s2[]);
char *strchr(char str[], int c);
char *strncat(char dest[], char src[], int n);
char *strcat(char dest[], char src[]);
int strcmp(char str1[], char str2[]);
char *strcpy(char dest[], char src[]);

int main()
{
    char worteins[50] = {"HOLZ"};
    char wortzwei[50] = {"HAUS"};
    char wortdrei[100] = {"Das ist ein Test string"};
    int kontrolle = 0;
    char *pointer = NULL;
    char *pointer2 = NULL;
    //strcpy(worteins, wortzwei);
    printf("%s\n", worteins);

    kontrolle = strcmp(worteins, wortzwei);
    printf("%d\n", kontrolle);

    pointer = strcat(worteins, wortzwei);
    printf("%s\n", worteins);

    pointer = strncat(worteins, wortzwei, 3);
    printf("%s\n", worteins);

    pointer = strchr(wortdrei, 'T');
    printf("%p\n", pointer);

    printf("TEST POINTER\n");
    pointer2 = &wortdrei[12];
    printf("%p\n", pointer2);
    printf("%c\n", *pointer2);

    pointer = strstr(wortdrei, "ein");
    printf("strstr Adresse %p\n", pointer);
    printf("strstr Wert %c\n", *pointer);

    printf("TEST POINTER\n");
    pointer2 = &wortdrei[12];
    printf("%p\n", pointer2);
    printf("%c\n", *pointer2);

    return 0;
}
/*Locate substring
Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
The matching process does not include the terminating null-characters, but it stops there.*/
char *strstr(char s1[], char s2[])
{
    int i = 0, j = 0, temp = 0, truex = 0;

    for (i = 0; s1[i] != '\0'; i++)
    {
        temp = i;
        for (j = 0; s2[j] != '\0'; j++)
        {
            if (s1[temp] != s2[j])
            {
                truex = 0;
                break;
            }
            truex++;
            temp++;
        }
        if (truex > 0)
        {
            return &s1[i];
        }
    }
    return NULL;
}

/*Locate first occurrence of character in string
Returns a pointer to the first occurrence of character in the C string str.
The terminating null-character is considered part of the C string. Therefore,
it can also be located in order to retrieve a pointer to the end of a string.
destination is returned or destination of c*/
char *strchr(char str[], int c)
{
    int i = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
        {
            return &str[i];
        }
    }
    return NULL;
}

/*Append characters from string
Appends the first num characters of source to destination, plus a terminating null-character.
If the length of the C string in source is less than num, only the content up to the terminating null-character is copied.
destination is returned.*/
char *strncat(char dest[], char src[], int n)
{
    int i = 0, j = 0;
    for (i = 0; dest[i] != '\0'; i++)
    {
    }
    for (j = 0; j < n; j++)
    {
        dest[i] = src[j];
        i++;
    }
    return &dest[0];
}

/*Concatenate strings
Appends a copy of the source string to the destination string.
The terminating null character in destination is overwritten by the first character of source,
and a null-character is included at the end of the new string formed by the concatenation of both in destination.
destination is returned.*/
char *strcat(char dest[], char src[])
{
    int i = 0, j = 0;
    for (i = 0; dest[i] != '\0'; i++)
    {
    }
    for (j = 0; src[j] != '\0'; j++)
    {
        dest[i] = src[j];
        i++;
    }
    return &dest[0];
}

/*Compare two strings
Compares the C string str1 to the C string str2.
This function starts comparing the first character of each string. If they are equal to each other, it continues with the following pairs 
until the characters differ or until a terminating null-character is reached.
This function performs a binary comparison of the characters. For a function that takes into account locale-specific rules, see strcoll.
destination is returned.*/
int strcmp(char str1[], char str2[])
{
    int i = 0;
    for (i = 0; str1[i] != '\0'; i++)
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }

    return 1;
}

/*Copy string
Copies the C string pointed by source into the array pointed by destination,
including the terminating null character (and stopping at that point).To avoid overflows, the size of the array pointed by destination shall be
long enough to contain the same C string as source (including the terminating null character),and should not overlap in memory with source.
destination is returned.
*/
char *strcpy(char dest[], char src[])
{
    int i = 0;
    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    return &dest[0];
}
