#include <stdio.h>
// von Benedikt Benjamin Mandlmeir & Philipp Vidmar

float potenzieren(float basis, int potenz)
{
	int i; 
    float ret;
	ret=1;
	for(i=0;i<potenz;i++)
	{
		ret*=basis;
	}
	return ret;
}

int main()
{
        int i;
        int Eingabe = 0;
        float H_Zahl = 2, Max_Zahl = 100; // 
        float R_Wert = 0, Ergebnis = 0;   //
 
        R_Wert = Max_Zahl * potenzieren(0.5,H_Zahl); // R_Wert +- Ergebniss
        
        Ergebnis = Max_Zahl/2; // sollte 50sein
        printf("\n \tIst die gesuchte Zahl: %.0f\n\t\nGeben sie bitte fuer Groesser 1,Kleiner 0, Gleich 2 ein\n",Ergebnis);
     
        for(i=0;i<10;i++)
        {
            R_Wert = Max_Zahl * potenzieren(0.5,H_Zahl); // zb 1)=50 2)=25 3)=12,5 4)6,25
            printf("\n %d.)\tGeben Sie bitte eine Zahl ein : ",i); scanf("%d",&Eingabe);
            if(Eingabe==1) // GROESSER
            {
            Ergebnis=Ergebnis+R_Wert; 
            printf("\tIst die Zahl Groesser|Kleiner %.0f\n",Ergebnis);
            }
            if(Eingabe==0) // KLEINER
            {
            Ergebnis=Ergebnis-R_Wert; 
            printf("\tIst die Zahl Groesser|Kleiner %.0f\n",Ergebnis);
            }
            if(Eingabe==2)
            { // Ist die Gesuchte Zahl
            printf("Die gesuchte Zahl wurde nach %d.Durchlaufen gefunden\n!!!!!!!! ENDE :) !!!!!!!! ",i);
            return 0;
            }
            if(Eingabe>=3)
            {
            printf("\tERROR die Eingabe Stimmt nicht!!!");
            return 0;
            }
            H_Zahl++; // H_Zahl= H_Zahl + 1  
        }

        return 0;     
}