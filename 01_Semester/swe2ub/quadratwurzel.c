/*
/////////////////////////////////////////////////////////////////////////////////////////////
#Author:           #Semester:    #Programm:                #Name:                 #Date          
#Philipp Vidmar    #1/2020       #C                        #quadratwurzel.c       #22.11.2020                   
#README:                                                                     
#
Computer müssen zur Lösung mathematischer Ausdrücke numerische Verfahren anwenden,
mit welchen Lösungen näherungsweise berechnet werden.
Meistens gibt es eine Vielzahl von Algorithmen für ein einziges Problem, jeder mit
seinen eigenen Vor- und Nachteilen. Ein einfaches Verfahren zur Berechnung von
Quadratwurzeln ist das Heron-Verfahren:
Seien a > 0 und x0 > 0 reelle Zahlen. Die Folge (xn), n ∈ sei durch
xn+1 = ½ * (xn + a/xn)
rekursiv definiert (d.h. der folgende Wert basiert immer auf dem zuletzt
berechneten). Dann konvergiert die Folge (xn) gegen die Quadratwurzel von
a. Der Startwert für x0 kann prinzipiell beliebig festgelegt werden, da das
Verfahren immer konvergiert – eine gute Wahl ist 
x0 = a/2.
Nehmen Sie diesen Satz als Grundlage für eine Funktion
double hsqrt(double a, int n) die von einer positiven reellen Zahl a die Wurzel mit
der gewünschten Genauigkeit bis zur n-ten Dezimalstelle berechnet und ausgibt. Die
gewünschte Genauigkeit ε ist erreicht, wenn |xn- xn+1| < ε erfüllt ist.
Eine mögliche Ausgabe könnte so aussehen:
Bitte Zahl eingeben, deren Wurzel berechnet werden soll!
5
Bitte Anzahl der gültigen Stellen hinter dem Komma eingeben!
7
Die Wurzel von 5 ergibt 2.2360680.
xn+1 = ½ * (xn + a/xn) |xn- xn+1| < ε
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

double hsqrt(double number, int repetition);
double hsqrt_r(double number, int repetition);
void pstop();

int main()
{
    double number = 0;
    double result = 0;
    double result_r = 0;
    int comma = 0;
    int repetition = 0;
    printf("Bitte Zahl eingeben, deren Wurzel berechnet werden soll:\n");
    scanf("%lf", &number);
    fflush(stdin);
    printf("Bitte Anzahl der gueltigen Stellen hinter dem Komma eingeben:\n");
    scanf("%d", &comma);

    result = hsqrt(number, 10);
    printf("\nresult: %.*lf", comma, result);

    //result_r = hsqrt_r(number, 3);
    //printf("\nresult: %.2lf", result_r);
    // bis auf 3 Nachkommastelle genau machen
    pstop();
    return 0;
}

void pstop()
{
    printf("\n####################\n#|End|  push ENTER #\n####################");
    fflush(stdin);
    getchar();
}

double hsqrt(double number, int repetition)
{
    double result = 0;
    int i = 0;
    if (number <= 0 || repetition <= 0)
    {
        printf("# Attention\n# Number or repetition was 0 or smaler");
        return 0;
    }
    result = number / 2;

    for (i = 0; i < repetition; i++)
    {
        result = (result + (number / result)) / 2;
    }
    return result;
}

//Recrusion
double hsqrt_r(double number, int repetition)
{
    double result = 0;

    result = number / 2; // nur 1 mal!! main ? global Variable next step ++1

    if (number <= 0)
    {
        printf("\n# Attention\n# Number or repetition was 0 or smaller");
        return 0;
    }
    if (repetition > 0)
    {
        result = (result + (number / result)) / 2;
        printf("\n %lf  result", result);
        result = hsqrt_r(result, repetition - 1);
        printf("\nIF i != 0");
        return result;
    }
    else
    {
        printf("ELSE\n");
    }

    return result;
}
