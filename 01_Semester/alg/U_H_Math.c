#include <stdio.h>
#include <math.h>

//U_H_Math.c

int main()
{
float Kante = 0;
double hypotenuse=0;

printf("Geben sie eine Kantenlaenge ein in mm ein");
scanf("%f",&Kante);

hypotenuse = Kante * sqrt(3); // sqrt(3) ist die Wurzel aus (3)

printf("Die hypotenuse ist %lf mm",hypotenuse); // %lf double;


return 0;        
}