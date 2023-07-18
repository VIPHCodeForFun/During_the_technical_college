/*Schreiben Sie ein C-Programm, welches einen Anmelde-Server simuliert.
Es soll ein String als Vergleichs-Wert festgelegt werden und mit einem zweiten String, welcher vom
Benutzer eingegeben wird, überprüft werden. Von beiden Strings soll der Hashwert,
mit der bereitgestellten Funktion „calculateHash()" berechnet werden. Zur Überprüfung ob
das richtige Passwort eingegeben wurde, ist es ausreichend nur die beiden Hashwerte zu
vergleichen. Zusätzlich bergrenzt der Server die Anzahl der Login-Versuche auf max. 3
und fordert den Benutzer auf, sein Passwort so lange einzugeben, bis die maximale
Anzahl erreicht wurde.
Wird das Passwort innerhalb des Versuch-Maximums erreicht, beendet der Server den
Überprüfungs- Vorgang. Der gesamte Vorgang soll zeitlich protokolliert werden d.h. bei
einem erfolgreichen Login, die benötigte Zeit fürs Anmelden auf der Konsole (Terminal)
ausgeben.
unsigned long calculateHash(unsigned char *str)
{
unsigned long hash = 5381;
int c;
while (c = *str++)
hash = ((hash << 5) + hash) + c; /* hash * 33 + c 
return hash;
}
Linksshift <<                Verschiebt den Inhalt einer Variable bitweise nach links.
Bei einer ganzen nicht negativen Zahl entspricht eine Verschiebung einer Multiplikation mit 2n,
wobei n die Anzahl der Verschiebungen ist, wenn das höchstwertige Bit nicht links hinausgeschoben wird.
Das Ergebnis ist undefiniert, wenn der zu verschiebende Wert negativ ist.
*/
#include <stdio.h>
#include <string.h>

unsigned long calculateHash();
int einleitetext();

int main()
{

unsigned char Eingabe[100]= "" ;    //Wichtig string leer = " ";
unsigned char pw[]="PASSWORT";      //PASSWORT
unsigned long int iohash=0;
unsigned long int pwhash=0;     

einleitetext();
int i=1;
    do{
    printf("++ :");
    scanf("%s",&Eingabe);
    pwhash = calculateHash(pw); //printf("PWHASH ZAHL\t= %d\n",pwhash);
    iohash = calculateHash(Eingabe); //printf("IOHASH ZAHL\t= %d\n",iohash);

    if(pwhash==iohash)
{
    printf("+++++++++++++++++++++++++++++++\n");
    printf("+Gratulation du bist im Server+\n");
    printf("+++++++++++++++++++++++++++++++\n");
    system("pause"); // Pausiert das System
    return 0;
}
    else
{

printf("+  %d.) Fehlversuch !!!  ++\n",i);
printf("+++++++++++++++++++++++++++\n");
i++;
}
    }while (i<=3);
    printf("+++++++++++++++++++++++++++\n");
    printf("++!!!FALSCHES PASSWORT!!!++\n");
    printf("+++++++++++++++++++++++++++\n");
system("pause"); // Pausiert das System
return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
unsigned long calculateHash(unsigned char str[])
{
unsigned long int hash = 5381; // Fix zu wählender Wert
unsigned long  pw=0;
int c=0; // zählt die teile im string von xx bis 0
int i=0; //für die for

c = strlen(str);  //strlen() ermittelt die Länge eines Strings

for(i=0;i<strlen(str)+1;i++)
    {
    pw= pw +*(str+c);
    c--;
    }
   // printf("STRING ZAHL\t= %d\n",pw);

    hash = (((hash + pw) << 5) + hash) + pw; /* hash * 33 + c */
    
return (hash);
}
/////////////////////////////////////////////////////////////////////////////////////////////
int einleitetext()
{
printf("++++++SERVER+ANMELDUNG+++++\n");
printf("Gib Bitte dein Passwort ein\n");
printf("+++++++++++++++++++++++++++\n");

return 0;
}