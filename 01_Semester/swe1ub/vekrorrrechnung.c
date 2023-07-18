/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #vekrorrrechnung.c                   
#README:                                                                     
#a)vec_add() vec_sub()
#b)vec_mult()   Multiplizieren
#c)vec_dot()    Skalarprodukt
#d)vec_cross()  Kreuzprodukt
1   Strings einlesen maximal 1x10 Vektoren int vec_X [11]
2   String länge, fürs abarbeiten , bestimmen
3   die Informationen der Funktion geben
4   ergebniss ausgeben
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> // I O
#include <stdlib.h>
#include <string.h> // strlen

#define Vmax 3

int scanstring();
int printstring();
void vec_add();
void vec_sub();
void vec_mult();
int vec_dot();
void vec_cross();
void pstop();

int main()
{
    int vec_a[Vmax]; //Vektor A
    int vec_b[Vmax]; //Vektor B
    int vec_e[Vmax]; //Vektor Ergebniss
    int skal = 0;

    printf("Geben sie einen Vektor A ein\n");
    vec_a[Vmax] = scanstring(vec_a);
    printf("Geben sie einen Vektor B ein\n");
    vec_b[Vmax] = scanstring(vec_b);

    printf("\nVektor_A:");
    printstring(vec_a);
    printf("\nVektor_B:");
    printstring(vec_b);

    printf("\nVektor_A + Vektor_B =");
    vec_add(vec_a, vec_b, vec_e);
    printstring(vec_e);

    printf("\nVektor_A - Vektor_B =");
    vec_sub(vec_a, vec_b, vec_e);
    printstring(vec_e);

    printf("\nVektor_A * Skalar =\nGeben sie bitte einen Skalar ein: ");
    scanf("%d", &skal);
    vec_mult(vec_a, vec_e, skal);
    printstring(vec_e);

    printf("\nVektor_A * Vektor_B = <A,B> = ");
    skal = vec_dot(vec_a, vec_b);
    printf("\n%d", skal);

    printf("\nVektor_A x Vektor_B =");
    vec_cross(vec_a, vec_b, vec_e);
    printstring(vec_e);

    pstop();
    return 0;
}
void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}
// Strings einlesen
int scanstring(int str[])
{
    for (int i = 0; i < Vmax; i++)
    {
        scanf("%d", &str[i]);
    }
    return 0;
}
// String ausgeben
//int printstring (String_result)
int printstring(int str[])
{
    for (int i = 0; i < Vmax; i++)
    {
        printf("\n|%d|", str[i]);
    }
    return 0;
}
// Vektor + Vektor Addieren
//void vec_add (String_1,  String_2,  String_result)
void vec_add(int vec_a[], int vec_b[], int vec_e[])
{
    for (int i = 0; i < Vmax; i++)
    {
        vec_e[i] = vec_a[i] + vec_b[i];
    }
}
// Vektor - Vektor Subtrahieren
//void vec_sub (String_1,  String_2,  String_result)
void vec_sub(int vec_a[], int vec_b[], int vec_e[])
{
    for (int i = 0; i < Vmax; i++)
    {
        vec_e[i] = vec_a[i] - vec_b[i];
    }
}
// Vektor * Skalar=Vektor
//void vec_add(value_1,String_result,Skalar)
void vec_mult(int vec_a[], int vec_e[], int skal)
{
    for (int i = 0; i < Vmax; i++)
    {
        vec_e[i] = skal * vec_a[i];
    }
}
// Vektor * Vektor=Skalarprodukt
//void vec_add(value_1,value_2)
int vec_dot(int vec_a[], int vec_b[])
{
    int e = 0;
    for (int i = 0; i < Vmax; i++)
    {
        e = e + (vec_a[i] * vec_b[i]);
    }
    return e;
}
// Vektor Kreuzprodukt
// Leider habe ich keine lösung mit Schleifen gefunden......
void vec_cross(int vec_a[], int vec_b[], int vec_e[])
{
    vec_e[0] = (vec_a[1] * vec_b[2]) - (vec_a[2] * vec_b[1]);
    vec_e[1] = (vec_a[2] * vec_b[0]) - (vec_a[0] * vec_b[2]);
    vec_e[2] = (vec_a[0] * vec_b[1]) - (vec_a[1] * vec_b[0]);
    // Onli for 3 Dimm vektoren!
}