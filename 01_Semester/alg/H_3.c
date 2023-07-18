/*Schreiben Sie ein C-Programm, dass die Funktionen pow(), log(), exp() verwendet. Die
Zahlen können beliebig ausgewählt werden. Ausgabe erfolgt auf der Konsole (Terminal).
Research:
pow() = needs <math.h>   [Mathematics] x^y    = pow(x, y) [In C programming] "Quadrieren"
log() = needs <math.h>   [Mathematics] loge x = log(x)    [In C programming]
exp() = needs <math.h>   [Mathematics] e^x    = exp(x)    [In C programming]
*/

#include <stdio.h>
#include <math.h>

int main()
{
float Zahl_1=0;       
Zahl_1 = pow(2.5,3);  // 2.5 hoch 3 = 15,625    
printf("%f\n",Zahl_1);

float Zahl_2=0;      
Zahl_2= log(10);    // Ln von 10 = 2,302585093.....        
printf("%f\n",Zahl_2);

float Zahl_3=0;      
Zahl_3 = exp(2);    // e(Euler) hoch 2 = 7,389056099......       
printf("%f\n",Zahl_3);
return 0;
}